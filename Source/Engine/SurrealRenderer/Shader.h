#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

namespace SurrealStudio {

	namespace SurrealRenderer {

		struct Transform
		{
			glm::vec3 position;
			glm::vec3 rotation;
			glm::vec3 scale;

			glm::mat4 GetModelMatrix() const;
		};

		struct VertexShader
		{
			std::string vertexShaderSource;
		};

		struct FragmentShader
		{
			std::string fragmentShaderSource;
		};

		class Shader
		{
		public:

			// Upload and linking shaders to the GPU via two different methods
			GLuint CompileAndLinkShaderViaGLSLShaderFiles(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) noexcept;
			GLuint CompileAndLinkShaderViaShaderVariables(const VertexShader& vertexShader, const FragmentShader& fragmentShader) noexcept;

			void SetMat4(const std::string& name, const glm::mat4& value) noexcept;
			void SetVec3(const std::string& name, const glm::vec3& value) noexcept;
			void SetFloat(const std::string& name, float value) noexcept;

			void Bind() const noexcept;
			void Unbind() const noexcept;

		private:

			GLuint m_RendererID = 0;
		};
	}
}