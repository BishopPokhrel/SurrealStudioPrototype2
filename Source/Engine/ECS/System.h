#pragma once

#include "Component.h"

namespace SurrealStudio {

	namespace ECS {

		// Base System class; everything else inherits from this
		class System
		{
		public:

			virtual bool Update(ComponentManager& componentManager, float deltaTime) noexcept = 0;
		};

		class MovementSystem : public System
		{
		public:

			bool Update(ComponentManager& componentManager, float deltaTime) noexcept override; 
		};

		// add more systems later
	}
}