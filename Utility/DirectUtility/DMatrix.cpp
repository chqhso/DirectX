#include "DMatrix.h"

DMatrix::DMatrix(){
	matrix = D3DXMATRIXA16(
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f);
}
DMatrix::DMatrix(
	float _11, float _12, float _13, float _14,
	float _21, float _22, float _23, float _24,
	float _31, float _32, float _33, float _34,
	float _41, float _42, float _43, float _44
	){
	matrix._11 = _11;
	matrix._12 = _12;
	matrix._13 = _13;
	matrix._14 = _14;

	matrix._21 = _21;
	matrix._22 = _22;
	matrix._23 = _23;
	matrix._24 = _24;

	matrix._31 = _31;
	matrix._32 = _32;
	matrix._33 = _33;
	matrix._34 = _34;

	matrix._41 = _41;
	matrix._42 = _42;
	matrix._43 = _43;
	matrix._44 = _44;
}
DMatrix::DMatrix(const Matrix4x4& mat){
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			matrix.m[i][j] = mat.m[i][j];
		}
	}
}
void DMatrix::Copy(Matrix4x4& mat){
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			mat.m[i][j] = matrix.m[i][j];
		}
	}
}
void DMatrix::Identity(){
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			matrix.m[i][j] = i == j;
		}
	}
}

DMatrix& operator *= (DMatrix& mat1, const DMatrix& mat2){
	DMatrix result;
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			for (int k = 0; k < 4; k++){
				result.matrix.m[i][j] += mat1.matrix.m[i][k] * mat2.matrix.m[k][j];
			}
		}
	}
	mat1 = result;
	return mat1;
}
DMatrix operator * (const DMatrix& mat1, const DMatrix& mat2){
	DMatrix result = mat1;
	return result *= mat2;
	
}