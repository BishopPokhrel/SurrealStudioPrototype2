#pragma once

#define GLFW_INCLUDE_NONE

#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <vector>

namespace SurrealStudio {

	namespace SurrealRenderer {

		struct Vertex
		{
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec2 textCoords;
		};

		class Mesh
		{
		public:

			Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int> indices) noexcept;
			~Mesh() noexcept;


			void Draw() const noexcept;

		private:

			GLuint m_VAO = 0;
			GLuint m_VBO = 0;
			GLuint m_EBO = 0;

			std::vector<Vertex> m_Vertices;
			std::vector<unsigned int> m_Indices;

			void SetupMesh() noexcept;
		};
	}
}