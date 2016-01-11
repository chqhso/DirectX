#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

#include "Collider.h"

class BoxCollider : public Collider{
public:
	BoxCollider();
	BoxCollider(Vector3 pos, Vector3 size);
	void SetPos(Vector3 pos);
	void SetSize(Vector3 size);
	~BoxCollider();
	Vector3 GetLeftBottomNearPos();
	Vector3 GetRightTopFar();
	virtual bool IsCollider(ICollider& other) override;
private:
	Vector3 m_Pos;
	Vector3 m_Size;
};

#endif