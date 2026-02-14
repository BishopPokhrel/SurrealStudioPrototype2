#include "Renderer.h"
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace SurrealStudio {

    namespace SurrealRenderer {

        void Renderer::RenderAllObjects(ECS::ObjectManager& objectManager,
            ECS::TransformComponentManager& transformManager) noexcept
        {
            if (!m_Shader)
                return;

            m_Shader->Bind();

            for (auto* obj : objectManager.GetAllObjects())
            {
                if (!obj->mesh)
                    continue;

                SurrealRenderer::Transform transform = obj->transform; // default to object's transform

                // Find transform component for this object by name
                for (auto* comp : transformManager.GetAllTransformComponents())
                {
                    if (comp->objectName == obj->name)
                    {
                        transform.position = comp->position;
                        transform.rotation = comp->rotation;
                        transform.scale = comp->scale;
                        break;
                    }
                }

                glm::mat4 model = transform.GetModelMatrix();
                m_Shader->SetMat4("model", model);

                obj->mesh->Draw();
            }

            m_Shader->Unbind();
        }
    }
}
