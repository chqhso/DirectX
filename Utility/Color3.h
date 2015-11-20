#ifndef COLOR3_H
#define COLOR3_H

class Color3{
public:
	float r, g, b;
public:
	Color3();
	Color3(float _r, float _g, float _b);
	~Color3();
};

Color3 operator + (const Color3& color);
Color3 operator - (const Color3& color);

Color3& operator += (Color3& color1, const Color3& color2);
Color3& operator -= (Color3& color1, const Color3& color2);
Color3& operator *= (Color3& color, float s);
Color3& operator /= (Color3& color, float s);

bool operator == (const Color3& color1, const Color3& color2);
bool operator != (const Color3& color1, const Color3& color2);

Color3 operator * (const Color3& color, float s);
Color3 operator * (float s, const Color3& color);
Color3 operator / (const Color3& color, float s);

#endif