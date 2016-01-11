#include "QuadTree.h"
#include "../Utility/Rect.h"
#include "../Utility/KLog.h"

/// 자식노드를 추가한다.
QuadTree*	QuadTree::_AddChild(int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR){
	QuadTree* pChild;
	pChild = new QuadTree(this);
	pChild->_SetCorners(nCornerTL, nCornerTR, nCornerBL, nCornerBR);
	return pChild;
}

/// 4개의 코너값을 셋팅한다.
bool		QuadTree::_SetCorners(int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR){
	m_nCorner[CORNER_TL] = nCornerTL;
	m_nCorner[CORNER_TR] = nCornerTR;
	m_nCorner[CORNER_BL] = nCornerBL;
	m_nCorner[CORNER_BR] = nCornerBR;
	m_nCenter = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR] + m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR]) / 4;

	return true;
}

/// QuadTree를 4개의 하위 트리로 부분분할(subdibide)한다.
bool		QuadTree::_SubDivide(){		// QuadTree를 subdivide한다.
	int		nTopEdgeCenter;
	int		nBottomEdgeCenter;
	int		nLeftEdgeCenter;
	int		nRightEdgeCenter;
	int		nCentralPoint;

	// 상단변 가운데
	nTopEdgeCenter = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR]) / 2;
	// 하단변 가운데
	nBottomEdgeCenter = (m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR]) / 2;
	// 좌측변 가운데
	nLeftEdgeCenter = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_BL]) / 2;
	// 우측변 가운데
	nRightEdgeCenter = (m_nCorner[CORNER_TR] + m_nCorner[CORNER_BR]) / 2;
	// 한가운데
	nCentralPoint = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR] + m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR]) / 4;
	// 더이상 분할이 불가능한가? 그렇다면 SubDivide()종료
	if ((m_nCorner[CORNER_TR] - m_nCorner[CORNER_TL]) <= 1)
		return false;

	// 4개의 자식노드 추가
	m_pChild[CORNER_TL] = _AddChild(m_nCorner[CORNER_TL], nTopEdgeCenter, nLeftEdgeCenter, nCentralPoint);
	m_pChild[CORNER_TR] = _AddChild(nTopEdgeCenter, m_nCorner[CORNER_TR], nCentralPoint, nRightEdgeCenter);
	m_pChild[CORNER_BL] = _AddChild(nLeftEdgeCenter, nCentralPoint, m_nCorner[CORNER_BL], nBottomEdgeCenter);
	m_pChild[CORNER_BR] = _AddChild(nCentralPoint, nRightEdgeCenter, nBottomEdgeCenter, m_nCorner[CORNER_BR]);

	return true;
}

/// 출력한 폴리곤의 인덱스를 생성한다. TODO : 32비트랑 16비트 나누기
//int			QuadTree::_GetTriIndex(int nTris, void* pIndex, CustomVertex* pHeightMap, IFrustum& pFrustum, float fLODRatio){
int			QuadTree::_GetTriIndex(int nTris, void* pIndex, std::vector<CustomVertex>& pHeightMap, IFrustum& pFrustum, float fLODRatio){
	// 컬링된 노드라면 그냥 리턴
	if (m_bCulled){
		m_bCulled = false;
		return nTris;
	}
	//if (bits > 0x0000ffff){
		unsigned long* p = ((unsigned long*)pIndex) + nTris * 3;
	//}
	//else{
	//	unsigned short* p = ((unsigned short*)pIndex) + nTris * 3;
	//}
	// 현재 노드가 출력되어야 하는가?
	if (IsVisible(pHeightMap, pFrustum.GetPosPtr(), fLODRatio)){
		// 만약 최하위 노드라면 부분분할(subdivide)이 불가능하므로 그냥 출력하고 리턴한다.
		if (m_nCorner[CORNER_TR] - m_nCorner[CORNER_TL] <= 1){
			// 좌측상단 삼각형
			*p++ = m_nCorner[0];
			*p++ = m_nCorner[1];
			*p++ = m_nCorner[2];
			nTris++;
			// 우측하단 삼각형
			*p++ = m_nCorner[2];
			*p++ = m_nCorner[1];
			*p++ = m_nCorner[3];
			nTris++;

			return nTris;
		}

		bool b[4] = { false, false, false, false };
		// 상단 이웃노드(neighbor node)가 출력가능한가?
		if (m_pNeighbor[EDGE_UP]) b[EDGE_UP] = m_pNeighbor[EDGE_UP]->IsVisible(pHeightMap, pFrustum.GetPosPtr(), fLODRatio);
		// 하단 이웃노드(neighbor node)가 출력가능한가?
		if (m_pNeighbor[EDGE_DN]) b[EDGE_DN] = m_pNeighbor[EDGE_DN]->IsVisible(pHeightMap, pFrustum.GetPosPtr(), fLODRatio);
		// 좌측 이웃노드(neighbor node)가 출력가능한가?
		if (m_pNeighbor[EDGE_LT]) b[EDGE_LT] = m_pNeighbor[EDGE_LT]->IsVisible(pHeightMap, pFrustum.GetPosPtr(), fLODRatio);
		// 우측 이웃노드(neighbor node)가 출력가능한가?
		if (m_pNeighbor[EDGE_RT]) b[EDGE_RT] = m_pNeighbor[EDGE_RT]->IsVisible(pHeightMap, pFrustum.GetPosPtr(), fLODRatio);

		// 이웃노드들이 모두다 출력가능하다면 현재노드와 이웃노드들이 같은 LOD이므로
		// 부분분할이 필요없다.
		if (b[EDGE_UP] && b[EDGE_DN] && b[EDGE_LT] && b[EDGE_RT]){
			*p++ = m_nCorner[0];
			*p++ = m_nCorner[1];
			*p++ = m_nCorner[2];
			nTris++;
			*p++ = m_nCorner[2];
			*p++ = m_nCorner[1];
			*p++ = m_nCorner[3];
			nTris++;
			return nTris;
		}

		int n;

		if (!b[EDGE_UP]){ // 상단 부분분할이 필요한가?
			n = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR]) / 2;
			*p++ = m_nCenter; *p++ = m_nCorner[CORNER_TL]; *p++ = n; nTris++;
			*p++ = m_nCenter; *p++ = n; *p++ = m_nCorner[CORNER_TR]; nTris++;
		}
		else{ // 상단 부분분할이 필요없을 경우
			*p++ = m_nCenter; *p++ = m_nCorner[CORNER_TL]; *p++ = m_nCorner[CORNER_TR]; nTris++;
		}

		if (!b[EDGE_DN]){ // 하단 부분분할이 필요한가?
			n = (m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR]) / 2;
			*p++ = m_nCenter; *p++ = m_nCorner[CORNER_BR]; *p++ = n; nTris++;
			*p++ = m_nCenter; *p++ = n; *p++ = m_nCorner[CORNER_BL]; nTris++;
		}
		else{ // 하단 부분분할이 필요없을 경우
			*p++ = m_nCenter; *p++ = m_nCorner[CORNER_BR]; *p++ = m_nCorner[CORNER_BL]; nTris++;
		}

		if (!b[EDGE_LT]){ // 좌측 부분분할이 필요한가?
			n = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_BL]) / 2;
			*p++ = m_nCenter; *p++ = m_nCorner[CORNER_BL]; *p++ = n; nTris++;
			*p++ = m_nCenter; *p++ = n; *p++ = m_nCorner[CORNER_TL]; nTris++;
		}
		else{ // 좌측 부분분할이 필요없을 경우
			*p++ = m_nCenter; *p++ = m_nCorner[CORNER_BL]; *p++ = m_nCorner[CORNER_TL]; nTris++;
		}

		if (!b[EDGE_RT]){ // 우측 부분분할이 필요한가?
			n = (m_nCorner[CORNER_TR] + m_nCorner[CORNER_BR]) / 2;
			*p++ = m_nCenter; *p++ = m_nCorner[CORNER_TR]; *p++ = n; nTris++;
			*p++ = m_nCenter; *p++ = n; *p++ = m_nCorner[CORNER_BR]; nTris++;
		}
		else{ // 우측 부분분할이 필요없을 경우
			*p++ = m_nCenter; *p++ = m_nCorner[CORNER_TR]; *p++ = m_nCorner[CORNER_BR]; nTris++;
		}
		return nTris; // 이 노드 아래의 자식노드는 탐색할 필요없으므로 리턴
	}

	if (m_pChild[CORNER_TL]) nTris = m_pChild[CORNER_TL]->_GetTriIndex(nTris, pIndex, pHeightMap, pFrustum, fLODRatio);
	if (m_pChild[CORNER_TR]) nTris = m_pChild[CORNER_TR]->_GetTriIndex(nTris, pIndex, pHeightMap, pFrustum, fLODRatio);
	if (m_pChild[CORNER_BL]) nTris = m_pChild[CORNER_BL]->_GetTriIndex(nTris, pIndex, pHeightMap, pFrustum, fLODRatio);
	if (m_pChild[CORNER_BR]) nTris = m_pChild[CORNER_BR]->_GetTriIndex(nTris, pIndex, pHeightMap, pFrustum, fLODRatio);

	return nTris;
}

/// 메모리에서 쿼드트리를 삭제한다.
void		QuadTree::_Destroy(){
	for (auto i : m_pChild)
		DEL(i);
}

/// 현재노드가 프러스텀에 포함되는가?
//int			QuadTree::_IsInFrustum(CustomVertex* pHeightMap, IFrustum& pFrustum){
int			QuadTree::_IsInFrustum(std::vector<CustomVertex>& pHeightMap, IFrustum& pFrustum){
	bool	b[4];
	bool	bInSphere;
	Vector3 vec;

	// 경계구안에 있는가?
	//pHeightMap[m_nCenter].p.Copy(vec);
	vec = pHeightMap[m_nCenter].p;
	bInSphere = pFrustum.IsInSphere(&vec, m_fRadius);

	if (!bInSphere) return FRUSTUM_OUT;		// 경계구 안에 없으면 점단위의 프러스텀 테스트 생략

	// 쿼드트리의 4군데 경계 프러스텀 테스트
	vec = pHeightMap[m_nCorner[0]].p;
	b[0] = pFrustum.IsIn(&vec);
	vec = pHeightMap[m_nCorner[1]].p;
	b[1] = pFrustum.IsIn(&vec);
	vec = pHeightMap[m_nCorner[2]].p;
	b[2] = pFrustum.IsIn(&vec);
	vec = pHeightMap[m_nCorner[3]].p;
	b[3] = pFrustum.IsIn(&vec);

	// 4개 모두 프러스텀 안에 있음
	if ((b[0] + b[1] + b[2] + b[3]) == 4) return FRUSTUM_COMPLETELY_IN;

	// 일부분이 프러스텀에 있는 경우
	return FRUSTUM_PARTIALLY_IN;
}

/// _IsInFrustum()함수의 결과에 따라 프러스텀 컬링 수행
//void		QuadTree::_FrustumCull(CustomVertex* pHeightMap, IFrustum& pFrustum){
void		QuadTree::_FrustumCull(std::vector<CustomVertex>& pHeightMap, IFrustum& pFrustum){
	int ret;

	m_bCulled = false;
	ret = _IsInFrustum(pHeightMap, pFrustum);
	switch (ret)
	{
	case FRUSTUM_COMPLETELY_IN:
		_AllInFrustum();
		return;
	case FRUSTUM_PARTIALLY_IN:
		m_bCulled = false;
		break;
	case FRUSTUM_OUT:
		m_bCulled = true;
		return;
	}
	if (m_pChild[0]) m_pChild[0]->_FrustumCull(pHeightMap, pFrustum);
	if (m_pChild[1]) m_pChild[1]->_FrustumCull(pHeightMap, pFrustum);
	if (m_pChild[2]) m_pChild[2]->_FrustumCull(pHeightMap, pFrustum);
	if (m_pChild[3]) m_pChild[3]->_FrustumCull(pHeightMap, pFrustum);
}

/// 카마라와 현재 노드와의 거리값을 기준으로 LOD값을 구한다.
//int			QuadTree::_GetLODLevel(CustomVertex* pHeightMap, Vector3* pCamera, float fLODRatio){
int			QuadTree::_GetLODLevel(std::vector<CustomVertex>& pHeightMap, Vector3* pCamera, float fLODRatio){
	Vector3 vec;
	vec = pHeightMap[m_nCenter].p;
	float d = Distance(vec, *pCamera);
	return max((int)(d * fLODRatio), 1);
}

/// 모든 자식노드의 m_bCulled값을 false로 한다.
void		QuadTree::_AllInFrustum(){
	m_bCulled = false;
	if (!m_pChild[0]) return;
	m_pChild[0]->_AllInFrustum();
	m_pChild[1]->_AllInFrustum();
	m_pChild[2]->_AllInFrustum();
	m_pChild[3]->_AllInFrustum();
}

/// 이웃노드를 만든다.(삼각형 찢어짐 방지용)
//void		QuadTree::_BuildNeighborNode(QuadTree* pRoot, CustomVertex* pHeightMap, int cx){
void		QuadTree::_BuildNeighborNode(QuadTree* pRoot, std::vector<CustomVertex>& pHeightMap, int cx){
	int n;
	int _0, _1, _2, _3;

	for (int i = 0; i < 4; i++){
		_0 = m_nCorner[0];
		_1 = m_nCorner[1];
		_2 = m_nCorner[2];
		_3 = m_nCorner[3];

		// 이웃노드의 4개 코너값을 얻는다.
		n = _GetNodeIndex(i, cx, _0, _1, _2, _3);
		// 코너값으로 이웃노드의 포인터를 얻어온다.
		if (n >= 0) m_pNeighbor[i] = pRoot->_FindNode(pHeightMap, _0, _1, _2, _3);
	}

	// 자식노드로 재귀호출
	if (m_pChild[0]){
		m_pChild[0]->_BuildNeighborNode(pRoot, pHeightMap, cx);
		m_pChild[1]->_BuildNeighborNode(pRoot, pHeightMap, cx);
		m_pChild[2]->_BuildNeighborNode(pRoot, pHeightMap, cx);
		m_pChild[3]->_BuildNeighborNode(pRoot, pHeightMap, cx);
	}
}

/// 쿼드트리를 만든다.(Build()함수에서 불린다.)
//bool		QuadTree::_BuildQuadTree(CustomVertex* pHeightMap){
bool		QuadTree::_BuildQuadTree(std::vector<CustomVertex>& pHeightMap){
	if (_SubDivide()){
		// 좌측상단과, 우측하단의 거리를 구한다.
		Vector3 vec1, vec2;
		vec1 = pHeightMap[m_nCorner[CORNER_TL]].p;
		vec2 = pHeightMap[m_nCorner[CORNER_BR]].p;
		// 거리를 2로 나누어 반지름을 구한다.
		//m_fRadius = Vector3::Distance(vec2, vec1) / 2.0f;
		m_fRadius = Length(vec1 - vec2) / 2.0f;
		m_pChild[CORNER_TL]->_BuildQuadTree(pHeightMap);
		m_pChild[CORNER_TR]->_BuildQuadTree(pHeightMap);
		m_pChild[CORNER_BL]->_BuildQuadTree(pHeightMap);
		m_pChild[CORNER_BR]->_BuildQuadTree(pHeightMap);
	}
	return true;
}

/// 쿼드트리를 검색해서 4개 코너값과 일치하는 노드를 찾는다.
//QuadTree*	QuadTree::_FindNode(CustomVertex* pHeightMap, int _0, int _1, int _2, int _3){
QuadTree*	QuadTree::_FindNode(std::vector<CustomVertex>& pHeightMap, int _0, int _1, int _2, int _3){
	// 일치하는 노드라면 노드값을 리턴
	if ((m_nCorner[0] == _0) && (m_nCorner[1] == _1) && (m_nCorner[2] == _2) && (m_nCorner[3] == _3))
		return this;

	// 자식 노드가 있는가?
	if (m_pChild[0]){
		Rect rc;
		Vector2 pt;
		int n = (_0 + _1 + _2 + _3) / 4;

		// 현재 맵상에서의 위치
		pt.x = (int)pHeightMap[n].p.x;
		pt.y = (int)pHeightMap[n].p.z;

		// 4개의 코너값을 기준으로 자식노드의 맵 점유범위를 얻는다.
		rc.SetRect(
			(int)pHeightMap[m_pChild[0]->m_nCorner[CORNER_TL]].p.x,
			(int)pHeightMap[m_pChild[0]->m_nCorner[CORNER_TL]].p.z,
			(int)pHeightMap[m_pChild[0]->m_nCorner[CORNER_BR]].p.x,
			(int)pHeightMap[m_pChild[0]->m_nCorner[CORNER_BR]].p.z);
		// pt값이 점유범위안에 있다면 자식노드로 들어간다.
		if (rc.IsInRect(pt))
			return m_pChild[0]->_FindNode(pHeightMap, _0, _1, _2, _3);

		// 4개의 코너값을 기준으로 자식노드의 맵 점유범위를 얻는다.
		rc.SetRect(
			(int)pHeightMap[m_pChild[1]->m_nCorner[CORNER_TL]].p.x,
			(int)pHeightMap[m_pChild[1]->m_nCorner[CORNER_TL]].p.z,
			(int)pHeightMap[m_pChild[1]->m_nCorner[CORNER_BR]].p.x,
			(int)pHeightMap[m_pChild[1]->m_nCorner[CORNER_BR]].p.z);
		// pt값이 점유범위안에 있다면 자식노드로 들어간다.
		if (rc.IsInRect(pt))
			return m_pChild[1]->_FindNode(pHeightMap, _0, _1, _2, _3);

		// 4개의 코너값을 기준으로 자식노드의 맵 점유범위를 얻는다.
		rc.SetRect(
			(int)pHeightMap[m_pChild[2]->m_nCorner[CORNER_TL]].p.x,
			(int)pHeightMap[m_pChild[2]->m_nCorner[CORNER_TL]].p.z,
			(int)pHeightMap[m_pChild[2]->m_nCorner[CORNER_BR]].p.x,
			(int)pHeightMap[m_pChild[2]->m_nCorner[CORNER_BR]].p.z);
		// pt값이 점유범위안에 있다면 자식노드로 들어간다.
		if (rc.IsInRect(pt))
			return m_pChild[2]->_FindNode(pHeightMap, _0, _1, _2, _3);

		// 4개의 코너값을 기준으로 자식노드의 맵 점유범위를 얻는다.
		rc.SetRect(
			(int)pHeightMap[m_pChild[3]->m_nCorner[CORNER_TL]].p.x,
			(int)pHeightMap[m_pChild[3]->m_nCorner[CORNER_TL]].p.z,
			(int)pHeightMap[m_pChild[3]->m_nCorner[CORNER_BR]].p.x,
			(int)pHeightMap[m_pChild[3]->m_nCorner[CORNER_BR]].p.z);
		// pt값이 점유범위안에 있다면 자식노드로 들어간다.
		if (rc.IsInRect(pt))
			return m_pChild[3]->_FindNode(pHeightMap, _0, _1, _2, _3);
	}
	return nullptr;
}

/// 4개 방향(상단, 하단, 좌측, 우측)의 이웃노드 인덱스를 구한다.
int			QuadTree::_GetNodeIndex(int ed, int cx, int& _0, int& _1, int& _2, int& _3){
	int _a, _b, _c, _d, gap;
	_a = _0;
	_b = _1;
	_c = _2;
	_d = _3;
	gap = _b - _a;	// 현재 노드의 좌우폭값

	switch (ed)
	{
	case EDGE_UP: // 위쪽 방향 이웃노드의 인덱스
		_0 = _a - cx * gap;
		_1 = _b - cx * gap;
		_2 = _a;
		_3 = _b;
		break;
	case EDGE_DN: // 아래 방향 이웃노드의 인덱스
		_0 = _c;
		_1 = _d;
		_2 = _c + cx * gap;
		_3 = _d + cx * gap;
		break;
	case EDGE_LT: // 좌측 방향 이웃노드의 인덱스
		_0 = _a - gap;
		_1 = _a;
		_2 = _c - gap;
		_3 = _c;
		break;
	case EDGE_RT: // 우측 방향 이웃노드의 인덱스
		_0 = _b;
		_1 = _b + gap;
		_2 = _d;
		_3 = _d + gap;
		if ((_0 / cx) != (_a / cx)) return -1;
		if ((_1 / cx) != (_b / cx)) return -1;
		break;
	}

	int n = (_0 + _1 + _2 + _3) / 4;		/// 가운데 인덱스
	if (!IS_IN_RANGE(n, 0, cx * cx - 1)) return -1;

	return n;
}

/// 최초 투르노드 생성자
QuadTree::QuadTree(int cx, int cy){
	m_pParent = nullptr;
	m_pChild.resize(4);
	m_pNeighbor.resize(4);
	m_nCorner.resize(4);
	//for (int i = 0; i < 4; i++){
	//	m_pChild[i] = nullptr;
	//	m_pNeighbor[i] = nullptr;
	//}
	_SetCorners(0, cx - 1, cx * (cy - 1), cx * cy - 1);
	m_fRadius = 0.0f;
	m_bCulled = false;
}

/// 하위 자식노드 생성자
QuadTree::QuadTree(QuadTree* pParent){
	m_nCenter = 0;
	m_pParent = pParent;
	m_pChild.resize(4);
	m_pNeighbor.resize(4);
	m_nCorner.resize(4);
	//for (int i = 0; i < 4; i++){
	//	m_pChild[i] = nullptr;
	//	m_pNeighbor[i] = nullptr;
	//	m_nCorner[i] = 0;
	//}
	m_bCulled = false;
	m_fRadius = 0.0f;
}

/// 소멸자
QuadTree::~QuadTree(){
	_Destroy();
}

/// QuadTree를 구축한다.
//bool QuadTree::Build(CustomVertex* pHeightMap){
bool QuadTree::Build(std::vector<CustomVertex>& pHeightMap){
	KLog::Instance()->Log("BuildQuadTree");
	// 쿼드트리 구축
	_BuildQuadTree(pHeightMap);

	KLog::Instance()->Log("BuildNeighborNode");
	// 이웃노드 구축
	_BuildNeighborNode(this, pHeightMap, m_nCorner[CORNER_TR] + 1);

	KLog::Instance()->Log("End");

	return true;
}

/// 코너 인덱스 값을 얻어온다.
void QuadTree::GetCorner(int& _0, int& _1, int& _2, int&_3){
	_0 = m_nCorner[0];
	_1 = m_nCorner[1];
	_2 = m_nCorner[2];
	_3 = m_nCorner[3];
}

/// 삼각형의 인덱스를 만들고, 출력할 삼각형의 개수를 반환한다.
//int	QuadTree::GenerateIndex(void* pIB, CustomVertex* pHeightMap, IFrustum& pFrustum, float fLODRatio){
int	QuadTree::GenerateIndex(void* pIB, std::vector<CustomVertex>& pHeightMap, IFrustum& pFrustum, float fLODRatio){
	_FrustumCull(pHeightMap, pFrustum);
	return _GetTriIndex(0, pIB, pHeightMap, pFrustum, fLODRatio);
}

/// 현재 노드가 LOD등급으로 볼때 출력이 가능한 노드인가?
//bool QuadTree::IsVisible(CustomVertex* pHeightMap, Vector3* pCamera, float fLODRatio){
bool QuadTree::IsVisible(std::vector<CustomVertex>& pHeightMap, Vector3* pCamera, float fLODRatio){
	return ((m_nCorner[CORNER_TR] - m_nCorner[CORNER_TL]) <= _GetLODLevel(pHeightMap, pCamera, fLODRatio));
}