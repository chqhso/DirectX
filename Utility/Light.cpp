#include "Light.h"

Light::Light(const Color32& diffuse, const Color32& specular, const Color32& ambient, const Vector3& pos){
	SetDiffuse(diffuse);
	SetSpecular(specular);
	SetAmbient(ambient);
	SetPosition(pos);
}
Light::~Light(){}
void Light::SetAmbient(const Color32& color){
	m_ambient = color;
}
void Light::SetDiffuse(const Color32& color){
	m_diffuse = color;
}
void Light::SetSpecular(const Color32& color){
	m_specular = color;
}
void Light::SetPosition(const Vector3& pos){
	m_position = pos;
}
const Color32& Light::GetAmbient(){
	return m_ambient;
}
const Color32& Light::GetDiffuse(){
	return m_diffuse;
}
const Color32& Light::GetSpecular(){
	return m_specular;
}
const Vector3& Light::GetPosition(){
	return m_position;
}