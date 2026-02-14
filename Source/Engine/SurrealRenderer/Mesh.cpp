#include "Mesh.h"

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace SurrealStudio {

	namespace SurrealRenderer {

		Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int> indices) noexcept
			: m_Vertices(vertices), m_Indices(indices), m_EBO(0), m_VAO(0), m_VBO(0)
		{
			SetupMesh();
		}

		Mesh::~Mesh() noexcept
		{
			if (m_VAO) glDeleteVertexArrays(1, &m_VAO);
			if (m_VBO) glDeleteBuffers(1, &m_VBO);
			if (m_EBO) glDeleteBuffers(1, &m_EBO);
		}

		Mesh::Mesh(Mesh&& other) noexcept
			: m_VAO(other.m_VAO),
			m_VBO(other.m_VBO),
			m_EBO(other.m_EBO),
			m_Vertices(std::move(other.m_Vertices)),
			m_Indices(std::move(other.m_Indices))
		{
			other.m_VAO = 0;
			other.m_VBO = 0;
			other.m_EBO = 0;
		}

		Mesh& Mesh::operator=(Mesh&& other) noexcept
		{
			if (this != &other)
			{
				// Delete current resources
				if (m_VAO) glDeleteVertexArrays(1, &m_VAO);
				if (m_VBO) glDeleteBuffers(1, &m_VBO);
				if (m_EBO) glDeleteBuffers(1, &m_EBO);

				// Move handles
				m_VAO = other.m_VAO;
				m_VBO = other.m_VBO;
				m_EBO = other.m_EBO;

				m_Vertices = std::move(other.m_Vertices);
				m_Indices = std::move(other.m_Indices);

				// Nullify source
				other.m_VAO = 0;
				other.m_VBO = 0;
				other.m_EBO = 0;
			}
			return *this;
		}

		void Mesh::Draw() const noexcept
		{
			if (m_VAO == 0)
				return;

			glBindVertexArray(m_VAO);

			if (!m_Indices.empty())
			{
				glDrawElements(GL_TRIANGLES, (GLsizei)m_Indices.size(), GL_UNSIGNED_INT, nullptr);
			}
			else
			{
				glDrawArrays(GL_TRIANGLES, 0, (GLsizei)m_Vertices.size());
			}

			glBindVertexArray(0);
		}

		void Mesh::SetupMesh() noexcept
		{
			if (m_Vertices.empty())
				return;

			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);
			glGenBuffers(1, &m_EBO);

			glBindVertexArray(m_VAO);

			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), m_Vertices.data(), GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), m_Indices.data(), GL_STATIC_DRAW);

			glEnableVertexAttribArray(0); // Position
			glEnableVertexAttribArray(1); // Normal
			glEnableVertexAttribArray(2); // Texture Coordinates

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textCoords));

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}