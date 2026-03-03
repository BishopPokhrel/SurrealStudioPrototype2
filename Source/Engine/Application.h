#pragma once

#include <SurrealEditor/SurrealStudioMainWindow.h>
#include <Engine/ECS/Object.h>
#include <Engine/ECS/Component.h>
#include <Engine/SurrealRenderer/Renderer.h>
#include <Engine/SurrealRenderer/Shader.h>

#include "ExampleCube.h"

#include <memory>

namespace SurrealStudio {

	class Application
	{
	public:
		Application() = default;
		bool EngineInit();
		bool EngineRun(int argc, char** argv);
		bool EngineShutdown();

		void InitTestScene();

		static std::unique_ptr<Application> CreateApplication();
		SurrealEditor::SurrealStudioMainWindow m_Window;
		ECS::ObjectManager m_ObjectManager;
		ECS::TransformComponentManager m_TransformManager;
		SurrealRenderer::Renderer m_Renderer;
		SurrealRenderer::Shader m_Shader;

		ExampleCube exampleCube;
	};
}