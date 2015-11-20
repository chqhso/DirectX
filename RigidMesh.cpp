#include "RigidMesh.h"
#include "Parser\KParsedMesh.h"
RigidMesh::RigidMesh(LPDIRECT3DDEVICE9 pDev, KParsedMesh* pMesh) : Mesh(pDev, pMesh){
	_CreateVIB(pMesh);
}
RigidMesh::~RigidMesh(){}
int RigidMesh::_CreateVIB(KParsedMesh* pMesh){
	VOID*		pV;			// �������� lock������ ������ ��
	VOID*		pI;			// �ε������� lock������ ������ ��
	std::vector<RigidVertex>	vtx;

	m_nVerts = pMesh->m_vtxFinal.size();
	m_dwFVF = RigidVertex::FVF;
	m_bboxMax = DVector3(pMesh->m_vtxFinal[0].p);
	m_bboxMin = DVector3(pMesh->m_vtxFinal[0].p);
	vtx.resize(m_nVerts);

	for (unsigned int i = 0; i < m_nVerts; i++){
		vtx[i].p = pMesh->m_vtxFinal[i].p;
		vtx[i].n = pMesh->m_vtxFinal[i].n;
		vtx[i].t = pMesh->m_vtxFinal[i].t;

		// �ƽ���ũ��Ʈ�� ������� �����ڴ� �̻��� ��찡 ���Ƽ� ��������Ѵ�.
		if (pMesh->m_vtxFinal[i].p.x > m_bboxMax.vector.x) m_bboxMax.vector.x = pMesh->m_vtxFinal[i].p.x;
		if (pMesh->m_vtxFinal[i].p.y > m_bboxMax.vector.y) m_bboxMax.vector.y = pMesh->m_vtxFinal[i].p.y;
		if (pMesh->m_vtxFinal[i].p.z > m_bboxMax.vector.z) m_bboxMax.vector.z = pMesh->m_vtxFinal[i].p.z;
		if (pMesh->m_vtxFinal[i].p.x < m_bboxMin.vector.x) m_bboxMin.vector.x = pMesh->m_vtxFinal[i].p.x;
		if (pMesh->m_vtxFinal[i].p.y < m_bboxMin.vector.y) m_bboxMin.vector.y = pMesh->m_vtxFinal[i].p.y;
		if (pMesh->m_vtxFinal[i].p.z < m_bboxMin.vector.z) m_bboxMin.vector.z = pMesh->m_vtxFinal[i].p.z;
	}

	// �������� ����
	m_pDev->CreateVertexBuffer(m_nVerts * sizeof(RigidVertex), 0, m_dwFVF, D3DPOOL_DEFAULT, &m_pVB, NULL);
	m_pVB->Lock(0, m_nVerts * sizeof(RigidVertex), (void**)&pV, 0);
	memcpy(pV, &vtx[0], m_nVerts * sizeof(RigidVertex));
	m_pVB->Unlock();
	stl_wipe_vector(vtx);

	// �ε��� ����
	D3DCAPS9 caps;
	m_pDev->GetDeviceCaps(&caps);
	m_nTriangles = pMesh->m_idxFinal.size();
	// �ε����� 32��Ʈ �ε����� �����ϸ� 32��Ʈ �ε��� ���� ����
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
	else{ // �ƴ϶�� 16��Ʈ �ε����� �ε��� ���� ����
		m_pDev->CreateIndexBuffer(m_nTriangles * sizeof(Index3w), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, NULL);
		m_pIB->Lock(0, m_nTriangles * sizeof(Index3w), (void**)& pI, 0);
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

int RigidMesh::Draw(DMatrix* pTM){
	m_pDev->MultiplyTransform(D3DTS_WORLD, &m_matTM.matrix);
	m_pDev->SetStreamSource(0, m_pVB, 0, sizeof(RigidVertex));
	m_pDev->SetFVF(m_dwFVF);
	m_pDev->SetIndices(m_pIB);
	m_pDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_nVerts, 0, m_nTriangles);

	return 1;
}