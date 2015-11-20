#ifndef SKINNED_MESH_H
#define SKINNED_MESH_H

#include "Mesh.h"

/**
 * ��Ű�� �޽� Ŭ������ BaseŬ����
 */
class SkinnedMesh : public Mesh{
protected:
	std::vector<int>			m_idxBones;
	std::vector<DMatrix>*		m_pMatPalette;
public:
	SkinnedMesh(LPDIRECT3DDEVICE9 pDev, KParsedMesh* pMesh);
	~SkinnedMesh();

	// ���ʿ� �ѹ� �Ҹ���.
	void SetMatrixPalette(std::vector<DMatrix>* pPal){ m_pMatPalette = pPal; }

	std::vector<int>& GetBones(){ return m_idxBones; }
	virtual int Draw(DMatrix* pTM){ return 1; }
	virtual int Draw(VSMgr* pVSMgr, PSMgr* pPSMgr){ return 1; }
};

#endif