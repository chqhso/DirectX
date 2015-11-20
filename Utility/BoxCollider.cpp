#include "BoxCollider.h"

BoxCollider::BoxCollider() : Collider(ColliderType::Box){
	SetPos(Vector3(0.0f, 0.0f, 0.0f));
	SetSize(Vector3(1.0f, 1.0f, 1.0f));
}
BoxCollider::BoxCollider(Vector3 pos, Vector3 size) : Collider(ColliderType::Box){
	SetPos(pos);
	SetSize(size);
}
BoxCollider::~BoxCollider(){

}
void BoxCollider::SetPos(Vector3 pos){
	m_Pos = pos;
}
void BoxCollider::SetSize(Vector3 size){
	m_Size = size;
}
bool BoxCollider::IsCollider(ICollider& other){
	switch (other.GetColliderType())
	{
	case ColliderType::Box:
		return IsCollide((BoxCollider*)this, (BoxCollider*)&other);
	case ColliderType::Sphere:
		break;
	}
}
Vector3 BoxCollider::GetLeftBottomNearPos(){
	return m_Pos - m_Size * 0.5f;
}
Vector3 BoxCollider::GetRightTopFar(){
	return m_Pos + m_Size * 0.5f;
}