#ifndef COLOR32_H
#define COLOR32_H

struct Color32{
public:
	float r, g, b, a;
public:
	Color32();
	Color32(float _r, float _g, float _b, float _a = 1.0f);
};

#endif