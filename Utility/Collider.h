#ifndef COLLIDER_H
#define COLLIDER_H

#include "../Interface/ICollider.h"

class BoxCollider;
class SphereCollider;

class Collider : public ICollider{
public:
	Collider(ColliderType collType);
	virtual ~Collider();
	virtual bool IsColliderEnter(ICollider& other) override;
	virtual bool IsColliderStay(ICollider& other) override;
	virtual bool IsColliderExit(ICollider& other) override;
	virtual bool IsCollider(ICollider& other) override;

	virtual unsigned int GetColliderID() override;
	virtual ColliderType GetColliderType() override;

protected:
public:
	bool IsCollide(BoxCollider* box1, BoxCollider* box2);
	bool IsCollide(SphereCollider* sphere1, SphereCollider* sphere2);
	bool IsCollide(BoxCollider* box, SphereCollider* sphere);
public:
	static unsigned int ColliderCount;
protected:
	unsigned int m_nColliderID;
	std::map<unsigned int, bool> m_HitBuffer;
	ColliderType m_ColliderType;
};


#endif