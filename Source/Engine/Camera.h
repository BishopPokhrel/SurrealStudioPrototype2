// Camera.h
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>

namespace SurrealStudio {

    class Camera
    {
    public:
        Camera(const glm::vec3& startPosition, const glm::vec3& startUp, float startYaw, float startPitch) noexcept;

        // Movement
        void MoveForward(float deltaTime) noexcept;
        void MoveRight(float deltaTime) noexcept;
        void MoveUp(float deltaTime) noexcept;

        // Rotation
        void Rotate(float deltaYaw, float deltaPitch) noexcept;

        // Get view matrix
        glm::mat4 GetViewMatrix() const noexcept;

        enum class CameraType
        {
            None = 0,
            Normal,
            Orthographic
        };

        CameraType cameraType;

        bool SetCameraType(CameraType type) noexcept
        {
            cameraType = type;
            return true;
        }
        
        static constexpr int MAX_CAMERAS_PER_WORLD = 10;
        std::vector<std::unique_ptr<Camera>> m_Cameras;

        // Camera properties
        glm::vec3 m_Position;
        glm::vec3 m_Direction;
        glm::vec3 m_Up;
        glm::vec3 m_Right;

        float m_Yaw;
        float m_Pitch;

        float m_MovementSpeed;
        float m_MouseSensitivity;

    private:
        void UpdateCameraVectors() noexcept;
    };
}
