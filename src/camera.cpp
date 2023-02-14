#include "Camera.h"
#include <iostream>

using namespace linalg;

void Camera::MoveTo(const vec3f& position) noexcept
{
	m_position = position;
}

void Camera::Move(const linalg::vec3f& direction) noexcept
{
	m_position += direction;
}
void Camera::Rotate(const float roll, const float yaw, const float pitch)noexcept
{
	const float sensitivity = 9.0f;
	float rotX = (pitch * fPI / 180.0f) / sensitivity;
	float rotY = (yaw * fPI / 180.0f) / sensitivity;
	m_rotation += vec3f(roll, rotX, rotY);

	if (m_rotation.z > 2 / fPI) m_rotation.z = 2 / fPI; //limits to y rotation up
	if (m_rotation.z < -2 / fPI) m_rotation.z = -2 / fPI; //and down

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

	return transpose(R) * mat4f::translation(-m_position);

}
mat4f Camera::ViewToWorldMatrix()  noexcept
{
	// Assuming a camera's position and rotation is defined by matrices T(p) and R,
	// the View-to-World transform is T(p)*R (for a first-person style camera).
	//
	// World-to-View then is the inverse of T(p)*R;
	//		inverse(T(p)*R) = inverse(R)*inverse(T(p)) = transpose(R)*T(-p)
	// Since now there is no rotation, this matrix is simply T(-p)
	mat4f R = mat4f::rotation(-m_rotation.x, -m_rotation.y, -m_rotation.z);

	return  mat4f::translation(m_position)*R;

}

mat4f Camera::ProjectionMatrix() const noexcept
{
	return mat4f::projection(m_vertical_fov, m_aspect_ratio, m_near_plane, m_far_plane);
}
void Camera::MoveForward(float input_direction, float dt) noexcept
{
	//move vectors
	vec4f forward = { 0.0f, 0.0f, -m_camera_velocity * dt, 0.0f };
	vec4f backward = { 0.0f, 0.0f, m_camera_velocity * dt, 0.0f };
	vec4f left = { m_camera_velocity * dt, 0.0f, 0.0f , 0.0f };
	vec4f right = { -m_camera_velocity * dt, 0.0f, 0.0f , 0.0f };

	if (input_direction == 0) {     //move to camera
		vec4f worldDirection = ViewToWorldMatrix() * forward; //moves where we are looking
		Move({ worldDirection.x, worldDirection.y, worldDirection.z });
	}
	if (input_direction == 1) {
		vec4f worldDirection = ViewToWorldMatrix() * backward;
		Move({ worldDirection.x, worldDirection.y, worldDirection.z });
	}
	if (input_direction == 2) {
		vec4f worldDirection = ViewToWorldMatrix() * left;
		Move({ worldDirection.x, worldDirection.y, worldDirection.z });
	}
	if (input_direction == 3) {
		vec4f worldDirection = ViewToWorldMatrix() * right;
		Move({ worldDirection.x, worldDirection.y, worldDirection.z });
	}
}