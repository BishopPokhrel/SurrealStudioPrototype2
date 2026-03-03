#include "Application.h"
#include "Logging.h"

#include <SurrealEditor/SurrealStudioMainWindow.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ExampleCube.h"

namespace SurrealStudio {

    bool Application::EngineInit()
    {
        SS_INFO("Engine is starting!");
        return true;
    }

    bool Application::EngineRun(int argc, char** argv)
    {
        m_Window.InitWindow();
        m_Window.CreateWindow(800, 600, "Surreal Studio");
        m_Window.SetApplication(this);
        
        //InitTestScene();

        m_Window.MainLoop();
        SS_INFO("Engine is running!");
        return true;
    }

    void Application::InitTestScene()
    {
        // -----------------------------
        //  Create the cube object
        // -----------------------------
        bool success = m_ObjectManager.CreateObject("Cube");
        if (!success)
        {
            SS_ERROR("Failed to create cube object!");
            return;
        }

        // Get the last created object
        int index = m_ObjectManager.GetObjectCount() - 1;
        auto* cube = m_ObjectManager.GetObjectPtr(index);
        if (!cube)
        {
            SS_ERROR("Failed to retrieve cube object!");
            return;
        }

        // Assign mesh using static helper
        cube->mesh = ExampleCube::CreateExampleCube();

        // Set initial transform
        cube->transform.position = { 0.0f, 0.0f, 0.0f };
        cube->transform.rotation = { 0.0f, 0.0f, 0.0f };
        cube->transform.scale = { 1.0f, 1.0f, 1.0f };

        // -----------------------------
        // Compile simple shader
        // -----------------------------
        const std::string vertexSource = R"(
        #version 330 core
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec3 aNormal;
        layout(location = 2) in vec2 aTexCoord;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main()
        {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
        }
    )";

        const std::string fragmentSource = R"(
        #version 330 core
        out vec4 FragColor;
        void main()
        {
            FragColor = vec4(0.2, 0.7, 0.9, 1.0);
        }
    )";

        m_Shader.CompileAndLinkShaderViaGLSLShaderFiles(vertexSource, fragmentSource);

        // -----------------------------
        //  Set camera / projection matrices
        // -----------------------------
        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
            1280.0f / 720.0f,
            0.1f, 100.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3));

        m_Shader.Bind();
        m_Shader.SetMat4("projection", projection);
        m_Shader.SetMat4("view", view);
        m_Shader.Unbind();

        SS_INFO("Test scene initialized: cube created and shader compiled.");
    }

    bool Application::EngineShutdown()
    {
        m_Window.DestroyWindow();
        SS_INFO("Engine is shutting down!");
        return true;
    }

    std::unique_ptr<Application> Application::CreateApplication()
    {
        return std::make_unique<Application>();
    }
}
