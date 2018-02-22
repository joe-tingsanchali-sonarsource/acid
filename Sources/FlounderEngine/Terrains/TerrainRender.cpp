﻿#include "TerrainRender.hpp"

#include "../Devices/Display.hpp"
#include "../Meshes/Mesh.hpp"
#include "UbosTerrains.hpp"

namespace Flounder
{
	const int TerrainRender::SIDE_LENGTH = 100;
	const std::vector<float> TerrainRender::SQUARE_SIZES = {
		2.0f, 4.0f, 10.0f, 25.0f
	};
	const std::vector<float> TerrainRender::TEXTURE_SCALES = {
		10.0f, 5.0f, 2.0f, 1.0f
	};

	TerrainRender::TerrainRender() :
		Component(),
		m_uniformObject(new UniformBuffer(sizeof(UbosTerrains::UboObject)))
	{
	}

	TerrainRender::~TerrainRender()
	{
	}

	void TerrainRender::Update()
	{
	}

	void TerrainRender::CmdRender(const VkCommandBuffer &commandBuffer, const Pipeline &pipeline, const UniformBuffer &uniformScene)
	{
		const auto logicalDevice = Display::Get()->GetLogicalDevice();
		const auto descriptorSet = pipeline.GetDescriptorSet();

		// Gets required components.
		auto mesh = m_gameObject->GetComponent<Mesh>();

		if (mesh == nullptr || mesh->GetModel() == nullptr)
		{
			return;
		}

		// Creates a UBO object and write descriptor.
		UbosTerrains::UboObject uboObject = {};
		m_gameObject->GetTransform()->GetWorldMatrix(&uboObject.transform);
		m_uniformObject->Update(&uboObject);

		std::vector<VkWriteDescriptorSet> descriptorWrites = std::vector<VkWriteDescriptorSet>{
			uniformScene.GetWriteDescriptor(0, descriptorSet),
			m_uniformObject->GetWriteDescriptor(1, descriptorSet)
		};
		vkUpdateDescriptorSets(logicalDevice, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);

		// Draws the object.
		VkDescriptorSet descriptors[] = {descriptorSet};
		vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.GetPipelineLayout(), 0, 1, descriptors, 0, nullptr);

		mesh->GetModel()->CmdRender(commandBuffer);
	}
}
