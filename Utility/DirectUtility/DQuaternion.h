#ifndef D_QUATERNION_H
#define D_QUATERNION_H

//#include "../../DirectDefine.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "../../Define.h"

class DQuaternion{
public:
	D3DXQUATERNION quaternion;
public:
	DQuaternion();
	DQuaternion(float x, float y, float z, float w);
	DQuaternion(const Quaternion& quat);
	void Copy(Quaternion& quat);
};

#endif