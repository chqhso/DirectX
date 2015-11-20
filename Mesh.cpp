#include "Mesh.h"
#include "Parser\KParsedMesh.h"

Mesh::Mesh(LPDIRECT3DDEVICE9 pDev, KParsedMesh* pMesh) : Node(pDev, pMesh){
	m_isSkinned = pMesh->m_isSkinned ? TRUE : FALSE;
	m_nNodeType = NODE_MESH;

	m_pVB = NULL;
	m_pIB = NULL;
}
Mesh::~Mesh(){
	REL(m_pVB);
	REL(m_pIB);
}
int Mesh::Draw(DMatrix* pTM){
	return 1;
}
int Mesh::Draw(VSMgr* pVSMgr, PSMgr* pPSMgr){
	return 1;
}