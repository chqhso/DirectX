#include "SphereCollider.h"

SphereCollider::SphereCollider() : Collider(ColliderType::Sphere){

}
SphereCollider::SphereCollider(Vector3 pos, float radius) : Collider(ColliderType::Sphere){
	SetPos(pos);
	SetRadius(radius);
}
SphereCollider::~SphereCollider(){

}
void SphereCollider::SetPos(Vector3 pos){
	m_Pos = pos;
}
void SphereCollider::SetRadius(float radius){
	m_fRadius = radius;
}
Vector3 SphereCollider::GetPos(){
	return m_Pos;
}
float SphereCollider::GetRadius(){
	return m_fRadius;
}
bool SphereCollider::IsCollider(ICollider& other){
	switch (other.GetColliderType())
	{
	case ColliderType::Box:
		//return IsCollide((BoxCollider*)this, (BoxCollider*)&other);
		break;
	case ColliderType::Sphere:
		return IsCollide((SphereCollider*)this, (SphereCollider*)&other);
	}
}