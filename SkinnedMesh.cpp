#include "SkinnedMesh.h"

SkinnedMesh::SkinnedMesh(LPDIRECT3DDEVICE9 pDev, KParsedMesh* pMesh) : Mesh(pDev, pMesh){
	m_pMatPalette = NULL;
}
SkinnedMesh::~SkinnedMesh(){
	m_pMatPalette = NULL;
	stl_wipe_vector(m_idxBones);
}