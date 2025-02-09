/**
 * @file camera.h
 * @brief Basic camera class
*/

#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "vec\vec.h"
#include "vec\mat.h"
#include <string>

/**
 * @brief Manages camera data, also handles generation of view and projection matrices.
*/
class Camera
{
public:
	/**
	 * @brief Creates a camera.
	 * @param[in] vertical_fov Vertical field of view.
	 * @param[in] aspect_ratio Aspect ratio, calculate from screen width / sceen height.
	 * @param[in] near_plane Near plane distance.
	 * @param[in] far_plane Far plane distance, must be larger than the near plane.
	*/
	inline constexpr Camera(float vertical_fov, float aspect_ratio, float near_plane, float far_plane) noexcept 
		: m_vertical_fov(vertical_fov), m_aspect_ratio(aspect_ratio), m_near_plane(near_plane), m_far_plane(far_plane), m_position(0.0f) {}

	/**
	 * @brief Move the camera to a new position
	 * @param[in] position New position for the camera
	*/
	void MoveTo(const linalg::vec3f& position) noexcept;

	/**
	 * @brief Move the camera along a vector
	 * @param[in] direction Direction to move along
	*/
	void MoveForward(float input_direction, float dt) noexcept;
	void Move(const linalg::vec3f& direction) noexcept;

	void Rotate(const float roll, const float yaw, const float pitch) noexcept;

	/**
	 * @brief Changes the camera aspect ratio.
	 * @param[in] aspect_ratio New aspect ratio, calculate with width / height
	*/
	inline void SetAspect(float aspect_ratio) noexcept { m_aspect_ratio = aspect_ratio; }

	/**
	 * @brief Get the World-to-View matrix of the camera.
	 * @return World-to-View matrix.
	*/
	linalg::mat4f WorldToViewMatrix()  noexcept;
	linalg::mat4f ViewToWorldMatrix()  noexcept;

	/**
	 * @brief get the Matrix transforming from View space to Clip space
	 * @return Projection matrix.
	 * 
	 * @note In a performance sensitive situation this matrix should be precomputed if possible
	*/
	linalg::mat4f ProjectionMatrix() const noexcept;

public:
	// Aperture attributes
	float m_vertical_fov;
	float m_aspect_ratio;

	// Clip planes in view space coordinates
	// Evrything outside of [m_near_plane, m_far_plane] is clipped away on the GPU side
	// m_near_plane should be > 0
	// m_far_plane should depend on the size of the scene
	// This range should be kept as tight as possibly to improve
	// numerical precision in the z-buffer
	float m_near_plane;
	float m_far_plane;

	linalg::vec3f m_position;
	linalg::vec3f m_rotation;
	linalg::vec3f m_direction;
	linalg::mat4f matrixDirection;
	float m_camera_velocity = 5.0f;
		// Camera movement velocity in units/s
};

#endif