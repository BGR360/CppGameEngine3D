#ifndef BENGINE_MATH_H
#define BENGINE_MATH_H

#include <Engine.h>

#define PI 3.1415926535f

namespace Math
{
	inline float ENGINE_DLL_EXPORT toRadians(float thetaDegrees)
	{
		return thetaDegrees * PI / 180.0f;
	}

	inline float ENGINE_DLL_EXPORT toDegrees(float thetaRadians)
	{
		return thetaRadians * 180.0f / PI;
	}
}

#endif //BENGINE_MATH_H