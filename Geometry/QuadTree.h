#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include "../Define.h"
#include "../DirectDefine.h"
//#include "../Utility/Frustum.h"
#include "../Interface/IFrustum.h"

/**
 * @brief QuadTree�� ���̽� Ŭ����
 *
 */
class QuadTree{
	/// ����Ʈ���� �����Ǵ� 4���� �ڳʰ��� ���� �����
	enum			CornerType{CORNER_TL, CORNER_TR, CORNER_BL, CORNER_BR};
	/// �̿���� ó���� �����
	enum			{EDGE_UP, EDGE_DN, EDGE_LT, EDGE_RT};
	/// ����Ʈ���� �������Ұ��� ����
	enum			QuadLocation{	FRUSTUM_OUT				= 0,		/// �������ҿ��� ���� ���
									FRUSTUM_PARTIALLY_IN	= 1,		/// �������ҿ� �κ� ����
									FRUSTUM_COMPLETELY_IN	= 2,		/// �������ҿ� ���� ����
									FRUSTUM_UNKNOWN			= -1};		/// �𸣰���

private:
	std::vector<QuadTree*>	m_pChild;			/// QuadTree�� 4���� �ڽĳ��
	QuadTree*				m_pParent;			/// Triangle Crack(Popping)�� �������ؼ� ����Ѵ�. 10/30�߰�
	std::vector<QuadTree*>	m_pNeighbor;		/// Triangle Crack(Popping)�� �������ؼ� ����Ѵ�. 10/30�߰�

	int						m_nCenter;			/// QuadTree�� ������ ù��° ��
	std::vector<int>		m_nCorner;			/// QuadTree�� ������ �ι�° ��
												///		TopLeft(TL)					TopRight(TR)
												///				0-----------------------1
												///				|						|
												///				|						|
												///				2-----------------------3
												///	BottomLeft(BL)					BottomRight(BR)
	bool					m_bCulled;			/// �������ҿ��� �ø��� ����ΰ�?
	float					m_fRadius;			/// ��带 ���δ� ��豸(bounding sphere)�� ������
	
private:
	/// �ڽĳ�带 �߰��Ѵ�.
	QuadTree*	_AddChild(int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR);

	/// 4���� �ڳʰ��� �����Ѵ�.
	bool		_SetCorners(int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR);

	/// QuadTree�� 4���� ���� Ʈ���� �κк���(subdibide)�Ѵ�.
	bool		_SubDivide();		// QuadTree�� subdivide�Ѵ�.

	/// ����� �������� �ε����� �����Ѵ�. TODO : 32��Ʈ�� 16��Ʈ ������
	//int			_GetTriIndex(int nTris, void* pIndex, CustomVertex* pHeightMap, IFrustum& pFrustum, float fLODRatio);
	int			_GetTriIndex(int nTris, void* pIndex, std::vector<CustomVertex>& pHeightMap, IFrustum& pFrustum, float fLODRatio);

	/// �޸𸮿��� ����Ʈ���� �����Ѵ�.
	void		_Destroy();

	/// �����尡 �������ҿ� ���ԵǴ°�?
	//int			_IsInFrustum(CustomVertex* pHeightMap, IFrustum& pFrustum);
	int			_IsInFrustum(std::vector<CustomVertex>& pHeightMap, IFrustum& pFrustum);

	/// _IsInFrustum()�Լ��� ����� ���� �������� �ø� ����
	//void		_FrustumCull(CustomVertex* pHeightMap, IFrustum& pFrustum);
	void		_FrustumCull(std::vector<CustomVertex>& pHeightMap, IFrustum& pFrustum);

	/// ī����� ���� ������ �Ÿ����� �������� LOD���� ���Ѵ�.
	//int			_GetLODLevel(CustomVertex* pHeightMap, Vector3* pCamera, float fLODRatio);
	int			_GetLODLevel(std::vector<CustomVertex>& pHeightMap, Vector3* pCamera, float fLODRatio);

	/// ��� �ڽĳ���� m_bCulled���� false�� �Ѵ�.
	void		_AllInFrustum();

	/// �̿���带 �����.(�ﰢ�� ������ ������)
	//void		_BuildNeighborNode(QuadTree* pRoot, CustomVertex* pHeightMap, int cx);
	void		_BuildNeighborNode(QuadTree* pRoot, std::vector<CustomVertex>& pHeightMap, int cx);

	/// ����Ʈ���� �����.(Build()�Լ����� �Ҹ���.)
	//bool		_BuildQuadTree(CustomVertex* pHeightMap);
	bool		_BuildQuadTree(std::vector<CustomVertex>& pHeightMap);

	/// ����Ʈ���� �˻��ؼ� 4�� �ڳʰ��� ��ġ�ϴ� ��带 ã�´�.
	//QuadTree*	_FindNode(CustomVertex* pHeightMap, int _0, int _1, int _2, int _3);
	QuadTree*	_FindNode(std::vector<CustomVertex>& pHeightMap, int _0, int _1, int _2, int _3);

	/// 4�� ����(���, �ϴ�, ����, ����)�� �̿���� �ε����� ���Ѵ�.
	int			_GetNodeIndex(int ed, int cx, int& _0, int& _1, int& _2, int& _3);

public:
	/// ���� ������� ������
	QuadTree(int cx, int cy);

	/// ���� �ڽĳ�� ������
	QuadTree(QuadTree* pParent);

	/// �Ҹ���
	~QuadTree();

	/// ���� ��尡 Culling�Ȱ��ΰ�?
	bool IsCulled(){ return m_bCulled; }

	/// QuadTree�� �����Ѵ�.
	//bool Build(CustomVertex* pHeightMap);
	bool Build(std::vector<CustomVertex>& pHeightMap);

	/// �ڳ� �ε��� ���� ���´�.
	void GetCorner(int& _0, int& _1, int& _2, int&_3);

	/// �ﰢ���� �ε����� �����, ����� �ﰢ���� ������ ��ȯ�Ѵ�.
	//int	GenerateIndex(void* pIB, CustomVertex* pHeightMap, IFrustum& pFrustum, float fLODRatio);
	int	GenerateIndex(void* pIB, std::vector<CustomVertex>& pHeightMap, IFrustum& pFrustum, float fLODRatio);

	/// ���� ��尡 LOD������� ���� ����� ������ ����ΰ�?
	//bool IsVisible(CustomVertex* pHeightMap, Vector3* pCamera, float fLODRatio);
	bool IsVisible(std::vector<CustomVertex>& pHeightMap, Vector3* pCamera, float fLODRatio);
};

#endif