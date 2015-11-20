#include "Color4.h"

Color4::Color4() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}
Color4::Color4(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) {}
Color4::~Color4(){}

Color4 operator + (const Color4& color){
	return color;
}
Color4 operator - (const Color4& color){
	return Color4(-color.r, -color.g, -color.b, -color.a);
}

Color4& operator += (Color4& color1, const Color4& color2){
	color1.a += color2.a;
	color1.r += color2.r;
	color1.g += color2.g;
	color1.b += color2.b;

	return color1;
}
Color4& operator -= (Color4& color1, const Color4& color2){
	return color1 += -color2;
}
Color4& operator *= (Color4& color, float s){
	color.r *= s;
	color.g *= s;
	color.b *= s;
	color.a *= s;

	return color;
}
Color4& operator /= (Color4& color, float s){
	return color *= 1.0f / s;
}

bool operator == (const Color4& color1, const Color4& color2){
	return (color1.a == color2.a) && (color1.r == color2.r) && (color1.g == color2.g) && (color1.b == color2.b);
}
bool operator != (const Color4& color1, const Color4& color2){
	return !(color1 == color2);
}

Color4 operator * (const Color4& color, float s){
	Color4 result = color;
	return result *= s;
}
Color4 operator * (float s, const Color4& color){
	Color4 result = color;
	return result *= s;
}
Color4 operator / (const Color4& color, float s){
	Color4 result = color;
	return result /= s;
}