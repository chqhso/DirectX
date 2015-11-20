#ifndef NODE_H
#define NODE_H

#include "Define.h"
#include "DirectDefine.h"
#include "Utility\DirectUtility\DVector3.h"
#include "Utility\DirectUtility\DMatrix.h"
#include "Utility\DirectUtility\DTrack.h"

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
	DVector3			m_bboxMaxOrig;	/// �ٿ�� �ڽ��� ���� �ִ밪(max)
	DVector3			m_bboxMinOrig;	/// �ٿ�� �ڽ��� ���� �ּҰ�(min)
	DVector3			m_bboxMax;		/// �ٿ�� �ڽ��� ���� �ִ밪(max)
	DVector3			m_bboxMin;		/// �ٿ�� �ڽ��� ���� �ּҰ�(min)
	DMatrix				m_matWorld;		/// world TM���(�Һ�)
	DMatrix				m_matLocal;		/// local TM���(�Һ�)

	/// m_matTM = m_matAni * m_matLocal * (parent's m_matTM) * (grandparent's m_matTM) * ...
	DMatrix				m_matTM;		/// ���� TM���(��ȭ)
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

	DMatrix& GetMatrixWorld(){ return m_matWorld; }
	DMatrix& GetMatrixLocal(){ return m_matLocal; }

	/// ������ TM���� ��´�.
	DMatrix* GetMatrixTMPtr(){ return &m_matTM; }

	/// �ٿ���ڽ��� ���� ��´�.
	void GetBBox(DVector3* pMin, DVector3* pMax){
		D3DXVec3TransformCoord(&m_bboxMin.vector, &m_bboxMinOrig.vector, &m_matTM.matrix);
		D3DXVec3TransformCoord(&m_bboxMax.vector, &m_bboxMaxOrig.vector, &m_matTM.matrix);
		//*pMin = m_bboxMin;
		//*pMax = m_bboxMax;
		//m_bboxMin.Copy(pMin->vector); m_bboxMax.Copy(*pMax);
		pMin->vector = m_bboxMin.vector;
		pMax->vector = m_bboxMax.vector;
	}

	// TODO : ����������
//	virtual DMatrix* Animate(float fFrame, DTrack* pTrack, DMatrix* pParentTM);
	virtual DMatrix& Animate(DMatrix* pParentTM);

	virtual int Draw(DMatrix* pTM) { return 1; }
	virtual int Draw(VSMgr* pVSMgr, PSMgr* pPSMgr){ return 1; }
	virtual int DrawBBox(DMatrix* pTM);
};

#endif