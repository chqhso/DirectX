#ifndef D_TRACK_H
#define D_TRACK_H

#include "../../DirectDefine.h"
#include "../../Define.h"
#include "DMatrix.h"

class DTrack{
public:
	enum INTERPOL{
		INTP_LINEAR,
		INTP_SPLINE,
		INTP_HERMIT,
	};
protected:
	DKeys		m_keys;
	DMatrix		m_matAni;

	float _GetAlpha(float f1, float f2, float frame){
		return ((frame - f1) / (f2 - f1));
	}

	void _Get2Keys(float frame, std::vector<DKeyPos>& keys, DKeyPos*& k1, DKeyPos*& k2);
	void _Get2Keys(float frame, std::vector<DKeyRot>& keys, DKeyRot*& k1, DKeyRot*& k2);
	void _Get2Keys(float frame, std::vector<DKeyScl>& keys, DKeyScl*& k1, DKeyScl*& k2);
	BOOL _GetPosKey(float frame, DVector3* pv);
	BOOL _GetRotKey(float frame, DQuaternion* pq);
	BOOL _GetSclKey(float frame, DVector3* pv);
public:
	DTrack(Track& keys);
	DTrack();
	~DTrack();
	void CreateTrack(Track& keys);
	DMatrix* Animate(float frame);
	DMatrix* BlendAnimate(DTrack* track, float frame1, float frame2, float blendTime);
};

#endif