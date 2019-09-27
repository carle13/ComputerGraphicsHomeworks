// Perspective Camera class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "ICamera.h"

/**
 * @brief Perspective Camera class
 */
class CCameraPerspective : public ICamera
{
public:
	/**
	 * @brief Constructor
	 * @param pos Camera origin (center of projection)
	 * @param dir Camera viewing direction
	 * @param up Up-vector
	 * @param angle (Vertical) full opening angle of the viewing frustum (in degrees)
	 * @param resolution The image resolution
	 */
	CCameraPerspective(Vec3f pos, Vec3f dir, Vec3f up, float angle, Size resolution)
		: ICamera(resolution)
		, m_pos(pos)
		, m_dir(dir)
		, m_up(up)
	{
		m_zAxis = dir;
		m_xAxis = m_zAxis.cross(m_up);
		m_yAxis = m_zAxis.cross(m_xAxis);

		//Normalize the positions
		m_xAxis = normalize(m_xAxis);
		m_yAxis = normalize(m_yAxis);
		m_zAxis = normalize(m_zAxis);

		//Calculate aspect ration and focus
		m_aspect = static_cast<float>(resolution.width / resolution.height);
		m_focus = 1.0f / tanf(angle * Pif / 360);
	}
	virtual ~CCameraPerspective(void) = default;

	virtual bool InitRay(float x, float y, Ray& ray) override
	{
		float shiftX = 0.5f;
		float shiftY = 0.5f;

		//Calculate screen position coordinates
		float screenX = 2 * (x + shiftX) / getResolution().width - 1;
		float screenY = 2 * (y + shiftY) / getResolution().height - 1;

		//Generate ray
		ray.org = m_pos;
		ray.dir = normalize(m_aspect * screenX * m_xAxis + screenY * m_yAxis + m_focus * m_zAxis);
		ray.t = std::numeric_limits<float>::infinity();

		return true;
	}


private:
	// input values
	Vec3f m_pos;
	Vec3f m_dir;
	Vec3f m_up;

	// preprocessed values
	float m_focus;
	Vec3f m_xAxis;
	Vec3f m_yAxis;
	Vec3f m_zAxis;
	float m_aspect;
};

