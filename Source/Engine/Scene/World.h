#pragma once

#include <string>
#include <memory>
#include <vector>

#include <Engine/ECS/Object.h>

namespace SurrealStudio {

	namespace SceneSystem {

		struct WorldData
		{
			std::string worldName;
			std::vector<std::unique_ptr<ECS::ObjectData>> objectsInWorld;
		};

		class World
		{
		public:

			World() = default;
			~World() = default;

			bool AddWorld(const std::string& name) noexcept;
			bool DeleteWorld(const std::string& name) noexcept;

			std::vector<WorldData*> GetAllWorlds()
			{
				std::vector<WorldData*> result;
				for (auto& ptr : m_Worlds)
					result.push_back(ptr.get());
				return result;
			}


		private:
			
			WorldData worldData;
			std::vector<std::unique_ptr<WorldData>> m_Worlds;
		};
	}
}