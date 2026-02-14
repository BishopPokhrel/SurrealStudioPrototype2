#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include <Engine/SurrealRenderer/Shader.h>
#include <Engine/SurrealRenderer/Mesh.h>

#include "Component.h"

namespace SurrealStudio {

	namespace ECS {

		class Component;

		constexpr unsigned int MAX_OBJECTS = 5000;

		struct ObjectData
		{
			std::string name;
			int objectID;
			SurrealRenderer::Transform transform;
			SurrealRenderer::Mesh* mesh = nullptr;
			
			std::vector<std::unique_ptr<Component>> components;

			template<typename T>
			T* GetComponent()
			{
				for (auto& comp : components)
				{
					if (auto ptr = dynamic_cast<T*>(comp.get()))
						return ptr;
				}
				return nullptr;
			}
		};

		class ObjectManager
		{
		public:

			bool CreateObject(const std::string& name) noexcept;
			bool DestroyObject(const std::string& name) noexcept;

			std::string GetObject(int index) const noexcept;
			std::vector<ObjectData*> GetAllObjects()
			{
				std::vector<ObjectData*> result;
				for (auto& ptr : m_Objects)
					result.push_back(ptr.get());
				return result;
			}
			
		private:

			std::vector<std::unique_ptr<ObjectData>> m_Objects;
			ObjectData object;
		};
	}
}