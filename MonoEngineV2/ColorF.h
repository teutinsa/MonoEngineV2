#pragma once
#include "Core.h"

struct ColorF
{
	float r;
	float g;
	float b;
	float a;

	ColorF(float r, float g, float b, float a = 1.0f);

	operator D2D1_COLOR_F();
};