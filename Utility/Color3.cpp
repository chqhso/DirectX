#include "Color3.h"

Color3::Color3() : r(0.0f), g(0.0f), b(0.0f) {}
Color3::Color3(float _r, float _g, float _b) : r(_r), g(_g), b(_b){}
Color3::~Color3(){}


Color3 operator + (const Color3& color){
	return color;
}
Color3 operator - (const Color3& color){
	return Color3(-color.r, -color.g, -color.b);
}

Color3& operator += (Color3& color1, const Color3& color2){
	color1.r += color2.r;
	color1.g += color2.g;
	color1.b += color2.b;
	return color1;
}
Color3& operator -= (Color3& color1, const Color3& color2){
	return color1 += -color2;
}
Color3& operator *= (Color3& color, float s){
	color.r *= s;
	color.g *= s;
	color.b *= s;
	return color;
}
Color3& operator /= (Color3& color, float s){
	return color *= 1.0f / s;
}

bool operator == (const Color3& color1, const Color3& color2){
	return (color1.r == color2.r) && (color1.g == color2.g) && (color1.b == color2.b);
}
bool operator != (const Color3& color1, const Color3& color2){
	return !(color1 == color2);
}

Color3 operator * (const Color3& color, float s){
	Color3 result = color;
	return result *= s;
}
Color3 operator * (float s, const Color3& color){
	return color * s;
}
Color3 operator / (const Color3& color, float s){
	Color3 result = color;
	return result /= s;
}