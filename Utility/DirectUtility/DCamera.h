#ifndef D_CAMERA_H
#define D_CAMERA_H

#include "../../Interface/ICamera.h"
#include "../../DirectDefine.h"
#include "DMatrix.h"

class DCamera : public ICamera{
private:
	DVector3	m_Eye;
	DVector3	m_Lookat;
	DVector3	m_Up;

	DVector3	m_View;
	DVector3	m_Cross;

	DMatrix		m_matView;

	DMatrix		m_matProj;

	LPDIRECT3DDEVICE9 m_pDev;
public:
	DCamera(LPDIRECT3DDEVICE9 pDev);
	virtual ~DCamera();

//	virtual void GetViewMatrixPtr(Matrix4x4* mat) override;
	virtual Matrix4x4 GetViewMatrix() override;
	virtual float* GetViewMatrixFPtr() override;
	DMatrix* GetViewDMatrixPtr();
	virtual void SetView(Vector3* pvEye, Vector3* pvLookat, Vector3* pvUp) override;

//	virtual void GetEyePtr(Vector3* pv) override;
	virtual Vector3 GetEye() override;
	virtual float* GetEyeFPtr() override;
	DVector3* GetEyeDPtr();
	virtual void SetEye(Vector3* pvEye) override;

//	virtual void GetLookatPtr(Vector3* pv) override;
	virtual Vector3 GetLookat() override;
	virtual float* GetLookatFPtr() override;
	DVector3* GetLookatDPtr();
	virtual void SetLookat(Vector3* pvLookat) override;

//	virtual void GetUpPtr(Vector3*) override;
	virtual Vector3 GetUp() override;
	virtual float* GetUpFPtr() override;
	DVector3* GetUpDPtr();
	virtual void SetUp(Vector3* pvUp) override;

	virtual void RotateLocalX(float angle) override;
	virtual void RotateLocalY(float angle) override;

	virtual void MoveTo(Vector3* pv) override;

	virtual void MoveLocalX(float dist) override;
	virtual void MoveLocalY(float dist) override;
	virtual void MoveLocalZ(float dist) override;


	virtual void SetPerspective(float fov, float aspect, float n, float f) override;
	virtual void SetOrthographic(float left, float right, float bottom, float top, float n, float f) override;

	virtual	Matrix4x4 GetProjection() override;
	virtual float* GetProjectionFPtr() override;

	DMatrix* GetProjectionDPtr();
private:
	void SetView(DVector3* pvEye, DVector3* pvLookat, DVector3* pvUp);
};

#endif