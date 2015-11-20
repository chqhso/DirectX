#ifndef RIGID_MESH_H
#define RIGID_MESH_H

#include "Mesh.h"

struct RigidVertex{
	enum{ FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1) };
	DVector3		p;
	DVector3		n;
	DVector2		t;
};

/**
 * 스키닝이 없는 메시
 */
class RigidMesh : public Mesh{
protected:
	int _CreateVIB(KParsedMesh* pMesh);
public:
	RigidMesh(LPDIRECT3DDEVICE9 pDev, KParsedMesh* pMesh);
	~RigidMesh();
	virtual int Draw(DMatrix* pTM);
};

#endif