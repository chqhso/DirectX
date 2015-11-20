#ifndef D_VECTOR2_H
#define D_VECTOR2_H

//#include "../../DirectDefine.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "../../Define.h"

class DVector2{
public:
	D3DXVECTOR2 vector;
public:
	DVector2();
	DVector2(float x, float y);
	DVector2(const Vector2& vec);
	DVector2(const Vector3& vec);
	DVector2(const Vector4& vec);
	void Copy(Vector2& vec);
};

#endif