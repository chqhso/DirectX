#ifndef SKINNED_MESH_H
#define SKINNED_MESH_H

#include "Mesh.h"

/**
 * 스키닝 메시 클래스의 Base클래스
 */
class SkinnedMesh : public Mesh{
protected:
	std::vector<int>			m_idxBones;
	std::vector<Matrix4x4>*		m_pMatPalette;
public:
	SkinnedMesh(LPDIRECT3DDEVICE9 pDev, KParsedMesh* pMesh);
	~SkinnedMesh();

	// 최초에 한번 불린다.
	void SetMatrixPalette(std::vector<Matrix4x4>* pPal){ m_pMatPalette = pPal; }

	std::vector<int>& GetBones(){ return m_idxBones; }
	virtual int Draw(Matrix4x4* pTM){ return 1; }
	virtual int Draw(VSMgr* pVSMgr, PSMgr* pPSMgr){ return 1; }
};

#endif