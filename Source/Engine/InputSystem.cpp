#define GLFW_INCLUDE_NONE

#include "InputSystem.h"

namespace SurrealStudio {

	bool InputSystem::InitInputSystem() noexcept
	{
		for (size_t i = 0; i < 512; i++)
			keys[i] = false;

		mouseX = 0.0f;
		mouseY = 0.0f;

		mouseDX = 0.0f;
		mouseDY = 0.0f;

		return true;
	}

	bool InputSystem::UpdateInputSystem(GLFWwindow* window) noexcept
	{
		mouseDX = 0.0f;
		mouseDY = 0.0f;

		for (int i = 0; i < 512; i++)
		{
			keys[i] = (glfwGetKey(window, i) == GLFW_PRESS);
		}
		
		return true;
	}

	int InputSystem::IsKeyPressed(int key) const noexcept
	{
		if (key >= 0 && key < 512)
			return 0;

		return keys[key];
	}

	bool InputSystem::GetMousePosition(float& x, float& y) const noexcept
	{
		x = mouseX;
		y = mouseY;
		return true;
	}

	bool InputSystem::GetMouseDelta(float& dx, float& dy) const noexcept
	{
		dx = mouseDX;
		dy = mouseDY;
		return true;
	}
}