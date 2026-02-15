#include "Shader.h"

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>
#include <string>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace SurrealStudio {

	namespace SurrealRenderer {

		// ------------------------------------------------------------
		// Internal helper: compile a single shader
		// ------------------------------------------------------------
		static bool CompileShader(GLuint shaderID, const char* source, const char* shaderName)
		{
			glShaderSource(shaderID, 1, &source, nullptr);
			glCompileShader(shaderID);

			GLint success = 0;
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				char infoLog[1024];
				glGetShaderInfoLog(shaderID, sizeof(infoLog), nullptr, infoLog);

				std::cout
					<< "[SURREAL RENDERER] "
					<< shaderName
					<< " compilation failed:\n"
					<< infoLog
					<< std::endl;

				return false;
			}

			return true;
		}

		// ------------------------------------------------------------
		// Compile + link from GLSL source strings
		// ------------------------------------------------------------
		GLuint Shader::CompileAndLinkShaderViaGLSLShaderFiles(
			const std::string& vertexShaderSource,
			const std::string& fragmentShaderSource) noexcept
		{
			if (vertexShaderSource.empty() || fragmentShaderSource.empty())
			{
				std::cout << "[SURREAL RENDERER] Shader source is empty!" << std::endl;
				return 0;
			}

			GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

			// Compile vertex shader
			if (!CompileShader(vertexShaderID, vertexShaderSource.c_str(), "Vertex Shader"))
			{
				glDeleteShader(vertexShaderID);
				glDeleteShader(fragmentShaderID);
				return 0;
			}

			// Compile fragment shader
			if (!CompileShader(fragmentShaderID, fragmentShaderSource.c_str(), "Fragment Shader"))
			{
				glDeleteShader(vertexShaderID);
				glDeleteShader(fragmentShaderID);
				return 0;
			}

			// Create and link program
			GLuint programID = glCreateProgram();
			glAttachShader(programID, vertexShaderID);
			glAttachShader(programID, fragmentShaderID);
			glLinkProgram(programID);

			GLint linkSuccess = 0;
			glGetProgramiv(programID, GL_LINK_STATUS, &linkSuccess);

			if (!linkSuccess)
			{
				char infoLog[1024];
				glGetProgramInfoLog(programID, sizeof(infoLog), nullptr, infoLog);

				std::cout
					<< "[SURREAL RENDERER] Shader program linking failed:\n"
					<< infoLog
					<< std::endl;

				glDeleteProgram(programID);
				glDeleteShader(vertexShaderID);
				glDeleteShader(fragmentShaderID);
				return 0;
			}

			// Cleanup shaders (no longer needed after linking)
			glDetachShader(programID, vertexShaderID);
			glDetachShader(programID, fragmentShaderID);
			glDeleteShader(vertexShaderID);
			glDeleteShader(fragmentShaderID);

			return programID;
		}

		// ------------------------------------------------------------
		// Compile + link via shader structs
		// ------------------------------------------------------------
		GLuint Shader::CompileAndLinkShaderViaShaderVariables(
			const VertexShader& vertexShader,
			const FragmentShader& fragmentShader) noexcept
		{
			if (vertexShader.vertexShaderSource.empty())
			{
				std::cout << "[SURREAL RENDERER] Vertex shader source is empty!" << std::endl;
				return 0;
			}

			if (fragmentShader.fragmentShaderSource.empty())
			{
				std::cout << "[SURREAL RENDERER] Fragment shader source is empty!" << std::endl;
				return 0;
			}

			return CompileAndLinkShaderViaGLSLShaderFiles(
				vertexShader.vertexShaderSource,
				fragmentShader.fragmentShaderSource
			);
		}

		void Shader::SetMat4(const std::string& name, const glm::mat4& value) noexcept
		{
			GLint location = glGetUniformLocation(m_RendererID, name.c_str());
			if (location == -1)
				return;

			glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
		}

		void Shader::SetVec3(const std::string& name, const glm::vec3& value) noexcept
		{
			GLint location = glGetUniformLocation(m_RendererID, name.c_str());
			if (location == -1)
				return;

			glUniform3fv(location, 1, glm::value_ptr(value));
		}

		void Shader::SetFloat(const std::string& name, float value) noexcept
		{
			GLint location = glGetUniformLocation(m_RendererID, name.c_str());
			if (location == -1)
				return;

			glUniform1f(location, value);
		}

		void Shader::Bind() const noexcept
		{
			if (m_RendererID != 0)
				glUseProgram(m_RendererID);
		}

		void Shader::Unbind() const noexcept
		{
			glUseProgram(0);
		}

		glm::mat4 Transform::GetModelMatrix() const
		{
			glm::mat4 model(1.0f);
			model = glm::translate(model, position);

			// Convert degrees to radians
			model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
			model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
			model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));

			model = glm::scale(model, scale);
			return model;
		}
	}
}