#ifndef SPHERE_COLLIDER_H
#define SPHERE_COLLIDER_H

#include "Collider.h"

class SphereCollider : public Collider{
public:
	SphereCollider();
	SphereCollider(Vector3 pos, float radius);
	~SphereCollider();
	void SetPos(Vector3 pos);
	void SetRadius(float radius);
	Vector3 GetPos();
	float GetRadius();
	virtual bool IsCollider(ICollider& other) override;
private:
	Vector3 m_Pos;
	float m_fRadius;
};

#endif