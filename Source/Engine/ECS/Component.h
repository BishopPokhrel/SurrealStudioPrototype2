#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <string>

namespace SurrealStudio {

	namespace ECS {

		constexpr uint32_t MAX_COMPONENTS_PER_WORLD = 10000;

		struct ObjectData;

		struct ComponentMain
		{
			virtual ~ComponentMain() = default;
		};

		// Example Component
		struct TransformComponent : public ComponentMain
		{
			glm::vec3 position;
			glm::vec3 rotation;
			glm::vec3 scale;

			std::string objectName; // to which object does it belong to 

		private:

			int index;
		};

		struct PhysicsComponent : public ComponentMain
		{
			glm::vec3 velocity;
			glm::vec3 angularVelocity;
			glm::vec3 scaleVelocity;

			std::string objectName; // to which object does it belong to

		private:

			int index;
		};

		class TransformComponentManager
		{
		public:

			bool AddTransformComponent(const std::string& objectName,glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) noexcept;
			bool DeleteTransformComponent(const std::string& objectName) noexcept;
			
			std::vector<TransformComponent*> GetAllTransformComponents() const noexcept
			{
				std::vector<TransformComponent*> result;
				for (auto& ptr : m_TransformComponents)
					result.push_back(ptr.get());
				return result;
			}
			
		private:

			std::vector<std::unique_ptr<TransformComponent>> m_TransformComponents;
			friend struct TransformComponent;
		};

		class PhysicsComponentManager
		{
		public:

			bool AddPhysicsComponent(const std::string& objectName, glm::vec3 velocity, glm::vec3 angularVelocity, glm::vec3 scaleVelocity) noexcept;
			bool DeletePhysicsComponent(const std::string& objectName) noexcept;
			std::vector<PhysicsComponent*> GetAllPhysicsComponents() const noexcept
			{
				std::vector<PhysicsComponent*> result;
				for (auto& ptr : m_PhysicsComponents)
					result.push_back(ptr.get());
				return result;
			}

		private:

			std::vector<std::unique_ptr<PhysicsComponent>> m_PhysicsComponents;
			friend struct PhysicsComponent;
		};

		// Central Component hub, where all the components live, NOT ComponentManager(s)
		class Component
		{
		public:

			TransformComponent transformComponent;
			PhysicsComponent physicsComponent;
		};

		// Central Component Manager 'hub'
		class ComponentManager
		{
		public:

			TransformComponentManager transformComponentManager;
			PhysicsComponentManager physicsComponentManager;
			// other components if needed.	

			std::vector<Component*> GetAllComponents() const noexcept
			{
				std::vector<Component*> compPtrs;
				for (auto& component : m_Components)
					compPtrs.push_back(component.get());
				return compPtrs;
			}

		private:

			std::vector<std::unique_ptr<Component>> m_Components;
		};
	}
}