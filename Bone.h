#ifndef BONE_H
#define BONE_H

#include "Node.h"

class Bone : public Node{
protected:
	DMatrix				m_matSkin;
public:
	Bone(LPDIRECT3DDEVICE9 pDev, KParsedMesh* pMesh);
	~Bone();
	DMatrix*	GetMatrixSkin(){ return &m_matSkin; }
//	DMatrix*	Animate(float frame, DMatrix* pParent, DTrack* pTrack);
	DMatrix&	Animate(DMatrix* pParentTM, DMatrix* pTrackMat);
	DMatrix&	Animate(DMatrix* pParentTM, DTrack* pTrack, float fFrame);
	DMatrix&	Animate(DMatrix* pParentTM, DTrack* pTrack1, DTrack* pTrack2, float fFrame1, float fFrame2, float blendFrame);

	virtual int Draw(DMatrix* pTM);
	virtual int Draw(VSMgr* pVSMgr, PSMgr* pPSMgr){ return 1; }
};

#endif