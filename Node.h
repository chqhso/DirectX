#ifndef NODE_H
#define NODE_H

#include "Define.h"
#include "DirectDefine.h"
#include "Utility\DirectUtility\DTrack.h"
#include "Parser\KParsedData.h"

struct KParsedMesh;
class PSMgr;
class VSMgr;

class Node{
public:
	enum NODETYPE
	{
		NODE_NODE,
		NODE_BONE,
		NODE_MESH,
	};
protected:
	int					m_nNodeType;	/// 노드의 종류
	int					m_nObjectID;	/// 오브젝트의 ID
	int					m_nParentID;	/// 부모의 ID
	int					m_nMaterialID;	/// 재질의 ID
	Vector3				m_bboxMaxOrig;	/// 바운딩 박스의 최초 최대값(max)
	Vector3				m_bboxMinOrig;	/// 바운딩 박스의 최초 최소값(min)
	Vector3				m_bboxMax;		/// 바운딩 박스의 현재 최대값(max)
	Vector3				m_bboxMin;		/// 바운딩 박스의 현재 최소값(min)
	Matrix4x4			m_matWorld;		/// world TM행렬(불변)
	Matrix4x4			m_matLocal;		/// local TM행렬(불변)

	/// m_matTM = m_matAni * m_matLocal * (parent's m_matTM) * (grandparent's m_matTM) * ...
	Matrix4x4				m_matTM;		/// 최종 TM행렬(변화)
//	Track*				m_pTrack;		/// 애니메이션 트랙정보(TODO 아직 안만들었음) nodeMgr로 이동
//	ShaderMgr*			m_pShaderMgr;	/// 쉐이더 매니져 마테리얼안쪽으로 이동
	LPDIRECT3DDEVICE9	m_pDev;
public:
	Node(LPDIRECT3DDEVICE9 pDev, KParsedMesh* pMesh);
	~Node();

	/// 노드의 종류
	int GetNodeType(){ return m_nNodeType; }
	/// 메시의 ID값을 얻는다.
	int GetObjectID(){ return m_nObjectID; }
	/// 부모메시의 ID값을 얻는다.
	int GetParentID(){ return m_nParentID; }
	/// 재질의 ID값을 얻는다.
	int GetMaterialID(){ return m_nMaterialID; }

	Matrix4x4& GetMatrixWorld(){ return m_matWorld; }
	Matrix4x4& GetMatrixLocal(){ return m_matLocal; }

	/// 현재의 TM값을 얻는다.
	Matrix4x4* GetMatrixTMPtr(){ return &m_matTM; }

	/// 바운딩박스의 값을 얻는다.
	void GetBBox(Vector3* pMin, Vector3* pMax){
		//D3DXVec3TransformCoord(&m_bboxMin.vector, &m_bboxMinOrig.vector, &m_matTM.matrix);
		//D3DXVec3TransformCoord(&m_bboxMax.vector, &m_bboxMaxOrig.vector, &m_matTM.matrix);
		m_bboxMax = TransformCoord(m_bboxMaxOrig, m_matTM);
		m_bboxMin = TransformCoord(m_bboxMinOrig, m_matTM);
		//TransformCoord()
		//*pMin = m_bboxMin;
		//*pMax = m_bboxMax;
		//m_bboxMin.Copy(pMin->vector); m_bboxMax.Copy(*pMax);
		//pMin->vector = m_bboxMin.vector;
		//pMax->vector = m_bboxMax.vector;
		pMin = &m_bboxMin;
		pMax = &m_bboxMax;
	}

	// TODO : 삭제할지도
//	virtual DMatrix* Animate(float fFrame, DTrack* pTrack, DMatrix* pParentTM);
	virtual Matrix4x4& Animate(Matrix4x4* pParentTM);

	virtual int Draw(Matrix4x4* pTM) { return 1; }
	virtual int Draw(VSMgr* pVSMgr, PSMgr* pPSMgr){ return 1; }
	virtual int DrawBBox(Matrix4x4* pTM);
};

#endif