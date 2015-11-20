#ifndef COLOR4_H
#define COLOR4_H

class Color4{
public:
	float r, g, b, a;
public:
	Color4();
	Color4(float _r, float _g, float _b, float _a = 1.0f);
	~Color4();
};

Color4 operator + (const Color4& color);
Color4 operator - (const Color4& color);

Color4& operator += (Color4& color1, const Color4& color2);
Color4& operator -= (Color4& color1, const Color4& color2);
Color4& operator *= (Color4& color, float s);
Color4& operator /= (Color4& color, float s);

bool operator == (const Color4& color1, const Color4& color2);
bool operator != (const Color4& color1, const Color4& color2);

Color4 operator * (const Color4& color, float s);
Color4 operator * (float s, const Color4& color);
Color4 operator / (const Color4& color, float s);

#endif