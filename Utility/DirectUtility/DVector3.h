#ifndef D_VECTOR3_H
#define D_VECTOR3_H

//#include "../../DirectDefine.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "../../Define.h"

class DVector3{
public:
	D3DXVECTOR3 vector;
public:
	DVector3();
	DVector3(float x, float y, float z);
	DVector3(const Vector2& vec, float z);
	DVector3(const Vector3& vec);
	DVector3(const Vector4& vec);
	void Copy(Vector3& vec);
};

#endif