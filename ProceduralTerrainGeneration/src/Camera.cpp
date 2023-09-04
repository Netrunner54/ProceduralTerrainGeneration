#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera3D::Camera3D(glm::vec3 position, float fov)
	: m_Position(position), m_Fov(fov)
{
	SetRotation({ 0.0f, -90.0f, 0.0f });
	RecalculateViewMatrix();
	RecalculateProjectionMatrix();
	RecalculateViewProjectionMatrix();
}

void Camera3D::Move(glm::vec3 step)
{
	m_Position += step;
	RecalculateViewMatrix();
	RecalculateViewProjectionMatrix();
}

void Camera3D::Rotate(glm::vec3 step)
{
	SetRotation(m_Rotation + step);
}

void Camera3D::SetPosition(glm::vec3 position)
{
	m_Position = position;
	RecalculateViewMatrix();
	RecalculateViewProjectionMatrix();
}

void Camera3D::SetRotation(glm::vec3 rotation)
{
	m_Rotation = rotation;
	RecalculateDirectionVector();
}

void Camera3D::RecalculateViewMatrix()
{
	m_View = glm::lookAt(m_Position, m_Position + m_Direction, { 0.0f, 1.0f, 0.0f });
}

void Camera3D::RecalculateProjectionMatrix()
{
	m_Projection = glm::perspective(m_Fov, 16.0f / 9.0f, 0.1f, 1000000.0f);
}

void Camera3D::RecalculateDirectionVector()
{
	m_Direction.x = glm::cos(glm::radians(m_Rotation.y)) * glm::cos(glm::radians(m_Rotation.x));
	m_Direction.y = glm::sin(glm::radians(m_Rotation.x));
	m_Direction.z = glm::sin(glm::radians(m_Rotation.y)) * glm::cos(glm::radians(m_Rotation.x));
}
