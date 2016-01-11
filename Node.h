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
	int					m_nNodeType;	/// ����� ����
	int					m_nObjectID;	/// ������Ʈ�� ID
	int					m_nParentID;	/// �θ��� ID
	int					m_nMaterialID;	/// ������ ID
	Vector3				m_bboxMaxOrig;	/// �ٿ�� �ڽ��� ���� �ִ밪(max)
	Vector3				m_bboxMinOrig;	/// �ٿ�� �ڽ��� ���� �ּҰ�(min)
	Vector3				m_bboxMax;		/// �ٿ�� �ڽ��� ���� �ִ밪(max)
	Vector3				m_bboxMin;		/// �ٿ�� �ڽ��� ���� �ּҰ�(min)
	Matrix4x4			m_matWorld;		/// world TM���(�Һ�)
	Matrix4x4			m_matLocal;		/// local TM���(�Һ�)

	/// m_matTM = m_matAni * m_matLocal * (parent's m_matTM) * (grandparent's m_matTM) * ...
	Matrix4x4				m_matTM;		/// ���� TM���(��ȭ)
//	Track*				m_pTrack;		/// �ִϸ��̼� Ʈ������(TODO ���� �ȸ������) nodeMgr�� �̵�
//	ShaderMgr*			m_pShaderMgr;	/// ���̴� �Ŵ��� ���׸���������� �̵�
	LPDIRECT3DDEVICE9	m_pDev;
public:
	Node(LPDIRECT3DDEVICE9 pDev, KParsedMesh* pMesh);
	~Node();

	/// ����� ����
	int GetNodeType(){ return m_nNodeType; }
	/// �޽��� ID���� ��´�.
	int GetObjectID(){ return m_nObjectID; }
	/// �θ�޽��� ID���� ��´�.
	int GetParentID(){ return m_nParentID; }
	/// ������ ID���� ��´�.
	int GetMaterialID(){ return m_nMaterialID; }

	Matrix4x4& GetMatrixWorld(){ return m_matWorld; }
	Matrix4x4& GetMatrixLocal(){ return m_matLocal; }

	/// ������ TM���� ��´�.
	Matrix4x4* GetMatrixTMPtr(){ return &m_matTM; }

	/// �ٿ���ڽ��� ���� ��´�.
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

	// TODO : ����������
//	virtual DMatrix* Animate(float fFrame, DTrack* pTrack, DMatrix* pParentTM);
	virtual Matrix4x4& Animate(Matrix4x4* pParentTM);

	virtual int Draw(Matrix4x4* pTM) { return 1; }
	virtual int Draw(VSMgr* pVSMgr, PSMgr* pPSMgr){ return 1; }
	virtual int DrawBBox(Matrix4x4* pTM);
};

#endif