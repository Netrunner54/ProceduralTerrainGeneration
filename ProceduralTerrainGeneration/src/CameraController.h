#pragma once

#include "Camera.h"

class CameraController3D : public Camera3D
{
public:
	CameraController3D(glm::vec3 position, float fov = 45.0f)
		: Camera3D(position, fov) {}

	void MoveRight(float step);
	void MoveLeft(float step);
	void MoveForward(float step);
	void MoveBackward(float step);
	void MoveUp(float step);
	void MoveDown(float step);

	void MouseMoveCallback(float xoffset, float yoffset);
private:
	glm::vec2 m_Last;
	bool m_First = true;
};

