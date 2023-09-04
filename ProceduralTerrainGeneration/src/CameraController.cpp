#include "CameraController.h"

void CameraController3D::MoveRight(float step)
{
	Move(glm::normalize(glm::cross(m_Direction, { 0.0f, 1.0, 0.0f })) * step);
}

void CameraController3D::MoveLeft(float step)
{
	Move(-glm::normalize(glm::cross(m_Direction, { 0.0f, 1.0, 0.0f })) * step);
}

void CameraController3D::MoveForward(float step)
{
	Move(-glm::cross(glm::cross(m_Direction, { 0.0f, 1.0, 0.0f }), { 0.0f, 1.0f, 0.0f }) * step);
}

void CameraController3D::MoveBackward(float step)
{
	Move(glm::cross(glm::cross(m_Direction, { 0.0f, 1.0, 0.0f }), { 0.0f, 1.0f, 0.0f }) * step);
}

void CameraController3D::MoveUp(float step)
{
	Move({ 0.0f, step, 0.0f });
}

void CameraController3D::MoveDown(float step)
{
	Move({ 0.0f, -step, 0.0f });
}

void CameraController3D::MouseMoveCallback(float xoffset, float yoffset)
{
	if (m_First)
	{
		m_Last = { xoffset, yoffset };
		m_First = false;
	}

	glm::vec2 pos(xoffset, yoffset);

	glm::vec2 offset = pos - m_Last;
	m_Last = pos;

	float sensivity = 0.5f;
	offset *= sensivity;

	m_Rotation.x -= offset.y;
	m_Rotation.y += offset.x;

	if (m_Rotation.x > 80.0f)
		m_Rotation.x = 80.0f;
	else if (m_Rotation.x < -80.0f)
		m_Rotation.x = -80.0f;

	RecalculateDirectionVector();
	RecalculateViewMatrix();
	RecalculateViewProjectionMatrix();


}
