#include "SurrealStudioMainWindow.h"
#include <Engine/Logging.h>

#define GLFW_INCLUDE_NONE

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <Engine/Application.h>

namespace SurrealStudio {

	namespace SurrealEditor {

		bool SurrealStudioMainWindow::InitWindow()
		{
			if (!glfwInit())
			{
				glfwTerminate();
				SS_ERROR("GLFW failed to initialize.");
				return false;
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			return true;
		}

		bool SurrealStudioMainWindow::CreateWindow(int width, int height, const char* title)
		{
			m_SurrealStudioWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
			if (!m_SurrealStudioWindow)
			{
				SS_ERROR("Failed to create GLFW window.\n");
				glfwTerminate();
				return false;
			}

			glfwMakeContextCurrent(m_SurrealStudioWindow);
			glfwSwapInterval(1); // Enable VSync

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				SS_ERROR("Failed to initialize GLAD.\n");
				glfwTerminate();
				return false;
			}

			// ----- ImGui Setup -----
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;

			ImGui::StyleColorsDark();

			ImGui_ImplGlfw_InitForOpenGL(m_SurrealStudioWindow, true);
			ImGui_ImplOpenGL3_Init("#version 330 core");

			return true;
		}

		bool SurrealStudioMainWindow::MainLoop()
		{
			// Optional: cache projection & view matrices
			glm::mat4 projection = glm::perspective(glm::radians(45.0f),
				1280.0f / 720.0f,
				0.1f, 100.0f);
			glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3));

			while (!glfwWindowShouldClose(m_SurrealStudioWindow))
			{
				glfwPollEvents();

				// ----- Start ImGui Frame -----
				ImGui_ImplOpenGL3_NewFrame();
				ImGui_ImplGlfw_NewFrame();
				ImGui::NewFrame();

				// ----- Example ImGui Window -----
				/*ImGui::Begin("Surreal Studio Editor");
				ImGui::Text("Hello, Surreal Studio!");
				ImGui::End();*/ 

				// ----- Clear frame -----
				glViewport(0, 0, 1280, 720);
				glClearColor(0.05f, 0.05f, 0.08f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glEnable(GL_DEPTH_TEST);

				// ----- Render Cube (or all objects) -----
				if (m_Application) // make sure pointer to your Application exists
				{
					// Bind cube shader
					m_Application->m_Shader.Bind();

					// Update camera & projection
					m_Application->m_Shader.SetMat4("view", view);
					m_Application->m_Shader.SetMat4("projection", projection);

					// Render all ECS objects (cube)
					m_Application->m_Renderer.RenderAllObjects(
						m_Application->m_ObjectManager,
						m_Application->m_TransformManager
					);

					m_Application->m_Shader.Unbind();
				}

				// ----- Render ImGui on top -----
				ImGui::Render();
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

				glfwSwapBuffers(m_SurrealStudioWindow);
			}

			return true;
		}
		bool SurrealStudioMainWindow::DestroyWindow()
		{
			// ----- Cleanup ImGui -----
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();

			if (m_SurrealStudioWindow)
			{
				glfwDestroyWindow(m_SurrealStudioWindow);
				glfwTerminate();
			}
			return true;
		}
	}
}
