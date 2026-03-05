#include "SceneManagerPanel.h"

#include <imgui.h>

namespace SurrealStudio {

	namespace SurrealEditor {

		bool SceneManagerPanel::DrawCameraCreation()
		{
			const char* c_CPTR_cameraOptions[] = {
				"Normal", "Orthographic"
			};

			if (ImGui::BeginCombo("Camera Options", c_CPTR_cameraOptions[i_selectedCameraIndex]))
			{	
				for (int n = 0; n < IM_ARRAYSIZE(c_CPTR_cameraOptions); n++)
				{
					bool b_IsCameraOptionSelected = (n == i_selectedCameraIndex);
					if (ImGui::Selectable(c_CPTR_cameraOptions[n], b_IsCameraOptionSelected))
						i_selectedCameraIndex = n;
					
					if (b_IsCameraOptionSelected == true)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			if (camera.m_Cameras.size() > camera.MAX_CAMERAS_PER_WORLD && b_openMaxCameraObjectsReachedPerWorld_SSERROR_DialogBox == true)
			{
				ImGui::OpenPopup("Surreal Studio Error - Max Cameras Per World Reached");
				b_openMaxCameraObjectsReachedPerWorld_SSERROR_DialogBox = false;
			}

			if (ImGui::BeginPopupModal("Surreal Studio Error - Max Cameras Per World Reached", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::TextColored(ImVec4(1, 0, 0, 1),
					"Max amount of Cameras per World is %d, got %d.", camera.MAX_CAMERAS_PER_WORLD, static_cast<int>(camera.m_Cameras.size())
				);

				if (ImGui::Button("OK"))
				{
					ImGui::CloseCurrentPopup();
					camera.m_Cameras.resize(camera.MAX_CAMERAS_PER_WORLD);
					b_openMaxCameraObjectsReachedPerWorld_SSERROR_DialogBox = false;
				}
				ImGui::EndPopup();
			}

			if (i_selectedCameraIndex == 0)
			{
				camera.SetCameraType(Camera::CameraType::Normal);
			}
			else if (i_selectedCameraIndex == 1)
			{
				camera.SetCameraType(Camera::CameraType::Orthographic);
			}

			DrawCameraProperites(c_CPTR_cameraOptions, i_selectedCameraIndex);

			return true;
		}

		bool SceneManagerPanel::DrawLightingCreation()
		{
			const char* c_CPTR_lightingOptions[] = {
				"World Environment Light", "Surreal Ambient Light", "Surreal Point Light",
				"Surreal Spot Light", "Surreal Area Light", "Surreal Emissive Light"
			};

			if (ImGui::BeginCombo("Lighting Types", c_CPTR_lightingOptions[i_selectedLightingIndex]))
			{
				for (int n = 0; n < IM_ARRAYSIZE(c_CPTR_lightingOptions); n++)
				{
					bool b_IsLightObjectSelected = (i_selectedLightingIndex == n);
					if (ImGui::Selectable(c_CPTR_lightingOptions[n], b_IsLightObjectSelected))
						i_selectedLightingIndex = n;

					if (b_IsLightObjectSelected == true)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			// Check if the max amount of Light Object has reached or not
			if (m_LightingObjects.size() > MAX_LIGHT_OBJECTS_PER_WORLD && b_OpenMaxLightObjectsReachedPerWorld_SSERROR_DialogBox == true)
			{
				ImGui::OpenPopup("[SS ERROR] Max amount of Lighting Objects reached per World");
				b_OpenMaxLightObjectsReachedPerWorld_SSERROR_DialogBox = false;
			}

			if (ImGui::BeginPopupModal("[SS ERROR] Max amount of Lighting Objects reached per World", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::Text("Max amount of Lighting Objects per World is %d, got %d.", MAX_LIGHT_OBJECTS_PER_WORLD, static_cast<int>(m_LightingObjects.size()));
				
				if (ImGui::Button("OK")) {
					ImGui::CloseCurrentPopup();
					m_LightingObjects.resize(MAX_LIGHT_OBJECTS_PER_WORLD); // Clamp to max value
					b_OpenMaxLightObjectsReachedPerWorld_SSERROR_DialogBox = true; // Reset
				}
				ImGui::EndPopup();
			}

			switch (i_selectedLightingIndex)
			{
				case 0:
				{
					if (lighting.hasLightingObjectBeenCreated)
						break; // no need to continue, lighting object has already been created.

					auto newLightingObject = std::make_unique<Lighting>();
					newLightingObject->lightingType = Lighting::LightingType::WorldEnvironmentLight;
					m_LightingObjects.push_back(std::move(newLightingObject));
					lighting.hasLightingObjectBeenCreated = true; 
					break;
				}
				case 1:
				{
					if (lighting.hasLightingObjectBeenCreated)
						break; // no need to continue, lighting object has already been created.

					auto newLightingObject = std::make_unique<Lighting>();
					newLightingObject->lightingType = Lighting::LightingType::SurrealAmbientLight;
					m_LightingObjects.push_back(std::move(newLightingObject));
					lighting.hasLightingObjectBeenCreated = true;
					break;
				}
				case 2:
				{
					if (lighting.hasLightingObjectBeenCreated)
						break; // no need to continue, lighting object has already been created.

					auto newLightingObject = std::make_unique<Lighting>();
					newLightingObject->lightingType = Lighting::LightingType::SurrealPointLight;
					m_LightingObjects.push_back(std::move(newLightingObject));
					lighting.hasLightingObjectBeenCreated = true;
					break;
				}
				case 3:
				{
					if (lighting.hasLightingObjectBeenCreated)
						break; // no need to continue, lighting object has already been created.

					auto newLightingObject = std::make_unique<Lighting>();
					newLightingObject->lightingType = Lighting::LightingType::SurrealSpotLight;
					m_LightingObjects.push_back(std::move(newLightingObject));
					lighting.hasLightingObjectBeenCreated = true;
					break;
				}
				case 4:
				{
					if (lighting.hasLightingObjectBeenCreated)
						break; // no need to continue, lighting object has already been created.

					auto newLightingObject = std::make_unique<Lighting>();
					newLightingObject->lightingType = Lighting::LightingType::SurrealAreaLight;
					m_LightingObjects.push_back(std::move(newLightingObject));
					lighting.hasLightingObjectBeenCreated = true;
					break;
				}
				case 5:
				{
					if (lighting.hasLightingObjectBeenCreated)
						break; // no need to continue, lighting object has already been created.

					auto newLightingObject = std::make_unique<Lighting>();
					newLightingObject->lightingType = Lighting::LightingType::SurrealEmissiveLight;
					m_LightingObjects.push_back(std::move(newLightingObject));
					lighting.hasLightingObjectBeenCreated = true;
					break;
				}
			}
			
			DrawLightingProperties(c_CPTR_lightingOptions, i_selectedLightingIndex);
			return true;
		}

		bool SceneManagerPanel::DrawCameraProperites(const char* cameraOptions[], int index)
		{
			if (!cameraOptions || index < 0 || index >= static_cast<int>(camera.m_Cameras.size()))
				return false; // Out of bounds

			Camera* cameraProperties = camera.m_Cameras[index].get();
			if (!cameraProperties)
				return false;  // not valid

			ImGui::DragFloat3("Position:", &cameraProperties->m_Position[0], 0.1f);
			ImGui::DragFloat3("Direction:", &cameraProperties->m_Direction[0], 0.1f);
			ImGui::DragFloat3("Right:", &cameraProperties->m_Right[0], 1.0f);
			ImGui::DragFloat3("Up:", &cameraProperties->m_Up[0], 0.1f);

			ImGui::DragFloat("Yaw:", &cameraProperties->m_Yaw, 0.1f);
			ImGui::DragFloat("Pitch:", &cameraProperties->m_Pitch, 0.1f);
			ImGui::DragFloat("Movement Speed:", &cameraProperties->m_MovementSpeed, 0.1f);
			ImGui::DragFloat("MouseSensitivity:", &cameraProperties->m_MouseSensitivity, 0.1f);

			return true;
		}

		bool SceneManagerPanel::DrawLightingProperties(const char* lightingOptions[], int index)
		{
			if (!lightingOptions || index < 0 || index >= static_cast<int>(m_LightingObjects.size()))
				return false; // Out of bounds

			Lighting* lighting = m_LightingObjects[index].get();
			if (!lighting)
				return false; // not valid

			ImGui::DragFloat3("Position:", &lighting->lightPosition[0], 0.1f);
			ImGui::DragFloat3("Direction:", &lighting->lightDirection[0], 0.1f);

			float lightColor[4] = {
				lighting->lightColor.x,
				lighting->lightColor.y,
				lighting->lightColor.z,
				lighting->lightColor.a,
			};

			ImGui::ColorEdit4("Light Color:", lightColor);
			
			ImGui::DragFloat("Intensity:", &lighting->intensity, 0.1f);
			ImGui::DragFloat("Radius:", &lighting->radius, 0.1f);
			ImGui::DragFloat("Angle:", &lighting->angle, 0.1f);

			ImGui::Checkbox("Casts Shadows:", &lighting->castsShadows);

			return true;
		}

		bool SceneManagerPanel::DrawSceneCreation()
		{
			if (ImGui::Button("Create Main Scene"))
			{
				if (!m_Scene.AddScene()) return false;
				isSceneCreated = true;
			}

			if (isSceneCreated)
			{
				if (ImGui::Button("Create Subscene"))
				{
					b_AskUserForSubsceneName = true;
					if (b_AskUserForSubsceneName)
					{
						ImGui::OpenPopup("Subscene Name");
						b_AskUserForSubsceneName = false;
					}

					if (ImGui::BeginPopupModal("Subscene Name", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::InputText("Subscene Name...", bufferForSubsceneNamePopup, sizeof(bufferForSubsceneNamePopup));

						if (ImGui::IsItemDeactivatedAfterEdit())
						{
							ImGui::TextColored(ImVec4(1, 0, 0, 1), "Please give a Subscene name!");
						}

						if (ImGui::Button("OK"))
						{
							ImGui::CloseCurrentPopup();
							std::string newSubsceneName = bufferForSubsceneNamePopup;
							m_Subscene.AddSubscene(newSubsceneName);
						}
						ImGui::EndPopup();
					}
				}
			}

			if (isSubsceneCreated)
			{
				if (ImGui::Button("Create World"))
				{
					b_AskUserForWorldName = true;
					if (b_AskUserForWorldName)
					{
						ImGui::OpenPopup("World Name");
						b_AskUserForWorldName = false;
					}

					if (ImGui::BeginPopupModal("World Name", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::InputText("World Name...", bufferForWorldNamePopup, sizeof(bufferForWorldNamePopup));
						
						if (ImGui::IsItemDeactivatedAfterEdit())
						{
							ImGui::TextColored(ImVec4(1, 0, 0, 1), "Please give a World Name!");
						}

						if (ImGui::Button("OK"))
						{
							ImGui::CloseCurrentPopup();
							std::string newWorldName = bufferForWorldNamePopup;
							m_World.AddWorld(newWorldName);
						}
						ImGui::EndPopup();
					}
				}
			}

			return true;
		}

		bool SceneManagerPanel::DrawSceneManagerPanel()
		{
			ImGui::Begin("Scene Manager Panel");

			DrawSceneCreation();

			if (ImGui::CollapsingHeader("Camera"))
				DrawCameraCreation();
			
			if (ImGui::CollapsingHeader("Lighting"))
				DrawLightingCreation();

			ImGui::End();

			return true;
		}
	}
}