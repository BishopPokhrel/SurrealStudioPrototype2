#include "ObjectSettingsPanel.h"

#include <imgui.h>

namespace SurrealStudio {

	namespace SurrealEditor {

		bool ObjectSettingsPanel::DrawObjectCreation()
		{
			const char* c_CPTR_objectOptions[] = {
				"Cube Object", "Sphere Object", "Capsule Object",
				"Plane Object", "Mesh Object"
			};

			const char* c_CPTR_meshTypeOptions[] = {
				"Static Mesh", "Custom Mesh"
			};

			if (ImGui::BeginCombo("Object Types", c_CPTR_objectOptions[i_selectedObjectIndex]))
			{
				for (int n = 0; n < IM_ARRAYSIZE(c_CPTR_objectOptions); n++)
				{
					bool b_IsObjectSelected = (i_selectedObjectIndex == n);
					if (ImGui::Selectable(c_CPTR_objectOptions[n], b_IsObjectSelected))
						i_selectedObjectIndex = n;

					if (b_IsObjectSelected == true)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			if (m_ObjectManager.m_Objects.size() > ECS::MAX_OBJECTS && b_OpenMaxObjectsReachedPerWorld_SSERROR_DialogBox == true)
			{
				ImGui::OpenPopup("[SS ERROR] Max amount of Objects reached per World");
				b_OpenMaxObjectsReachedPerWorld_SSERROR_DialogBox = false;
			}

			if (ImGui::BeginPopupModal("[SS ERROR] Max amount of Objects reached per World", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::Text("Max amount of Objects per World is ", ECS::MAX_OBJECTS, static_cast<int>(m_ObjectManager.m_Objects.size()));
				
				if (ImGui::Button("OK"))
				{
					ImGui::CloseCurrentPopup();
					m_ObjectManager.m_Objects.resize(ECS::MAX_OBJECTS);
					b_OpenMaxObjectsReachedPerWorld_SSERROR_DialogBox = true;
				}
				ImGui::EndPopup();
			}

			if (b_OpenMeshConfigurationTypePopup == true)
			{
				ImGui::OpenPopup("Mesh Type Configuration");
				b_OpenMeshConfigurationTypePopup = false;
			}

			if (ImGui::BeginPopupModal("Mesh Type Configuration", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::Text("Mesh Types");
				if (ImGui::BeginCombo("Mesh Types", c_CPTR_meshTypeOptions[i_SelectedMeshConfigurationTypeIndex]))
				{
					for (int n = 0; n < IM_ARRAYSIZE(c_CPTR_meshTypeOptions); n++)
					{
						bool b_IsMeshTypeSelected = (i_SelectedMeshConfigurationTypeIndex == n);
						if (ImGui::Selectable(c_CPTR_meshTypeOptions[n], b_IsMeshTypeSelected))
							i_SelectedMeshConfigurationTypeIndex = n;

						if (b_IsMeshTypeSelected == true)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}
			}

			if (i_SelectedMeshConfigurationTypeIndex == 0) m_Mesh.meshType = SurrealRenderer::MeshType::StaticMesh;
			else if (i_SelectedMeshConfigurationTypeIndex == 1) m_Mesh.meshType = SurrealRenderer::MeshType::CustomMesh;

			if		(i_selectedObjectIndex == 0) m_SelectedObjectData.SetObjectType(ECS::ObjectData::ObjectType::Cube);
			else if (i_selectedObjectIndex == 1) m_SelectedObjectData.SetObjectType(ECS::ObjectData::ObjectType::Sphere);
			else if (i_selectedObjectIndex == 2) m_SelectedObjectData.SetObjectType(ECS::ObjectData::ObjectType::Capsule);
			else if (i_selectedObjectIndex == 3) m_SelectedObjectData.SetObjectType(ECS::ObjectData::ObjectType::Plane);
			else if (i_selectedObjectIndex == 4) m_SelectedObjectData.SetObjectType(ECS::ObjectData::ObjectType::Mesh);

			DrawObjectProperties(c_CPTR_objectOptions, i_selectedObjectIndex);

			return true;
		}

		bool ObjectSettingsPanel::DrawObjectProperties(const char* objectOptions[], int index)
		{
			if (!objectOptions || index < 0 || index >= static_cast<int>(m_ObjectManager.m_Objects.size()))
				return false; // Out of bounds

			ECS::ObjectData* objectData = m_ObjectManager.m_Objects[index].get();
			if (!objectData)
				return false; // not valid

			ImGui::DragFloat3("Position:", &objectData->transform.position[0], 0.1f);
			ImGui::DragFloat3("Rotation:", &objectData->transform.rotation[0], 0.1f);
			ImGui::DragFloat3("Scale:", &objectData->transform.scale[0], 0.1f);

			// TODO: Add more properties to edit for the objects (e.g. mesh, material, etc.)
			return true;
		}

		bool ObjectSettingsPanel::DrawRemoveObject()
		{
			b_OpenMaxObjectsReachedPerWorld_SSERROR_DialogBox = true;
			if (b_OpenObjectDeletionConfirmation_SSERROR_DialogBox == true)
			{
				ImGui::OpenPopup("Surreal Studio - Object Deletion");
				b_OpenMaxObjectsReachedPerWorld_SSERROR_DialogBox = false;
			}

			if (ImGui::BeginPopupModal("Surreal Studio - Object Deletion", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::InputText("Enter the Object Name you would like to delete... ", objToDeleteBuffer, sizeof(objToDeleteBuffer));

				if (ImGui::IsItemDeactivatedAfterEdit())
				{
					ImGui::TextColored(ImVec4(1, 0, 0, 1), "Pleae enter a Object name!");
				}

				if (ImGui::Button("OK"))
				{
					ImGui::CloseCurrentPopup();
					std::string objectNameToDelete = objToDeleteBuffer;
					m_ObjectManager.DestroyObject(objectNameToDelete);
				}

				if (ImGui::Button("Cancel")) {
					ImGui::CloseCurrentPopup();
				}
			}

			return true;
		}

		bool ObjectSettingsPanel::DrawObjectSettingsPanel()
		{
			ImGui::Begin("Object Settings");

			DrawObjectCreation();
			if (ImGui::Button("Delete Object"))
				DrawRemoveObject();

			ImGui::End();
			return true;
		}
		
	} 
} 