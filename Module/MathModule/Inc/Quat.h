#pragma once

#include "Mat4x4.h"
#include "MathModule.h"
#include "Vec3.h"


/**
 * @brief 쿼터니언입니다.
 * 
 * @see 
 * - https://gabormakesgames.com/quaternions.html
 * - https://en.wikipedia.org/wiki/Quaternion
 * - https://github.com/mmp/pbrt-v3/blob/master/src/core/quaternion.h
 */
struct Quat
{
	/**
	 * @brief 쿼터니언의 다양한 원소 형식입니다.
	 */
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
		struct 
		{
			Vec3f v;
			float w;
		};
		float data[4];
	};
};