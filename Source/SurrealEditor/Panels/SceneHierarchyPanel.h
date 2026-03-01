#pragma once

#include <Engine/InputSystem.h>

namespace SurrealStudio {

	namespace SurrealEditor {

		class SceneHierarchyPanel
		{
		public:

			bool DrawSceneHierarchy();
			bool DrawCommandPlattle();  // Trigged when right clicked
			bool DrawSceneHierarchyPanel();

		private:

			InputSystem m_InputSystem;
			GLFWwindow* m_Window; 
		};
	}
}