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

			DrawCompoentPropertiesForCEP(c_CPTR_componentTypeOptions, m_ComponentEditorPanelAdditonalDataNeeded.componentCreationDataNeeded.i_ComponentCreationOptionsIndex);

			return true;
		}

		bool ComponentEditorPanel::DrawComponentDeletionForCEP()
		{
			m_ComponentEditorPanelAdditonalDataNeeded.componentDeletionDataNeeded.b_FlagToOpenComponentDeletionDialogBox = true;
			if (m_ComponentEditorPanelAdditonalDataNeeded.componentDeletionDataNeeded.b_FlagToOpenComponentDeletionDialogBox)
			{
				ImGui::OpenPopup("Component Deletion");
				m_ComponentEditorPanelAdditonalDataNeeded.componentDeletionDataNeeded.b_FlagToOpenComponentDeletionDialogBox = false; 
			}

			if (ImGui::BeginPopupModal("Component Deletion", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::Text("Enter the Object name in which the desired Component (to be deleted) is a child of.");
				ImGui::InputText("Object Name...", m_ComponentEditorPanelAdditonalDataNeeded.componentDeletionDataNeeded.char_ObjectNameInWhichComponentIsAChildOfAndWillBeDeleted, 
					sizeof(m_ComponentEditorPanelAdditonalDataNeeded.componentDeletionDataNeeded.char_ObjectNameInWhichComponentIsAChildOfAndWillBeDeleted));

				if (ImGui::IsItemDeactivatedAfterEdit())
				{
					ImGui::TextColored(ImVec4(1, 0, 0, 1), "Please enter an Object name!");
				}

				ImGui::InputText("Component Type...", m_ComponentEditorPanelAdditonalDataNeeded.componentDeletionDataNeeded.char_ComponentDeletionForWhichComponentTypeIsRequired,
					sizeof(m_ComponentEditorPanelAdditonalDataNeeded.componentDeletionDataNeeded.char_ComponentDeletionForWhichComponentTypeIsRequired));

				if (ImGui::IsItemDeactivatedAfterEdit())
				{
					ImGui::TextColored(ImVec4(1, 0, 0, 1), "Please enter a Component Type!");
				}

				if (ImGui::Button("OK"))
				{
					ImGui::CloseCurrentPopup();
					std::string str_objectNameInWhichComponentWillBeDeleted = m_ComponentEditorPanelAdditonalDataNeeded.componentDeletionDataNeeded.char_ObjectNameInWhichComponentIsAChildOfAndWillBeDeleted;
					std::string str_ComponentTypeInWhichComponentWillBeDeleted = m_ComponentEditorPanelAdditonalDataNeeded.componentDeletionDataNeeded.char_ComponentDeletionForWhichComponentTypeIsRequired;

					if (str_ComponentTypeInWhichComponentWillBeDeleted == "Transform Component")
					{
						m_ComponentManager.transformComponentManager.DeleteTransformComponent(str_objectNameInWhichComponentWillBeDeleted);
					}

					else if (str_ComponentTypeInWhichComponentWillBeDeleted == "Physics Component")
					{
						m_ComponentManager.physicsComponentManager.DeletePhysicsComponent(str_objectNameInWhichComponentWillBeDeleted);
					}
				}

				ImGui::SameLine();
				if (ImGui::Button("Cancel"))
					ImGui::CloseCurrentPopup();

				ImGui::EndPopup();
			}

			return true;
		}

		bool ComponentEditorPanel::DrawCompoentPropertiesForCEP(const char* componentOptions[], int index)
		{
			if (!componentOptions || index < 0 || index >= 2)
				return false; // Out of bounds

			ECS::Component* componentData = m_ComponentManager.m_Components[index].get();
			if (!componentData)
				return false; // not valid

			if (index == 0)
			{
				// Transform Component
				ImGui::DragFloat3("Position:", &componentData->transformComponent.position[0], 0.1f);
				ImGui::DragFloat3("Rotation:", &componentData->transformComponent.rotation[0], 0.1f);
				ImGui::DragFloat3("Scale:", &componentData->transformComponent.scale[0], 0.1f);
			}

			else if (index == 1)
			{
				// Physics Component
				ImGui::DragFloat3("Velocity", &componentData->physicsComponent.velocity[0], 0.1f);
				ImGui::DragFloat3("Angluar Velocity", &componentData->physicsComponent.angularVelocity[0], 0.1f);
				ImGui::DragFloat3("Scale Velocity", &componentData->physicsComponent.scaleVelocity[0], 0.1f);
			}

			return true;
		}

		bool ComponentEditorPanel::DrawComponentEditorPanel()
		{
			ImGui::Begin("Component Editor Panel");

			DrawCompoentCreationForCEP();
			if (ImGui::Button("Delete Component..."))
				DrawComponentDeletionForCEP();

			ImGui::End();
			return true;
		}
	}
}