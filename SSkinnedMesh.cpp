#include "SSkinnedMesh.h"
#include "Parser\KParsedMesh.h"
#include "Resources\VSMgr.h"
#include "Resources\PSMgr.h"
#include <set>
#include <sstream>

SSkinnedMesh::SSkinnedMesh(LPDIRECT3DDEVICE9 pDev, KParsedMesh* pMesh) : SkinnedMesh(pDev, pMesh){
	_CreateVIB(pMesh);
}
SSkinnedMesh::~SSkinnedMesh(){}
int SSkinnedMesh::_CreateVIB(KParsedMesh* pMesh){
	float			b[4];
	int				bi[4];
	CustomVertex*	pV;
	VOID*			pI;
	std::set<int>	idxBones;

	m_dwFVF = CustomVertex::FVF;
	m_nVerts = pMesh->m_vtxFinal.size();
	m_bboxMax = pMesh->m_vtxFinal[0].p;
	m_bboxMin = pMesh->m_vtxFinal[0].p;

	m_pDev->CreateVertexBuffer(m_nVerts * sizeof(CustomVertex), 0, m_dwFVF, D3DPOOL_DEFAULT, &m_pVB, NULL);
	m_pVB->Lock(0, m_nVerts * sizeof(CustomVertex), (void**)&pV, 0);

	for (unsigned int i = 0; i < m_nVerts; i++){
		for (int j = 0; j < 4; j++){
			bi[j] = ((pMesh->m_vtxFinal[i].i >> (j * 8)) & 0xff);
			idxBones.insert(bi[j]);
		}
		b[0] = pMesh->m_vtxFinal[i].b[0];
		b[1] = pMesh->m_vtxFinal[i].b[1];
		b[2] = pMesh->m_vtxFinal[i].b[2];
		b[3] = 1.0f - (b[0] + b[1] + b[2]);

		(pV + i)->p = pMesh->m_vtxFinal[i].p;
		(pV + i)->n = pMesh->m_vtxFinal[i].n;
		(pV + i)->t = pMesh->m_vtxFinal[i].t;
		(pV + i)->b = Vector4(b[3], b[2], b[1], b[0]);
		(pV + i)->i = Vector4(bi[3], bi[2], bi[1], bi[0]);

		// 맥스스크립트로 얻어지는 경계상자는 이상할 경우가 많아서 직접 계산한다.
		if (pMesh->m_vtxFinal[i].p.x > m_bboxMax.x) m_bboxMax.x = pMesh->m_vtxFinal[i].p.x;
		if (pMesh->m_vtxFinal[i].p.y > m_bboxMax.y) m_bboxMax.y = pMesh->m_vtxFinal[i].p.y;
		if (pMesh->m_vtxFinal[i].p.z > m_bboxMax.z) m_bboxMax.z = pMesh->m_vtxFinal[i].p.z;
		if (pMesh->m_vtxFinal[i].p.x < m_bboxMin.x) m_bboxMin.x = pMesh->m_vtxFinal[i].p.x;
		if (pMesh->m_vtxFinal[i].p.y < m_bboxMin.y) m_bboxMin.y = pMesh->m_vtxFinal[i].p.y;
		if (pMesh->m_vtxFinal[i].p.z < m_bboxMin.z) m_bboxMin.z = pMesh->m_vtxFinal[i].p.z;
	}
	m_pVB->Unlock();

	// 값이 겹치면 안되므로 STL의 set컨테이너를 사용한다.
	for (std::set<int>::iterator it = idxBones.begin(); it != idxBones.end(); it++){
		m_idxBones.push_back(*it);
	}
	idxBones.clear();

	D3DCAPS9 caps;
	m_pDev->GetDeviceCaps(&caps);
	m_nTriangles = pMesh->m_idxFinal.size();

	// 인덱스가 32비트 인덱스를 지원하면 32비트 인덱스 버퍼 생성
	if (caps.MaxVertexIndex > 0x0000ffff){
		m_pDev->CreateIndexBuffer(m_nTriangles * sizeof(Index3i), 0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &m_pIB, NULL);
		m_pIB->Lock(0, m_nTriangles * sizeof(Index3i), (void**)&pI, 0);
		DWORD* pW = (DWORD*)pI;
		for (unsigned int i = 0; i < m_nTriangles; i++){
			*(pW + 0) = pMesh->m_idxFinal[i].i[0];
			*(pW + 1) = pMesh->m_idxFinal[i].i[1];
			*(pW + 2) = pMesh->m_idxFinal[i].i[2];
			pW += 3;
		}
		m_pIB->Unlock();
	}
	else{ // 아니라면 16비트 인덱스로 인덱스 버퍼 생성
		m_pDev->CreateIndexBuffer(m_nTriangles * sizeof(Index3w), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, NULL);
		m_pIB->Lock(0, m_nTriangles * sizeof(Index3w), (void**)&pI, 0);
		WORD* pW = (WORD*)pI;
		for (unsigned int i = 0; i < m_nTriangles; i++){
			*(pW + 0) = (WORD)pMesh->m_idxFinal[i].i[0];
			*(pW + 1) = (WORD)pMesh->m_idxFinal[i].i[1];
			*(pW + 2) = (WORD)pMesh->m_idxFinal[i].i[2];
			pW += 3;
		}
		m_pIB->Unlock();
	}
	return 1;
}
//void SSkinnedMesh::_ApplyPalette(Matrix4x4* pTM){
//	Matrix4x4 m;
//	int		size = m_idxBones.size();
//
//	size = (*m_pMatPalette).size();
//	if (size > 50) size = 50;	// 50개의 뼈대만 지원
//	for (int i = 0; i < size; i++){
//		m = m_matTM * ((*m_pMatPalette)[i]);
//		m = m * *pTM;	// NodeManager의 TM행렬
//		//D3DXMatrixTranspose(&m.matrix, &m.matrix);
//		m = Transpose(m);
//		//m_pDev->SetVertexShaderConstantF(i * 4, (float*)&m.matrix, 4);
//		m_pDev->SetVertexShaderConstantF(i * 4, (float*)m, 4);
//	}
//}
//int SSkinnedMesh::Draw(Matrix4x4* pTM){
//	// TODO : 쉐이더 설정
//
//	_ApplyPalette(pTM);
//
//	m_pDev->SetStreamSource(0, m_pVB, 0, sizeof(CustomVertex));
////	m_pDev->SetFvF(m_dwFVF);
//	m_pDev->SetIndices(m_pIB);
//	m_pDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_nVerts, 0, m_nTriangles);
//	// TODO : 쉐이더 초기화설정
//	m_pDev->SetVertexDeclaration(NULL);
//	m_pDev->SetVertexShader(NULL);
//	m_pDev->SetPixelShader(NULL);
//
//	return 1;
//}
void SSkinnedMesh::_ApplyPalette(VSMgr* pVSMgr){
	Matrix4x4 m;
	int size = m_idxBones.size();
	std::ostringstream os;
	size = (*m_pMatPalette).size();
	if (size > 50) size = 50;
	for (int i = 0; i < size; i++){
		m = m_matTM * ((*m_pMatPalette)[i]);
		os.str("");
		os << "matPal[" << i << "]";
		pVSMgr->SetMatrix(os.str(), m);
	}
}
int SSkinnedMesh::Draw(VSMgr* pVSMgr, PSMgr* pPSMgr){
	m_pDev->SetVertexDeclaration(pVSMgr->GetVSTable()->pDecl);
	m_pDev->SetVertexShader(pVSMgr->GetVSTable()->pShader);
	m_pDev->SetPixelShader(pPSMgr->GetPSTable()->pShader);

	_ApplyPalette(pVSMgr);
	
	m_pDev->SetStreamSource(0, m_pVB, 0, sizeof(CustomVertex));
	m_pDev->SetIndices(m_pIB);
	m_pDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_nVerts, 0, m_nTriangles);

	m_pDev->SetVertexDeclaration(NULL);
	m_pDev->SetVertexShader(NULL);
	m_pDev->SetPixelShader(NULL);
	return 1;
}