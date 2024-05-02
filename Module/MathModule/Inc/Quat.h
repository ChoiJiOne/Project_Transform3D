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
	 * @brief 쿼터니언의 기본 생성자입니다.
	 *
	 * @note 모든 원소의 값을 0으로 초기화합니다.
	 */
	Quat() noexcept : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}


	/**
	 * @brief 쿼터니언의 생성자입니다.
	 *
	 * @param xx 쿼터니언의 x 성분입니다.
	 * @param yy 쿼터니언의 y 성분입니다.
	 * @param zz 쿼터니언의 z 성분입니다.
	 * @param ww 쿼터니언의 w 성분입니다.
	 */
	Quat(float&& xx, float&& yy, float&& zz, float&& ww) noexcept : x(xx), y(yy), z(zz), w(ww) {}


	/**
	 * @brief 쿼터니언의 생성자입니다.
	 *
	 * @param xx 쿼터니언의 x 성분입니다.
	 * @param yy 쿼터니언의 y 성분입니다.
	 * @param zz 쿼터니언의 z 성분입니다.
	 * @param ww 쿼터니언의 w 성분입니다.
	 */
	Quat(const float& xx, const float& yy, const float& zz, const float& ww) noexcept : x(xx), y(yy), z(zz), w(ww) {}


	/**
	 * @brief 쿼터니언의 생성자입니다.
	 *
	 * @param vv i,j,k 축의 벡터 요소입니다.
	 * @param ww 회전의 스케일을 조정하는 w 성분입니다.
	 */
	Quat(Vec3f&& vv, float&& ww) noexcept : v(vv), w(ww) {}


	/**
	 * @brief 쿼터니언의 생성자입니다.
	 *
	 * @param vv i,j,k 축의 벡터 요소입니다.
	 * @param ww 회전의 스케일을 조정하는 w 성분입니다.
	 */
	Quat(const Vec3f& vv, const float& ww) noexcept : v(vv), w(ww) {}


	/**
	 * @brief 쿼터니언의 생성자입니다.
	 * 
	 * @param axis 회전 축입니다.
	 * @param radian 라디안 단위의 회전 각도입니다. 
	 */
	Quat(const Vec3f& axis, float radian)
	{
		float s = MathModule::Sin(radian * 0.5f);
		float c = MathModule::Cos(radian * 0.5f);
		Vec3f norm = Vec3f::Normalize(axis);

		v = norm * s;
		w = c;
	}


	/**
	 * @brief 쿼터니언의 복사 생성자입니다.
	 *
	 * @param q 원소를 복사할 쿼터니언 구조체의 인스턴스입니다.
	 */
	Quat(Quat&& q) noexcept : x(q.x), y(q.y), z(q.z), w(q.w) {}


	/**
	 * @brief 쿼터니언의 복사 생성자입니다.
	 *
	 * @param q 원소를 복사할 쿼터니언 구조체의 인스턴스입니다.
	 */
	Quat(const Quat& q) noexcept : x(q.x), y(q.y), z(q.z), w(q.w) {}


	/**
	 * @brief 쿼터니언의 대입 연산자입니다.
	 *
	 * @param q 원소를 복사할 쿼터니언 구조체의 인스턴스입니다.
	 *
	 * @return 대입한 쿼터니언의 참조자를 반환합니다.
	 */
	Quat& operator=(Quat&& q) noexcept
	{
		if (this == &q) return *this;

		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;

		return *this;
	}


	/**
	 * @brief 쿼터니언의 대입 연산자입니다.
	 *
	 * @param q 원소를 복사할 쿼터니언 구조체의 인스턴스입니다.
	 *
	 * @return 대입한 쿼터니언의 참조자를 반환합니다.
	 */
	Quat& operator=(const Quat& q) noexcept
	{
		if (this == &q) return *this;

		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;

		return *this;
	}


	/**
	 * @brief 쿼터니언에 -부호를 취합니다.
	 *
	 * @return 쿼터니언에 -부호를 취한 새로운 벡터를 반환합니다.
	 */
	Quat operator-() const
	{
		return Quat(-x, -y, -z, -w);
	}


	/**
	 * @brief 두 쿼터니언에 대응하는 원소를 더합니다.
	 *
	 * @param q 쿼터니언의 덧셈을 수행할 피연산자입니다.
	 *
	 * @return 두 쿼터니언에 대응하는 원소를 더한 결과를 반환합니다.
	 */
	Quat operator+(Quat&& q) const
	{
		return Quat(x + q.x, y + q.y, z + q.z, w + q.w);
	}


	/**
	 * @brief 두 쿼터니언에 대응하는 원소를 더합니다.
	 *
	 * @param q 쿼터니언의 덧셈을 수행할 피연산자입니다.
	 *
	 * @return 두 쿼터니언에 대응하는 원소를 더한 결과를 반환합니다.
	 */
	Quat operator+(const Quat& q) const
	{
		return Quat(x + q.x, y + q.y, z + q.z, w + q.w);
	}


	/**
	 * @brief 두 쿼터니언에 대응하는 원소를 뺍니다.
	 *
	 * @param q 쿼터니언의 뺄셈을 수행할 피연산자입니다.
	 *
	 * @return 두 쿼터니언에 대응하는 원소를 뺀 결과를 반환합니다.
	 */
	Quat operator-(Quat&& q) const
	{
		return Quat(x - q.x, y - q.y, z - q.z, w - q.w);
	}


	/**
	 * @brief 두 쿼터니언에 대응하는 원소를 뺍니다.
	 *
	 * @param q 쿼터니언의 뺄셈을 수행할 피연산자입니다.
	 *
	 * @return 두 쿼터니언에 대응하는 원소를 뺀 결과를 반환합니다.
	 */
	Quat operator-(const Quat& q) const
	{
		return Quat(x - q.x, y - q.y, z - q.z, w - q.w);
	}


	/**
	 * @brief 쿼터니언의 스케일 연산을 수행합니다.
	 *
	 * @param s 스케일 연산을 수행할 값입니다.
	 *
	 * @return 스케일 연산을 수행한 결과를 반환합니다.
	 */
	Quat operator*(float s) const
	{
		return Quat(x * s, y * s, z * s, w * s);
	}
	

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