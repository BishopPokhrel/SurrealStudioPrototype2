#pragma once

#include <SurrealEditor/SurrealStudioMainWindow.h>
#include <Engine/ECS/Object.h>
#include <Engine/ECS/Component.h>
#include <Engine/SurrealRenderer/Renderer.h>
#include <Engine/SurrealRenderer/Shader.h>

#include "ExampleCube.h"

namespace SurrealStudio {

	class Application
	{
	public:

		bool EngineInit();
		bool EngineRun(int argc, char** argv);
		bool EngineShutdown();

		void InitTestScene();

		static Application* CreateApplication();
		SurrealEditor::SurrealStudioMainWindow m_Window;
		ECS::ObjectManager m_ObjectManager;
		ECS::TransformComponentManager m_TransformManager;
		SurrealRenderer::Renderer m_Renderer;
		SurrealRenderer::Shader m_Shader;

		ExampleCube exampleCube;

	};
}