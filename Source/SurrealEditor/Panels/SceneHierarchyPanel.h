#pragma once

#include <Engine/InputSystem.h>
#include <Engine/ECS/Object.h>
#include <Engine/ECS/Component.h>

#include <Engine/Scene/Subscene.h>
#include <Engine/Scene/World.h>

namespace SurrealStudio {

	namespace SurrealEditor {

		struct SceneHierarchyPanelAdditionalDataNeeded
		{
			// Buffer needed for ImGui::InputText (Add Object, ImGui::MenuItem())
			struct ObjectDataNeeded
			{
				char objToAdd_NameRequiredBuffer[512];
				bool openAddObjectNamePopupDialogBox = false; // To open an ImGui popup to add a name for the Object.
				bool openMaxObjectsReached_PerWorld_SSERROR_DialogBox_SHP = false; // To prevent mulitple variables having the same name
			};

			struct ComponentDataNeeded
			{
				char objectNameRequiredForComponentCreation[512]; // To ensure that a Component is at least a child of an Object.
				bool initalTransformComponentPropertiesToBeFilled = false; 
				bool initalPhysicsComponentPropertiesToBeFilled = false; 
			};

			struct SubsceneAndWorldDataNeeded
			{
				char subsceneNameRequiredForSubsceneCreationBuffer[512];
				char worldNameRequiredForWorldCreationBuffer[512];

				bool openSubsceneNamePopup_NeededForSubsceneCreation = false; 
				bool openWorldNamePopup_NeededForWorldCreation = false; 
			};

			SubsceneAndWorldDataNeeded subsceneAndWorldDataNeeded;
			ComponentDataNeeded componentDataNeeded;
			ObjectDataNeeded objectDataNeeded;
		};

		class SceneHierarchyPanel
		{
		public:

			bool DrawSceneHierarchy();
			bool DrawCommandPalette();  // Trigged when right clicked
			bool DrawSceneHierarchyPanel();

		private:

			SceneHierarchyPanelAdditionalDataNeeded m_SceneHierarchyPanelAdditionalDataNeeded;
			InputSystem m_InputSystem;
			GLFWwindow* m_Window; 

			bool m_OpenCommandPalttleDialogBox = false; 

			// ECS/Scene System classes instances
			ECS::ObjectData m_ObjectData; 
			ECS::ObjectManager m_ObjectManager;
			ECS::ComponentManager m_ComponentManager;

			SceneSystem::Subscene m_Subscene;
			SceneSystem::World m_World;
			SceneSystem::WorldData m_WorldData;
		};
	}
}