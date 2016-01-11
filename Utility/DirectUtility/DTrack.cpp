#include "DTrack.h"

DTrack::DTrack(Track& keys){
	CreateTrack(keys);
}
DTrack::DTrack(){

}
void DTrack::CreateTrack(Track& keys){
	if (keys.pos.size()){
		m_keys.pos.resize(keys.pos.size());
		for (int i = 0; i < m_keys.pos.size(); i++){
			m_keys.pos[i].frame = keys.pos[i].frame;
			//m_keys.pos[i].value = DVector3(keys.pos[i].value);
			m_keys.pos[i].value = keys.pos[i].value;
		}
	}

	if (keys.rot.size()){
		Quaternion q = Quaternion(0, 0, 0, 1);
		m_keys.rot.resize(keys.rot.size());
		m_keys.rot[0].frame = keys.rot[0].frame;
		m_keys.rot[0].value = q;
		for (int i = 1; i < m_keys.rot.size(); i++){
			m_keys.rot[i].frame = keys.rot[i].frame;
			if (keys.rot[i].frame <= keys.start){ // 애니메이션이 시작되는 프레임보다 작은 키값들은 전부 단위 퀘터니언
				q = Quaternion(0, 0, 0, 1);
			}
			else{
				//q = Quaternion(keys.rot[i].value);
				q = keys.rot[i].value;
			}
			//D3DXQuaternionMultiply(&m_keys.rot[i].value.quaternion, &m_keys.rot[i - 1].value.quaternion, &q.quaternion);
			m_keys.rot[i].value = q * m_keys.rot[i - 1].value;
		}
	}

	if (keys.scl.size()){
		m_keys.scl.resize(keys.scl.size());
		for (int i = 0; i < m_keys.scl.size(); i++){
			m_keys.scl[i].frame = keys.scl[i].frame;
			m_keys.scl[i].value = keys.scl[i].value;
		}
	}
}
DTrack::~DTrack(){
	stl_wipe_vector(m_keys.pos);
	stl_wipe_vector(m_keys.rot);
	stl_wipe_vector(m_keys.scl);
}
void DTrack::_Get2Keys(float frame, std::vector<DKeyPos>& keys, DKeyPos*& k1, DKeyPos*& k2){
	int mkey;
	int lkey = 0;
	int rkey = keys.size() - 1;

	if (keys.size() > 1){
		if (frame > keys[rkey].frame){
			k1 = &keys[rkey];
			k2 = &keys[rkey];
			return;
		}
		if (frame < keys[lkey].frame){
			k1 = &keys[lkey];
			k2 = &keys[lkey];
			return;
		}
		while (rkey >= lkey){
			mkey = (rkey + lkey) / 2;
			if (keys[mkey].frame <= frame && keys[mkey + 1].frame >= frame){
				k1 = &keys[mkey];
				k2 = &keys[mkey + 1];
				return;
			}
			if (keys[mkey].frame > frame){
				rkey = mkey;
			}
			else{
				lkey = mkey;
			}
		}
	}
	k1 = k2 = NULL;
}
void DTrack::_Get2Keys(float frame, std::vector<DKeyRot>& keys, DKeyRot*& k1, DKeyRot*& k2){
	int mkey;
	int lkey = 0;
	int rkey = keys.size() - 1;

	if (keys.size() > 1){
		if (frame > keys[rkey].frame){
			k1 = &keys[rkey];
			k2 = &keys[rkey];
			return;
		}
		if (frame < keys[lkey].frame){
			k1 = &keys[lkey];
			k2 = &keys[lkey];
			return;
		}

		while (rkey >= lkey){
			mkey = (rkey + lkey) / 2.0f;
			if (keys[mkey].frame <= frame && keys[mkey + 1].frame >= frame){
				k1 = &keys[mkey];
				k2 = &keys[mkey + 1];
				return;
			}
			if (keys[mkey].frame > frame){
				rkey = mkey;
			}
			else{
				lkey = mkey;
			}
		}
	}
	k1 = k2 = NULL;
}
void DTrack::_Get2Keys(float frame, std::vector<DKeyScl>& keys, DKeyScl*& k1, DKeyScl*& k2){
	int mkey;
	int lkey = 0;
	int rkey = keys.size() - 1;

	if (keys.size() > 1){
		if (frame > keys[rkey].frame){
			k1 = &keys[rkey];
			k2 = &keys[rkey];
			return;
		}
		if (frame < keys[lkey].frame){
			k1 = &keys[lkey];
			k2 = &keys[lkey];
			return;
		}

		while (rkey >= lkey){
			mkey = (rkey + lkey) / 2.0f;
			if (keys[mkey].frame <= frame && keys[mkey + 1].frame >= frame){
				k1 = &keys[mkey];
				k2 = &keys[mkey + 1];
				return;
			}
			if (keys[mkey].frame > frame){
				rkey = mkey;
			}
			else{
				lkey = mkey;
			}
		}
	}
	k1 = k2 = NULL;
}
BOOL DTrack::_GetPosKey(float frame, Vector3* pv){
	float a;
	DKeyPos *p1, *p2;

	_Get2Keys(frame, m_keys.pos, p1, p2);

	if (!p1 || !p2) return FALSE;

	if (p1 == p2){
		//pv->vector.x = p1->value.vector.x;
		//pv->vector.y = p1->value.vector.y;
		//pv->vector.z = p1->value.vector.z;
//		pv->vector = p1->value.vector;
		*pv = p1->value;
	}
	else{
		a = _GetAlpha(p1->frame, p2->frame, frame);
		//D3DXVec3Lerp(&pv->vector, &p1->value.vector, &p2->value.vector, a);
		*pv = Lerp(p1->value, p2->value, a);
	}
	return TRUE;
}
BOOL DTrack::_GetRotKey(float frame, Quaternion* pq){
	float a;
	DKeyRot *p1, *p2;

	_Get2Keys(frame, m_keys.rot, p1, p2);

	if (!p1 || !p2) return FALSE;

	if (p1 == p2){
		//pq->quaternion = p1->value.quaternion;
		*pq = p1->value;
	}
	else{
		a = _GetAlpha(p1->frame, p2->frame, frame);
		//D3DXQuaternionSlerp(&pq->quaternion, &p1->value.quaternion, &p2->value.quaternion, a);
		*pq = Slerp(p1->value, p2->value, a);
	}
	return TRUE;
}
BOOL DTrack::_GetSclKey(float frame, Vector3* pv){
	float a;
	DKeyScl *p1, *p2;

	_Get2Keys(frame, m_keys.scl, p1, p2);

	if (!p1 || !p2) return FALSE;

	if (p1 == p2){
		//pv->vector = p1->value.vector;
		*pv = p1->value;
	}
	else{
		a = _GetAlpha(p1->frame, p2->frame, frame);
		//D3DXVec3Lerp(&pv->vector, &p1->value.vector, &p2->value.vector, a);
		*pv = Lerp(p1->value, p2->value, a);
	}
	return TRUE;
}
Matrix4x4* DTrack::Animate(float frame){
	Vector3 v;
	Quaternion q;

	//D3DXMatrixIdentity(&m_matAni.matrix);
	m_matAni = Identity();

	if (_GetRotKey(frame, &q)){
		//D3DXMatrixRotationQuaternion(&m_matAni.matrix, &q.quaternion);
		m_matAni = Rotate(q);
	}
	if (_GetPosKey(frame, &v)){
		//m_matAni.matrix._41 = v.vector.x;
		//m_matAni.matrix._42 = v.vector.y;
		//m_matAni.matrix._43 = v.vector.z;
		m_matAni.m[3][0] = v.x;
		m_matAni.m[3][1] = v.y;
		m_matAni.m[3][2] = v.z;
	}
	if (_GetSclKey(frame, &v)){
		//m_matAni.matrix._11 *= v.vector.x;
		//m_matAni.matrix._22 *= v.vector.y;
		//m_matAni.matrix._33 *= v.vector.z;
		m_matAni.m[0][0] *= v.x;
		m_matAni.m[1][1] *= v.y;
		m_matAni.m[2][2] *= v.z;
	}

	return &m_matAni;
}
Matrix4x4* DTrack::BlendAnimate(DTrack* track, float frame1, float frame2, float blendTime){
	Vector3 v, v1, v2;
	Quaternion q, q1, q2;
	float a;
	a = _GetAlpha(0.0f, blendTime, frame2);

	//D3DXMatrixIdentity(&m_matAni.matrix);
	m_matAni = Identity();

	if (_GetRotKey(frame1, &q1) && track->_GetRotKey(frame2, &q2)){
		//D3DXQuaternionSlerp(&q.quaternion, &q1.quaternion, &q2.quaternion, a);
		//D3DXMatrixRotationQuaternion(&m_matAni.matrix, &q.quaternion);
		q = Slerp(q1, q2, a);
		m_matAni = Rotate(q);
	}
	if (_GetPosKey(frame1, &v1) && track->_GetPosKey(frame2, &v2)){
		//D3DXVec3Lerp(&v.vector, &v1.vector, &v2.vector, a);
		//m_matAni.matrix._41 = v.vector.x;
		//m_matAni.matrix._42 = v.vector.y;
		//m_matAni.matrix._43 = v.vector.z;
		v = Lerp(v1, v2, a);
		m_matAni.m[3][0] = v.x;
		m_matAni.m[3][1] = v.y;
		m_matAni.m[3][2] = v.z;
	}
	if (_GetSclKey(frame1, &v1) && track->_GetSclKey(frame2, &v2)){
		//D3DXVec3Lerp(&v.vector, &v1.vector, &v2.vector, a);
		//m_matAni.matrix._11 *= v.vector.x;
		//m_matAni.matrix._22 *= v.vector.y;
		//m_matAni.matrix._33 *= v.vector.z;
		v = Lerp(v1, v2, a);
		m_matAni.m[0][0] *= v.x;
		m_matAni.m[1][1] *= v.y;
		m_matAni.m[2][2] *= v.z;
	}

	return &m_matAni;
}