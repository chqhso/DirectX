#include "Matrix4x4.h"
#include "Vector4.h"
#include "Vector3.h"
#include "Quaternion.h"
#include <cmath>

Matrix4x4::Matrix4x4() {
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			m[i][j] = 0.0f;
		}
	}
}
Matrix4x4::Matrix4x4(const Matrix4x4& other) {
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			m[i][j] = other.m[i][j];
		}
	}
}
Matrix4x4::Matrix4x4(float _m11, float _m12, float _m13, float _m14,
		  float _m21, float _m22, float _m23, float _m24,
		  float _m31, float _m32, float _m33, float _m34,
		  float _m41, float _m42, float _m43, float _m44) {
	m[0][0] = _m11; m[0][1] = _m12; m[0][2] = _m13; m[0][3] = _m14;
	m[1][0] = _m21; m[1][1] = _m22; m[1][2] = _m23; m[1][3] = _m24;
	m[2][0] = _m31; m[2][1] = _m32; m[2][2] = _m33; m[2][3] = _m34;
	m[3][0] = _m41; m[3][1] = _m42; m[3][2] = _m43; m[3][3] = _m44;
}

Matrix4x4 operator - (const Matrix4x4& mat){
	Matrix4x4 result;

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			result.m[i][j] = -mat.m[i][j];
		}
	}

	return result;
}
Matrix4x4 operator + (const Matrix4x4& mat){
	return mat;
}

Matrix4x4& operator += (Matrix4x4& mat1, const Matrix4x4& mat2){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			mat1.m[i][j] += mat2.m[i][j];
		}
	}
	return mat1;
}
Matrix4x4& operator -= (Matrix4x4& mat1, const Matrix4x4& mat2){
	return mat1 += -mat2;
}
Matrix4x4& operator *= (Matrix4x4& mat1, const Matrix4x4& mat2){
	Matrix4x4 result;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			for(int k = 0; k < 4; k++){
				result.m[i][j] += mat1.m[i][k] * mat2.m[k][j];
			}
		}
	}
	mat1 = result;
	return mat1;
}

bool operator == (const Matrix4x4& mat1, const Matrix4x4& mat2){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(mat1.m[i][j] != mat2.m[i][j])
				return false;
		}
	}
	return true;
}
bool operator != (const Matrix4x4& mat1, const Matrix4x4& mat2){
	return !(mat1 == mat2);
}

Matrix4x4 operator * (const Matrix4x4& mat1, const Matrix4x4& mat2){
	Matrix4x4 result = mat1;
	return result *= mat2;
}
Vector4 operator * (const Vector4& v, const Matrix4x4& mat){
	return Transform(v, mat);
}
Vector3 operator * (const Vector3& v, const Matrix4x4& mat){
	return Transform(v, mat);
}
Matrix4x4	Scale(const Vector3& s){
	Matrix4x4 result(
		s.x, 0.0f, 0.0f, 0.0f,
		0.0f, s.y, 0.0f, 0.0f,
		0.0f, 0.0f, s.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);
	return result;
}
Matrix4x4	RotateX(float angle){
	float _sin = sin(angle);
	float _cos = cos(angle);
	Matrix4x4 result(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, _cos, _sin, 0.0f,
		0.0f, -_sin, _cos, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);
	return result;
}
Matrix4x4	RotateY(float angle){
	float _sin = sin(angle);
	float _cos = cos(angle);
	Matrix4x4 result(
		_cos, 0.0f, -_sin, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		_sin, 0.0f, _cos, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);
	return result;
}
Matrix4x4	RotateZ(float angle){
	float _sin = sin(angle);
	float _cos = cos(angle);
	Matrix4x4 result(
		_cos, _sin, 0.0f, 0.0f,
		-_sin, _cos, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);
	return result;
}
Matrix4x4	Rotate(const Quaternion& q){
	float xx = q.x * q.x * 2.0f;
	float yy = q.y * q.y * 2.0f;
	float zz = q.z * q.z * 2.0f;
	float xy = q.x * q.y * 2.0f;
	float xz = q.x * q.z * 2.0f;
	float yz = q.y * q.z * 2.0f;
	float wx = q.w * q.x * 2.0f;
	float wy = q.w * q.y * 2.0f;
	float wz = q.w * q.z * 2.0f;

	//Matrix4x4 result(
	//	1.0f - yy - zz, xy + wz, xz - wy, 0.0f,
	//	xy - wz, 1.0f - xx - zz, yz + wz, 0.0f,
	//	xz + wy, yz - wx, 1.0f - xx - yy, 0.0f,
	//	0.0f, 0.0f, 0.0f, 1.0f
	//	);


	Matrix4x4 result(
		1.0f - yy - zz, xy + wz, xz - wy, 0.0f,
		xy - wz, 1.0f - xx - zz, yz + wx, 0.0f,
		xz + wy, yz - wx, 1.0f - xx - yy, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);

	return result;
}
Matrix4x4	Rotate(const Vector3& v, float angle){
	/** 规过1
	float _cos = cos(angle);
	float _sin = sin(angle);

	float xx = axe.x * axe.x;
	float yy = axe.y * axe.y;
	float zz = axe.z * axe.z;
	float xy = axe.x * axe.y;
	float xz = axe.x * axe.z;
	float yz = axe.y * axe.z;
	float oneminuscos = (1 - _cos);

	Matrix4x4 result(
	xx * oneminuscos + _cos, xy * oneminuscos + axe.z * _sin, xz * oneminuscos - axe.y * _sin, 0.0f,
	xy * oneminuscos - axe.z * _sin,		 yy * oneminuscos + _cos, yz * oneminuscos + axe.x * _sin, 0.0f,
	xz * oneminuscos + axe.y * _sin, yz * oneminuscos - axe.x * _sin,		  zz * oneminuscos + _cos, 0.0f,
	0.0f,							0.0f,							 0.0f, 1.0f
	);
	return result;
	*/
	return Rotate(Quaternion(v, angle));
}
Matrix4x4	Translate(const Vector3& p){
	Matrix4x4 result(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		p.x, p.y, p.z, 1.0f
		);
	return result;
}
Vector3		Transform(const Vector3& v, const Matrix4x4& mat){
	Vector4 v4 = Transform(Vector4(v.x, v.y, v.z, 1.0f), mat);
	return Vector3(v4.x, v4.y, v4.z);
}
Vector3		TransformCoord(const Vector3& v, const Matrix4x4& mat){
	float w = v.x * mat.m[0][3] + v.y * mat.m[1][3] + v.z * mat.m[2][3] + mat.m[3][3];
	Vector3 result = {
		(v.x * mat.m[0][0] + v.y * mat.m[1][0] + v.z * mat.m[2][0] + mat.m[3][0]) / w,
		(v.x * mat.m[0][1] + v.y * mat.m[1][1] + v.z * mat.m[2][1] + mat.m[3][1]) / w,
		(v.x * mat.m[0][2] + v.y * mat.m[1][2] + v.z * mat.m[2][2] + mat.m[3][2]) / w
	};
	return result;

}
Vector3		TransformNormal(const Vector3& v, const Matrix4x4& mat){
	Vector3 result(
		(v.x * mat.m[0][0] + v.y * mat.m[0][1] + v.z * mat.m[0][2]),
		(v.x * mat.m[1][0] + v.y * mat.m[1][1] + v.z * mat.m[1][2]),
		(v.x * mat.m[2][0] + v.y * mat.m[2][1] + v.z * mat.m[2][2])
		);
	return result;
}
Vector4		Transform(const Vector4& v, const Matrix4x4& mat){
	Vector4 result(
		(v.x * mat.m[0][0] + v.y * mat.m[1][0] + v.z * mat.m[2][0] + v.w * mat.m[3][0]),
		(v.x * mat.m[0][1] + v.y * mat.m[1][1] + v.z * mat.m[2][1] + v.w * mat.m[3][1]),
		(v.x * mat.m[0][2] + v.y * mat.m[1][2] + v.z * mat.m[2][2] + v.w * mat.m[3][2]),
		(v.x * mat.m[0][3] + v.y * mat.m[1][3] + v.z * mat.m[2][3] + v.w * mat.m[3][3])
		);
	return result;
}
Matrix4x4	Identity(){
	static const Matrix4x4 result(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);
	return result;
}
Matrix4x4	Inverse(const Matrix4x4& mat){
	float a0 = mat.m[0][0] * mat.m[1][1] - mat.m[0][1] * mat.m[1][0];
	float a1 = mat.m[0][0] * mat.m[1][2] - mat.m[0][2] * mat.m[1][0];
	float a2 = mat.m[0][0] * mat.m[1][3] - mat.m[0][3] * mat.m[1][0];
	float a3 = mat.m[0][1] * mat.m[1][2] - mat.m[0][2] * mat.m[1][1];
	float a4 = mat.m[0][1] * mat.m[1][3] - mat.m[0][3] * mat.m[1][1];
	float a5 = mat.m[0][2] * mat.m[1][3] - mat.m[0][3] * mat.m[1][2];

	float b0 = mat.m[2][0] * mat.m[3][1] - mat.m[2][1] * mat.m[3][0];
	float b1 = mat.m[2][0] * mat.m[3][2] - mat.m[2][2] * mat.m[3][0];
	float b2 = mat.m[2][0] * mat.m[3][3] - mat.m[2][3] * mat.m[3][0];
	float b3 = mat.m[2][1] * mat.m[3][2] - mat.m[2][2] * mat.m[3][1];
	float b4 = mat.m[2][1] * mat.m[3][3] - mat.m[2][3] * mat.m[3][1];
	float b5 = mat.m[2][2] * mat.m[3][3] - mat.m[2][3] * mat.m[3][2];

	float det = (a0 * b5) - (a1 * b4) + (a2 * b3) + (a3 * b2) - (a4 * b1) + (a5 * b0);

	if (det == 0.0f){
		return mat; // 开青纺捞 粮犁X
	}

	float invDet = 1.0f / det;

	Matrix4x4 result(
		(mat.m[1][1] * b5 - mat.m[1][2] * b4 + mat.m[1][3] * b3) * invDet,
		(-mat.m[0][1] * b5 + mat.m[0][2] * b4 - mat.m[0][3] * b3) * invDet,
		(mat.m[3][1] * a5 - mat.m[3][2] * a4 + mat.m[3][3] * a3) * invDet,
		(-mat.m[2][1] * a5 + mat.m[2][2] * a4 - mat.m[2][3] * a3) * invDet,
		(-mat.m[1][0] * b5 + mat.m[1][2] * b2 - mat.m[1][3] * b1) * invDet,
		(mat.m[0][0] * b5 - mat.m[0][2] * b2 + mat.m[0][3] * b1) * invDet,
		(-mat.m[3][0] * a5 + mat.m[3][2] * a2 - mat.m[3][3] * a1) * invDet,
		(mat.m[2][0] * a5 - mat.m[2][2] * a2 + mat.m[2][3] * a1) * invDet,
		(mat.m[1][0] * b4 - mat.m[1][1] * b2 + mat.m[1][3] * b0) * invDet,
		(-mat.m[0][0] * b4 + mat.m[0][1] * b2 - mat.m[0][3] * b0) * invDet,
		(mat.m[3][0] * a4 - mat.m[3][1] * a2 + mat.m[3][3] * a0) * invDet,
		(-mat.m[2][0] * a4 + mat.m[2][1] * a2 - mat.m[2][3] * a0) * invDet,
		(-mat.m[1][0] * b3 + mat.m[1][1] * b1 - mat.m[1][2] * b0) * invDet,
		(mat.m[0][0] * b3 - mat.m[0][1] * b1 + mat.m[0][2] * b0) * invDet,
		(-mat.m[3][0] * a3 + mat.m[3][1] * a1 - mat.m[3][2] * a0) * invDet,
		(mat.m[2][0] * a3 - mat.m[2][1] * a1 + mat.m[2][2] * a0) * invDet
		);
	return result;
}
Matrix4x4	Transpose(const Matrix4x4& mat){
	Matrix4x4 result(
		mat.m[0][0], mat.m[1][0], mat.m[2][0], mat.m[3][0],
		mat.m[0][1], mat.m[1][1], mat.m[2][1], mat.m[3][1],
		mat.m[0][2], mat.m[1][2], mat.m[2][2], mat.m[3][2],
		mat.m[0][3], mat.m[1][3], mat.m[2][3], mat.m[3][3]
		);

	/*
	for(int i = 0; i < 4; i++){
	for(int j = 0; j < 4; j++){
	result.m[i][j] = mat.m[j][i];
	}
	}
	*/
	return result;
}

Matrix4x4	Orthographic(float left, float right, float bottom, float top, float zNear, float zFar){
	//Matrix4x4 result(
	//	2.0f / (right - left), 0.0f, 0.0f, -((right + left) / (right - left)),
	//	0.0f, 2.0f / (top - bottom), 0.0f, -((top + bottom) / (top - bottom)),
	//	0.0f, 0.0f, -(2.0f / (zFar - zNear)), -((zFar + zNear) / (zFar - zNear)),
	//	0.0f, 0.0f, 0.0f, 1.0f
	//	);
	Matrix4x4 result(
		2.0f / (right - left), 0.0f, 0.0f, -((right + left) / (right - left)),
		0.0f, 2.0f / (top - bottom), 0.0f, -((top + bottom) / (top - bottom)),
		0.0f, 0.0f, (1.0f / (zFar - zNear)), -((zNear) / (zFar - zNear)),
		0.0f, 0.0f, 0.0f, 1.0f
		);
	return result;
}
Matrix4x4	Perspective(float fov, float aspect, float zNear, float zFar){
	//float ys = 1.0f / tan(fov / 2.0f);
	//float xs = ys / aspect;
	//Matrix4x4 result(
	//	xs, 0.0f, 0.0f, 0.0f,
	//	0.0f, ys, 0.0f, 0.0f,
	//	0.0f, 0.0f, (zFar + zNear) / (zNear - zFar), 1.0f,
	//	0.0f, 0.0f, (2.0f* zFar * zNear) / (zNear - zFar), 0.0f
	//	);

	float ys = 1.0f / tan(fov / 2.0f);
	float xs = ys / aspect;
	Matrix4x4 result(
		xs, 0.0f, 0.0f, 0.0f,
		0.0f, ys, 0.0f, 0.0f,
		0.0f, 0.0f, (zFar) / (zFar - zNear), 1.0f,
		0.0f, 0.0f, -(zFar * zNear) / (zFar - zNear), 0.0f
		);

	return result;
}
Matrix4x4	LookAt(const Vector3& eye, const Vector3& at, const Vector3& up){
	Vector3 z = Normalized(at - eye);
	Vector3 x = Normalized(Cross(up, z));
	Vector3 y = Cross(z, x);

	Matrix4x4 result(
		x.x, y.x, z.x, 0.0f,
		x.y, y.y, z.y, 0.0f,
		x.z, y.z, z.z, 0.0f,
		-Dot(eye, x), -Dot(eye, y), -Dot(eye, z), 1.0f
		);
	return result;
}
Matrix4x4	Screen(float x, float y, float width, float height){
	float w = width / 2.0f;
	float h = height / 2.0f;
	Matrix4x4 result(
		w, 0.0f, 0.0f, 0.0f,
		0.0f, -h, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		w + x, h + y, 0.0f, 1.0f
		);
	return result;
}
/// OpenGL??
Matrix4x4	TRS(const Vector3& pos, const Quaternion& q, const Vector3& s){
	return Translate(pos) * Rotate(q) * Scale(s);
}
///DirectX??
Matrix4x4	SRT(const Vector3& pos, const Quaternion& q, const Vector3& s){
	return Scale(s) * Rotate(q) * Translate(pos);
}
