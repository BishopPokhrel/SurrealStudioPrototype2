#pragma once

#include <Engine/Camera.h>

namespace SurrealStudio {

	namespace SurrealEditor {
		
		// TEMPORARY CODE
		enum class LightingType
		{
			None = 0,
			WorldEnvironmentLight,
			SurrealAmbientLight,
			SurrealPointLight, 
			SurrealSpotLight,
			SurrealAreaLight,
			SurrealEmissiveLight
		};

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
			int i_selectedLightingIndex = 0;

			// temporary code, will be replaced by the actual constant in a Lighting System to be later implemented
			const int MAX_LIGHT_OBJECTS_PER_WORLD = 25;
		};
	}
}