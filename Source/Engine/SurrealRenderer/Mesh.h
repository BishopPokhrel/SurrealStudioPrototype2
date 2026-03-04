#pragma once

#define GLFW_INCLUDE_NONE

#include "Shader.h"

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

		enum class MeshType
		{
			None = 0,
			StaticMesh,
			CustomMesh
		};

		class Mesh
		{
		public:

			Mesh() = default;

			Mesh(Mesh&&) noexcept;
			Mesh& operator=(Mesh&&) noexcept;

			Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int> indices) noexcept;
			~Mesh() noexcept;


			void Draw() const noexcept;

			void LoadToGPU() noexcept { SetupMesh(); }

			MeshType meshType;
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