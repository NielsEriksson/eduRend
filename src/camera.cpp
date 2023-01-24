#include "Camera.h"

using namespace linalg;

void Camera::MoveTo(const vec3f& position) noexcept
{
	m_position = position;
}

void Camera::Move(const vec3f& direction) noexcept
{
	m_position += direction;
}
void Camera::Rotate(const float roll, const float yaw, const float pitch)noexcept
{
	float rotX = (pitch * fPI / 180.0f) / 9.0f;
	float rotY = (yaw * fPI / 180.0f) / 9.0f;
	m_rotation += vec3f(roll, rotX, rotY);
}
mat4f Camera::WorldToViewMatrix() const noexcept
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

mat4f Camera::ProjectionMatrix() const noexcept
{
	return mat4f::projection(m_vertical_fov, m_aspect_ratio, m_near_plane, m_far_plane);
}