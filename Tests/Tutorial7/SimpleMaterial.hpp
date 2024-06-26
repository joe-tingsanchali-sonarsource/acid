#pragma once

#include "Materials/Material.hpp"

using namespace acid;

/*
 * To simplify things, this will be a material that has just a diffuse texture and no lighting
 */
class SimpleMaterial : public Material {
public:
	explicit SimpleMaterial(Pipeline::Stage stage, std::shared_ptr<Image2d> image) :
		stage(std::move(stage)), imageMaterial(std::move(image)) {
	}

	/*
	 * CreatePipeline is called by the Mesh rendering Subrenderer when it needs to create a pipeline
	 * to render the material, we are provided the vertexInput by the mesh, but it seems
	 * at this point the format is hard coded and cant be overridden
	 * In our case we dont want normals, but we are stuck with them since Acid forces it.
	 * So we have inNormal in our shader even though we dont use it.
	 */
	void CreatePipeline(const Shader::VertexInput &vertexInput, bool animated) override {
		pipelineMaterial = MaterialPipeline::Create(stage, {
			{"Tutorial/Shaders/tri7.vert", "Tutorial/Shaders/tri7.frag"},
			{vertexInput}//, {}, PipelineGraphics::Mode::Polygon
		});
	}

	/*
	 * This is the sampler for our frag shader, not that the name matches
	 * The renderer calls this to push the descriptors we want
	 */
	void PushDescriptors(DescriptorsHandler &descriptorSet) override {
		descriptorSet.Push("texSampler", imageMaterial);
	}

	/*
	 * The Subrenderer for Meshes calls this to get us to add our transform to the UniformObject uniform
	 * This will have to match the name in the vert shader
	 * It will be the transform of the mesh
	 */
	void PushUniforms(UniformHandler &uniformObject, const Transform *transform) override {
		/*
		 * If the Mesh has no Transform component, it will be null
		 */
		if (transform) {
			uniformObject.Push("transform", transform->GetWorldMatrix());
		}
	}

	Pipeline::Stage stage;
	std::shared_ptr<Image2d> imageMaterial;
};
