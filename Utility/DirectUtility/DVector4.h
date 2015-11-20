#ifndef D_VECTOR4_H
#define D_VECTOR4_H

//#include "../../DirectDefine.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "../../Define.h"

class DVector4{
public:
	D3DXVECTOR4 vector;
public:
	DVector4();
	DVector4(float x, float y, float z, float w);
	DVector4(const Vector3& vec, float w);
	DVector4(const Vector4& vec);
	void Copy(Vector4& vec);
};

#endif