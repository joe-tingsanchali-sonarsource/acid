set(FLOUNDERENGINE_HEADERS_
        "Devices/Audio.hpp"
        "Devices/Display.hpp"
        "Devices/Joysticks.hpp"
        "Devices/Keyboard.hpp"
        "Devices/Mouse.hpp"
        "Engine/Engine.hpp"
        "Engine/IModule.hpp"
        "Engine/IUpdater.hpp"
        "Engine/ModuleUpdater.hpp"
        "Engine/Platform.hpp"
        "Entities/EntityRender.hpp"
        "Entities/RendererEntities.hpp"
        "Entities/UbosEntities.hpp"
        "Events/EventChange.hpp"
        "Events/Events.hpp"
        "Events/EventStandard.hpp"
        "Events/EventTime.hpp"
        "Events/IEvent.hpp"
        "Files/Config.hpp"
        "Files/ConfigKey.hpp"
        "Files/Csv/FileCsv.hpp"
        "Files/IFile.hpp"
        "Files/Xml/FileXml.hpp"
        "Files/Xml/XmlNode.hpp"
        "Flounder.hpp"
        "Fonts/Character.hpp"
        "Fonts/FontFamily.hpp"
        "Fonts/FontType.hpp"
        "Fonts/Justify.hpp"
        "Fonts/Line.hpp"
        "Fonts/Metafile.hpp"
        "Fonts/RendererFonts.hpp"
        "Fonts/Text.hpp"
        "Fonts/UbosFonts.hpp"
        "Fonts/Word.hpp"
        "Guis/Gui.hpp"
        "Guis/RendererGuis.hpp"
        "Guis/UbosGuis.hpp"
        "Helpers/FileSystem.hpp"
        "Helpers/FormatString.hpp"
        "Helpers/SquareArray.hpp"
        "Inputs/AxisButton.hpp"
        "Inputs/AxisCompound.hpp"
        "Inputs/AxisJoystick.hpp"
        "Inputs/ButtonCompound.hpp"
        "Inputs/ButtonJoystick.hpp"
        "Inputs/ButtonKeyboard.hpp"
        "Inputs/ButtonMouse.hpp"
        "Inputs/IAxis.hpp"
        "Inputs/IButton.hpp"
        "Lights/Fog.hpp"
        "Lights/Light.hpp"
        "Materials/Material.hpp"
        "Maths/Colour.hpp"
        "Maths/Constraint3.hpp"
        "Maths/Delta.hpp"
        "Maths/Interpolation/SmoothFloat.hpp"
        "Maths/Maths.hpp"
        "Maths/Matrix2.hpp"
        "Maths/Matrix3.hpp"
        "Maths/Matrix4.hpp"
        "Maths/Quaternion.hpp"
        "Maths/Timer.hpp"
        "Maths/Transform.hpp"
        "Maths/Vector2.hpp"
        "Maths/Vector3.hpp"
        "Maths/Vector4.hpp"
        "Maths/Visual/DriverBounce.hpp"
        "Maths/Visual/DriverConstant.hpp"
        "Maths/Visual/DriverFade.hpp"
        "Maths/Visual/DriverLinear.hpp"
        "Maths/Visual/DriverSinwave.hpp"
        "Maths/Visual/DriverSlide.hpp"
        "Maths/Visual/IDriver.hpp"
        "Meshes/Mesh.hpp"
        "Models/Model.hpp"
        "Models/Shapes/MeshPattern.hpp"
        "Models/Shapes/MeshSimple.hpp"
        "Models/Shapes/ShapeCube.hpp"
        "Models/Shapes/ShapeRectangle.hpp"
        "Models/Shapes/ShapeSphere.hpp"
        "Models/Vertex.hpp"
        "Models/VertexData.hpp"
        "Maths/Noise/NoiseFast.hpp"
        "Objects/Behaviour.hpp"
        "Objects/Component.hpp"
        "Objects/ComponentRegister.hpp"
        "Objects/GameObject.hpp"
        "Objects/Prefabs/PrefabComponent.hpp"
        "Objects/Prefabs/PrefabObject.hpp"
        "Particles/Particle.hpp"
        "Particles/Particles.hpp"
        "Particles/ParticleSystem.hpp"
        "Particles/ParticleType.hpp"
        "Particles/RendererParticles.hpp"
        "Particles/Spawns/ISpawnParticle.hpp"
        "Particles/Spawns/SpawnCircle.hpp"
        "Particles/Spawns/SpawnLine.hpp"
        "Particles/Spawns/SpawnPoint.hpp"
        "Particles/Spawns/SpawnSphere.hpp"
        "Physics/Aabb.hpp"
        "Physics/Collider.hpp"
        "Physics/Frustum.hpp"
        "Physics/Intersect.hpp"
        "Physics/Ray.hpp"
        "Physics/Rigidbody.hpp"
        "Physics/Space/ISpatialStructure.hpp"
        "Physics/Space/StructureBasic.hpp"
        "Physics/Sphere.hpp"
        "Post/Deferred/RendererDeferred.hpp"
        "Post/Deferred/UbosDeferred.hpp"
        "Post/Filters/FilterCrt.hpp"
        "Post/Filters/FilterDarken.hpp"
        "Post/Filters/FilterDefault.hpp"
        "Post/Filters/FilterEmboss.hpp"
        "Post/Filters/FilterFxaa.hpp"
        "Post/Filters/FilterGrain.hpp"
        "Post/Filters/FilterGrey.hpp"
        "Post/Filters/FilterLensflare.hpp"
        "Post/Filters/FilterNegative.hpp"
        "Post/Filters/FilterPixel.hpp"
        "Post/Filters/FilterSepia.hpp"
        "Post/Filters/FilterTiltshift.hpp"
        "Post/Filters/FilterTone.hpp"
        "Post/Filters/FilterWobble.hpp"
        "Post/IPostFilter.hpp"
        "Post/IPostPipeline.hpp"
        "Prerequisites.hpp"
        "Renderer/Buffers/Buffer.hpp"
        "Renderer/Buffers/IndexBuffer.hpp"
        "Renderer/Buffers/UniformBuffer.hpp"
        "Renderer/Buffers/VertexBuffer.hpp"
        "Renderer/IManagerRender.hpp"
        "Renderer/IRenderer.hpp"
        "Renderer/Pass/RenderPass.hpp"
        "Renderer/Pipelines/Pipeline.hpp"
        "Renderer/Pipelines/PipelineCreate.hpp"
        "Renderer/Queue/QueueFamily.hpp"
        "Renderer/Renderer.hpp"
        "Renderer/Screenshot/Screenshot.hpp"
        "Renderer/Stencils/DepthStencil.hpp"
        "Renderer/Swapchain/Framebuffers.hpp"
        "Renderer/Swapchain/Swapchain.hpp"
        "Resources/IResource.hpp"
        "Resources/Resources.hpp"
        "Scenes/ICamera.hpp"
        "Scenes/IManagerUis.hpp"
        "Scenes/Scene.hpp"
        "Scenes/Scenes.hpp"
        "Shadows/RendererShadows.hpp"
        "Shadows/ShadowBox.hpp"
        "Shadows/Shadows.hpp"
        "Shadows/UbosShadows.hpp"
        "Skyboxes/CelestialBody.hpp"
        "Skyboxes/RendererSkyboxes.hpp"
        "Skyboxes/Skyboxes.hpp"
        "Skyboxes/SkyboxRender.hpp"
        "Skyboxes/UbosSkyboxes.hpp"
        "Sounds/Sound.hpp"
        "Sounds/SoundBuffer.hpp"
        "Tasks/Tasks.hpp"
        "Terrains/LodBehaviour.hpp"
        "Terrains/MeshTerrain.hpp"
        "Terrains/RendererTerrains.hpp"
        "Terrains/TerrainRender.hpp"
        "Terrains/Terrains.hpp"
        "Terrains/UbosTerrains.hpp"
        "Textures/Cubemap.hpp"
        "Textures/Texture.hpp"
        "Uis/InputButton.hpp"
        "Uis/InputDelay.hpp"
        "Uis/InputGrabber.hpp"
        "Uis/InputSlider.hpp"
        "Uis/InputText.hpp"
        "Uis/UiBound.hpp"
        "Uis/UiObject.hpp"
        "Uis/Uis.hpp"
        "Uis/UiSelector.hpp"
        "Uis/UiStartLogo.hpp"
        "Waters/MeshWater.hpp"
        "Waters/RendererWaters.hpp"
        "Waters/UbosWaters.hpp"
        "Waters/WaterRender.hpp"
        "Waters/Waters.hpp"
        "Worlds/Worlds.hpp"
)

set(FLOUNDERENGINE_SOURCES_
        "Devices/Audio.cpp"
        "Devices/Display.cpp"
        "Devices/Joysticks.cpp"
        "Devices/Keyboard.cpp"
        "Devices/Mouse.cpp"
        "Engine/Engine.cpp"
        "Engine/ModuleUpdater.cpp"
        "Engine/Platform.cpp"
        "Entities/EntityRender.cpp"
        "Entities/RendererEntities.cpp"
        "Events/EventChange.cpp"
        "Events/Events.cpp"
        "Events/EventStandard.cpp"
        "Events/EventTime.cpp"
        "Files/Config.cpp"
        "Files/ConfigKey.cpp"
        "Files/Csv/FileCsv.cpp"
        "Files/Xml/FileXml.cpp"
        "Files/Xml/XmlNode.cpp"
        "Fonts/Character.cpp"
        "Fonts/FontFamily.cpp"
        "Fonts/FontType.cpp"
        "Fonts/Line.cpp"
        "Fonts/Metafile.cpp"
        "Fonts/RendererFonts.cpp"
        "Fonts/Text.cpp"
        "Fonts/Word.cpp"
        "Guis/Gui.cpp"
        "Guis/RendererGuis.cpp"
        "Helpers/FileSystem.cpp"
        "Helpers/FormatString.cpp"
        "Helpers/SquareArray.cpp"
        "Inputs/AxisButton.cpp"
        "Inputs/AxisCompound.cpp"
        "Inputs/AxisJoystick.cpp"
        "Inputs/ButtonCompound.cpp"
        "Inputs/ButtonJoystick.cpp"
        "Inputs/ButtonKeyboard.cpp"
        "Inputs/ButtonMouse.cpp"
        "Lights/Fog.cpp"
        "Lights/Light.cpp"
        "Materials/Material.cpp"
        "Maths/Colour.cpp"
        "Maths/Constraint3.cpp"
        "Maths/Delta.cpp"
        "Maths/Interpolation/SmoothFloat.cpp"
        "Maths/Matrix2.cpp"
        "Maths/Matrix3.cpp"
        "Maths/Matrix4.cpp"
        "Maths/Quaternion.cpp"
        "Maths/Timer.cpp"
        "Maths/Transform.cpp"
        "Maths/Vector2.cpp"
        "Maths/Vector3.cpp"
        "Maths/Vector4.cpp"
        "Maths/Visual/DriverBounce.cpp"
        "Maths/Visual/DriverConstant.cpp"
        "Maths/Visual/DriverFade.cpp"
        "Maths/Visual/DriverLinear.cpp"
        "Maths/Visual/DriverSinwave.cpp"
        "Maths/Visual/DriverSlide.cpp"
        "Meshes/Mesh.cpp"
        "Models/Model.cpp"
        "Models/Shapes/MeshPattern.cpp"
        "Models/Shapes/MeshSimple.cpp"
        "Models/Shapes/ShapeCube.cpp"
        "Models/Shapes/ShapeRectangle.cpp"
        "Models/Shapes/ShapeSphere.cpp"
        "Models/Vertex.cpp"
        "Models/VertexData.cpp"
        "Maths/Noise/NoiseFast.cpp"
        "Objects/Behaviour.cpp"
        "Objects/Component.cpp"
        "Objects/ComponentRegister.cpp"
        "Objects/GameObject.cpp"
        "Objects/Prefabs/PrefabComponent.cpp"
        "Objects/Prefabs/PrefabObject.cpp"
        "Particles/Particle.cpp"
        "Particles/Particles.cpp"
        "Particles/ParticleSystem.cpp"
        "Particles/ParticleType.cpp"
        "Particles/RendererParticles.cpp"
        "Particles/Spawns/SpawnCircle.cpp"
        "Particles/Spawns/SpawnLine.cpp"
        "Particles/Spawns/SpawnPoint.cpp"
        "Particles/Spawns/SpawnSphere.cpp"
        "Physics/Aabb.cpp"
        "Physics/Collider.cpp"
        "Physics/Frustum.cpp"
        "Physics/Ray.cpp"
        "Physics/Rigidbody.cpp"
        "Physics/Space/StructureBasic.cpp"
        "Physics/Sphere.cpp"
        "Post/Deferred/RendererDeferred.cpp"
        "Post/Filters/FilterCrt.cpp"
        "Post/Filters/FilterDarken.cpp"
        "Post/Filters/FilterDefault.cpp"
        "Post/Filters/FilterEmboss.cpp"
        "Post/Filters/FilterFxaa.cpp"
        "Post/Filters/FilterGrain.cpp"
        "Post/Filters/FilterGrey.cpp"
        "Post/Filters/FilterLensflare.cpp"
        "Post/Filters/FilterNegative.cpp"
        "Post/Filters/FilterPixel.cpp"
        "Post/Filters/FilterSepia.cpp"
        "Post/Filters/FilterTiltshift.cpp"
        "Post/Filters/FilterTone.cpp"
        "Post/Filters/FilterWobble.cpp"
        "Post/IPostFilter.cpp"
        "Post/IPostPipeline.cpp"
        "Renderer/Buffers/Buffer.cpp"
        "Renderer/Buffers/IndexBuffer.cpp"
        "Renderer/Buffers/UniformBuffer.cpp"
        "Renderer/Buffers/VertexBuffer.cpp"
        "Renderer/Pass/RenderPass.cpp"
        "Renderer/Pipelines/Pipeline.cpp"
        "Renderer/Queue/QueueFamily.cpp"
        "Renderer/Renderer.cpp"
        "Renderer/Screenshot/Screenshot.cpp"
        "Renderer/Stencils/DepthStencil.cpp"
        "Renderer/Swapchain/Framebuffers.cpp"
        "Renderer/Swapchain/Swapchain.cpp"
        "Resources/Resources.cpp"
        "Scenes/Scene.cpp"
        "Scenes/Scenes.cpp"
        "Shadows/RendererShadows.cpp"
        "Shadows/ShadowBox.cpp"
        "Shadows/Shadows.cpp"
        "Skyboxes/CelestialBody.cpp"
        "Skyboxes/RendererSkyboxes.cpp"
        "Skyboxes/Skyboxes.cpp"
        "Skyboxes/SkyboxRender.cpp"
        "Sounds/Sound.cpp"
        "Sounds/SoundBuffer.cpp"
        "Tasks/Tasks.cpp"
        "Terrains/LodBehaviour.cpp"
        "Terrains/MeshTerrain.cpp"
        "Terrains/RendererTerrains.cpp"
        "Terrains/TerrainRender.cpp"
        "Terrains/Terrains.cpp"
        "Textures/Cubemap.cpp"
        "Textures/Texture.cpp"
        "Uis/InputButton.cpp"
        "Uis/InputDelay.cpp"
        "Uis/InputGrabber.cpp"
        "Uis/InputSlider.cpp"
        "Uis/InputText.cpp"
        "Uis/UiBound.cpp"
        "Uis/UiObject.cpp"
        "Uis/Uis.cpp"
        "Uis/UiSelector.cpp"
        "Uis/UiStartLogo.cpp"
        "Waters/MeshWater.cpp"
        "Waters/RendererWaters.cpp"
        "Waters/WaterRender.cpp"
        "Waters/Waters.cpp"
        "Worlds/Worlds.cpp"
)

source_group("Header Files" FILES ${FLOUNDERENGINE_HEADERS_})
source_group("Source Files" FILES ${FLOUNDERENGINE_SOURCES_})

set(FLOUNDERENGINE_SOURCES
        ${FLOUNDERENGINE_HEADERS_}
        ${FLOUNDERENGINE_SOURCES_}
)
