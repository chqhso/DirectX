#ifndef MATRIX4X4_H
#define MATRIX4X4_H

struct Vector4;
struct Vector3;
struct Quaternion;

struct Matrix4x4{
public:
	float m[4][4];
public:
	Matrix4x4();
	Matrix4x4(const Matrix4x4& other);
	Matrix4x4(float _m11, float _m12, float _m13, float _m14,
			  float _m21, float _m22, float _m23, float _m24,
			  float _m31, float _m32, float _m33, float _m34,
			  float _m41, float _m42, float _m43, float _m44);
};

Matrix4x4 operator - (const Matrix4x4& mat);
Matrix4x4 operator + (const Matrix4x4& mat);

Matrix4x4& operator += (Matrix4x4& mat1, const Matrix4x4& mat2);
Matrix4x4& operator -= (Matrix4x4& mat1, const Matrix4x4& mat2);
Matrix4x4& operator *= (Matrix4x4& mat1, const Matrix4x4& mat2);

bool operator == (const Matrix4x4& mat1, const Matrix4x4& mat2);
bool operator != (const Matrix4x4& mat1, const Matrix4x4& mat2);

Matrix4x4 operator * (const Matrix4x4& mat1, const Matrix4x4& mat2);
Vector4 operator * (const Vector4& v, const Matrix4x4& mat);
Vector3 operator * (const Vector3& v, const Matrix4x4& mat);

Matrix4x4	Scale(const Vector3& s);
Matrix4x4	RotateX(float angle);
Matrix4x4	RotateY(float angle);
Matrix4x4	RotateZ(float angle);
Matrix4x4	Rotate(const Quaternion& q);
Matrix4x4	Rotate(const Vector3& v, float angle);
Matrix4x4	Translate(const Vector3& p);
Vector3		Transform(const Vector3& v, const Matrix4x4& mat);
Vector3		TransformCoord(const Vector3& v, const Matrix4x4& mat);
Vector3		TransformNormal(const Vector3& v, const Matrix4x4& mat);
Vector4		Transform(const Vector4& v, const Matrix4x4& mat);
Matrix4x4	Identity();
Matrix4x4	Inverse(const Matrix4x4& mat);
Matrix4x4	Transpose(const Matrix4x4& mat);
Matrix4x4	Orthographic(float left, float right, float bottom, float top, float zNear, float zFar);
Matrix4x4	Perspective(float fov, float aspect, float zNear, float zFar);
Matrix4x4	LookAt(const Vector3& eye, const Vector3& at, const Vector3& up);
Matrix4x4	Screen(float x, float y, float width, float height);
/// OpenGL
static Matrix4x4	TRS(const Vector3& pos, const Quaternion& q, const Vector3& s);
/// DirectX
static Matrix4x4	SRT(const Vector3& pos, const Quaternion& q, const Vector3& s);

#endif