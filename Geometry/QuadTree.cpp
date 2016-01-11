#include "QuadTree.h"
#include "../Utility/Rect.h"
#include "../Utility/KLog.h"

/// �ڽĳ�带 �߰��Ѵ�.
QuadTree*	QuadTree::_AddChild(int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR){
	QuadTree* pChild;
	pChild = new QuadTree(this);
	pChild->_SetCorners(nCornerTL, nCornerTR, nCornerBL, nCornerBR);
	return pChild;
}

/// 4���� �ڳʰ��� �����Ѵ�.
bool		QuadTree::_SetCorners(int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR){
	m_nCorner[CORNER_TL] = nCornerTL;
	m_nCorner[CORNER_TR] = nCornerTR;
	m_nCorner[CORNER_BL] = nCornerBL;
	m_nCorner[CORNER_BR] = nCornerBR;
	m_nCenter = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR] + m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR]) / 4;

	return true;
}

/// QuadTree�� 4���� ���� Ʈ���� �κк���(subdibide)�Ѵ�.
bool		QuadTree::_SubDivide(){		// QuadTree�� subdivide�Ѵ�.
	int		nTopEdgeCenter;
	int		nBottomEdgeCenter;
	int		nLeftEdgeCenter;
	int		nRightEdgeCenter;
	int		nCentralPoint;

	// ��ܺ� ���
	nTopEdgeCenter = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR]) / 2;
	// �ϴܺ� ���
	nBottomEdgeCenter = (m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR]) / 2;
	// ������ ���
	nLeftEdgeCenter = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_BL]) / 2;
	// ������ ���
	nRightEdgeCenter = (m_nCorner[CORNER_TR] + m_nCorner[CORNER_BR]) / 2;
	// �Ѱ��
	nCentralPoint = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR] + m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR]) / 4;
	// ���̻� ������ �Ұ����Ѱ�? �׷��ٸ� SubDivide()����
	if ((m_nCorner[CORNER_TR] - m_nCorner[CORNER_TL]) <= 1)
		return false;

	// 4���� �ڽĳ�� �߰�
	m_pChild[CORNER_TL] = _AddChild(m_nCorner[CORNER_TL], nTopEdgeCenter, nLeftEdgeCenter, nCentralPoint);
	m_pChild[CORNER_TR] = _AddChild(nTopEdgeCenter, m_nCorner[CORNER_TR], nCentralPoint, nRightEdgeCenter);
	m_pChild[CORNER_BL] = _AddChild(nLeftEdgeCenter, nCentralPoint, m_nCorner[CORNER_BL], nBottomEdgeCenter);
	m_pChild[CORNER_BR] = _AddChild(nCentralPoint, nRightEdgeCenter, nBottomEdgeCenter, m_nCorner[CORNER_BR]);

	return true;
}

/// ����� �������� �ε����� �����Ѵ�. TODO : 32��Ʈ�� 16��Ʈ ������
//int			QuadTree::_GetTriIndex(int nTris, void* pIndex, CustomVertex* pHeightMap, IFrustum& pFrustum, float fLODRatio){
int			QuadTree::_GetTriIndex(int nTris, void* pIndex, std::vector<CustomVertex>& pHeightMap, IFrustum& pFrustum, float fLODRatio){
	// �ø��� ����� �׳� ����
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
	// ���� ��尡 ��µǾ�� �ϴ°�?
	if (IsVisible(pHeightMap, pFrustum.GetPosPtr(), fLODRatio)){
		// ���� ������ ����� �κк���(subdivide)�� �Ұ����ϹǷ� �׳� ����ϰ� �����Ѵ�.
		if (m_nCorner[CORNER_TR] - m_nCorner[CORNER_TL] <= 1){
			// ������� �ﰢ��
			*p++ = m_nCorner[0];
			*p++ = m_nCorner[1];
			*p++ = m_nCorner[2];
			nTris++;
			// �����ϴ� �ﰢ��
			*p++ = m_nCorner[2];
			*p++ = m_nCorner[1];
			*p++ = m_nCorner[3];
			nTris++;

			return nTris;
		}

		bool b[4] = { false, false, false, false };
		// ��� �̿����(neighbor node)�� ��°����Ѱ�?
		if (m_pNeighbor[EDGE_UP]) b[EDGE_UP] = m_pNeighbor[EDGE_UP]->IsVisible(pHeightMap, pFrustum.GetPosPtr(), fLODRatio);
		// �ϴ� �̿����(neighbor node)�� ��°����Ѱ�?
		if (m_pNeighbor[EDGE_DN]) b[EDGE_DN] = m_pNeighbor[EDGE_DN]->IsVisible(pHeightMap, pFrustum.GetPosPtr(), fLODRatio);
		// ���� �̿����(neighbor node)�� ��°����Ѱ�?
		if (m_pNeighbor[EDGE_LT]) b[EDGE_LT] = m_pNeighbor[EDGE_LT]->IsVisible(pHeightMap, pFrustum.GetPosPtr(), fLODRatio);
		// ���� �̿����(neighbor node)�� ��°����Ѱ�?
		if (m_pNeighbor[EDGE_RT]) b[EDGE_RT] = m_pNeighbor[EDGE_RT]->IsVisible(pHeightMap, pFrustum.GetPosPtr(), fLODRatio);

		// �̿������� ��δ� ��°����ϴٸ� ������� �̿������� ���� LOD�̹Ƿ�
		// �κк����� �ʿ����.
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

		if (!b[EDGE_UP]){ // ��� �κк����� �ʿ��Ѱ�?
			n = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR]) / 2;
			*p++ = m_nCenter; *p++ = m_nCorner[CORNER_TL]; *p++ = n; nTris++;
			*p++ = m_nCenter; *p++ = n; *p++ = m_nCorner[CORNER_TR]; nTris++;
		}
		else{ // ��� �κк����� �ʿ���� ���
			*p++ = m_nCenter; *p++ = m_nCorner[CORNER_TL]; *p++ = m_nCorner[CORNER_TR]; nTris++;
		}

		if (!b[EDGE_DN]){ // �ϴ� �κк����� �ʿ��Ѱ�?
			n = (m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR]) / 2;
			*p++ = m_nCenter; *p++ = m_nCorner[CORNER_BR]; *p++ = n; nTris++;
			*p++ = m_nCenter; *p++ = n; *p++ = m_nCorner[CORNER_BL]; nTris++;
		}
		else{ // �ϴ� �κк����� �ʿ���� ���
			*p++ = m_nCenter; *p++ = m_nCorner[CORNER_BR]; *p++ = m_nCorner[CORNER_BL]; nTris++;
		}

		if (!b[EDGE_LT]){ // ���� �κк����� �ʿ��Ѱ�?
			n = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_BL]) / 2;
			*p++ = m_nCenter; *p++ = m_nCorner[CORNER_BL]; *p++ = n; nTris++;
			*p++ = m_nCenter; *p++ = n; *p++ = m_nCorner[CORNER_TL]; nTris++;
		}
		else{ // ���� �κк����� �ʿ���� ���
			*p++ = m_nCenter; *p++ = m_nCorner[CORNER_BL]; *p++ = m_nCorner[CORNER_TL]; nTris++;
		}

		if (!b[EDGE_RT]){ // ���� �κк����� �ʿ��Ѱ�?
			n = (m_nCorner[CORNER_TR] + m_nCorner[CORNER_BR]) / 2;
			*p++ = m_nCenter; *p++ = m_nCorner[CORNER_TR]; *p++ = n; nTris++;
			*p++ = m_nCenter; *p++ = n; *p++ = m_nCorner[CORNER_BR]; nTris++;
		}
		else{ // ���� �κк����� �ʿ���� ���
			*p++ = m_nCenter; *p++ = m_nCorner[CORNER_TR]; *p++ = m_nCorner[CORNER_BR]; nTris++;
		}
		return nTris; // �� ��� �Ʒ��� �ڽĳ��� Ž���� �ʿ�����Ƿ� ����
	}

	if (m_pChild[CORNER_TL]) nTris = m_pChild[CORNER_TL]->_GetTriIndex(nTris, pIndex, pHeightMap, pFrustum, fLODRatio);
	if (m_pChild[CORNER_TR]) nTris = m_pChild[CORNER_TR]->_GetTriIndex(nTris, pIndex, pHeightMap, pFrustum, fLODRatio);
	if (m_pChild[CORNER_BL]) nTris = m_pChild[CORNER_BL]->_GetTriIndex(nTris, pIndex, pHeightMap, pFrustum, fLODRatio);
	if (m_pChild[CORNER_BR]) nTris = m_pChild[CORNER_BR]->_GetTriIndex(nTris, pIndex, pHeightMap, pFrustum, fLODRatio);

	return nTris;
}

/// �޸𸮿��� ����Ʈ���� �����Ѵ�.
void		QuadTree::_Destroy(){
	for (auto i : m_pChild)
		DEL(i);
}

/// �����尡 �������ҿ� ���ԵǴ°�?
//int			QuadTree::_IsInFrustum(CustomVertex* pHeightMap, IFrustum& pFrustum){
int			QuadTree::_IsInFrustum(std::vector<CustomVertex>& pHeightMap, IFrustum& pFrustum){
	bool	b[4];
	bool	bInSphere;
	Vector3 vec;

	// ��豸�ȿ� �ִ°�?
	//pHeightMap[m_nCenter].p.Copy(vec);
	vec = pHeightMap[m_nCenter].p;
	bInSphere = pFrustum.IsInSphere(&vec, m_fRadius);

	if (!bInSphere) return FRUSTUM_OUT;		// ��豸 �ȿ� ������ �������� �������� �׽�Ʈ ����

	// ����Ʈ���� 4���� ��� �������� �׽�Ʈ
	vec = pHeightMap[m_nCorner[0]].p;
	b[0] = pFrustum.IsIn(&vec);
	vec = pHeightMap[m_nCorner[1]].p;
	b[1] = pFrustum.IsIn(&vec);
	vec = pHeightMap[m_nCorner[2]].p;
	b[2] = pFrustum.IsIn(&vec);
	vec = pHeightMap[m_nCorner[3]].p;
	b[3] = pFrustum.IsIn(&vec);

	// 4�� ��� �������� �ȿ� ����
	if ((b[0] + b[1] + b[2] + b[3]) == 4) return FRUSTUM_COMPLETELY_IN;

	// �Ϻκ��� �������ҿ� �ִ� ���
	return FRUSTUM_PARTIALLY_IN;
}

/// _IsInFrustum()�Լ��� ����� ���� �������� �ø� ����
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

/// ī����� ���� ������ �Ÿ����� �������� LOD���� ���Ѵ�.
//int			QuadTree::_GetLODLevel(CustomVertex* pHeightMap, Vector3* pCamera, float fLODRatio){
int			QuadTree::_GetLODLevel(std::vector<CustomVertex>& pHeightMap, Vector3* pCamera, float fLODRatio){
	Vector3 vec;
	vec = pHeightMap[m_nCenter].p;
	float d = Distance(vec, *pCamera);
	return max((int)(d * fLODRatio), 1);
}

/// ��� �ڽĳ���� m_bCulled���� false�� �Ѵ�.
void		QuadTree::_AllInFrustum(){
	m_bCulled = false;
	if (!m_pChild[0]) return;
	m_pChild[0]->_AllInFrustum();
	m_pChild[1]->_AllInFrustum();
	m_pChild[2]->_AllInFrustum();
	m_pChild[3]->_AllInFrustum();
}

/// �̿���带 �����.(�ﰢ�� ������ ������)
//void		QuadTree::_BuildNeighborNode(QuadTree* pRoot, CustomVertex* pHeightMap, int cx){
void		QuadTree::_BuildNeighborNode(QuadTree* pRoot, std::vector<CustomVertex>& pHeightMap, int cx){
	int n;
	int _0, _1, _2, _3;

	for (int i = 0; i < 4; i++){
		_0 = m_nCorner[0];
		_1 = m_nCorner[1];
		_2 = m_nCorner[2];
		_3 = m_nCorner[3];

		// �̿������ 4�� �ڳʰ��� ��´�.
		n = _GetNodeIndex(i, cx, _0, _1, _2, _3);
		// �ڳʰ����� �̿������ �����͸� ���´�.
		if (n >= 0) m_pNeighbor[i] = pRoot->_FindNode(pHeightMap, _0, _1, _2, _3);
	}

	// �ڽĳ��� ���ȣ��
	if (m_pChild[0]){
		m_pChild[0]->_BuildNeighborNode(pRoot, pHeightMap, cx);
		m_pChild[1]->_BuildNeighborNode(pRoot, pHeightMap, cx);
		m_pChild[2]->_BuildNeighborNode(pRoot, pHeightMap, cx);
		m_pChild[3]->_BuildNeighborNode(pRoot, pHeightMap, cx);
	}
}

/// ����Ʈ���� �����.(Build()�Լ����� �Ҹ���.)
//bool		QuadTree::_BuildQuadTree(CustomVertex* pHeightMap){
bool		QuadTree::_BuildQuadTree(std::vector<CustomVertex>& pHeightMap){
	if (_SubDivide()){
		// ������ܰ�, �����ϴ��� �Ÿ��� ���Ѵ�.
		Vector3 vec1, vec2;
		vec1 = pHeightMap[m_nCorner[CORNER_TL]].p;
		vec2 = pHeightMap[m_nCorner[CORNER_BR]].p;
		// �Ÿ��� 2�� ������ �������� ���Ѵ�.
		//m_fRadius = Vector3::Distance(vec2, vec1) / 2.0f;
		m_fRadius = Length(vec1 - vec2) / 2.0f;
		m_pChild[CORNER_TL]->_BuildQuadTree(pHeightMap);
		m_pChild[CORNER_TR]->_BuildQuadTree(pHeightMap);
		m_pChild[CORNER_BL]->_BuildQuadTree(pHeightMap);
		m_pChild[CORNER_BR]->_BuildQuadTree(pHeightMap);
	}
	return true;
}

/// ����Ʈ���� �˻��ؼ� 4�� �ڳʰ��� ��ġ�ϴ� ��带 ã�´�.
//QuadTree*	QuadTree::_FindNode(CustomVertex* pHeightMap, int _0, int _1, int _2, int _3){
QuadTree*	QuadTree::_FindNode(std::vector<CustomVertex>& pHeightMap, int _0, int _1, int _2, int _3){
	// ��ġ�ϴ� ����� ��尪�� ����
	if ((m_nCorner[0] == _0) && (m_nCorner[1] == _1) && (m_nCorner[2] == _2) && (m_nCorner[3] == _3))
		return this;

	// �ڽ� ��尡 �ִ°�?
	if (m_pChild[0]){
		Rect rc;
		Vector2 pt;
		int n = (_0 + _1 + _2 + _3) / 4;

		// ���� �ʻ󿡼��� ��ġ
		pt.x = (int)pHeightMap[n].p.x;
		pt.y = (int)pHeightMap[n].p.z;

		// 4���� �ڳʰ��� �������� �ڽĳ���� �� ���������� ��´�.
		rc.SetRect(
			(int)pHeightMap[m_pChild[0]->m_nCorner[CORNER_TL]].p.x,
			(int)pHeightMap[m_pChild[0]->m_nCorner[CORNER_TL]].p.z,
			(int)pHeightMap[m_pChild[0]->m_nCorner[CORNER_BR]].p.x,
			(int)pHeightMap[m_pChild[0]->m_nCorner[CORNER_BR]].p.z);
		// pt���� ���������ȿ� �ִٸ� �ڽĳ��� ����.
		if (rc.IsInRect(pt))
			return m_pChild[0]->_FindNode(pHeightMap, _0, _1, _2, _3);

		// 4���� �ڳʰ��� �������� �ڽĳ���� �� ���������� ��´�.
		rc.SetRect(
			(int)pHeightMap[m_pChild[1]->m_nCorner[CORNER_TL]].p.x,
			(int)pHeightMap[m_pChild[1]->m_nCorner[CORNER_TL]].p.z,
			(int)pHeightMap[m_pChild[1]->m_nCorner[CORNER_BR]].p.x,
			(int)pHeightMap[m_pChild[1]->m_nCorner[CORNER_BR]].p.z);
		// pt���� ���������ȿ� �ִٸ� �ڽĳ��� ����.
		if (rc.IsInRect(pt))
			return m_pChild[1]->_FindNode(pHeightMap, _0, _1, _2, _3);

		// 4���� �ڳʰ��� �������� �ڽĳ���� �� ���������� ��´�.
		rc.SetRect(
			(int)pHeightMap[m_pChild[2]->m_nCorner[CORNER_TL]].p.x,
			(int)pHeightMap[m_pChild[2]->m_nCorner[CORNER_TL]].p.z,
			(int)pHeightMap[m_pChild[2]->m_nCorner[CORNER_BR]].p.x,
			(int)pHeightMap[m_pChild[2]->m_nCorner[CORNER_BR]].p.z);
		// pt���� ���������ȿ� �ִٸ� �ڽĳ��� ����.
		if (rc.IsInRect(pt))
			return m_pChild[2]->_FindNode(pHeightMap, _0, _1, _2, _3);

		// 4���� �ڳʰ��� �������� �ڽĳ���� �� ���������� ��´�.
		rc.SetRect(
			(int)pHeightMap[m_pChild[3]->m_nCorner[CORNER_TL]].p.x,
			(int)pHeightMap[m_pChild[3]->m_nCorner[CORNER_TL]].p.z,
			(int)pHeightMap[m_pChild[3]->m_nCorner[CORNER_BR]].p.x,
			(int)pHeightMap[m_pChild[3]->m_nCorner[CORNER_BR]].p.z);
		// pt���� ���������ȿ� �ִٸ� �ڽĳ��� ����.
		if (rc.IsInRect(pt))
			return m_pChild[3]->_FindNode(pHeightMap, _0, _1, _2, _3);
	}
	return nullptr;
}

/// 4�� ����(���, �ϴ�, ����, ����)�� �̿���� �ε����� ���Ѵ�.
int			QuadTree::_GetNodeIndex(int ed, int cx, int& _0, int& _1, int& _2, int& _3){
	int _a, _b, _c, _d, gap;
	_a = _0;
	_b = _1;
	_c = _2;
	_d = _3;
	gap = _b - _a;	// ���� ����� �¿�����

	switch (ed)
	{
	case EDGE_UP: // ���� ���� �̿������ �ε���
		_0 = _a - cx * gap;
		_1 = _b - cx * gap;
		_2 = _a;
		_3 = _b;
		break;
	case EDGE_DN: // �Ʒ� ���� �̿������ �ε���
		_0 = _c;
		_1 = _d;
		_2 = _c + cx * gap;
		_3 = _d + cx * gap;
		break;
	case EDGE_LT: // ���� ���� �̿������ �ε���
		_0 = _a - gap;
		_1 = _a;
		_2 = _c - gap;
		_3 = _c;
		break;
	case EDGE_RT: // ���� ���� �̿������ �ε���
		_0 = _b;
		_1 = _b + gap;
		_2 = _d;
		_3 = _d + gap;
		if ((_0 / cx) != (_a / cx)) return -1;
		if ((_1 / cx) != (_b / cx)) return -1;
		break;
	}

	int n = (_0 + _1 + _2 + _3) / 4;		/// ��� �ε���
	if (!IS_IN_RANGE(n, 0, cx * cx - 1)) return -1;

	return n;
}

/// ���� ������� ������
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

/// ���� �ڽĳ�� ������
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

/// �Ҹ���
QuadTree::~QuadTree(){
	_Destroy();
}

/// QuadTree�� �����Ѵ�.
//bool QuadTree::Build(CustomVertex* pHeightMap){
bool QuadTree::Build(std::vector<CustomVertex>& pHeightMap){
	KLog::Instance()->Log("BuildQuadTree");
	// ����Ʈ�� ����
	_BuildQuadTree(pHeightMap);

	KLog::Instance()->Log("BuildNeighborNode");
	// �̿���� ����
	_BuildNeighborNode(this, pHeightMap, m_nCorner[CORNER_TR] + 1);

	KLog::Instance()->Log("End");

	return true;
}

/// �ڳ� �ε��� ���� ���´�.
void QuadTree::GetCorner(int& _0, int& _1, int& _2, int&_3){
	_0 = m_nCorner[0];
	_1 = m_nCorner[1];
	_2 = m_nCorner[2];
	_3 = m_nCorner[3];
}

/// �ﰢ���� �ε����� �����, ����� �ﰢ���� ������ ��ȯ�Ѵ�.
//int	QuadTree::GenerateIndex(void* pIB, CustomVertex* pHeightMap, IFrustum& pFrustum, float fLODRatio){
int	QuadTree::GenerateIndex(void* pIB, std::vector<CustomVertex>& pHeightMap, IFrustum& pFrustum, float fLODRatio){
	_FrustumCull(pHeightMap, pFrustum);
	return _GetTriIndex(0, pIB, pHeightMap, pFrustum, fLODRatio);
}

/// ���� ��尡 LOD������� ���� ����� ������ ����ΰ�?
//bool QuadTree::IsVisible(CustomVertex* pHeightMap, Vector3* pCamera, float fLODRatio){
bool QuadTree::IsVisible(std::vector<CustomVertex>& pHeightMap, Vector3* pCamera, float fLODRatio){
	return ((m_nCorner[CORNER_TR] - m_nCorner[CORNER_TL]) <= _GetLODLevel(pHeightMap, pCamera, fLODRatio));
}