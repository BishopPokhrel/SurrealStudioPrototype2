#pragma once

#include <Engine/ECS/Component.h>

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

			ComponentCreationDataNeeded componentCreationDataNeeded;
		};

		class ComponentEditorPanel
		{
		public:

			bool DrawCompoentCreationForCEP();
			bool DrawCompoentPropertiesForCEP();
			bool DrawComponentDeletionForCEP();
			bool DrawComponentEditorPanel();

		private:

			ECS::ComponentManager m_ComponentManager;
			ComponentEditorPanel_AdditonalDataNeeded m_ComponentEditorPanelAdditonalDataNeeded;
		};
	}
}