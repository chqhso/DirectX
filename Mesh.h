#ifndef MESH_H
#define MESH_H

#include "Node.h"

/**
 * 3D ������Ʈ�� �޽üӼ��� ���� Ŭ����
 */

class Mesh : public Node{
protected:
	BOOL						m_isSkinned;		// ��Ű���� ����Ǵ� �޽��ΰ�?

	DWORD						m_nVerts;			// ��ü ������ ����
	DWORD						m_nTriangles;		// �׷��� �ﰢ���� ����
	DWORD						m_dwFVF;			// ������ fvf��
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	LPDIRECT3DINDEXBUFFER9		m_pIB;
public:
	Mesh(LPDIRECT3DDEVICE9 pDev, KParsedMesh* pMesh);
	~Mesh();

	BOOL IsSkinned(){ return m_isSkinned; }

	virtual int Draw(DMatrix* pTM);
	virtual int Draw(VSMgr* pVSMgr, PSMgr* pPSMgr);
};

#endif