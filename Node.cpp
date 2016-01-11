#include "Node.h"
#include "Parser\KParsedMesh.h"

Node::Node(LPDIRECT3DDEVICE9 pDev, KParsedMesh* pMesh){
	m_pDev = pDev;
	m_nNodeType = NODE_NODE;
	m_nObjectID = pMesh->m_nObjectID;
	m_nParentID = pMesh->m_nParentID;

	m_bboxMaxOrig = pMesh->m_bboxMax;
	m_bboxMinOrig = pMesh->m_bboxMin;
	m_nMaterialID = pMesh->m_nMaterialID;

	m_matLocal = pMesh->m_tmLocal;
	m_matWorld = pMesh->m_tmWorld;
	m_matTM = m_matLocal;
//	m_pTrack = new ZTrack(pMesh->m_track);
}
Node::~Node(){
	//DEL(m_pTrack);
}

//DMatrix* Node::Animate(float fFrame, DTrack* pTrack, DMatrix* pParentTM){
//	DMatrix* pMatAni;
//	// TODO Track의 사용법을 좀더 생각해보자
//	pMatAni = pTrack->Animate(fFrame);
//	m_matTM = m_matLocal * *pMatAni;
//
//	// 만약 pos키값이 없으면 local TM의 좌표를 사용한다.
//	if (pMatAni->matrix._41 == 0.0f && pMatAni->matrix._42 == 0.0f && pMatAni->matrix._43 == 0.0f){
//		m_matTM.matrix._41 = m_matLocal.matrix._41;
//		m_matTM.matrix._42 = m_matLocal.matrix._42;
//		m_matTM.matrix._43 = m_matLocal.matrix._43;
//	}
//	else{ // pos키값을 좌표값으로 적용한다.(이렇게 하지 않으면 TM의 pos성분이 두번적용된다.)
//		m_matTM.matrix._41 = pMatAni->matrix._41;
//		m_matTM.matrix._42 = pMatAni->matrix._42;
//		m_matTM.matrix._43 = pMatAni->matrix._43;
//	}
//	m_matTM = m_matTM * *pParentTM;
//	return &m_matTM;
//}
Matrix4x4& Node::Animate(Matrix4x4* pParentTM){
	m_matTM = m_matLocal * *pParentTM;
//	m_matTM = m_matTM * *pParentTM;
	return m_matTM;
}

// TODO : 쉐이더의 준비가 안됨
int Node::DrawBBox(Matrix4x4* pTM){
	//BoxVertex vtx[8];
	//vtx[0] = BoxVertex(m_bboxMinOrig.vector.x, m_bboxMaxOrig.vector.y, m_bboxMaxOrig.vector.z, 0xffff0000);
	//vtx[1] = BoxVertex(m_bboxMaxOrig.vector.x, m_bboxMaxOrig.vector.y, m_bboxMaxOrig.vector.z, 0xffff0000);
	//vtx[2] = BoxVertex(m_bboxMaxOrig.vector.x, m_bboxMaxOrig.vector.y, m_bboxMinOrig.vector.z, 0xffff0000);
	//vtx[3] = BoxVertex(m_bboxMinOrig.vector.x, m_bboxMaxOrig.vector.y, m_bboxMinOrig.vector.z, 0xffff0000);
	//vtx[4] = BoxVertex(m_bboxMinOrig.vector.x, m_bboxMinOrig.vector.y, m_bboxMaxOrig.vector.z, 0xffff0000);
	//vtx[5] = BoxVertex(m_bboxMaxOrig.vector.x, m_bboxMinOrig.vector.y, m_bboxMaxOrig.vector.z, 0xffff0000);
	//vtx[6] = BoxVertex(m_bboxMaxOrig.vector.x, m_bboxMinOrig.vector.y, m_bboxMinOrig.vector.z, 0xffff0000);
	//vtx[7] = BoxVertex(m_bboxMinOrig.vector.x, m_bboxMinOrig.vector.y, m_bboxMinOrig.vector.z, 0xffff0000);

	CustomVertex vtx[8];
	vtx[0].p.x = m_bboxMinOrig.x; vtx[0].p.y = m_bboxMaxOrig.y; vtx[0].p.z = m_bboxMaxOrig.z;
	vtx[1].p.x = m_bboxMaxOrig.x; vtx[1].p.y = m_bboxMaxOrig.y; vtx[1].p.z = m_bboxMaxOrig.z;
	vtx[2].p.x = m_bboxMaxOrig.x; vtx[2].p.y = m_bboxMaxOrig.y; vtx[2].p.z = m_bboxMinOrig.z;
	vtx[3].p.x = m_bboxMinOrig.x; vtx[3].p.y = m_bboxMaxOrig.y; vtx[3].p.z = m_bboxMinOrig.z;
	vtx[4].p.x = m_bboxMinOrig.x; vtx[4].p.y = m_bboxMinOrig.y; vtx[4].p.z = m_bboxMaxOrig.z;
	vtx[5].p.x = m_bboxMaxOrig.x; vtx[5].p.y = m_bboxMinOrig.y; vtx[5].p.z = m_bboxMaxOrig.z;
	vtx[6].p.x = m_bboxMaxOrig.x; vtx[6].p.y = m_bboxMinOrig.y; vtx[6].p.z = m_bboxMinOrig.z;
	vtx[7].p.x = m_bboxMinOrig.x; vtx[7].p.y = m_bboxMinOrig.y; vtx[7].p.z = m_bboxMinOrig.z;

	Index3w idx[12] = {
		{ 0, 1, 2 }, { 0, 2, 3 },	/// 윗면
		{ 4, 6, 5 }, { 4, 7, 6 },	/// 아랫면
		{ 0, 3, 7 }, { 0, 7, 4 },	/// 왼면
		{ 1, 5, 6 }, { 1, 6, 2 },	/// 오른면
		{ 3, 2, 6 }, { 3, 6, 7 },	/// 앞면
		{ 0, 4, 5 }, { 0, 5, 1 },	/// 뒷면
	};

	//m_pDev->MultiplyTransform(D3DTS_WORLD, &m_matTM);
	//m_pDev->SetFVF(BoxVertex::FVF);
	//m_pDev->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 8, 12, idx, D3DFMT_INDEX16, vtx, sizeof(BoxVertex));
	return 1;
}