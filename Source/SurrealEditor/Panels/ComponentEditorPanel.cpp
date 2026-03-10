#include "ComponentEditorPanel.h"

#include <imgui.h>

namespace SurrealStudio {

	namespace SurrealEditor {

		bool ComponentEditorPanel::DrawCompoentCreationForCEP()
		{
			const char* c_CPTR_componentTypeOptions[] = {
				"Transform Component", "Physics Component"
			};

			if (ImGui::CollapsingHeader("Component Creation"))
			{
				if (ImGui::BeginCombo("Component Types", c_CPTR_componentTypeOptions[m_ComponentEditorPanelAdditonalDataNeeded.componentCreationDataNeeded.i_ComponentCreationOptionsIndex]))
				{
					for (int n = 0; n < IM_ARRAYSIZE(c_CPTR_componentTypeOptions); n++)
					{
						bool b_IsComponentTypeSelected = (m_ComponentEditorPanelAdditonalDataNeeded.componentCreationDataNeeded.i_ComponentCreationOptionsIndex == n);
						if (ImGui::Selectable(c_CPTR_componentTypeOptions[n], b_IsComponentTypeSelected))
							m_ComponentEditorPanelAdditonalDataNeeded.componentCreationDataNeeded.i_ComponentCreationOptionsIndex = n;

						if (b_IsComponentTypeSelected == true)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}

				if (m_ComponentManager.m_Components.size() > (size_t)ECS::MAX_COMPONENTS_PER_WORLD && m_ComponentEditorPanelAdditonalDataNeeded.componentCreationDataNeeded.b_OpenMaxComponentsReachedPerWorld_SSERROR_DialogBox == true)
				{
					ImGui::OpenPopup("[SS ERROR] Max Components reached per World!");
					m_ComponentEditorPanelAdditonalDataNeeded.componentCreationDataNeeded.b_OpenMaxComponentsReachedPerWorld_SSERROR_DialogBox = false;
				}

				if (ImGui::BeginPopupModal("[SS ERROR] Max Components reached per World!", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text("Max amount of Components per World is %d, got %d.", (int)ECS::MAX_COMPONENTS_PER_WORLD, static_cast<int>(m_ComponentManager.m_Components.size()));
					if (ImGui::Button("OK")) {
						ImGui::CloseCurrentPopup();
					}
				}

				if (ImGui::Button("Create Component"))
				{
					m_ComponentEditorPanelAdditonalDataNeeded.componentCreationDataNeeded.b_FlagToOpenChooseObjectForComponentToBeAChildOf_Dialog = true;
					if (m_ComponentEditorPanelAdditonalDataNeeded.componentCreationDataNeeded.b_FlagToOpenChooseObjectForComponentToBeAChildOf_Dialog)
					{
						ImGui::OpenPopup("Choose a Object for the Component to Be a child of...");
						m_ComponentEditorPanelAdditonalDataNeeded.componentCreationDataNeeded.b_FlagToOpenChooseObjectForComponentToBeAChildOf_Dialog = false;
					}

					if (ImGui::BeginPopupModal("Choose a Object for the Component to Be a child of...", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
					{
						ImGui::InputText("Object Name...", m_ComponentEditorPanelAdditonalDataNeeded.componentCreationDataNeeded.char_ObjectNameInWhichComponentWillBeAChildOf_BufferRequired,
							sizeof(m_ComponentEditorPanelAdditonalDataNeeded.componentCreationDataNeeded.char_ObjectNameInWhichComponentWillBeAChildOf_BufferRequired));

						if (ImGui::IsItemDeactivatedAfterEdit())
						{
							ImGui::TextColored(ImVec4(1, 0, 0, 1), "Please enter a Object Name!");
						}

						if (ImGui::Button("OK"))
						{
							ImGui::CloseCurrentPopup();
							std::string objectNameToBeAChildOfNewComponent = m_ComponentEditorPanelAdditonalDataNeeded.componentCreationDataNeeded.char_ObjectNameInWhichComponentWillBeAChildOf_BufferRequired;
							switch (m_ComponentEditorPanelAdditonalDataNeeded.componentCreationDataNeeded.i_ComponentCreationOptionsIndex)
							{
								case 0:
								{
									if (m_ComponentEditorPanelAdditonalDataNeeded.componentCreationDataNeeded.b_HasTransformComponentAlreadyBeenCreated)
										break; // Transform Component already created, no need to make the component again 

									m_ComponentManager.transformComponentManager.AddTransformComponent(objectNameToBeAChildOfNewComponent, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
									m_ComponentEditorPanelAdditonalDataNeeded.componentCreationDataNeeded.b_HasTransformComponentAlreadyBeenCreated = true;
									break;
								}

								case 1:
								{
									if (m_ComponentEditorPanelAdditonalDataNeeded.componentCreationDataNeeded.b_HasPhysicsComponentAlreadyBeenCreated)
										break; // Transform Component already created, no need to make the component again.

									m_ComponentManager.physicsComponentManager.AddPhysicsComponent(objectNameToBeAChildOfNewComponent, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
									m_ComponentEditorPanelAdditonalDataNeeded.componentCreationDataNeeded.b_HasPhysicsComponentAlreadyBeenCreated = true;
									break;
								}
							}
						}

						ImGui::SameLine();
						if (ImGui::Button("Cancel"))
						{
							ImGui::CloseCurrentPopup();
						}

						ImGui::EndPopup();
					}
				}
			}

			return true;
		}

		bool ComponentEditorPanel::DrawComponentDeletionForCEP()
		{
			return true;
		}

		bool ComponentEditorPanel::DrawCompoentPropertiesForCEP()
		{
			return true;
		}

		bool ComponentEditorPanel::DrawComponentEditorPanel()
		{
			return true;
		}
	}
}