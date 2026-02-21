#pragma once

#include <Engine/Camera.h> // this eader includes glm, vector and memory
#include <Engine/Scene/Scene.h>
#include <Engine/Scene/Subscene.h>
#include <Engine/Scene/World.h>

namespace SurrealStudio {

	namespace SurrealEditor {
		
		// TEMPORARY CODE
		struct Lighting 
		{
			glm::vec3 lightPosition{ 0.0f, 0.0f, 0.0f };
			glm::vec3 lightDirection{ 0.0f, 0.0f, 0.0f };
			glm::vec4 lightColor{ 0.0f, 0.0f, 0.0f, 0.0f };

			float intensity = 0.0f;
			float radius = 0.0f;
			float angle = 0.0f;

			bool castsShadows = false;

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

			LightingType lightingType;	
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
			
			Lighting lighting;  // TODO: Replace this with the actual lighting system
			std::vector<std::unique_ptr<Lighting>> m_LightingObjects;

			// POPUP FLAGS FOR IMGUI
			bool b_OpenMaxLightObjectsReachedPerWorld_SSERROR_DialogBox = true;
			bool b_openMaxCameraObjectsReachedPerWorld_SSERROR_DialogBox = true;

			SceneSystem::Scene m_Scene;
			SceneSystem::Subscene m_Subscene;
			SceneSystem::World m_World;

			// To check if some scenes or subscenes are created
			bool isSceneCreated = false; // If the scene is created (like, if (ImGui::Button("Create Main Scene")) {}), we will set this flag to be true, and we will check if that flag is true
			// or not, and if it is true, then the user can create a Subscene
			
			// Same logic with this other flag
			bool isSubsceneCreated = false;

			// Flag to ask the user to add a Subscene name (see .cpp file implementation for further details)
			bool b_AskUserForSubsceneName = false;
			char bufferForSubsceneNamePopup[512]; // The buffer required for ImGui::InputText. See .cpp file implementation for further details.
			
			// Flag to ask the user to add a World name (see .cpp file implementation for further details)
			bool b_AskUserForWorldName = false;
			char bufferForWorldNamePopup[512]; // The buffer required for ImGui::InputText. See .cpp file implementation for further details
		};
	}
};