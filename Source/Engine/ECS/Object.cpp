#include "Object.h"
#include "Component.h"

#include <iostream>

namespace SurrealStudio {

	namespace ECS {

		bool ObjectManager::CreateObject(const std::string& name) noexcept
		{
			auto newObject = std::make_unique<ObjectData>();
			newObject->name = name;
			newObject->objectID = m_NextObjectID++;
			m_Objects.push_back(std::move(newObject));
			return true;
		}

		bool ObjectManager::DestroyObject(const std::string& name) noexcept
		{
			if (m_Objects.empty())
				return false;
			
			for (auto it = m_Objects.begin(); it != m_Objects.end(); it++)
			{
				if ((*it)->name == name)
				{
					m_Objects.erase(it);	
					return true; // success
				}
			}

			// fail
			std::cout << "Failed to destroy Object " << name << ".\n";
			return false;
		}

		std::string ObjectManager::GetObject(int index) const noexcept
		{
			if (index < 0 || index >= static_cast<int>(m_Objects.size()))
				return ""; // invalid ID

			return m_Objects[index]->name;
		}
	}
}