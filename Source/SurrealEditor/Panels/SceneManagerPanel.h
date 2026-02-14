#pragma once

#include <Engine/Camera.h>

namespace SurrealStudio {

	namespace SurrealEditor {

		class SceneManagerPanel
		{
		public:

			bool DrawSceneCreation();
			bool DrawLightingCreation();
			bool DrawCameraCreation();
			bool DrawLightingProperties(const char* lightingOptions[], int index);
			bool DrawCameraProperites(const char* cameraOptions[], int index);
			bool DrawSceneManagerPanel();

		private:

			Camera camera;
			int i_selectedCameraIndex = 0;
		};
	}
}