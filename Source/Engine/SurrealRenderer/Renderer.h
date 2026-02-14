#pragma once

#include <Engine/SurrealRenderer/Shader.h>
#include <Engine/SurrealRenderer/Mesh.h>
#include <Engine/ECS/Object.h>
#include <Engine/ECS/Component.h>

namespace SurrealStudio {

    namespace SurrealRenderer {

        class Renderer
        {
        public:
            Renderer() = default;

            void SetShader(Shader* shader) noexcept
            {
                m_Shader = shader;
            }

            void RenderAllObjects(ECS::ObjectManager& objectManager, ECS::TransformComponentManager& transformManager) noexcept;

        private:
            SurrealRenderer::Shader* m_Shader = nullptr;
        };

    } // namespace ECS
} // namespace SurrealStudio
