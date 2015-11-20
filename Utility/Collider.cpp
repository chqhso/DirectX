#include "Collider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"


unsigned int Collider::ColliderCount = 0;

Collider::Collider(ColliderType collType){
	m_HitBuffer.clear();
	m_nColliderID = ColliderCount++;
	m_ColliderType = collType;
}
Collider::~Collider(){
	m_HitBuffer.clear();
}
bool Collider::IsColliderEnter(ICollider& other){
	if (m_HitBuffer.find(other.GetColliderID()) == m_HitBuffer.end()){
		m_HitBuffer.emplace(other.GetColliderID(), false);
	}
	if (!m_HitBuffer[other.GetColliderID()] && IsCollider(other)){
		m_HitBuffer[other.GetColliderID()] = true;
		return true;
	}
	return false;
}
bool Collider::IsColliderStay(ICollider& other){
	return (m_HitBuffer[other.GetColliderID()] && IsCollider(other));
}
bool Collider::IsColliderExit(ICollider& other){
	if (m_HitBuffer[other.GetColliderID()] && !IsCollider(other)){
		m_HitBuffer[other.GetColliderID()] = false;
		return true;
	}
	return false;
}
bool Collider::IsCollider(ICollider& other){
	return false;
	//switch (m_ColliderType)
	//{
	//case ColliderType::Box:
	//	return IsCollider();
	//	break;
	//case ColliderType::Sphere:
	//	return IsCollider(other);
	//	break;
	//}
}
unsigned int Collider::GetColliderID(){
	return m_nColliderID;
}
ColliderType Collider::GetColliderType(){
	return m_ColliderType;
}
bool Collider::IsCollide(BoxCollider* box1, BoxCollider* box2){
	//Vector3 thisLBN = GetLeftBottomNearPos();
	//Vector3 thisRTF = GetRightTopFar();
	Vector3 box1LBN = box1->GetLeftBottomNearPos();
	Vector3 box1RTF = box1->GetRightTopFar();
	//Vector3 otherLBN = otherCollider->GetLeftBottomNearPos();
	//Vector3 otherRTF = otherCollider->GetRightTopFar();
	Vector3 box2LBN = box2->GetLeftBottomNearPos();
	Vector3 box2RTF = box2->GetRightTopFar();
	if (box1LBN.x < box2RTF.x && box1LBN.y < box2RTF.y && box1LBN.z < box2RTF.z &&
		box1RTF.x > box2LBN.x && box1RTF.y > box2LBN.y && box1RTF.z > box2LBN.z
		){
		return true;
	}
	return false;
}
bool Collider::IsCollide(SphereCollider* sphere1, SphereCollider* sphere2){
	float radiussum = sphere1->GetRadius() + sphere2->GetRadius();
	float distance = Vector3::Distance(sphere1->GetPos(), sphere2->GetPos());
	return distance <= radiussum;
}
bool Collider::IsCollide(BoxCollider* box, SphereCollider* sphere){
	float radiusSquared = pow(sphere->GetRadius(), 2);
	/// 원의 반지름의 스퀘어랑 각점(LBN, RTF)의 위치비교후 거리의 두배를 줄여나감
	/// 원의 반지름의 스퀘어가 0이상일경우 충돌, 0이하일경우 비충돌
	if (sphere->GetPos().x < box->GetLeftBottomNearPos().x) radiusSquared -= pow(sphere->GetPos().x - box->GetLeftBottomNearPos().x, 2);
	else if (box->GetRightTopFar().x < sphere->GetPos().x) radiusSquared -= pow(sphere->GetPos().x - box->GetRightTopFar().x, 2);

	if (sphere->GetPos().y < box->GetLeftBottomNearPos().y) radiusSquared -= pow(sphere->GetPos().y - box->GetLeftBottomNearPos().y, 2);
	else if (box->GetRightTopFar().y < sphere->GetPos().y) radiusSquared -= pow(sphere->GetPos().y - box->GetRightTopFar().y, 2);

	if (sphere->GetPos().z < box->GetLeftBottomNearPos().z) radiusSquared -= pow(sphere->GetPos().z - box->GetLeftBottomNearPos().z, 2);
	else if (box->GetRightTopFar().z < sphere->GetPos().z) radiusSquared -= pow(sphere->GetPos().z - box->GetRightTopFar().z, 2);

	return radiusSquared > 0;
}