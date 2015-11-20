#ifndef S_SKINNED_MESH_H
#define S_SKINNED_MESH_H

#include "SkinnedMesh.h"

/**
 * Shader�� ����� ��Ű�� �޽� Ŭ����
 */
class SSkinnedMesh : public SkinnedMesh{
protected:
	int			_CreateVIB(KParsedMesh* pMesh);
	void		_ApplyPalette(DMatrix* pTM);
	void		_ApplyPalette(VSMgr* pVSMgr);
public:
	SSkinnedMesh(LPDIRECT3DDEVICE9 pDev, KParsedMesh* pMesh);
	~SSkinnedMesh();

	virtual int Draw(DMatrix* pTM);
	virtual int Draw(VSMgr* pVSMgr, PSMgr* pPSMgr);
};

#endif