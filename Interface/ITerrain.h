#ifndef I_TERRAIN_H
#define I_TERRAIN_H

#include "../Define.h"
#include "../Geometry/QuadTree.h"
#include "IFrustum.h"
#include "../Resources/VSMgr.h"
#include "../Resources/PSMgr.h"

#define MAX_TERRAIN_TEX 1

class ITerrain{
protected:
	long				m_cxDIB;			/// DIB�� �����ȼ���
	long				m_czDIB;			/// DIB�� �����ȼ���
	long				m_cyDIB;			/// DIB�� �ִ���̰�(�� 0 ~ 255������ ��)
	Vector3			m_vfScale;			/// scale
	float			m_fLODRatio;		/// LODó���ÿ� ���� ��
	QuadTree*		m_pQuadTree;		/// ����Ʈ�� ��ü�� ������
	int				m_nTriangles;		/// ����� �ﰢ���� ����
	IFrustum*		m_pFrustum;
public:
	ITerrain(){}
	virtual ~ITerrain(){}
	virtual bool Create(Vector3 pvfScale, float fLODRatio, std::string sHeightMap, std::string sTex[MAX_TERRAIN_TEX]) = 0;
	/// x, z��ġ�� ����(y)���� ����.
	virtual float	GetHeight(int x, int z) = 0;
	/// ���̸� ������ �����ȼ���
	int		GetCXDIB(){ return m_cxDIB; }
	/// ���̸� ������ �����ȼ���
	int		GetCZDIB(){ return m_czDIB; }
	/// ���̸��� ���� x�� ��(column)��
	float	GetCXTerrain(){ return m_cxDIB * m_vfScale.x; }
	/// ���̸��� ���� y�� ����(height)��
	float	GetCYTerrain(){ return m_cyDIB * m_vfScale.y; }
	/// ���̸��� ���� z�� ����(row)��
	float	GetCZTerrain(){ return m_czDIB * m_vfScale.z; }
	virtual void	Draw(VSMgr* pVSMgr, PSMgr* pPSMgr) = 0;
	/// frustum ����
	void	SetFrustum(IFrustum* pFrustum){ m_pFrustum = pFrustum; }
};

#endif