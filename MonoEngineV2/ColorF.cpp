#include "pch.h"
#include "ColorF.h"

ColorF::ColorF(float r, float g, float b, float a)
	: r(r), g(g), b(b), a(a)
{ }

ColorF::operator D2D1_COLOR_F()
{
	return *reinterpret_cast<D2D1_COLOR_F*>(this);
}
