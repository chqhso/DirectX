#ifndef MESH_H
#define MESH_H

#include "Node.h"

/**
 * 3D 오브젝트중 메시속성을 가진 클래스
 */

class Mesh : public Node{
protected:
	BOOL						m_isSkinned;		// 스키닝이 적용되는 메시인가?

	DWORD						m_nVerts;			// 전체 정점의 개수
	DWORD						m_nTriangles;		// 그려질 삼각형의 개수
	DWORD						m_dwFVF;			// 정점의 fvf값
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