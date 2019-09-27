// Sphere Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief Sphere Geaometrical Primitive class
 */
class CPrimSphere : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param center Position of the center of the sphere
	 * @param radius Radius of the sphere
	 */
	CPrimSphere(Vec3f center, float radius)
		: CPrim()
		, m_center(center)
		, m_radius(radius)
	{}
	virtual ~CPrimSphere(void) = default;

	virtual bool Intersect(Ray &ray) override
	{
		Vec3f difference = ray.org - m_center;
		float varA = ray.dir.dot(ray.dir);
		float varB = 2 * ray.dir.dot(difference);
		float varC = difference.dot(difference) - m_radius * m_radius;

		float inRoot = varB * varB - 4 * varA * varC;
		if (inRoot < 0)
		{
			return false;
		}
		float root = sqrtf(inRoot);

		float distance = (-varB - root) / (2 * varA);
		if (distance > ray.t)
		{
			return false;
		}

		if (distance < Epsilon)
		{
			distance = (-varB + root) / (2 * varA);
			if (distance < Epsilon || distance > ray.t)
			{
				return false;
			}
		}

		ray.t = distance;
		return true;
	}
	
	
private:
	Vec3f m_center;	///< Position of the center of the sphere
	float m_radius;	///< Radius of the sphere
};

