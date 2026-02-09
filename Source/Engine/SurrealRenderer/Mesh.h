#pragma once

#define GLFW_INCLUDE_NONE

#include "Shader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

namespace SurrealStudio {

	namespace SurrealRenderer {

		struct Vertex
		{
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec3 textCoords;
		};

		class Mesh
		{
		public:

			Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int> indices);
			~Mesh();


			void Draw() const;

		private:

			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;

			void SetupMesh();
		};
	}
}