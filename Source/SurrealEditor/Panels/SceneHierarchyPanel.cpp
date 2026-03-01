#include "SceneHierarchyPanel.h"

#include <imgui.h>

namespace SurrealStudio {
	
	namespace SurrealEditor {

		bool SceneHierarchyPanel::DrawSceneHierarchy()
		{
			return true; 
		}

		bool SceneHierarchyPanel::DrawCommandPlattle()
		{
			return true;
		}

		bool SceneHierarchyPanel::DrawSceneHierarchyPanel()
		{
			ImGui::Begin("Scene Hierarchy Panel");

			DrawSceneHierarchy();

			if (m_InputSystem.IsRightMouseButtonPressed(m_Window))
				DrawCommandPlattle();

			ImGui::End();
			return true;
		}
	}
}