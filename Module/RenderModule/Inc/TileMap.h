#pragma once

#include <cstdint>

#include "IResource.h"


/**
 * @brief 격자 타일 맵입니다.
 * 
 * @note
 * - 격자 타일맵의 크기는 반드시 2^n 입니다.
 * - 격자 타일맵의 크기는 외부에서 특수한 값으로만 지정할 수 있습니다.
 */
class TileMap : public IResource
{
public:
	/**
	 * @brief 격자 타일맵의 크기입니다.
	 */
	enum class ESize
	{
		Size_128x128 = 128,
		Size_256x256 = 256,
		Size_512x512 = 512,
		Size_1024x1024 = 1024,
		Size_2048x2048 = 2048,
	};


public:
	/**
	 * @brief 격자 타일맵의 가로 크기입니다.
	 * 
	 * @note 격자 타일맵의 크기는 반드시 2^n 입니다.
	 */
	int32_t width_ = 0;


	/**
	 * @brief 격자 타일맵의 세로 크기입니다.
	 * 
	 * @note 격자 타일맵의 크기는 반드시 2^n 입니다.
	 */
	int32_t height_ = 0;
};