#pragma once

#include <cstdint> // for uint32_t
#include <string>
#include <vector>
#include <memory>

#include <Engine/Logging.h>

namespace SurrealStudio {

	namespace SurrealEditor {

		// TEMP CODE (TODO: REPLACE LATER)
		struct MaterialEditorPanel_Materials_DataRequired
		{
			struct MaterialDataRequired
			{
				// For ImGui -> UI_MaterialDataRequired
				struct UI_MaterialDataRequired
				{
					struct UI_MaterialCreationDataRequired
					{
						int i_MaterialCreationTypeIndex = 0;

						// Popup flags (ImGui::BeginPopupModal/OpenPopup) 
						bool b_OpenMaxTextureMaterialsPerWorld_SSERROR_DialogBox = false; // Default
						bool b_OpenMaxCustomMaterialsPerWorld_SSERROR_DialogBox = false; // Default
						bool b_OpenMaxOverallMaterialsPerWorld_SSERROR_DialogBox = false; // Default
						bool b_OpenMaxColorMaterialsPerWorld_SSERROR_DialogBox = false; // Default
						bool b_OpenMaterialNamePopup = false;
						char char_MaterialNamePopupBuffer[512];
						bool b_HasMaterialAlreadyBeenCreated = false; 
					};

					UI_MaterialCreationDataRequired ui_MaterialCreationDataRequired;
				};

				// const ints
				const uint32_t Material_MAX_COLOR_MATERIALS_PER_WORLD = 50;
				const uint32_t Material_MAX_TEXTURE_MATERIALS_PER_WORLD = 25;
				const uint32_t Material_MAX_CUSTOM_MATERIALS_PER_WORLD = 10;
				const uint32_t Material_MAX_OVERALL_MATERIALS_PER_WORLD = Material_MAX_COLOR_MATERIALS_PER_WORLD + Material_MAX_TEXTURE_MATERIALS_PER_WORLD + Material_MAX_CUSTOM_MATERIALS_PER_WORLD;

				std::string str_MaterialName;
				int materialID;

				enum class MaterialType
				{
					None = 0,
					ColorMaterial,
					TextureMaterial,
					CustomMaterial
				};

				MaterialType materialType;
				UI_MaterialDataRequired ui_MaterialDataRequired;
			};

			std::unique_ptr<MaterialDataRequired> materialDataRequired;
			std::vector<std::unique_ptr<MaterialDataRequired>> materialDataRequiredVec;

			void AddMaterial(const MaterialDataRequired::MaterialType& type, const std::string& name) noexcept
			{
				auto newMaterial = std::make_unique<MaterialDataRequired>();
				newMaterial->str_MaterialName = name;
				newMaterial->materialType = type;
				newMaterial->materialID = nextMaterialID++;
				materialDataRequiredVec.push_back(std::move(newMaterial));
			}

			void DeleteMaterial(const std::string& name, int id)
			{
				for (auto it = materialDataRequiredVec.begin(); it != materialDataRequiredVec.end(); it++)
				{
					if ((*it)->materialID == id && (*it)->str_MaterialName == name)
					{
						materialDataRequiredVec.erase(it);
					}
				}
			}

			uint32_t nextMaterialID = 0;
		};

		class MaterialEditorPanel
		{
		public:

			bool DrawMaterialEditorPanel();
			bool DrawMaterialCreation();
			bool DrawFullEditor_Material(const char* materialTypeOptions[], int index);

		private:

			MaterialEditorPanel_Materials_DataRequired m_MaterialEditorPanel_Materials_DataRequired;
		};
	}
}