#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace SurrealStudio {

	namespace SceneGraph {

		struct NodeData
		{
			std::string name;
			size_t id;
			size_t mainParentID = SIZE_MAX;
			std::vector<size_t> children;
		};

		class Node
		{
		public:

			void AddChild(const std::string& childName, int mainParentID) noexcept;
			void RemoveChild(size_t id) noexcept;
		
		private:

			NodeData m_NodeData;
			size_t nextID;
			std::vector<NodeData> m_NodeDataVec;
			friend class SceneGraph;
		};

		class SceneGraph
		{
		public:
			SceneGraph() = default;
			~SceneGraph() = default;

			void AddNode(const std::string& name, size_t parentID) noexcept;
			void RemoveNode(size_t id) noexcept;
			Node* GetNode(size_t id) noexcept;
			void Transverse(size_t id) noexcept;
			int FindNodeIDByName(const std::string& name) const noexcept;
			void RenameNode(const std::string& name, size_t id) noexcept;
		private:

			std::unordered_map<size_t, Node> m_Nodes;
			size_t m_NextID;
			Node m_Node;
		};
	}
} 