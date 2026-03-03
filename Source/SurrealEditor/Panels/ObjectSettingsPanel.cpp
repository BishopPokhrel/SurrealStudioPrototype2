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
				ImGui::Text("Max amount of Objects per World is %d", ECS::MAX_OBJECTS, static_cast<int>(m_ObjectManager.m_Objects.size()));
				
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

			if (ImGui::CollapsingHeader("Transform"))
			{
				ImGui::DragFloat3("Position:", &objectData->transform.position[0], 0.1f);
				ImGui::DragFloat3("Rotation:", &objectData->transform.rotation[0], 0.1f);
				ImGui::DragFloat3("Scale:", &objectData->transform.scale[0], 0.1f);
			}

			if (ImGui::CollapsingHeader("Color"))
			{
				float objColor[4] = {
					m_AdditionalObjectData.color.x,
					m_AdditionalObjectData.color.y,
					m_AdditionalObjectData.color.z,
					m_AdditionalObjectData.color.a
				};

				ImGui::ColorEdit4("Color:", objColor);
			}

			if (ImGui::CollapsingHeader("Physics"))
			{
				ImGui::Checkbox("Enable Physics", &m_AdditionalObjectData.enablePhysics);
			}

			ImGui::Separator();
			ImGui::Spacing();

			if (ImGui::CollapsingHeader("Materials"))
			{
				const char* c_CPTR_materialTypeOptions[] = {
					"Color Material", "Texture Material", "Custom Material"
				};

				if (ImGui::BeginCombo("Material Types", c_CPTR_materialTypeOptions[m_AdditionalObjectData.materials.i_selectedMaterialIndex]))
				{
					for (int n = 0; n < IM_ARRAYSIZE(c_CPTR_materialTypeOptions); n++)
					{
						bool b_IsMaterialTypeSelected = (m_AdditionalObjectData.materials.i_selectedMaterialIndex == n);
						if (ImGui::Selectable(c_CPTR_materialTypeOptions[n], b_IsMaterialTypeSelected))
							m_AdditionalObjectData.materials.i_selectedMaterialIndex = n;

						if (b_IsMaterialTypeSelected == true)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}

				// Check if we exceed the max limit or not
				if (
					m_AdditionalObjectData.materialsVec.size() > m_AdditionalObjectData.materials.MAX_COLOR_MATERIALS_PER_WORLD &&
					m_AdditionalObjectData.materials.b_OpenMaxColorMaterialsPerWorld_SSERROR_DialogBox == true
					)
				{
					ImGui::OpenPopup("[SS ERROR] Max Color Materials reached per World.");
					m_AdditionalObjectData.materials.b_OpenMaxColorMaterialsPerWorld_SSERROR_DialogBox = false; 
				}

				if (
					m_AdditionalObjectData.materialsVec.size() > m_AdditionalObjectData.materials.MAX_TEXTURE_MATERIALS_PER_WORLD &&
					m_AdditionalObjectData.materials.b_OpenMaxTextureMaterialsPerWorld_SSERROR_DialogBox == true
					)
				{
					ImGui::OpenPopup("[SS ERROR] Max Texture Materials reached per World.");
					m_AdditionalObjectData.materials.b_OpenMaxTextureMaterialsPerWorld_SSERROR_DialogBox = false; 
				}

				if (
					m_AdditionalObjectData.materialsVec.size() > m_AdditionalObjectData.materials.MAX_CUSTOM_MATERIALS_PER_WORLD &&
					m_AdditionalObjectData.materials.b_OpenMaxCustomMaterialsPerWorld_SSERROR_DialogBox == true
					)
				{
					ImGui::OpenPopup("[SS ERROR] Max Custom Materials reached per World.");
					m_AdditionalObjectData.materials.b_OpenMaxCustomMaterialsPerWorld_SSERROR_DialogBox = false;
				}

				if (
					m_AdditionalObjectData.materialsVec.size() > m_AdditionalObjectData.materials.MAX_OVERALL_TEXTURE_MATERIALS_PER_WORLD &&
					m_AdditionalObjectData.materials.b_OpenMaxOverallMaterialsPerWorld_SSERROR_DialogBox == true
					)
				{
					ImGui::OpenPopup("[SS ERROR] Max Materials reached per World.");
					m_AdditionalObjectData.materials.b_OpenMaxOverallMaterialsPerWorld_SSERROR_DialogBox = false; 
				}

				// Modal writes now
				if (ImGui::BeginPopupModal("[SS ERROR] Max Color Materials reached per World", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text(
						"Max Color Materials per World is %d (Current: %d)",
						m_AdditionalObjectData.materials.MAX_COLOR_MATERIALS_PER_WORLD,
						static_cast<int>(m_AdditionalObjectData.materialsVec.size())
					);

					if (ImGui::Button("OK"))
					{
						ImGui::CloseCurrentPopup();
						m_AdditionalObjectData.materialsVec.resize(m_AdditionalObjectData.materials.MAX_COLOR_MATERIALS_PER_WORLD);
						m_AdditionalObjectData.materials.b_OpenMaxColorMaterialsPerWorld_SSERROR_DialogBox = true;
					}

					ImGui::EndPopup();
				}

				if (ImGui::BeginPopupModal("[SS ERROR] Max Texture Materials reached per World", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text(
						"Max Texture Materials per World is %d (Current: %d)",
						m_AdditionalObjectData.materials.MAX_TEXTURE_MATERIALS_PER_WORLD,
						static_cast<int>(m_AdditionalObjectData.materialsVec.size())
					);

					if (ImGui::Button("OK"))
					{
						ImGui::CloseCurrentPopup();
						m_AdditionalObjectData.materialsVec.resize(m_AdditionalObjectData.materials.MAX_TEXTURE_MATERIALS_PER_WORLD);
						m_AdditionalObjectData.materials.b_OpenMaxTextureMaterialsPerWorld_SSERROR_DialogBox = true;
					}

					ImGui::EndPopup();
				}

				if (ImGui::BeginPopupModal("[SS ERROR] Max Custom Materials reached per World", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text(
						"Max Custom Materials per World is %d (Current: %d)",
						m_AdditionalObjectData.materials.MAX_CUSTOM_MATERIALS_PER_WORLD,
						static_cast<int>(m_AdditionalObjectData.materialsVec.size())
					);

					if (ImGui::Button("OK"))
					{
						ImGui::CloseCurrentPopup();
						m_AdditionalObjectData.materialsVec.resize(m_AdditionalObjectData.materials.MAX_CUSTOM_MATERIALS_PER_WORLD);
						m_AdditionalObjectData.materials.b_OpenMaxCustomMaterialsPerWorld_SSERROR_DialogBox = true;
					}

					ImGui::EndPopup();
				}

				if (ImGui::BeginPopupModal("[SS ERROR] Max Materials reached per World", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text(
						"Max Materials per World is %d (Current: %d)",
						m_AdditionalObjectData.materials.MAX_OVERALL_TEXTURE_MATERIALS_PER_WORLD,
						static_cast<int>(m_AdditionalObjectData.materialsVec.size())
					);

					if (ImGui::Button("OK"))
					{
						ImGui::CloseCurrentPopup();
						m_AdditionalObjectData.materialsVec.resize(m_AdditionalObjectData.materials.MAX_OVERALL_TEXTURE_MATERIALS_PER_WORLD);
						m_AdditionalObjectData.materials.b_OpenMaxOverallMaterialsPerWorld_SSERROR_DialogBox = true; 
					}

					ImGui::EndPopup();
				}

				if (ImGui::Button("Create new Material"))
				{
					m_AdditionalObjectData.materials.openMaterialNamePopup = true;
					if (m_AdditionalObjectData.materials.openMaterialNamePopup)
					{
						ImGui::OpenPopup("Material Name...");
						m_AdditionalObjectData.materials.openMaterialNamePopup = false;
					}

					if (ImGui::BeginPopupModal("Material Name...", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::InputText("Material Name...", m_AdditionalObjectData.materials.materialNamePopupBuffer, sizeof(m_AdditionalObjectData.materials.materialNamePopupBuffer));
						
						if (ImGui::Button("OK"))
						{
							ImGui::CloseCurrentPopup();
							std::string newMaterialName = m_AdditionalObjectData.materials.materialNamePopupBuffer;

							switch (m_AdditionalObjectData.materials.i_selectedMaterialIndex)
							{
								case 0:
								{
									if (m_AdditionalObjectData.materials.hasMaterialBeenCreated)
										break; // already been created, no need to do it again (to make sure that it doesn't repeat every frame)

									auto newMaterial = std::make_unique<AdditionalObjectData::Materials>();
									newMaterial->name = newMaterialName;
									newMaterial->id = static_cast<int>(m_AdditionalObjectData.materialsVec.size());
									newMaterial->materialType = AdditionalObjectData::Materials::MaterialType::ColorMaterial;
									m_AdditionalObjectData.materialsVec.push_back(std::move(newMaterial));
									m_AdditionalObjectData.materials.hasMaterialBeenCreated = true; 
									break;
								}

								case 1:
								{
									if (m_AdditionalObjectData.materials.hasMaterialBeenCreated)
										break; // already been created, no need to do it again (to make sure that it doesn't repeat every frame)

									auto newMaterial = std::make_unique<AdditionalObjectData::Materials>();
									newMaterial->name = newMaterialName;
									newMaterial->id = static_cast<int>(m_AdditionalObjectData.materialsVec.size());
									newMaterial->materialType = AdditionalObjectData::Materials::MaterialType::TextureMaterial;
									m_AdditionalObjectData.materialsVec.push_back(std::move(newMaterial));
									m_AdditionalObjectData.materials.hasMaterialBeenCreated = true;
									break;

								}

								case 2:
								{
									if (m_AdditionalObjectData.materials.hasMaterialBeenCreated)
										break; // already been created, no need to do it again (to make sure that it doesn't repeat every frame)

									auto newMaterial = std::make_unique<AdditionalObjectData::Materials>();
									newMaterial->name = newMaterialName;
									newMaterial->id = static_cast<int>(m_AdditionalObjectData.materialsVec.size());
									newMaterial->materialType = AdditionalObjectData::Materials::MaterialType::CustomMaterial;
									m_AdditionalObjectData.materialsVec.push_back(std::move(newMaterial));
									m_AdditionalObjectData.materials.hasMaterialBeenCreated = true;
									break;
								}
							}
						}

						if (ImGui::Button("Cancel")) {
							ImGui::CloseCurrentPopup();
						}
					}
				}
			}
			
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
				ImGui::InputInt("Enter the Object ID you would like to delete... ", objToDeleteBuffer, sizeof(objToDeleteBuffer));

				if (ImGui::IsItemDeactivatedAfterEdit())
				{
					ImGui::TextColored(ImVec4(1, 0, 0, 1), "Pleae enter a Object name!");
				}

				if (ImGui::Button("OK"))
				{
					ImGui::CloseCurrentPopup();
					m_ObjectManager.DestroyObject((uint64_t)objToDeleteBuffer);
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