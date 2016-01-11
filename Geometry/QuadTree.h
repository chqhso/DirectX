#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include "../Define.h"
#include "../DirectDefine.h"
//#include "../Utility/Frustum.h"
#include "../Interface/IFrustum.h"

/**
 * @brief QuadTree의 베이스 클래스
 *
 */
class QuadTree{
	/// 쿼드트리에 보관되는 4개의 코너값에 대한 상수값
	enum			CornerType{CORNER_TL, CORNER_TR, CORNER_BL, CORNER_BR};
	/// 이웃노드 처리용 상수값
	enum			{EDGE_UP, EDGE_DN, EDGE_LT, EDGE_RT};
	/// 쿼드트리와 프러스텀간의 관계
	enum			QuadLocation{	FRUSTUM_OUT				= 0,		/// 프러스텀에서 완전 벗어남
									FRUSTUM_PARTIALLY_IN	= 1,		/// 프러스텀에 부분 포함
									FRUSTUM_COMPLETELY_IN	= 2,		/// 프러스텀에 완전 포함
									FRUSTUM_UNKNOWN			= -1};		/// 모르겠음

private:
	std::vector<QuadTree*>	m_pChild;			/// QuadTree의 4개의 자식노드
	QuadTree*				m_pParent;			/// Triangle Crack(Popping)을 막기위해서 사용한다. 10/30추가
	std::vector<QuadTree*>	m_pNeighbor;		/// Triangle Crack(Popping)을 막기위해서 사용한다. 10/30추가

	int						m_nCenter;			/// QuadTree에 보관할 첫번째 값
	std::vector<int>		m_nCorner;			/// QuadTree에 보관할 두번째 값
												///		TopLeft(TL)					TopRight(TR)
												///				0-----------------------1
												///				|						|
												///				|						|
												///				2-----------------------3
												///	BottomLeft(BL)					BottomRight(BR)
	bool					m_bCulled;			/// 프러스텀에서 컬링된 노드인가?
	float					m_fRadius;			/// 노드를 감싸는 경계구(bounding sphere)의 반지름
	
private:
	/// 자식노드를 추가한다.
	QuadTree*	_AddChild(int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR);

	/// 4개의 코너값을 셋팅한다.
	bool		_SetCorners(int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR);

	/// QuadTree를 4개의 하위 트리로 부분분할(subdibide)한다.
	bool		_SubDivide();		// QuadTree를 subdivide한다.

	/// 출력한 폴리곤의 인덱스를 생성한다. TODO : 32비트랑 16비트 나누기
	//int			_GetTriIndex(int nTris, void* pIndex, CustomVertex* pHeightMap, IFrustum& pFrustum, float fLODRatio);
	int			_GetTriIndex(int nTris, void* pIndex, std::vector<CustomVertex>& pHeightMap, IFrustum& pFrustum, float fLODRatio);

	/// 메모리에서 쿼드트리를 삭제한다.
	void		_Destroy();

	/// 현재노드가 프러스텀에 포함되는가?
	//int			_IsInFrustum(CustomVertex* pHeightMap, IFrustum& pFrustum);
	int			_IsInFrustum(std::vector<CustomVertex>& pHeightMap, IFrustum& pFrustum);

	/// _IsInFrustum()함수의 결과에 따라 프러스텀 컬링 수행
	//void		_FrustumCull(CustomVertex* pHeightMap, IFrustum& pFrustum);
	void		_FrustumCull(std::vector<CustomVertex>& pHeightMap, IFrustum& pFrustum);

	/// 카마라와 현재 노드와의 거리값을 기준으로 LOD값을 구한다.
	//int			_GetLODLevel(CustomVertex* pHeightMap, Vector3* pCamera, float fLODRatio);
	int			_GetLODLevel(std::vector<CustomVertex>& pHeightMap, Vector3* pCamera, float fLODRatio);

	/// 모든 자식노드의 m_bCulled값을 false로 한다.
	void		_AllInFrustum();

	/// 이웃노드를 만든다.(삼각형 찢어짐 방지용)
	//void		_BuildNeighborNode(QuadTree* pRoot, CustomVertex* pHeightMap, int cx);
	void		_BuildNeighborNode(QuadTree* pRoot, std::vector<CustomVertex>& pHeightMap, int cx);

	/// 쿼드트리를 만든다.(Build()함수에서 불린다.)
	//bool		_BuildQuadTree(CustomVertex* pHeightMap);
	bool		_BuildQuadTree(std::vector<CustomVertex>& pHeightMap);

	/// 쿼드트리를 검색해서 4개 코너값과 일치하는 노드를 찾는다.
	//QuadTree*	_FindNode(CustomVertex* pHeightMap, int _0, int _1, int _2, int _3);
	QuadTree*	_FindNode(std::vector<CustomVertex>& pHeightMap, int _0, int _1, int _2, int _3);

	/// 4개 방향(상단, 하단, 좌측, 우측)의 이웃노드 인덱스를 구한다.
	int			_GetNodeIndex(int ed, int cx, int& _0, int& _1, int& _2, int& _3);

public:
	/// 최초 투르노드 생성자
	QuadTree(int cx, int cy);

	/// 하위 자식노드 생성자
	QuadTree(QuadTree* pParent);

	/// 소멸자
	~QuadTree();

	/// 현재 노드가 Culling된것인가?
	bool IsCulled(){ return m_bCulled; }

	/// QuadTree를 구축한다.
	//bool Build(CustomVertex* pHeightMap);
	bool Build(std::vector<CustomVertex>& pHeightMap);

	/// 코너 인덱스 값을 얻어온다.
	void GetCorner(int& _0, int& _1, int& _2, int&_3);

	/// 삼각형의 인덱스를 만들고, 출력할 삼각형의 개수를 반환한다.
	//int	GenerateIndex(void* pIB, CustomVertex* pHeightMap, IFrustum& pFrustum, float fLODRatio);
	int	GenerateIndex(void* pIB, std::vector<CustomVertex>& pHeightMap, IFrustum& pFrustum, float fLODRatio);

	/// 현재 노드가 LOD등급으로 볼때 출력이 가능한 노드인가?
	//bool IsVisible(CustomVertex* pHeightMap, Vector3* pCamera, float fLODRatio);
	bool IsVisible(std::vector<CustomVertex>& pHeightMap, Vector3* pCamera, float fLODRatio);
};

#endif