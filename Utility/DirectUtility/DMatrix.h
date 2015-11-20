#ifndef D_MATRIX_H
#define D_MATRIX_H

//#include "../../DirectDefine.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "../../Define.h"

class DMatrix{
public:
	D3DXMATRIXA16 matrix;
public:
	DMatrix();
	DMatrix(
		float _11, float _12, float _13, float _14,
		float _21, float _22, float _23, float _24,
		float _31, float _32, float _33, float _34,
		float _41, float _42, float _43, float _44
		);
	DMatrix(const Matrix4x4& mat);
	void Copy(Matrix4x4& mat);
	void Identity();
};

DMatrix& operator *= (DMatrix& mat1, const DMatrix& mat2);

DMatrix operator * (const DMatrix& mat1, const DMatrix& mat2);


#endif