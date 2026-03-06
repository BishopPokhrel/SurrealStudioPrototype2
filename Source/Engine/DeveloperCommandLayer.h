#pragma once

#include <string>
#include <vector>

#include <Engine/ECS/Object.h>
#include <Engine/ECS/Component.h>
#include <Engine/Scene/Scene.h>
#include <Engine/Scene/Subscene.h>
#include <Engine/Scene/World.h>

namespace SurrealStudio {

	enum class DeveloperCommands
	{
		None = 0,	
		CreateObjectCommand,
		CreateTransformomponentCommand,
		CreatePhysicsComponentCommand,
		CreateSceneCommand,
		CreateSubsceneCommand,
		CreateWorldCommand,
		DeleteObjectCommand,
		DeleteTransformComponentCommand,
		DeletePhysicsComponentCommand,
		DeleteSceneCommand,
		DeleteSubsceneCommand,
		DeleteWorldCommand,
		GetObjectIDByNameCommand,
		GetObjectNameByIDCommand,
		RenameObjectCommand,
		RenameSubsceneCommand,
		RenameWorldCommand,
		GetInfoAboutSurrealStudioCommand,
		HelpCommand
	};

	class DeveloperCommandLayer
	{
	public:

		DeveloperCommandLayer() noexcept;
		bool WriteCommand(const std::string& command) noexcept;
	
	private:

		std::vector<std::string> m_AvailableCommands;

		ECS::ObjectManager m_DeveloperCommandLayer_ObjectManager;
		ECS::ComponentManager m_DeveloperCommandLayer_ComponentManager;
		
		SceneSystem::Scene m_DeveloperCommandLayer_Scene;
		SceneSystem::Subscene m_DeveloperCommandLayer_Subscene;
		SceneSystem::World m_DeveloperCommandLayer_World;
	};
}