#pragma once

#define GLFW_INCLUDE_NONE

#include <SurrealEditor/Panels/ObjectSettingsPanel.h>
#include <SurrealEditor/Panels/SceneHierarchyPanel.h>
#include <SurrealEditor/Panels/SceneManagerPanel.h>

#include "GLFW/glfw3.h"

namespace SurrealStudio {
    class Application; // forward declaration
}

namespace SurrealStudio {

    namespace SurrealEditor {

        class SurrealStudioMainWindow
        {
        public:
            bool InitWindow();
            bool CreateWindow(int width, int height, const char* title);
            bool MainLoop();
            bool DestroyWindow();

            void SetApplication(SurrealStudio::Application* app) { m_Application = app; }

        private:
            GLFWwindow* m_SurrealStudioWindow = nullptr;
            SurrealStudio::Application* m_Application = nullptr;

            SurrealEditor::SceneHierarchyPanel m_SceneHierarchyPanel;
            SurrealEditor::SceneManagerPanel m_SceneManagerPanel;
            SurrealEditor::ObjectSettingsPanel m_ObjectSettingsPanel;
        };
    }
}
