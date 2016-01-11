#ifndef I_COLLIDER_H
#define I_COLLIDER_H

#include "../Define.h"

enum class ColliderType{
	Box,
	Sphere,
};

class ICollider{
public:
	ICollider(){}
	virtual ~ICollider(){}
	virtual bool IsColliderEnter(ICollider& other) = 0;
	virtual bool IsColliderStay(ICollider& other) = 0;
	virtual bool IsColliderExit(ICollider& other) = 0;
	virtual bool IsCollider(ICollider& other) = 0;
	virtual unsigned int GetColliderID() = 0;
	virtual ColliderType GetColliderType() = 0;
};


#endif