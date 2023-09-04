#pragma once

#include <glm/glm.hpp>

class Camera3D
{
public:
	Camera3D(glm::vec3 position, float fov = 45.0f);

	void Move(glm::vec3 step);
	void Rotate(glm::vec3 step);

	void SetPosition(glm::vec3 position);
	void SetRotation(glm::vec3 rotation);


	glm::vec3& GetPosition() { return m_Position; };
	glm::vec3& GetRotation() { return m_Rotation; };
	glm::vec3& GetDirection() { return m_Direction; };

	glm::mat4& GetProjectionMatrix() { return m_Projection; }
	glm::mat4& GetViewMatrix() { return m_View; }
	glm::mat4& GetViewProjectionMatrix() { return m_VP; }

protected:
	void RecalculateViewMatrix();
	void RecalculateProjectionMatrix();
	void RecalculateViewProjectionMatrix() { m_VP = m_Projection * m_View; };
	void RecalculateDirectionVector();

protected:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Direction;
	float m_Fov;

	glm::mat4 m_Projection;
	glm::mat4 m_View;
	glm::mat4 m_VP;
};

