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

		using ObjectID = uint64_t;

		class Component;

		constexpr unsigned int MAX_OBJECTS = 5000;

		struct ObjectData
		{
			std::string name;
			int objectID;
			SurrealRenderer::Transform transform;
			std::shared_ptr<SurrealRenderer::Mesh> mesh = nullptr;
			
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

			enum class ObjectType
			{
				None = 0,
				Cube,
				Sphere,
				Capsule,
				Plane,
				Mesh
			};

			ObjectType objectType = ObjectType::None;
			bool SetObjectType(ObjectType type) noexcept
			{
				objectType = type;
				return true;
			}
		};

		class ObjectManager
		{
		public:

			ObjectID CreateObject(const std::string& name) noexcept;
			ObjectID DestroyObject(ObjectID id) noexcept;

			const std::string& GetObjectNameByID(ObjectID id) const noexcept;
			std::vector<ObjectData*> GetAllObjects()
			{
				std::vector<ObjectData*> result;
				for (auto& ptr : m_Objects)
					result.push_back(ptr.get());
				return result;
			}

			ObjectData* GetObjectPtr(int index) noexcept
			{
				if (index < 0 || index >= static_cast<int>(m_Objects.size()))
					return nullptr;

				return m_Objects[index].get();
			}

			int GetObjectCount() const noexcept
			{
				return static_cast<int>(m_Objects.size());
			}

			std::vector<std::unique_ptr<ObjectData>> m_Objects;

		private:

			ObjectData object;
			int m_NextObjectID = 1;
		};
	}
}