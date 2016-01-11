#include "Bone.h"

Bone::Bone(LPDIRECT3DDEVICE9 pDev, KParsedMesh* pMesh) : Node(pDev, pMesh){
	m_nNodeType = NODE_BONE;
	//D3DXMatrixIdentity(&m_matSkin.matrix);
	m_matSkin = Identity();
}
Bone::~Bone(){}
//DMatrix* Bone::Animate(float frame, DMatrix* pParent, DTrack* pTrack){
//	DMatrix* pMatAni;
//	DMatrix mWI;		// world inverse;
//
//	// 애니메이션 행렬을 만든다.
//	pMatAni = pTrack->Animate(frame);
//	m_matTM = m_matLocal * *pMatAni;
//
//	// 만약 pos키값이 없으면 local TM의 좌표를 사용한다.
//	if (pMatAni->matrix._41 == 0.0f && pMatAni->matrix._42 == 0.0f && pMatAni->matrix._43 == 0.0f){
//		m_matTM.matrix._41 = m_matLocal.matrix._41;
//		m_matTM.matrix._42 = m_matLocal.matrix._42;
//		m_matTM.matrix._43 = m_matLocal.matrix._43;
//	}
//	else{ // pos 키값을 좌표값으로 적용한다.(이렇게 하지 않으면 TM의 pos성분이 두번적용된다.)
//		m_matTM.matrix._41 = pMatAni->matrix._41;
//		m_matTM.matrix._42 = pMatAni->matrix._42;
//		m_matTM.matrix._43 = pMatAni->matrix._43;
//	}
//
//	m_matTM = m_matTM * *pParent;
//
//	// mWI = inverse(m_matWorld)
//	D3DXMatrixInverse(&mWI.matrix, NULL, &m_matWorld.matrix);
//	// skin = inverse(m_world) * m_ani * m_parent;
//	m_matSkin = mWI * m_matTM;
//	return &m_matSkin;
//}
Matrix4x4& Bone::Animate(Matrix4x4* pParentTM, DTrack* pTrack, float fFrame){
	Matrix4x4 mWI;
	Matrix4x4* pMatAni;

	pMatAni = pTrack->Animate(fFrame);
	m_matTM = m_matLocal * *pMatAni;

	if (pMatAni->m[3][0] == 0.0f && pMatAni->m[3][1] == 0.0f && pMatAni->m[3][2] == 0.0f){
		m_matTM.m[3][0] = m_matLocal.m[3][0];
		m_matTM.m[3][1] = m_matLocal.m[3][1];
		m_matTM.m[3][2] = m_matLocal.m[3][2];
	}
	else{ 
		m_matTM.m[3][0] = pMatAni->m[3][0];
		m_matTM.m[3][1] = pMatAni->m[3][1];
		m_matTM.m[3][2] = pMatAni->m[3][2];
	}

	m_matTM = m_matTM * *pParentTM;

//	D3DXMatrixInverse(&mWI.matrix, NULL, &m_matWorld.matrix);
	mWI = Inverse(m_matWorld);
	m_matSkin = mWI * m_matTM;
	return m_matSkin;
}
Matrix4x4& Bone::Animate(Matrix4x4* pParentTM, DTrack* pTrack1, DTrack* pTrack2, float fFrame1, float fFrame2, float blendFrame){
	Matrix4x4 mWI;
	Matrix4x4* pMatAni;

	pMatAni = pTrack1->BlendAnimate(pTrack2, fFrame1, fFrame2, blendFrame);
	m_matTM = m_matLocal * *pMatAni;

	if (pMatAni->m[3][0] == 0.0f && pMatAni->m[3][1] == 0.0f && pMatAni->m[3][2] == 0.0f){
		m_matTM.m[3][0] = m_matLocal.m[3][0];
		m_matTM.m[3][1] = m_matLocal.m[3][1];
		m_matTM.m[3][2] = m_matLocal.m[3][2];
	}
	else{
		m_matTM.m[3][0] = pMatAni->m[3][0];
		m_matTM.m[3][1] = pMatAni->m[3][1];
		m_matTM.m[3][2] = pMatAni->m[3][2];
	}

	m_matTM = m_matTM * *pParentTM;

	//D3DXMatrixInverse(&mWI.matrix, NULL, &m_matWorld.matrix);
	mWI = Inverse(m_matWorld);
	m_matSkin = mWI * m_matTM;
	return m_matSkin;
}
Matrix4x4& Bone::Animate(Matrix4x4* pParentTM, Matrix4x4* pTrackMat){
	Matrix4x4 mWI;
	m_matTM = m_matLocal * *pTrackMat;

	// 만약 pos키값이 없으면 local TM의 좌표를 사용한다.
	if (pTrackMat->m[3][0] == 0.0f && pTrackMat->m[3][1] == 0.0f && pTrackMat->m[3][2] == 0.0f){
		m_matTM.m[3][0] = m_matLocal.m[3][0];
		m_matTM.m[3][1] = m_matLocal.m[3][1];
		m_matTM.m[3][2] = m_matLocal.m[3][2];
	}
	else{ // pos 키값을 좌표값으로 적용한다.(이렇게 하지 않으면 TM의 pos성분이 두번적용된다.)
		m_matTM.m[3][0] = pTrackMat->m[3][0];
		m_matTM.m[3][1] = pTrackMat->m[3][1];
		m_matTM.m[3][2] = pTrackMat->m[3][2];
	}

	m_matTM = m_matTM * *pParentTM;

	// mWI = inverse(m_matWorld)
	//D3DXMatrixInverse(&mWI.matrix, NULL, &m_matWorld.matrix);
	mWI = Inverse(m_matWorld);
	// skin = inverse(m_world) * m_ani * m_parent;
	m_matSkin = mWI * m_matTM;
	return m_matSkin;
}

// TODO : 쉐이더 준비X
int Bone::Draw(Matrix4x4* pTM){
	//BoxVertex vtx[8];
	//vtx[0] = BoxVertex(-1,  1,  1, 0xffff0000);
	//vtx[1] = BoxVertex( 1,  1,  1, 0xffff0000);
	//vtx[2] = BoxVertex( 1,  1, -1, 0xffff0000);
	//vtx[3] = BoxVertex(-1,  1, -1, 0xffff0000);
	//vtx[4] = BoxVertex(-1, -1,  1, 0xffff0000);
	//vtx[5] = BoxVertex( 1, -1,  1, 0xffff0000);
	//vtx[6] = BoxVertex( 1, -1, -1, 0xffff0000);
	//vtx[7] = BoxVertex(-1, -1, -1, 0xffff0000);
	CustomVertex vtx[8];

	Index3w idx[12] = {
		{ 0, 1, 2 }, { 0, 2, 3 },	/// 윗면
		{ 4, 6, 5 }, { 4, 7, 6 },	/// 아랫면
		{ 0, 3, 7 }, { 0, 7, 4 },	/// 왼면
		{ 1, 5, 6 }, { 1, 6, 2 },	/// 오른면
		{ 3, 2, 6 }, { 3, 6, 7 },	/// 앞면
		{ 0, 4, 5 }, { 0, 5, 1 },	/// 뒷면
	};

	//m_pDev->MultiplyTransform(D3DTS_WORLD, &m_matTM.matrix);
	//m_pDev->SetFVF(BoxVertex::FVF);
	//m_pDev->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 8, 12, idx, D3DFMT_INDEX16, vtx, sizeof(BoxVertex));

	return 1;
}