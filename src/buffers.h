/**
 * @file buffers.h
 * @brief Contains constant buffers
*/

#pragma once

#include "vec/mat.h"

/**
 * @brief Contains transformation matrices.
*/
struct TransformationBuffer
{
	linalg::mat4f ModelToWorldMatrix; //!< Matrix for converting from object space to world space.
	linalg::mat4f WorldToViewMatrix; //!< Matrix for converting from world space to view space.
	linalg::mat4f ProjectionMatrix; //!< Matrix for converting from view space to clip cpace.
};
struct CameraLigthBuffer
{
	float4 CameraPos; //!<Camera Position.
	float4 LigthPos; //!< Ligth Source Position.
};
struct MaterialBuffer
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
};