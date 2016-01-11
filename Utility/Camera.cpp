#include "Camera.h"

Camera::Camera(){}
Camera::~Camera(){}


const Matrix4x4& Camera::GetViewMatrix(){
	return m_matView;
}
void Camera::SetView(const Vector3& pvEye, const Vector3& pvLookat, const Vector3& pvUp){
	SetEye(pvEye);
	SetLookat(pvLookat);
	SetUp(pvUp);
	
	m_View = Normalized(m_Lookat - m_Eye);
	m_Cross = Cross(m_Up, m_View);

	m_matView = LookAt(m_Eye,m_Lookat, m_Up);
}

const Vector3& Camera::GetEye(){
	return m_Eye;
}
void Camera::SetEye(const Vector3& pvEye){
	m_Eye = pvEye;
}

const Vector3& Camera::GetLookat(){
	return m_Lookat;
}
void Camera::SetLookat(const Vector3& pvLookat){
	m_Lookat = pvLookat;
}

const Vector3& Camera::GetUp(){
	return m_Up;
}
void Camera::SetUp(const Vector3& pvUp){
	m_Up = pvUp;
}
// TODO
void Camera::RotateLocalX(float angle){
	Matrix4x4 matRot;
	matRot = Rotate(m_Cross, angle);

	Vector3 newDst;
	newDst = TransformCoord(m_View, matRot);
	newDst += m_Eye;

	SetView(m_Eye, newDst, m_Up);
}
void Camera::RotateLocalY(float angle){
	Matrix4x4 matRot;
	matRot = Rotate(m_Up, angle);

	Vector3 newDst;
	newDst = TransformCoord(m_View, matRot);
	newDst += m_Eye;

	SetView(m_Eye, newDst, m_Up);
}

void Camera::MoveTo(const Vector3& pv){
	Vector3 dv = pv - m_Eye;
	SetEye(pv);
	m_Lookat += dv;
	SetView(m_Eye, m_Lookat, m_Up);
}

void Camera::MoveLocalX(float dist){
	Vector3 newEye = m_Eye;
	Vector3 newDst = m_Lookat;
	Vector3 direction = Normalized(m_Cross);
	direction *= dist;
	newEye += direction;
	newDst += direction;
	SetView(newEye, newDst, m_Up);
}
void Camera::MoveLocalY(float dist){
	Vector3 newEye = m_Eye;
	Vector3 newDst = m_Lookat;
	Vector3 direction = Normalized(m_Up);
	direction *= dist;
	newEye += direction;
	newDst += direction;
	SetView(newEye, newDst, m_Up);
}
void Camera::MoveLocalZ(float dist){
	Vector3 newEye = m_Eye;
	Vector3 newDst = m_Lookat;
	Vector3 direction = Normalized(m_View);
	direction *= dist;
	newEye += direction;
	newDst += direction;
	SetView(newEye, newDst, m_Up);
}

void Camera::SetPerspective(float fov, float aspect, float n, float f){
	m_matProj = Perspective(fov, aspect, n, f);
}
void Camera::SetOrthographic(float left, float right, float bottom, float top, float n, float f){
	m_matProj = Orthographic(left, right, bottom, top, n, f);
}

const Matrix4x4& Camera::GetProjection(){
	return m_matProj;
}