#include "SceneGraph.h"

#include <algorithm>
#include <iostream>

namespace SurrealStudio {

	namespace SceneGraph {

		void Node::AddChild(const std::string& childName, int mainParentID) noexcept
		{
			NodeData nodeData;
			nodeData.name = childName;
			nodeData.mainParentID = mainParentID;
			nodeData.id = nextID++;
			m_NodeDataVec.push_back(nodeData);
		}

		void Node::RemoveChild(size_t id) noexcept
		{
			for (auto it = m_NodeDataVec.begin(); it != m_NodeDataVec.end(); it++)
			{
				if (it->id == id)
				{
					m_NodeDataVec.erase(it);
					break;
				}
				else continue;
			}
		}

		void SceneGraph::AddNode(const std::string& name, size_t parentID) noexcept
		{
			Node node;
			node.m_NodeData.name = name;
			node.m_NodeData.children = {};
			node.m_NodeData.mainParentID = parentID;
			node.m_NodeData.id = m_NextID++;
			m_Nodes[parentID] = node;

			if (parentID >= 1) // if parentID is 0, then that means there is no parent. I
			{
				for (auto& [nodeID, nodeObj] : m_Nodes)
				{
					if (nodeID == parentID) continue;
					m_Nodes[parentID].m_NodeData.children.emplace_back(nodeID);	
				}
			}
		}

		void SceneGraph::RemoveNode(size_t id) noexcept
		{
			// Step 1: Check if the node exists
			auto it = m_Nodes.find(id);
			if (it == m_Nodes.end())
				return;

			Node& node = it->second;

			// Step 2: Recursively remove all children
			for (size_t childID : node.m_NodeData.children)
			{
				RemoveNode(childID);
			}

			// Step 3: Remove this node from its parent's children vector
			if (node.m_NodeData.mainParentID != 0)
			{
				auto parentIt = m_Nodes.find(node.m_NodeData.mainParentID);
				if (parentIt != m_Nodes.end())
				{
					auto& siblings = parentIt->second.m_NodeData.children;
					siblings.erase(
						std::remove(siblings.begin(), siblings.end(), id),
						siblings.end()
					);
				}
			}

			// Step 4: Remove the node from the map
			m_Nodes.erase(it);
		}
		Node* SceneGraph::GetNode(size_t id) noexcept
		{
			auto it = m_Nodes.find(id);
			if (it != m_Nodes.end())
				return &it->second;
			return nullptr;
		}

		void SceneGraph::Transverse(size_t id) noexcept
		{
			if (m_Nodes.find(id) == m_Nodes.end())
				return; // Does not exist

			// Print it out for now
			for (auto& childID : m_Node.m_NodeData.children)
			{
				Transverse(childID);
			}
		}

		int SceneGraph::FindNodeIDByName(const std::string& name) const noexcept
		{
			for (auto it = m_Node.m_NodeDataVec.begin(); it != m_Node.m_NodeDataVec.end(); it++)
			{
				if (it->name == name)
					return (int)it->id;
			}
		}

		void SceneGraph::RenameNode(const std::string& name, size_t id) noexcept
		{
			for (auto it = m_Node.m_NodeDataVec.begin(); it != m_Node.m_NodeDataVec.end(); it++)
			{
				if (it->id == id)
				{
					m_Nodes[id].m_NodeData.name = name;
					break;
				}
			}
		}
	}
}
