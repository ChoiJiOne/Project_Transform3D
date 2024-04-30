#pragma once

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"


/**
 * @brief 2D 위치 정보를 가진 정점입니다.
 */
struct VertexPosition2D
{
	/**
	 * @brief 2D 위치 정보를 가진 정점의 기본 생성자입니다.
	 */
	VertexPosition2D() noexcept : position(0.0f, 0.0f) {}


	/**
	 * @brief 2D 위치 정보를 가진 정점의 생성자입니다.
	 *
	 * @param p 정점의 위치입니다.
	 */
	VertexPosition2D(Vec2f&& p) noexcept : position(p) {}


	/**
	 * @brief 2D 위치 정보를 가진 정점의 생성자입니다.
	 *
	 * @param p 정점의 위치입니다.
	 */
	VertexPosition2D(const Vec2f& p) noexcept : position(p) {}


	/**
	 * @brief 2D 위치 정보를 가진 정점의 생성자입니다.
	 *
	 * @param x 위치의 X좌표입니다.
	 * @param y 위치의 Y좌표입니다.
	 */
	VertexPosition2D(float x, float y) noexcept : position(x, y) {}


	/**
	 * @brief 2D 위치 정보를 가진 정점의 생성자입니다.
	 *
	 * @param instance 복사할 정점 인스턴스입니다.
	 */
	VertexPosition2D(VertexPosition2D&& instance) noexcept
		: position(instance.position) {}


	/**
	 * @brief 2D 위치 정보를 가진 정점의 생성자입니다.
	 *
	 * @param instance 복사할 정점 인스턴스입니다.
	 */
	VertexPosition2D(const VertexPosition2D& instance) noexcept
		: position(instance.position) {}


	/**
	 * @brief 2D 위치 정보를 가진 정점의 대입 연산자입니다.
	 *
	 * @param instance 대입할 정점 인스턴스입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	VertexPosition2D& operator=(VertexPosition2D&& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;

		return *this;
	}


	/**
	 * @brief 2D 위치 정보를 가진 정점의 대입 연산자입니다.
	 *
	 * @param instance 대입할 정점 인스턴스입니다.
	 *
	 * @return 대입한 객체의 참조자를 반환합니다.
	 */
	VertexPosition2D& operator=(const VertexPosition2D& instance) noexcept
	{
		if (this == &instance) return *this;

		position = instance.position;

		return *this;
	}


	/**
	 * @brief 정점의 바이트 보폭 값을 얻습니다.
	 *
	 * @return 정점의 파이트 보폭(Stride) 값을 반환합니다.
	 */
	static uint32_t GetStride()
	{
		return sizeof(VertexPosition2D);
	}


	/**
	 * @brief 정점의 위치입니다.
	 */
	Vec2f position;
};
