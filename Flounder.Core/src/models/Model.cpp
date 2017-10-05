#include "Model.hpp"

#include <cassert>
#include "../devices/Display.hpp"
#include "../helpers/HelperFile.hpp"
#include "../helpers/HelperString.hpp"
#include "../renderer/Renderer.hpp"

namespace Flounder
{
	Model::Model(const std::string &file) :
		m_file(file),
		m_vertices(std::vector<Vertex>()),
		m_indices(std::vector<uint16_t>()),
		m_aabb(new Aabb()),
		m_vertexBuffer(nullptr),
		m_indexBuffer(nullptr)
	{
		LoadFromFile();
		m_vertexBuffer = new VertexBuffer(sizeof(m_vertices[0]), m_vertices.size(), m_vertices.data());
		m_indexBuffer = new IndexBuffer(VK_INDEX_TYPE_UINT16, sizeof(m_indices[0]), m_indices.size(), m_indices.data());
	}

	Model::Model(const std::vector<Vertex> &vertices, const std::vector<uint16_t> &indices) :
		m_file(""),
		m_vertices(std::vector<Vertex>(vertices)),
		m_indices(std::vector<uint16_t>(indices)),
		m_aabb(new Aabb()),
		m_vertexBuffer(new VertexBuffer(sizeof(m_vertices[0]), m_vertices.size(), m_vertices.data())),
		m_indexBuffer(new IndexBuffer(VK_INDEX_TYPE_UINT16, sizeof(m_indices[0]), m_indices.size(), m_indices.data()))
	{
	}

	Model::~Model()
	{
		delete m_indexBuffer;
		delete m_vertexBuffer;
		delete m_aabb;
	}

	void Model::LoadFromFile()
	{
		std::string fileLoaded = HelperFile::ReadTextFile(std::string(m_file));
		std::vector<std::string> lines = HelperString::Split(fileLoaded, "\n");

		std::vector<uint16_t> indices = std::vector<uint16_t>();
		std::vector<VertexData*> vertices = std::vector<VertexData*>();
		std::vector<Vector2> textures = std::vector<Vector2>();
		std::vector<Vector3> normals = std::vector<Vector3>();

		std::vector<std::string> splitFile = HelperString::Split(std::string(m_file), "/");
		std::string fileName = splitFile.at(splitFile.size() - 1);

		for (auto it = lines.begin(); it < lines.end(); ++it)
		{
			std::string line = HelperString::Trim(*it);

			std::vector<std::string> split = HelperString::Split(line, " ");

			if (!split.empty())
			{
				std::string prefix = split.at(0);

				if (prefix == "#")
				{
					continue;
				}
				else if (prefix == "v")
				{
					Vector3 vertex = Vector3(stof(split.at(1)), stof(split.at(2)), stof(split.at(3)));
					VertexData *newVertex = new VertexData(static_cast<int>(vertices.size()), vertex);
					vertices.push_back(newVertex);
				}
				else if (prefix == "vt")
				{
					Vector2 texture = Vector2(stof(split.at(1)), 1.0f - stof(split.at(2)));
					textures.push_back(texture);
				}
				else if (prefix == "vn")
				{
					Vector3 normal = Vector3(stof(split.at(1)), stof(split.at(2)), stof(split.at(3)));
					normals.push_back(normal);
				}
				else if (prefix == "f")
				{
					// The split length of 3 faced + 1 for the f prefix.
					if (split.size() != 4 || HelperString::Contains(line, "//"))
					{
						printf("Error reading the OBJ '%s', it does not appear to be UV mapped! The model will not be loaded.\n", m_file.c_str());
						assert(false);
					}

					std::vector<std::string> vertex1 = HelperString::Split(split.at(1), "/");
					std::vector<std::string> vertex2 = HelperString::Split(split.at(2), "/");
					std::vector<std::string> vertex3 = HelperString::Split(split.at(3), "/");

					VertexData *v0 = ProcessDataVertex(Vector3(stof(vertex1.at(0)), stof(vertex1.at(1)), stof(vertex1.at(2))), &vertices, &indices);
					VertexData *v1 = ProcessDataVertex(Vector3(stof(vertex2.at(0)), stof(vertex2.at(1)), stof(vertex2.at(2))), &vertices, &indices);
					VertexData *v2 = ProcessDataVertex(Vector3(stof(vertex3.at(0)), stof(vertex3.at(1)), stof(vertex3.at(2))), &vertices, &indices);
					CalculateTangents(v0, v1, v2, &textures);
				}
				else if (prefix == "o")
				{
				}
				else if (prefix == "s")
				{
					// Smooth faces?
				}
				else
				{
					printf("OBJ '%s' ", m_file.c_str());
					printf("unknown line: '%s'.\n", line.c_str());
				}
			}
		}

		// Averages out vertex tangents, and disabled non set vertices,
		for (auto current : vertices)
		{
			current->AverageTangents();

			if (!current->IsSet())
			{
				current->SetTextureIndex(0);
				current->SetNormalIndex(0);
			}
		}

		m_indices.swap(indices);

		// Turns the loaded OBJ data into a formal that can be used by OpenGL.
		for (auto current : vertices)
		{
			const Vector3 position = current->GetPosition();
			const Vector2 textureCoord = textures.at(current->GetTextureIndex());
			const Vector3 normal = normals.at(current->GetNormalIndex());
			const Vector3 tangent = current->GetAverageTangent();

			Vertex vertex = Vertex();
			vertex.position.Set(position);
			vertex.textures.Set(textureCoord);
			vertex.normal.Set(normal);
			vertex.tangent.Set(tangent);

			m_vertices.push_back(vertex);

			delete current;
		}
	}

	VertexData *Model::ProcessDataVertex(Vector3 vertex, std::vector<VertexData*> *vertices, std::vector<uint16_t> *indices)
	{
		int index = static_cast<int>(vertex.m_x) - 1;
		VertexData *currentVertex = vertices->at(index);
		int textureIndex = static_cast<int>(vertex.m_y) - 1;
		int normalIndex = static_cast<int>(vertex.m_z) - 1;

		if (!currentVertex->IsSet())
		{
			currentVertex->SetTextureIndex(textureIndex);
			currentVertex->SetNormalIndex(normalIndex);
			indices->push_back(index);
			return currentVertex;
		}

		return DealWithAlreadyProcessedDataVertex(currentVertex, textureIndex, normalIndex, indices, vertices);
	}

	VertexData *Model::DealWithAlreadyProcessedDataVertex(VertexData *previousVertex, const int &newTextureIndex, const int &newNormalIndex, std::vector<uint16_t> *indices, std::vector<VertexData*> *vertices)
	{
		if (previousVertex->HasSameTextureAndNormal(newTextureIndex, newNormalIndex))
		{
			indices->push_back(previousVertex->GetIndex());
			return previousVertex;
		}

		VertexData *anotherVertex = previousVertex->GetDuplicateVertex();

		if (anotherVertex != nullptr)
		{
			return DealWithAlreadyProcessedDataVertex(anotherVertex, newTextureIndex, newNormalIndex, indices, vertices);
		}

		VertexData *duplicateVertex = new VertexData((int) vertices->size(), previousVertex->GetPosition());
		duplicateVertex->SetTextureIndex(newTextureIndex);
		duplicateVertex->SetNormalIndex(newNormalIndex);
		previousVertex->SetDuplicateVertex(duplicateVertex);
		vertices->push_back(duplicateVertex);
		indices->push_back(duplicateVertex->GetIndex());
		return duplicateVertex;
	}

	void Model::CalculateTangents(VertexData *v0, VertexData *v1, VertexData *v2, std::vector<Vector2> *textures)
	{
		Vector3 *deltaPos1 = Vector3::Subtract(v1->GetPosition(), v0->GetPosition(), nullptr);
		Vector3 *deltaPos2 = Vector3::Subtract(v2->GetPosition(), v0->GetPosition(), nullptr);
		Vector2 uv0 = textures->at(v0->GetTextureIndex());
		Vector2 uv1 = textures->at(v1->GetTextureIndex());
		Vector2 uv2 = textures->at(v2->GetTextureIndex());
		Vector2 *deltaUv1 = Vector2::Subtract(uv1, uv0, nullptr);
		Vector2 *deltaUv2 = Vector2::Subtract(uv2, uv0, nullptr);

		float r = 1.0f / (deltaUv1->m_x * deltaUv2->m_y - deltaUv1->m_y * deltaUv2->m_x);
		deltaPos1->Scale(deltaUv2->m_y);
		deltaPos2->Scale(deltaUv1->m_y);

		Vector3 *tangent = Vector3::Subtract(*deltaPos1, *deltaPos2, nullptr);
		tangent->Scale(r);
		v0->AddTangent(tangent);
		v1->AddTangent(tangent);
		v2->AddTangent(tangent);

		delete deltaPos1;
		delete deltaPos2;
		delete deltaUv1;
		delete deltaUv2;
	}

	void Model::CreateAabb()
	{
		float minX = +INFINITY;
		float minY = +INFINITY;
		float minZ = +INFINITY;
		float maxX = -INFINITY;
		float maxY = -INFINITY;
		float maxZ = -INFINITY;

		if (m_vertices.size() > 1)
		{
			for (int i = 0; i < m_vertices.size(); i += 3)
			{
				const Vector3 position = m_vertices.at(i).position;

				if (position.m_x < minX)
				{
					minX = position.m_x;
				}
				else if (position.m_x > maxX)
				{
					maxX = position.m_x;
				}

				if (position.m_y < minY)
				{
					minY = position.m_y;
				}
				else if (position.m_y > maxY)
				{
					maxY = position.m_y;
				}

				if (position.m_z < minZ)
				{
					minZ = position.m_z;
				}
				else if (position.m_z > maxZ)
				{
					maxZ = position.m_z;
				}
			}
		}

		//m_aabb->extentsMin->set(minX, minY, minZ);
		//m_aabb->extentsMax->set(maxX, maxY, maxZ);
	}
}
