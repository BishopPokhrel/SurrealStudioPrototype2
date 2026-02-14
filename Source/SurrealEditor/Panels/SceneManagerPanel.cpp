#include "SceneManagerPanel.h"

#include <imgui.h>

namespace SurrealStudio {

	namespace SurrealEditor {

		bool SceneManagerPanel::DrawCameraCreation()
		{
			
			const char* c_CPTR_cameraOptions[] = {
				"Normal", "Orthographic"
			};
			bool b_openMaxCameraObjectsReachedPerWorld_SSERROR_DialogBox = true;

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
			return true;
		}

		bool SceneManagerPanel::DrawCameraProperites(const char* cameraOptions[], int index)
		{
			return true;
		}

		bool SceneManagerPanel::DrawLightingProperties(const char* lightingOptions[], int index)
		{
			return true;
		}

		bool SceneManagerPanel::DrawSceneCreation()
		{
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