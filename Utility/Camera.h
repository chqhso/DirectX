#ifndef CAMERA_H
#define CAMERA_H

#include "../Interface/ICamera.h"
#include "Vector3.h"
#include "Matrix4x4.h"

class Camera : public ICamera{
private:
	Vector3 m_Eye;
	Vector3 m_Lookat;
	Vector3 m_Up;

	Vector3 m_View;
	Vector3 m_Cross;

	Matrix4x4 m_matView;
	Matrix4x4 m_matProj;
public:
	Camera();
	virtual ~Camera();

	virtual const Matrix4x4& GetViewMatrix() override;
	virtual void SetView(const Vector3& pvEye, const Vector3& pvLookat, const Vector3& pvUp) override;

	virtual const Vector3& GetEye() override;
	virtual void SetEye(const Vector3& pvEye) override;

	virtual const Vector3& GetLookat() override;
	virtual void SetLookat(const Vector3& pvLookat) override;

	virtual const Vector3& GetUp() override;
	virtual void SetUp(const Vector3& pvUp) override;

	virtual void RotateLocalX(float angle) override;
	virtual void RotateLocalY(float angle) override;

	virtual void MoveTo(const Vector3& pv) override;

	virtual void MoveLocalX(float dist) override;
	virtual void MoveLocalY(float dist) override;
	virtual void MoveLocalZ(float dist) override;

	virtual void SetPerspective(float fov, float aspect, float n, float f) override;
	virtual void SetOrthographic(float left, float right, float bottom, float top, float n, float f) override;

	virtual const Matrix4x4& GetProjection() override;
};

#endif