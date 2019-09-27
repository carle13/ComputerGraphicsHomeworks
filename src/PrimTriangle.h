// Triangle Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief Triangle Geaometrical Primitive class
 */
class CPrimTriangle : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param a Position of the first vertex
	 * @param b Position of the second vertex
	 * @param c Position of the third vertex
	 */
	CPrimTriangle(Vec3f a, Vec3f b, Vec3f c)
		: CPrim()
		, m_a(a)
		, m_b(b)
		, m_c(c)
  	{}
	virtual ~CPrimTriangle(void) = default;
	
	virtual bool Intersect(Ray& ray) override
	{
		const Vec3f edge1 = m_b - m_a;
		const Vec3f edge2 = m_c - m_a;

		const Vec3f pvector = ray.dir.cross(edge2);

		const float determinant = edge1.dot(pvector);
		if (fabs(determinant) < Epsilon)
		{
			return false;
		}

		const float invDeterminant = 1.0f / determinant;

		const Vec3f tvector = ray.org - m_a;
		float lambda = tvector.dot(pvector);
		lambda *= invDeterminant;

		if (lambda < 0.0f || lambda > 1.0f)
		{
			return false;
		}

		const Vec3f qvector = tvector.cross(edge1);
		float mu = ray.dir.dot(qvector);
		mu *= invDeterminant;

		if (mu < 0.0f || mu + lambda > 1.0f)
		{
			return false;
		}

		float f = edge2.dot(qvector);
		f *= invDeterminant;
		if (ray.t <= f || f < 1E-4)
		{
			return false;
		}

		ray.t = f;

		return true;
	}

	
private:
	Vec3f m_a;	///< Position of the first vertex
	Vec3f m_b;	///< Position of the second vertex
	Vec3f m_c;	///< Position of the third vertex
};
