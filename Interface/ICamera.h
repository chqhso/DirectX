#ifndef I_CAMERA_H
#define I_CAMERA_H

#include "../Define.h"

class ICamera{
public:
	ICamera(){}
	virtual ~ICamera(){}

//	virtual void GetViewMatrixPtr(Matrix4x4* mat) = 0;
	virtual const Matrix4x4& GetViewMatrix() = 0;
	virtual void SetView(const Vector3& pvEye, const Vector3& pvLookat, const Vector3& pvUp) = 0;

//	virtual void GetEyePtr(Vector3* pv) = 0;
	virtual const Vector3& GetEye() = 0;
	virtual void SetEye(const Vector3& pvEye) = 0;

//	virtual void GetLookatPtr(Vector3* pv) = 0;
	virtual const Vector3& GetLookat() = 0;
	virtual void SetLookat(const Vector3& pvLookat) = 0;

//	virtual void GetUpPtr(Vector3* pv) = 0;
	virtual const Vector3& GetUp() = 0;
	virtual void SetUp(const Vector3& pvUp) = 0;

	virtual void RotateLocalX(float angle) = 0;
	virtual void RotateLocalY(float angle) = 0;

	virtual void MoveTo(const Vector3& pv) = 0;

	virtual void MoveLocalX(float dist) = 0;
	virtual void MoveLocalY(float dist) = 0;
	virtual void MoveLocalZ(float dist) = 0;

	virtual void SetPerspective(float fov, float aspect, float n, float f) = 0;
	virtual void SetOrthographic(float left, float right, float bottom, float top, float n, float f) = 0;

	virtual const Matrix4x4& GetProjection() = 0;
};

#endif