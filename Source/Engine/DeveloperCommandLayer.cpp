#include "DeveloperCommandLayer.h"

#include <sstream>
#include <iostream>

namespace SurrealStudio {

	DeveloperCommandLayer::DeveloperCommandLayer() noexcept
	{
		m_AvailableCommands = 
		{
			"ssinfo",
			"cr Object",
			"cr TransComp",
			"cr PhysicsComp",
			"cr Scene",
			"cr Subscene",
			"cr World",
			"del Object",
			"del TransComp"	,
			"del PhysicsComp",
			"del Scene",
			"del Subscene",
			"del World",
			"get Object --name --id", // Get Object Name by ID
			"get Object --id --name", // Get Object ID by Name
			"rename Object",
			"rename Subscene",
			"rename World",
			"help"
		};
	}

	bool DeveloperCommandLayer::WriteCommand(const std::string& command) noexcept
	{
		for (const auto& cmd : m_AvailableCommands)
		{
			if (command == cmd)
			{
				std::stringstream ss(command);
				std::string commandType;
				std::string commandArg1;
				std::string commandArg2;
				std::string commandArg3;
				std::string commandArg4;

				if (ss >> commandType)
				{
					if (commandType.empty())
					{
						std::cout << "Command Type is empty: Use help to gain info about commands"; 
						break;
					}

					if (commandType == "cr")
					{
						if (commandArg1.empty()) { std::cout << "Command Args is empty: Use help to gain info about the commands."; break; }
						if (ss >> commandArg1)
						{
							if (commandArg1 == "Object")
							{
								if (ss >> commandArg2)
								{
									if (!commandArg2.empty())
									{
										if (m_DeveloperCommandLayer_ObjectManager.m_Objects.size() > ECS::MAX_OBJECTS)
										{
											std::cout << "Cannot create Object " << commandArg2 << " because the max amount of Objects per World is " << ECS::MAX_OBJECTS << " but got " << m_DeveloperCommandLayer_ObjectManager.m_Objects.size();

										}

										// The second Command Argument for Object is not empty, so with that name, we can create an object.
										m_DeveloperCommandLayer_ObjectManager.CreateObject(commandArg2);
									}
									else
									{
										std::cout << "Command Args for Object (2nd) is empty: Use help to gain info about the commands."; 
										break;
									}
								}
							}

							if (commandArg1 == "TransComp")
							{
								if (ss >> commandArg2)
								{
									if (!commandArg2.empty())
									{
										// The second Command Argument for TransComp (Transform Component) is not empty, so we can create a Transform Component
										m_DeveloperCommandLayer_ComponentManager.transformComponentManager.AddTransformComponent(commandArg2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
									}
									else
									{
										std::cout << "Command Args for TransComp (Transform Component) (2nd) is empty: Use help to gain info about the commands.";
										break;
									}
								}
							}

							if (commandArg1 == "PhysicsComp")
							{
								if (ss >> commandArg2)
								{
									if (!commandArg2.empty())
									{
										// The second Command Argument for Physics (Physics Component) is not empty, so we can create a Physics Component
										m_DeveloperCommandLayer_ComponentManager.physicsComponentManager.AddPhysicsComponent(commandArg2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
									}
									else
									{
										std::cout << "Command Args for PhysicsComp (Physics Component) (2nd) is empty: Use help to gain info about the commands.";
										break;
									}
								}
							}

							if (commandArg1 == "Scene")
							{
								m_DeveloperCommandLayer_Scene.AddScene();
							}

							if (commandArg1 == "Subscene")
							{
								if (ss >> commandArg2)
								{
									if (!commandArg2.empty())
									{
										m_DeveloperCommandLayer_Subscene.AddSubscene(commandArg2);
									}
									else
									{
										std::cout << "Command Args for Subscene (2nd) is empty: Use help to gain info about the commands.";
										break;
									}
								}
							}

							if (commandArg1 == "World")
							{
								if (ss >> commandArg2)
								{
									if (!commandArg2.empty())
									{
										m_DeveloperCommandLayer_World.AddWorld(commandArg2);
									}
									else
									{
										std::cout << "Command Args for World (2nd) is empty: Use help to gain info about the commands.";
										break;
									}
								}
							}
						}
					}

					if (commandType == "del")
					{
						if (commandArg1.empty()) { std::cout << "Command Arg (1) for command type 'del' is missing. See help for more info."; break; }
						if (ss >> commandArg1)
						{
							if (commandArg1 == "Object")
							{
								if (ss >> commandArg2)
								{
									if (!commandArg2.empty())
									{
										auto objIDToGetForRemovalOfObject = m_DeveloperCommandLayer_ObjectManager.GetObjectIDByName(commandArg2);

										if (objIDToGetForRemovalOfObject)
										{
											ECS::ObjectID objectForRemovalID = objectForRemovalID;
											m_DeveloperCommandLayer_ObjectManager.DestroyObject(objectForRemovalID);
										}
										else
										{
											std::cout << "Failed to find Object " << commandArg2 << " and therefore could not delete it.";
										}
									}
								}
							}
						}
					}
				}
			}
			else
				return false; // Command was not valid. We can show an error message later in UI.
		}
	}
}