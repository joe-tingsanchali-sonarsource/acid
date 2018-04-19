#include "MeshRender.hpp"

namespace Flounder
{
	MeshRender::MeshRender() :
		Component(),
		m_descriptorSet(new DescriptorsHandler()),
		m_uniformObject(new UniformHandler())
	{
	}

	MeshRender::~MeshRender()
	{
		delete m_descriptorSet;
		delete m_uniformObject;
	}

	void MeshRender::Update()
	{
		auto material = GetGameObject()->GetComponent<IMaterial>();

		if (material == nullptr)
		{
			return;
		}

		// Updates uniforms.
		material->PushUniforms(m_uniformObject);
	}

	void MeshRender::CmdRender(const VkCommandBuffer &commandBuffer, UniformHandler *uniformScene)
	{
		// Checks if the mesh is in view.
		/*auto rigidbody = GetGameObject()->GetComponent<Rigidbody>();

		if (rigidbody != nullptr && rigidbody->GetCollider() != nullptr)
		{
			if (!rigidbody->GetCollider()->InFrustum(*Scenes::Get()->GetCamera()->GetViewFrustum()))
			{
				return;
			}
		}*/

		// Gets required components.
		auto material = GetGameObject()->GetComponent<IMaterial>();
		auto mesh = GetGameObject()->GetComponent<Mesh>();

		if (material == nullptr || mesh == nullptr)
		{
			return;
		}

		// Updates descriptors.
		m_descriptorSet->Push("UboScene", uniformScene);
		m_descriptorSet->Push("UboObject", m_uniformObject);
		material->PushDescriptors(m_descriptorSet);
		bool descriptorsSet = m_descriptorSet->Update(*material->GetMaterial()->GetPipeline());

		if (!descriptorsSet)
		{
			return;
		}

		// Draws the object.
		material->GetMaterial()->CmdRender(commandBuffer, mesh->GetModel(), m_descriptorSet->GetDescriptorSet());
	}

	void MeshRender::Load(LoadedValue *value)
	{
	}

	void MeshRender::Write(LoadedValue *value)
	{
	}
}