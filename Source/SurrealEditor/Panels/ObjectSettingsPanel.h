#pragma once

#include <Engine/ECS/Object.h>
#include <Engine/SurrealRenderer/Mesh.h>

namespace SurrealStudio {

	namespace SurrealEditor {

		// TEMP CODE
		struct AdditionalObjectData
		{
			glm::vec4 color;
			bool enablePhysics = false; // enable with physics engine (LATER)

			struct Materials
			{
				const uint32_t MAX_TEXTURE_MATERIALS_PER_WORLD = 25; // Limit to 25 texture materials per World only
				const uint32_t MAX_CUSTOM_MATERIALS_PER_WORLD = 10; // Limit to 10 custom texture materials per World only
				const uint32_t MAX_COLOR_MATERIALS_PER_WORLD = 50;
				const uint32_t MAX_OVERALL_TEXTURE_MATERIALS_PER_WORLD = MAX_TEXTURE_MATERIALS_PER_WORLD + MAX_CUSTOM_MATERIALS_PER_WORLD + MAX_COLOR_MATERIALS_PER_WORLD; // Overal limit

				// ImGui indices
				int i_selectedMaterialIndex = 0;

				// Popup flags (ImGui::BeginPopupModal/OpenPopup) 
				bool b_OpenMaxTextureMaterialsPerWorld_SSERROR_DialogBox = false; // Default
				bool b_OpenMaxCustomMaterialsPerWorld_SSERROR_DialogBox = false; // Default
				bool b_OpenMaxOverallMaterialsPerWorld_SSERROR_DialogBox = false; // Default
				bool b_OpenMaxColorMaterialsPerWorld_SSERROR_DialogBox = false; // Default

				enum class MaterialType
				{
					None = 0,
					ColorMaterial,
					TextureMaterial,
					CustomMaterial
				};

				MaterialType materialType = MaterialType::None;
				
				// to ensure that in switch statement, where we set the actual type of the materials, the materials isn't created every frame
				bool hasMaterialBeenCreated = false;

				std::string name;
				int id;

				// Variables needed for Material Name popup
				bool openMaterialNamePopup = false; 
				char materialNamePopupBuffer[256] = {}; // The actual buffer/name needed for ImGui::InputText.
			};

			std::vector<std::unique_ptr<Materials>> materialsVec;
			Materials materials;
		};

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
			int objToDeleteBuffer[512];

			bool b_OpenMeshConfigurationTypePopup = true; // Open a Mesh Type Configuration popup
			// Required when creating an Object in SS.

			const std::vector<SurrealRenderer::Vertex>& vertices = {
				{
					{0.0f, 0.0f, 0.0f}, // position
					{0.0f, 0.0f, 0.0f},
					{0.0f, 0.0f}
				}
			};

			std::vector<unsigned int> indices;
			SurrealRenderer::Mesh m_Mesh = SurrealRenderer::Mesh(vertices, indices);
			
			int i_SelectedMeshConfigurationTypeIndex = 0;

			AdditionalObjectData m_AdditionalObjectData;
		};
	} 
}