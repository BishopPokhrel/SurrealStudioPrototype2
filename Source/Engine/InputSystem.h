#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

namespace SurrealStudio {

	class InputSystem
	{
	public:	

		bool InitInputSystem() noexcept;
		bool UpdateInputSystem(GLFWwindow* window) noexcept;
		int IsKeyPressed(int key) const noexcept;
		bool GetMousePosition(float& x, float& y) const noexcept;
		bool GetMouseDelta(float& dx, float& dy) const noexcept;

	private:

		bool keys[512];

		float mouseX = 0.0f;
		float mouseY = 0.0f;
		float mouseDX = 0.0f;
		float mouseDY = 0.0f;
	};
}