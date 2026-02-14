#include "System.h"

#include <Engine/Logging.h>

namespace SurrealStudio {

	namespace ECS {

		bool MovementSystem::Update(ComponentManager& componentManager, float deltaTime) noexcept
		{
			for (auto* component : componentManager.GetAllComponents())
			{
				if (!component) return false;

				component->transformComponent.position.x += component->physicsComponent.velocity.x * deltaTime;
				component->transformComponent.position.y += component->physicsComponent.velocity.y * deltaTime;
				component->transformComponent.position.z += component->physicsComponent.velocity.z * deltaTime;

				component->transformComponent.rotation.x += component->physicsComponent.angularVelocity.x * deltaTime;
				component->transformComponent.rotation.y += component->physicsComponent.angularVelocity.y * deltaTime;
				component->transformComponent.rotation.z += component->physicsComponent.angularVelocity.z * deltaTime;

				component->transformComponent.scale.x += component->physicsComponent.scaleVelocity.x * deltaTime;
				component->transformComponent.scale.y += component->physicsComponent.scaleVelocity.y * deltaTime;
				component->transformComponent.scale.z += component->physicsComponent.scaleVelocity.z * deltaTime;
			}

			return true;
		}
	}
}