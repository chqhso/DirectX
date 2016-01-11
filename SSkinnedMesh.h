#ifndef S_SKINNED_MESH_H
#define S_SKINNED_MESH_H

#include "SkinnedMesh.h"

/**
 * Shader를 사용한 스키닝 메시 클래스
 */
class SSkinnedMesh : public SkinnedMesh{
protected:
	int			_CreateVIB(KParsedMesh* pMesh);
//	void		_ApplyPalette(Matrix4x4* pTM);
	void		_ApplyPalette(VSMgr* pVSMgr);
public:
	SSkinnedMesh(LPDIRECT3DDEVICE9 pDev, KParsedMesh* pMesh);
	~SSkinnedMesh();

//	virtual int Draw(Matrix4x4* pTM);
	virtual int Draw(VSMgr* pVSMgr, PSMgr* pPSMgr);
};

#endif