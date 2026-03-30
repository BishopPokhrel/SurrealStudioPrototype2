#pragma once

#include <cstdint> // for uint32_t
#include <string>
#include <vector>
#include <memory>

#include <glm/glm.hpp>
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

					struct MaterialPropertiesDataRequired
					{
						struct General
						{
							char char_MaterialNameBuffer[512]; // We will first display the name from the actual real material name.
							bool b_MaterialEnabled = true; // default 
							int i_MaterialRenderModeIndex = 0;

							enum class RenderMode
							{
								None = 0,
								Opaque,
								Transparent,
								Additive
							};

							RenderMode renderMode = RenderMode::None;

							// Checkboxes (all default)
							bool b_ReceiveLighting = false;
							bool b_TwoSidedRendering = false;
							bool b_CastsShadows = false;

							void RequestRenderModeSet(int index) noexcept
							{
								if (index == 0)
									renderMode = RenderMode::Opaque;
								else if (index == 1)
									renderMode = RenderMode::Transparent;
								else if (index == 2)
									renderMode = RenderMode::Additive;
								else return;
							}
						};

						struct ColorMaterialProperties
						{
							glm::vec4 color;
							float f_SliderIntensity = 1.0f;
							bool b_UseVertexColor = false; 
							float f_AmbientStrength = 0.0f;
							float f_DiffuseStrength = 0.0f;
							// ONLY IF RENDERMODE IS ONT OPAQUE
							float f_Opacity = 0.0f;
						};

						struct TextureMaterialProperties
						{
							std::string str_AssetPath = "";
							glm::vec4 color;
							glm::vec2 textureTilling;
							glm::vec2 textureOffset;
							bool b_FlipX = false;
							bool b_FlipY = false;
							enum class FilteringMode { None = 0, Nearest, Linear }; FilteringMode fileringMode = FilteringMode::None;
							bool b_MipmapsEnabled = false;
							float f_Opacticy = 0.0f;
							char char_AssetPathBuffer[1024]; 
						};

						struct CustomMaterialProperties
						{
							std::string str_CustomMaterialFilePath = "";
							std::string str_CustomMaterialName = "";
						};

						General general;
						ColorMaterialProperties colorMaterialProperties;
						TextureMaterialProperties textureMaterialProperties;
						CustomMaterialProperties customMaterialProperties;
					};

					UI_MaterialCreationDataRequired ui_MaterialCreationDataRequired;
					MaterialPropertiesDataRequired materialPropertiesDataRequired;
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

			void DeleteMaterial(const std::string& name, int id) noexcept
			{
				for (auto it = materialDataRequiredVec.begin(); it != materialDataRequiredVec.end(); it++)
				{
					if ((*it)->materialID == id && (*it)->str_MaterialName == name)
					{
						materialDataRequiredVec.erase(it);
					}
				}
			}

			void RenameMaterial(const std::string& oldName, const std::string & newName, int count = 0) noexcept
			{
				if (oldName.empty() || newName.empty()) 
					return;

				for (auto it = materialDataRequiredVec.begin(); it != materialDataRequiredVec.end(); it++)
				{
					if ((*it)->str_MaterialName == oldName)
					{
						count++;
						(*it)->str_MaterialName = newName;
						if (count >= 1) return;
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