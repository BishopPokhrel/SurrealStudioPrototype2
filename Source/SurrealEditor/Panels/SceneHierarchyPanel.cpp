#include "SceneHierarchyPanel.h"

#include <imgui.h>

namespace SurrealStudio {
	
	namespace SurrealEditor {

		bool SceneHierarchyPanel::DrawSceneHierarchy()
		{
			return true; 
		}

		bool SceneHierarchyPanel::DrawCommandPalette()
		{
			if (m_OpenCommandPalttleDialogBox)
			{
				ImGui::OpenPopup("Command Palette");
				m_OpenCommandPalttleDialogBox = false;
			}

			if (ImGui::BeginPopupModal("Command Palette", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
			{
				if (ImGui::BeginMenu("Add..."))
				{
					if (ImGui::MenuItem("Add Object"))
					{
						if (m_ObjectManager.m_Objects.size() > ECS::MAX_OBJECTS && m_SceneHierarchyPanelAdditionalDataNeeded.objectDataNeeded.openMaxObjectsReached_PerWorld_SSERROR_DialogBox_SHP)
						{
							ImGui::OpenPopup("[SS ERROR] Max amount of Objects reached per World");
							m_SceneHierarchyPanelAdditionalDataNeeded.objectDataNeeded.openMaxObjectsReached_PerWorld_SSERROR_DialogBox_SHP = false;
						}

						if (ImGui::BeginPopupModal("[SS ERROR] Max amount of Objects reached per World", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
						{
							ImGui::Text("Max amount of Objects per World is %d, got %d.", ECS::MAX_OBJECTS, static_cast<int>(m_ObjectManager.m_Objects.size()));

							if (ImGui::Button("OK")) {
								ImGui::CloseCurrentPopup();
								m_ObjectManager.m_Objects.resize((size_t)ECS::MAX_OBJECTS); // Clamp to the max value ig
								m_SceneHierarchyPanelAdditionalDataNeeded.objectDataNeeded.openAddObjectNamePopupDialogBox = true; // Reset
							}
							ImGui::EndPopup();
						}

						m_SceneHierarchyPanelAdditionalDataNeeded.objectDataNeeded.openAddObjectNamePopupDialogBox = true; 
						if (m_SceneHierarchyPanelAdditionalDataNeeded.objectDataNeeded.openAddObjectNamePopupDialogBox)
						{
							ImGui::OpenPopup("Object Name...");
							m_SceneHierarchyPanelAdditionalDataNeeded.objectDataNeeded.openAddObjectNamePopupDialogBox = false;
						}

						if (ImGui::BeginPopupModal("Object Name...", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
						{
							ImGui::InputText("Enter the Object Name...",
								m_SceneHierarchyPanelAdditionalDataNeeded.objectDataNeeded.objToAdd_NameRequiredBuffer,
								sizeof(m_SceneHierarchyPanelAdditionalDataNeeded.objectDataNeeded.objToAdd_NameRequiredBuffer));

							if (ImGui::Button("OK"))
							{
								ImGui::CloseCurrentPopup();
								std::string objectName = m_SceneHierarchyPanelAdditionalDataNeeded.objectDataNeeded.objToAdd_NameRequiredBuffer;
								m_ObjectManager.CreateObject(objectName);
							}

							if (ImGui::Button("Cancel"))
							{
								ImGui::CloseCurrentPopup();
							}

							ImGui::EndPopup();
						}
					}

					if (ImGui::BeginMenu("Add Component"))
					{
						if (ImGui::MenuItem("Add Transform Component"))
						{
							m_SceneHierarchyPanelAdditionalDataNeeded.componentDataNeeded.initalTransformComponentPropertiesToBeFilled = true; 
							if (m_SceneHierarchyPanelAdditionalDataNeeded.componentDataNeeded.initalTransformComponentPropertiesToBeFilled)
							{
								ImGui::OpenPopup("Initial Transform Component Properties");
								m_SceneHierarchyPanelAdditionalDataNeeded.componentDataNeeded.initalTransformComponentPropertiesToBeFilled = false;
							}

							if (ImGui::BeginPopupModal("Initial Transform Component Properties", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
							{
								ImGui::InputText("Object Name (which Object the Component should be a child of)", 
									m_SceneHierarchyPanelAdditionalDataNeeded.componentDataNeeded.objectNameRequiredForComponentCreation, 
									sizeof(m_SceneHierarchyPanelAdditionalDataNeeded.componentDataNeeded.objectNameRequiredForComponentCreation));

								if (ImGui::Button("OK"))
								{
									ImGui::CloseCurrentPopup();
									std::string objectNameForTransformComponentToBeChildOfObject = m_SceneHierarchyPanelAdditionalDataNeeded.componentDataNeeded.objectNameRequiredForComponentCreation;
									m_ComponentManager.transformComponentManager.AddTransformComponent(objectNameForTransformComponentToBeChildOfObject, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, {0.0f, 0.0f, 0.0f});
								}

								if (ImGui::Button("Cancel"))
								{
									ImGui::CloseCurrentPopup();
								}
								ImGui::EndPopup();
							}
						}

						if (ImGui::MenuItem("Add Physics Component"))
						{
							m_SceneHierarchyPanelAdditionalDataNeeded.componentDataNeeded.initalPhysicsComponentPropertiesToBeFilled = true;
							if (m_SceneHierarchyPanelAdditionalDataNeeded.componentDataNeeded.initalPhysicsComponentPropertiesToBeFilled)
							{
								ImGui::OpenPopup("Initial Physics Component Properties");
								m_SceneHierarchyPanelAdditionalDataNeeded.componentDataNeeded.initalPhysicsComponentPropertiesToBeFilled = false; 
							}

							if (ImGui::BeginPopupModal("Initial Physics Component Properties", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
							{
								ImGui::InputText("Object Name (which Object the Component should be a child of)",
									m_SceneHierarchyPanelAdditionalDataNeeded.componentDataNeeded.objectNameRequiredForComponentCreation,
									sizeof(m_SceneHierarchyPanelAdditionalDataNeeded.componentDataNeeded.objectNameRequiredForComponentCreation));

								if (ImGui::Button("OK"))
								{
									ImGui::CloseCurrentPopup();
									std::string objectNameForPhysicsComponentToBeChildOfObject = m_SceneHierarchyPanelAdditionalDataNeeded.componentDataNeeded.objectNameRequiredForComponentCreation;
									m_ComponentManager.physicsComponentManager.AddPhysicsComponent(objectNameForPhysicsComponentToBeChildOfObject, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
								}

								if (ImGui::Button("Cancel"))
								{
									ImGui::CloseCurrentPopup();
								}
								ImGui::EndPopup();
							}
						}

						ImGui::EndMenu();
					}

					if (ImGui::MenuItem("Add Subscene"))
					{
						m_SceneHierarchyPanelAdditionalDataNeeded.subsceneAndWorldDataNeeded.openSubsceneNamePopup_NeededForSubsceneCreation = true;
						if (m_SceneHierarchyPanelAdditionalDataNeeded.subsceneAndWorldDataNeeded.openSubsceneNamePopup_NeededForSubsceneCreation)
						{
							ImGui::OpenPopup("Subscene Name");
							m_SceneHierarchyPanelAdditionalDataNeeded.subsceneAndWorldDataNeeded.openSubsceneNamePopup_NeededForSubsceneCreation = false; 
						}

						if (ImGui::BeginPopupModal("Subscene Name", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) 
						{
							ImGui::InputText("Enter the Subscene name...",
								m_SceneHierarchyPanelAdditionalDataNeeded.subsceneAndWorldDataNeeded.subsceneNameRequiredForSubsceneCreationBuffer,
								sizeof(m_SceneHierarchyPanelAdditionalDataNeeded.subsceneAndWorldDataNeeded.subsceneNameRequiredForSubsceneCreationBuffer));

							if (ImGui::Button("OK"))
							{
								ImGui::CloseCurrentPopup();
								std::string newSubsceneName = m_SceneHierarchyPanelAdditionalDataNeeded.subsceneAndWorldDataNeeded.subsceneNameRequiredForSubsceneCreationBuffer;
								m_Subscene.AddSubscene(newSubsceneName);
							}

							if (ImGui::Button("Cancel"))
							{
								ImGui::CloseCurrentPopup();
							}
							ImGui::EndPopup();
						}
					}

					if (ImGui::MenuItem("Add World"))
					{
						m_SceneHierarchyPanelAdditionalDataNeeded.subsceneAndWorldDataNeeded.openWorldNamePopup_NeededForWorldCreation = true;
						if (m_SceneHierarchyPanelAdditionalDataNeeded.subsceneAndWorldDataNeeded.openWorldNamePopup_NeededForWorldCreation)
						{
							ImGui::OpenPopup("World Name");
							m_SceneHierarchyPanelAdditionalDataNeeded.subsceneAndWorldDataNeeded.openWorldNamePopup_NeededForWorldCreation = false;
						}

						if (ImGui::BeginPopupModal("World Name", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
						{
							ImGui::InputText("Enter the World name...",
								m_SceneHierarchyPanelAdditionalDataNeeded.subsceneAndWorldDataNeeded.worldNameRequiredForWorldCreationBuffer,
								sizeof(m_SceneHierarchyPanelAdditionalDataNeeded.subsceneAndWorldDataNeeded.worldNameRequiredForWorldCreationBuffer));

							if (ImGui::Button("OK"))
							{
								ImGui::CloseCurrentPopup();
								std::string newWorldName = m_SceneHierarchyPanelAdditionalDataNeeded.subsceneAndWorldDataNeeded.worldNameRequiredForWorldCreationBuffer;
								m_World.AddWorld(newWorldName);
							}
							ImGui::EndPopup();
						}
					}

					if (ImGui::MenuItem("Rename Object"))
					{
						m_SceneHierarchyPanelAdditionalDataNeeded.objectDataNeeded.openRenameObjectPopupDialogBox = true;
						if (m_SceneHierarchyPanelAdditionalDataNeeded.objectDataNeeded.openRenameObjectPopupDialogBox)
						{
							ImGui::OpenPopup("Rename Object");
							m_SceneHierarchyPanelAdditionalDataNeeded.objectDataNeeded.openRenameObjectPopupDialogBox = false; 
						}

						if (ImGui::BeginPopupModal("Rename Object", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
						{
							ImGui::InputText("Old Object Name...",
								m_SceneHierarchyPanelAdditionalDataNeeded.objectDataNeeded.oldObjName_RenameObject_RequiredNameBuffer,
								sizeof(m_SceneHierarchyPanelAdditionalDataNeeded.objectDataNeeded.oldObjName_RenameObject_RequiredNameBuffer));

							if (ImGui::IsItemDeactivatedAfterEdit())
							{
								ImGui::TextColored(ImVec4(1, 0, 0, 1), "Please enter the old Object Name!");
							}

							ImGui::InputText("Object Name...",
								m_SceneHierarchyPanelAdditionalDataNeeded.objectDataNeeded.objToRename_RequiredNameBuffer, sizeof(m_SceneHierarchyPanelAdditionalDataNeeded.objectDataNeeded.objToRename_RequiredNameBuffer));

							if (ImGui::IsItemDeactivatedAfterEdit())
							{
								ImGui::TextColored(ImVec4(1, 0, 0, 1), "Please enter a Object Name!");
							}

							if (ImGui::Button("OK"))
							{
								ImGui::CloseCurrentPopup();
								std::string newRenamedObject = m_SceneHierarchyPanelAdditionalDataNeeded.objectDataNeeded.objToRename_RequiredNameBuffer;
								std::string oldRenamedObject = m_SceneHierarchyPanelAdditionalDataNeeded.objectDataNeeded.oldObjName_RenameObject_RequiredNameBuffer; // to get the actual id of it
								auto oldObjectIDOpt = m_ObjectManager.GetObjectIDByName(oldRenamedObject);

								if (oldObjectIDOpt)
								{
									ECS::ObjectID oldObjectID = *oldObjectIDOpt;
									m_ObjectManager.RenameObject(oldObjectID, newRenamedObject);
								}
								else
								{
									ImGui::TextColored(ImVec4(1, 0, 0, 1), "Object not found!");
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

					ImGui::EndMenu();
				}
				ImGui::EndPopup();
			}

			return true;
		}

		bool SceneHierarchyPanel::DrawSceneHierarchyPanel()
		{
			ImGui::Begin("Scene Hierarchy Panel");

			DrawSceneHierarchy();
			DrawCommandPalette();

			ImGui::End();
			return true;
		}
	}
}