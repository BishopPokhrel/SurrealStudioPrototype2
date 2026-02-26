#pragma once

#include <Engine/ECS/Object.h>
#include <Engine/SurrealRenderer/Mesh.h>

namespace SurrealStudio {

	namespace SurrealEditor {

		class ObjectSettingsPanel
		{
		public:

			bool DrawObjectCreation();
			bool DrawObjectProperties(const char* objectOptions[], int index);
			bool DrawRemoveObject();
			bool DrawObjectSettingsPanel();

		private:

			ECS::ObjectData m_SelectedObjectData;
			ECS::ObjectManager m_ObjectManager;
		
			// ImGui state variables
			// Indices needed
			int i_selectedObjectIndex = 0;

			// ImGui popup state variables needed for max popup limits
			bool b_OpenMaxObjectsReachedPerWorld_SSERROR_DialogBox = false; // So that the popup doesn't randomly open at times when the max amount of objects per world hasn't reached yet

			// Popup state variables for object deletion confirmation
			bool b_OpenObjectDeletionConfirmation_SSERROR_DialogBox = false; // So that the popup doesn't randomly open at times when the user doesn't want to delete an object

			// buffer to add the name for deletion of object
			char objToDeleteBuffer[512];

			bool b_OpenMeshConfigurationTypePopup = true; // Open a Mesh Type Configuration popup
			// Required when creating an Object in SS.

			SurrealRenderer::Mesh m_Mesh;
			
			int i_SelectedMeshConfigurationTypeIndex = 0;
		};
	} 
}