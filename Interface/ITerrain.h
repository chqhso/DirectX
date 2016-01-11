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
	long				m_cxDIB;			/// DIB의 가로픽셀수
	long				m_czDIB;			/// DIB의 세로픽셀수
	long				m_cyDIB;			/// DIB의 최대높이값(즉 0 ~ 255사이의 값)
	Vector3			m_vfScale;			/// scale
	float			m_fLODRatio;		/// LOD처리시에 사용될 값
	QuadTree*		m_pQuadTree;		/// 쿼드트리 객체의 포인터
	int				m_nTriangles;		/// 출력할 삼각형의 개수
	IFrustum*		m_pFrustum;
public:
	ITerrain(){}
	virtual ~ITerrain(){}
	virtual bool Create(Vector3 pvfScale, float fLODRatio, std::string sHeightMap, std::string sTex[MAX_TERRAIN_TEX]) = 0;
	/// x, z위치의 높이(y)값만 얻어내다.
	virtual float	GetHeight(int x, int z) = 0;
	/// 높이맵 파일의 가로픽셀수
	int		GetCXDIB(){ return m_cxDIB; }
	/// 높이맵 파일의 세로픽셀수
	int		GetCZDIB(){ return m_czDIB; }
	/// 높이맵의 실제 x축 폭(column)값
	float	GetCXTerrain(){ return m_cxDIB * m_vfScale.x; }
	/// 높이맵의 실제 y축 높이(height)값
	float	GetCYTerrain(){ return m_cyDIB * m_vfScale.y; }
	/// 높이맵의 실제 z축 길이(row)값
	float	GetCZTerrain(){ return m_czDIB * m_vfScale.z; }
	virtual void	Draw(VSMgr* pVSMgr, PSMgr* pPSMgr) = 0;
	/// frustum 설정
	void	SetFrustum(IFrustum* pFrustum){ m_pFrustum = pFrustum; }
};

#endif