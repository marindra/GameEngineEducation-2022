#pragma once

#include "../RenderObject.h"

namespace
{
	struct PosColorVertex
	{
		float m_x;
		float m_y;
		float m_z;
		uint32_t m_abgr;
	};
};

class Cube : public RenderObject
{
public:
	Cube();

private:
	inline static const PosColorVertex s_cubeVertices[] =
	{
		{ 0.0f,  4.0f,  0.0f, 0xffffffff},
		{ 2.0f,  0.0f, -2.0f, 0xffff0000},
		{ 2.0f,  0.0f,  2.0f, 0xff00ff00},
		{-2.0f,  0.0f,  2.0f, 0xff0000ff},
		{-2.0f,  0.0f, -2.0f, 0xffffff00},
		{ 0.0f, -4.0f,  0.0f, 0xff000000},
	};

	inline static const uint16_t s_cubeTriList[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 1,
		1, 4, 5,
		1, 5, 2,
		2, 5, 3,
		3, 5, 4,
	};
};

