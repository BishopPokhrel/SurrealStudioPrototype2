#include "Object.h"
#include "Component.h"

#include <iostream>

namespace SurrealStudio {

	namespace ECS {

		ObjectID ObjectManager::CreateObject(const std::string& name) noexcept
		{
			auto newObject = std::make_unique<ObjectData>();
			newObject->name = name;
			newObject->objectID = m_NextObjectID++;
			m_Objects.push_back(std::move(newObject));
			return newObject->objectID;
		}

		ObjectID ObjectManager::DestroyObject(ObjectID id) noexcept
		{
			if (m_Objects.empty())
				return 1;

			
			for (auto it = m_Objects.begin(); it != m_Objects.end(); it++)
			{
				if ((*it)->objectID == id)
				{
					m_Objects.erase(it);	
					return 0; // success
				}
			}
				
			// fail
			std::cout << "Failed to destroy Object with ID " << id;
			return false;
		}

		const std::string& ObjectManager::GetObjectNameByID(ObjectID id) const noexcept
		{
			for (const auto& obj : m_Objects)
			{
				if (obj->objectID == id)
					return obj->name;
			}

			static const std::string emptyString = "";
			return emptyString;
		}

		std::optional<ObjectID> ObjectManager::GetObjectIDByName(const std::string& name) const noexcept
		{
			for (const auto& obj : m_Objects)
			{
				if (obj->name == name)
				{
					return obj->objectID;
				}
			}

			return std::nullopt;
		}

		bool ObjectManager::RenameObject(ObjectID id, const std::string& newName) noexcept
		{
			for (auto& obj : m_Objects)
			{
				if (obj->objectID == id)
				{
					obj->name = newName;
					return true;
				}
			}

			return false;
		}
	}
}