#include "DLight.h"

DLight::DLight(Color3& specular, Color3& diffuse, Color3& ambient, Vector3& pos){
	SetAmbient(ambient);
	SetDiffuse(diffuse);
	SetSpecular(specular);
	SetPosition(pos);
}
DLight::~DLight(){}
void DLight::SetAmbient(Color3& ambient){
	m_Ambient = ambient;
}
void DLight::SetDiffuse(Color3& diffuse){
	m_Diffuse = diffuse;
}
void DLight::SetSpecular(Color3& specular){
	m_Specular = specular;
}
void DLight::SetPosition(Vector3& pos){
	m_position = DVector4(pos, 1.0f);
}
float* DLight::GetAmbientFPtr(){
	return (float*)&m_Ambient.color;
}
float* DLight::GetDiffuseFPtr(){
	return (float*)&m_Diffuse.color;
}
float* DLight::GetSpecularFPtr(){
	return (float*)&m_Specular.color;
}
float* DLight::GetPositionFPtr(){
	return (float*)&m_position.vector;
}
DColor4* DLight::GetAmbientDPtr(){
	return &m_Ambient;
}
DColor4* DLight::GetSpecularDPtr(){
	return &m_Specular;
}
DColor4* DLight::GetDiffuseDPtr(){
	return &m_Diffuse;
}
DVector4* DLight::GetPositionDPtr(){
	return &m_position;
}