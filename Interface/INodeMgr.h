#ifndef I_NODE_MGR_H
#define I_NODE_MGR_H

#include "../Define.h"
#include "../DirectDefine.h"
#include "../Utility/DirectUtility/DTrack.h"

class VSMgr;
class PSMgr;

class INodeMgr{
public:
	INodeMgr(){}
	virtual ~INodeMgr(){}
	virtual ObjectInfo& GetInfo() = 0;
	virtual Matrix4x4* GetTM() = 0;
	//TODO
	//virtual void GetTM(Matrix4x4& tm) = 0;
	//virtual void GetTM(DMatrix& tm) = 0;

	virtual void SetTM(Matrix4x4& tm) = 0;
//	virtual void SetTM(DMatrix& tm) = 0;
	virtual float GetRadius() = 0;
	virtual void Animate(std::vector<DTrack*> tracks, float fFrame) = 0;
	virtual void Animate(std::vector<DTrack*> tracks1, std::vector<DTrack*> tracks2, float fFrame1, float fFrame2, float blendFrame) = 0;
	virtual void Draw(VSMgr* pVSMgr, PSMgr* pPSMgr) = 0;
	virtual std::vector<DTrack*>& GetTracks() = 0;
	virtual Matrix4x4* GetBoneMatrix(std::string boneName) = 0;
//	virtual DMatrix* GetBoneDMatrixPtr(std::string boneName) = 0;
};

#endif