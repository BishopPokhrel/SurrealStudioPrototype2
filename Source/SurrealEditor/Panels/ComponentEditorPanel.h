#pragma once

#include <memory>

namespace SurrealStudio::ECS {
	class ComponentManager;
}

namespace SurrealStudio {

	namespace SurrealEditor {

		struct ComponentEditorPanel_AdditonalDataNeeded
		{
			struct ComponentCreationDataNeeded
			{
				int i_ComponentCreationOptionsIndex = 0;
				bool b_OpenMaxComponentsReachedPerWorld_SSERROR_DialogBox = true;
				bool b_HasTransformComponentAlreadyBeenCreated = false; 
				bool b_HasPhysicsComponentAlreadyBeenCreated = false; 
				bool b_FlagToOpenChooseObjectForComponentToBeAChildOf_Dialog = false; 

				char char_ObjectNameInWhichComponentWillBeAChildOf_BufferRequired[512];
			};

			struct ComponentDeletionDataNeeded
			{
				char char_ObjectNameInWhichComponentIsAChildOfAndWillBeDeleted[512];
				char char_ComponentDeletionForWhichComponentTypeIsRequired[512]; // eg, Transform Component, Physics Component...
				char char_IDForComponentToBeDeleted[512];
				bool b_FlagToOpenComponentDeletionDialogBox = false; 
			};

			ComponentCreationDataNeeded componentCreationDataNeeded;
			ComponentDeletionDataNeeded componentDeletionDataNeeded;
		};

		class ComponentEditorPanel
		{
		public:

			bool DrawCompoentCreationForCEP();
			bool DrawCompoentPropertiesForCEP(const char* componentTypes[], int index);
			bool DrawComponentDeletionForCEP();
			bool DrawComponentEditorPanel();

		private:

			std::unique_ptr<ECS::ComponentManager> m_ComponentManager;
			ComponentEditorPanel_AdditonalDataNeeded m_ComponentEditorPanelAdditonalDataNeeded;
		};
	}
}