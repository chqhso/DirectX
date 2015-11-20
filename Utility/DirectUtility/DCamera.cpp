#include "DCamera.h"

DCamera::DCamera(LPDIRECT3DDEVICE9 pDev) : m_pDev(pDev){

}
DCamera::~DCamera(){

}

Matrix4x4 DCamera::GetViewMatrix(){
	Matrix4x4 mat;
	m_matView.Copy(mat);
	return mat;
}
float* DCamera::GetViewMatrixFPtr(){
	return (float*)&m_matView.matrix;
}
DMatrix* DCamera::GetViewDMatrixPtr(){
	return &m_matView;
}
void DCamera::SetView(Vector3* pvEye, Vector3* pvLookat, Vector3* pvUp){
	SetEye(pvEye);
	SetLookat(pvLookat);
	SetUp(pvUp);
	D3DXVec3Normalize(&m_View.vector, &(m_Lookat.vector - m_Eye.vector));
	D3DXVec3Cross(&m_Cross.vector, &m_Up.vector, &m_View.vector);

	D3DXMatrixLookAtLH(&m_matView.matrix, &m_Eye.vector, &m_Lookat.vector, &m_Up.vector);
}
void DCamera::SetView(DVector3* pvEye, DVector3* pvLookat, DVector3* pvUp){
	m_Eye = *pvEye;
	m_Lookat = *pvLookat;
	m_Up = *pvUp;
	D3DXVec3Normalize(&m_View.vector, &(m_Lookat.vector - m_Eye.vector));
	D3DXVec3Cross(&m_Cross.vector, &m_Up.vector, &m_View.vector);

	D3DXMatrixLookAtLH(&m_matView.matrix, &m_Eye.vector, &m_Lookat.vector, &m_Up.vector);
}

Vector3 DCamera::GetEye(){
	Vector3	pv;
	m_Eye.Copy(pv);
	return pv;
}
float* DCamera::GetEyeFPtr(){
	return (float*)&m_Eye.vector;
}
DVector3* DCamera::GetEyeDPtr(){
	return &m_Eye;
}
void DCamera::SetEye(Vector3* pvEye){
	m_Eye = *pvEye;
}

Vector3 DCamera::GetLookat(){
	Vector3 pv;
	m_Lookat.Copy(pv);
	return pv;
}
float* DCamera::GetLookatFPtr(){
	return (float*)&m_Lookat.vector;
}
DVector3* DCamera::GetLookatDPtr(){
	return &m_Lookat;
}
void DCamera::SetLookat(Vector3* pvLookat){
	m_Lookat = *pvLookat;
}

Vector3 DCamera::GetUp(){
	Vector3 pv;
	m_Up.Copy(pv);
	return pv;
}
float* DCamera::GetUpFPtr(){
	return (float*)&m_Up.vector;
}
DVector3* DCamera::GetUpDPtr(){
	return &m_Up;
}
void DCamera::SetUp(Vector3* pvUp){
	m_Up = *pvUp;
}

void DCamera::RotateLocalX(float angle){
	DMatrix matRot;
	D3DXMatrixRotationAxis(&matRot.matrix, &m_Cross.vector, angle);

	DVector3 NewDst;
	D3DXVec3TransformCoord(&NewDst.vector, &m_View.vector, &matRot.matrix);
	NewDst.vector += m_Eye.vector;

	SetView(&m_Eye, &NewDst, &m_Up);
}
void DCamera::RotateLocalY(float angle){
	DMatrix matRot;
	D3DXMatrixRotationAxis(&matRot.matrix, &m_Up.vector, angle);

	DVector3 NewDst;
	D3DXVec3TransformCoord(&NewDst.vector, &m_View.vector, &matRot.matrix);
	NewDst.vector += m_Eye.vector;

	SetView(&m_Eye, &m_Up, &m_Up);
}

void DCamera::MoveTo(Vector3* pv){
	DVector3 v = *pv;
	DVector3 dv;
	dv.vector = v.vector - m_Eye.vector;
	SetEye(pv);
	m_Lookat.vector += dv.vector;
	SetView(&m_Eye, &m_Lookat, &m_Up);
}

void DCamera::MoveLocalX(float dist){
	DVector3 NewEye = m_Eye;
	DVector3 NewDst = m_Lookat;

	DVector3 Move;
	D3DXVec3Normalize(&Move.vector, &m_Cross.vector);
	Move.vector *= dist;
	NewEye.vector += Move.vector;
	NewDst.vector += Move.vector;

	SetView(&NewEye, &NewDst, &m_Up);
}
void DCamera::MoveLocalY(float dist){
	DVector3 NewEye = m_Eye;
	DVector3 NewDst = m_Lookat;

	DVector3 Move;
	D3DXVec3Normalize(&Move.vector, &m_Up.vector);
	Move.vector *= dist;
	NewEye.vector += Move.vector;
	NewDst.vector += Move.vector;

	SetView(&NewEye, &NewDst, &m_Up);
}
void DCamera::MoveLocalZ(float dist){
	DVector3 NewEye = m_Eye;
	DVector3 NewDst = m_Lookat;

	DVector3 Move;
	D3DXVec3Normalize(&Move.vector, &m_View.vector);
	Move.vector *= dist;
	NewEye.vector += Move.vector;
	NewDst.vector += Move.vector;

	SetView(&NewEye, &NewDst, &m_Up);
}

void DCamera::SetPerspective(float fov, float aspect, float n, float f){
	D3DXMatrixPerspectiveFovLH(&m_matProj.matrix, fov, aspect, n, f);
}
void DCamera::SetOrthographic(float left, float right, float bottom, float top, float n, float f){
	D3DXMatrixOrthoOffCenterLH(&m_matProj.matrix, left, right, bottom, top, n, f);
}

Matrix4x4 DCamera::GetProjection(){
	Matrix4x4 mat;
	m_matProj.Copy(mat);
	return mat;
}
float* DCamera::GetProjectionFPtr(){
	return (float*)&m_matProj.matrix;
}

DMatrix* DCamera::GetProjectionDPtr(){
	return &m_matProj;
}