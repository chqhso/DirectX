#ifndef D_COLOR4_H
#define D_COLOR4_H

//#include "../../DirectDefine.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "../../Define.h"

class DColor4{
public:
	D3DCOLORVALUE color;
public:
	DColor4();
	DColor4(float r, float g, float b, float a);
	DColor4(const Color3& col);
	DColor4(const Color3& col, float a);
	DColor4(const Color4& col);
	void Copy(Color4& col);
};

#endif