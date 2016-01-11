#ifndef BONE_H
#define BONE_H

#include "Node.h"

class Bone : public Node{
protected:
	Matrix4x4				m_matSkin;
public:
	Bone(LPDIRECT3DDEVICE9 pDev, KParsedMesh* pMesh);
	~Bone();
	Matrix4x4*	GetMatrixSkin(){ return &m_matSkin; }
//	DMatrix*	Animate(float frame, DMatrix* pParent, DTrack* pTrack);
	Matrix4x4&	Animate(Matrix4x4* pParentTM, Matrix4x4* pTrackMat);
	Matrix4x4&	Animate(Matrix4x4* pParentTM, DTrack* pTrack, float fFrame);
	Matrix4x4&	Animate(Matrix4x4* pParentTM, DTrack* pTrack1, DTrack* pTrack2, float fFrame1, float fFrame2, float blendFrame);

	virtual int Draw(Matrix4x4* pTM);
	virtual int Draw(VSMgr* pVSMgr, PSMgr* pPSMgr){ return 1; }
};

#endif