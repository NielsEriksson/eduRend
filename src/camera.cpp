#include "Camera.h"
#include <iostream>

using namespace linalg;

void Camera::MoveTo(const vec3f& position) noexcept
{
	m_position = position;
}

void Camera::Move(const float direction) noexcept
{
	m_direction = { 0.0f,0.0f,-1.0f };
		matrixDirection = mat4f::translation(m_direction);	
		std::cout << matrixDirection;
}
void Camera::Rotate(const float roll, const float yaw, const float pitch)noexcept
{
	const float sensitivity = 9.0f;
	float rotX = (pitch * fPI / 180.0f) / sensitivity;
	float rotY = (yaw * fPI / 180.0f) / sensitivity;
	m_rotation += vec3f(roll, rotX, rotY);
}
mat4f Camera::WorldToViewMatrix()  noexcept
{
	// Assuming a camera's position and rotation is defined by matrices T(p) and R,
	// the View-to-World transform is T(p)*R (for a first-person style camera).
	//
	// World-to-View then is the inverse of T(p)*R;
	//		inverse(T(p)*R) = inverse(R)*inverse(T(p)) = transpose(R)*T(-p)
	// Since now there is no rotation, this matrix is simply T(-p)
	mat4f R = mat4f::rotation(-m_rotation.x, -m_rotation.y, -m_rotation.z);
	mat4f worldDirection = mat4f::translation(m_position) * R *matrixDirection;
	

	linalg::vec3f worldDirVec = (worldDirection.m11, worldDirection.m12, worldDirection.m13);
	m_position += (worldDirVec*m_camera_velocity*0.1);


	
	return transpose(R) * mat4f::translation(-m_position);

}

mat4f Camera::ProjectionMatrix() const noexcept
{
	return mat4f::projection(m_vertical_fov, m_aspect_ratio, m_near_plane, m_far_plane);
}