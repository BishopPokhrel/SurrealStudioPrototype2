#pragma once

#include <string>
#include <vector>

namespace SurrealStudio {

	namespace SceneGraph {

		struct NodeData
		{
			std::string name;
			size_t nextID;
			size_t mainParentID = SIZE_MAX;
			std::vector<size_t> children;
		};

		class Node
		{
		public:
			Node() = default;
			~Node() = default;
			
			void AddChild(const std::string& childName, const std::string& parentName) noexcept;
			void RemoveChild(size_t id) noexcept;

		private:

			NodeData nodeData;
		};

		class SceneGraph
		{
		public:
			SceneGraph() = default;
			~SceneGraph() = default;

			
		private:

		};
	}
}