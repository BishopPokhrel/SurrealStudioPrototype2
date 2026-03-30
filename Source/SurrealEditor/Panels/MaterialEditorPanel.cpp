	#include "MaterialEditorPanel.h"

	#include <imgui.h>

	namespace SurrealStudio {

		namespace SurrealEditor {

			bool MaterialEditorPanel::DrawMaterialCreation()
			{
				const char* c_CPTR_materialTypeOptions[] = {
					"Color Material", "Texture Material", "Custom Material"
				};

				if (ImGui::CollapsingHeader("Material Creation"))
				{
					if (ImGui::BeginCombo("Material Types", c_CPTR_materialTypeOptions[m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.i_MaterialCreationTypeIndex]))
					{
						for (int n = 0; n < IM_ARRAYSIZE(c_CPTR_materialTypeOptions); n++)
						{
							bool b_IsMaterialTypeSelected = (m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.i_MaterialCreationTypeIndex == n);
							if (ImGui::Selectable(c_CPTR_materialTypeOptions[n], b_IsMaterialTypeSelected))
								m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.i_MaterialCreationTypeIndex = n;

							if (b_IsMaterialTypeSelected == true)
								ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}

					// Checks
					// Check if we exceed the max limit or not
					if (
						m_MaterialEditorPanel_Materials_DataRequired.materialDataRequiredVec.size() > m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->Material_MAX_COLOR_MATERIALS_PER_WORLD &&
						m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.b_OpenMaxColorMaterialsPerWorld_SSERROR_DialogBox == true
						)
					{
						ImGui::OpenPopup("[SS ERROR] Max Color Materials reached per World.");
						m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.b_OpenMaxColorMaterialsPerWorld_SSERROR_DialogBox = false;
					}

					if (
						m_MaterialEditorPanel_Materials_DataRequired.materialDataRequiredVec.size() > m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->Material_MAX_TEXTURE_MATERIALS_PER_WORLD &&
						m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.b_OpenMaxTextureMaterialsPerWorld_SSERROR_DialogBox == true
						)
					{
						ImGui::OpenPopup("[SS ERROR] Max Texture Materials reached per World.");
						m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.b_OpenMaxTextureMaterialsPerWorld_SSERROR_DialogBox= false;
					}

					if (
						m_MaterialEditorPanel_Materials_DataRequired.materialDataRequiredVec.size() > m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->Material_MAX_CUSTOM_MATERIALS_PER_WORLD &&
						m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.b_OpenMaxCustomMaterialsPerWorld_SSERROR_DialogBox == true
						)
					{
						ImGui::OpenPopup("[SS ERROR] Max Custom Materials reached per World.");
						m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.b_OpenMaxCustomMaterialsPerWorld_SSERROR_DialogBox = false;
					}

					if (
						m_MaterialEditorPanel_Materials_DataRequired.materialDataRequiredVec.size() > m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->Material_MAX_OVERALL_MATERIALS_PER_WORLD &&
						m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.b_OpenMaxOverallMaterialsPerWorld_SSERROR_DialogBox== true
						)
					{
						ImGui::OpenPopup("[SS ERROR] Max Materials reached per World.");
						m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.b_OpenMaxOverallMaterialsPerWorld_SSERROR_DialogBox = false;
					}

					// Modal writes now
					if (ImGui::BeginPopupModal("[SS ERROR] Max Color Materials reached per World", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::Text(
							"Max Color Materials per World is %d (Current: %d)",
							m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.b_OpenMaxColorMaterialsPerWorld_SSERROR_DialogBox,
							static_cast<int>(m_MaterialEditorPanel_Materials_DataRequired.materialDataRequiredVec.size())
						);

						if (ImGui::Button("OK"))
						{
							ImGui::CloseCurrentPopup();
							m_MaterialEditorPanel_Materials_DataRequired.materialDataRequiredVec.resize(m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->Material_MAX_COLOR_MATERIALS_PER_WORLD);
							m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.b_OpenMaxColorMaterialsPerWorld_SSERROR_DialogBox = true;
						}

						ImGui::EndPopup();
					}

					if (ImGui::BeginPopupModal("[SS ERROR] Max Texture Materials reached per World", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::Text(
							"Max Texture Materials per World is %d (Current: %d)",
							m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->Material_MAX_TEXTURE_MATERIALS_PER_WORLD,
							static_cast<int>(m_MaterialEditorPanel_Materials_DataRequired.materialDataRequiredVec.size())
						);

						if (ImGui::Button("OK"))
						{
							ImGui::CloseCurrentPopup();
							m_MaterialEditorPanel_Materials_DataRequired.materialDataRequiredVec.resize(m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->Material_MAX_TEXTURE_MATERIALS_PER_WORLD);
							m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.b_OpenMaxTextureMaterialsPerWorld_SSERROR_DialogBox = true;
						}

						ImGui::EndPopup();
					}

					if (ImGui::BeginPopupModal("[SS ERROR] Max Custom Materials reached per World", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::Text(
							"Max Custom Materials per World is %d (Current: %d)",
							m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->Material_MAX_CUSTOM_MATERIALS_PER_WORLD,
							static_cast<int>(m_MaterialEditorPanel_Materials_DataRequired.materialDataRequiredVec.size())
						);

						if (ImGui::Button("OK"))
						{
							ImGui::CloseCurrentPopup();
							m_MaterialEditorPanel_Materials_DataRequired.materialDataRequiredVec.resize(m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->Material_MAX_CUSTOM_MATERIALS_PER_WORLD);
							m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.b_OpenMaxCustomMaterialsPerWorld_SSERROR_DialogBox = true;
						}

						ImGui::EndPopup();
					}

					if (ImGui::BeginPopupModal("[SS ERROR] Max Materials reached per World", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::Text(
							"Max Materials per World is %d (Current: %d)",
							m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->Material_MAX_OVERALL_MATERIALS_PER_WORLD,
							static_cast<int>(m_MaterialEditorPanel_Materials_DataRequired.materialDataRequiredVec.size())
						);

						if (ImGui::Button("OK"))
						{
							ImGui::CloseCurrentPopup();
							m_MaterialEditorPanel_Materials_DataRequired.materialDataRequiredVec.resize(m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->Material_MAX_OVERALL_MATERIALS_PER_WORLD);
							m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.b_OpenMaxOverallMaterialsPerWorld_SSERROR_DialogBox = true;
						}

						ImGui::EndPopup();
					}

					if (ImGui::Button("Create new Material..."))
					{
						m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.b_OpenMaterialNamePopup = true;
						if (m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.b_OpenMaterialNamePopup)
						{
							ImGui::OpenPopup("Material Name...");
							m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.b_OpenMaterialNamePopup = false; 
						}

						if (ImGui::BeginPopupModal("Material Name...", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
						{
							ImGui::InputText("Enter a Material Name...", m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.char_MaterialNamePopupBuffer,
								sizeof(m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.char_MaterialNamePopupBuffer));

							if (ImGui::IsItemDeactivatedAfterEdit())
							{
								ImGui::TextColored(ImVec4(1, 0, 0, 1), "Please enter a Material Name!");
							}

							if (ImGui::Button("OK"))
							{
								ImGui::CloseCurrentPopup();
								std::string str_NewMaterialName = m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.char_MaterialNamePopupBuffer;

								switch (m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.i_MaterialCreationTypeIndex)
								{
									case 0:
									{
										if (m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.b_HasMaterialAlreadyBeenCreated)
											break; // Material already created, no need to create again.

										m_MaterialEditorPanel_Materials_DataRequired.AddMaterial(MaterialEditorPanel_Materials_DataRequired::MaterialDataRequired::MaterialType::ColorMaterial, str_NewMaterialName);
										m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.b_HasMaterialAlreadyBeenCreated = true;
										break;
									}

									case 1:
									{
										if (m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.b_HasMaterialAlreadyBeenCreated)
											break; // Material already created, no need to create again.

										m_MaterialEditorPanel_Materials_DataRequired.AddMaterial(MaterialEditorPanel_Materials_DataRequired::MaterialDataRequired::MaterialType::TextureMaterial, str_NewMaterialName);
										m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.b_HasMaterialAlreadyBeenCreated = true;
										break;
									}

									case 2:
									{
										if (m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.b_HasMaterialAlreadyBeenCreated)
											break; // Material already created, no need to create again.

										m_MaterialEditorPanel_Materials_DataRequired.AddMaterial(MaterialEditorPanel_Materials_DataRequired::MaterialDataRequired::MaterialType::CustomMaterial, str_NewMaterialName);
										m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.b_HasMaterialAlreadyBeenCreated = true;
										break;
									}
								}
							}

							ImGui::SameLine();
							if (ImGui::Button("Cancel")) { ImGui::CloseCurrentPopup(); }
						}
					}
				}

				DrawFullEditor_Material(c_CPTR_materialTypeOptions, m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.i_MaterialCreationTypeIndex);

				return true;
			}

			bool MaterialEditorPanel::DrawFullEditor_Material(const char* materialTypeOptions[], int index)
			{
				// Data needed
				const char* c_CPTR_renderMode[] = {
					"Opaque", "Transparent", "Additive"
				};

				if (ImGui::CollapsingHeader("Material Properties"))
				{
					if (ImGui::CollapsingHeader("General"))
					{
						ImGui::Text("Current Material Name: %s", m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.ui_MaterialCreationDataRequired.char_MaterialNamePopupBuffer);
						ImGui::InputText("Material Name (Optional) ",
							m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.materialPropertiesDataRequired.general.char_MaterialNameBuffer,
							sizeof(m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.materialPropertiesDataRequired.general.char_MaterialNameBuffer)
						);

						// Render Mode dropdown
						auto& general = m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.materialPropertiesDataRequired.general;
						if (ImGui::BeginCombo("Render Mode", c_CPTR_renderMode[general.i_MaterialRenderModeIndex]))
						{
							for (int n = 0; n < IM_ARRAYSIZE(c_CPTR_renderMode); n++)
							{
								bool b_IsRenderModeOptionSelected = (general.i_MaterialRenderModeIndex == n);
								if (ImGui::Selectable(c_CPTR_renderMode[n], b_IsRenderModeOptionSelected))
									general.i_MaterialRenderModeIndex = n;

								if (b_IsRenderModeOptionSelected == true)
									ImGui::SetItemDefaultFocus();
							}
							ImGui::EndCombo();
						}

						general.RequestRenderModeSet(general.i_MaterialRenderModeIndex);

						if (ImGui::Checkbox("Receive Lighting", &general.b_ReceiveLighting)) {} // TODO: add imp
						if (ImGui::Checkbox("Two Sided Rendering", &general.b_TwoSidedRendering)) {}
						if (ImGui::Checkbox("Casts Shadows", &general.b_CastsShadows)) {}

						if (index == 0)
						{
							if (ImGui::CollapsingHeader("Color Material Properties"))
							{
								auto& colMaterial = m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.materialPropertiesDataRequired.colorMaterialProperties;

								// Color Material
								float f_materialCol[4] = {
									colMaterial.color.r,
									colMaterial.color.g,
									colMaterial.color.b,
									colMaterial.color.a,
								};

								ImGui::ColorEdit4("Material Color", f_materialCol);
								ImGui::SliderFloat("Material Intensity", &colMaterial.f_SliderIntensity, 1.0f, 5.0f);
								if (ImGui::Checkbox("Use Vertex Color", &colMaterial.b_UseVertexColor)) {} // TODO: imp
								ImGui::SliderFloat("Ambient Strength", &colMaterial.f_AmbientStrength, 0.0f, 5.0f);
								ImGui::SliderFloat("Diffuse Strength", &colMaterial.f_DiffuseStrength, 0.0f, 5.0f);

								using RenderMode = MaterialEditorPanel_Materials_DataRequired::MaterialDataRequired::UI_MaterialDataRequired::MaterialPropertiesDataRequired::General::RenderMode;
								if (general.renderMode == RenderMode::Opaque)
									ImGui::SliderFloat("Opacity", &colMaterial.f_Opacity, 0.0f, 1.0f);
							}
						}

						else if (index == 1)
						{
							if (ImGui::CollapsingHeader("Texture Material Properties"))
							{
								auto& textMaterial = m_MaterialEditorPanel_Materials_DataRequired.materialDataRequired->ui_MaterialDataRequired.materialPropertiesDataRequired.textureMaterialProperties;
								
								float colText[4] = {
									textMaterial.color.r,
									textMaterial.color.g,
									textMaterial.color.b,
									textMaterial.color.a
								};

								ImGui::InputText("Enter the path of the Texture Material: ", textMaterial.char_AssetPathBuffer, sizeof(textMaterial.char_AssetPathBuffer));
								ImGui::ColorEdit4("Texture Material Color", colText);
								ImGui::DragFloat2("Texture Tilling", &textMaterial.textureTilling[0], 0.1f);
							}
						}
					}
				}

				return true;
			}

			bool MaterialEditorPanel::DrawMaterialEditorPanel()
			{
				ImGui::Begin("Material Editor Panel");

				DrawMaterialCreation();

				ImGui::End();
				return true;
			}
		}
	}