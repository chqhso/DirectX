#ifndef K_PARSED_MESH_H
#define K_PARSED_MESH_H

#include "../Define.h"

/// 파싱된 메시정보
class KParsedMesh{
public:
	std::string					m_strNodeType;
	int							m_nObjectID;				/// 오브젝트 ID, 오브젝트명은 ZParser.Info.strObjectNameTable에 있다.
	int							m_nObjectHashID;			/// hashed string 알고리즘을 사용하기 위한 변수
	int							m_nParentID;				/// 부모의 ID

	bool						m_isSkinned;				/// skinned mesh == true
	Vector3						m_bboxMax;					/// 바운딩 박스의 최대값(max)
	Vector3						m_bboxMin;					/// 바운딩 박스의 최소값(min)
	Matrix4x4					m_tmLocal;					/// Local TM 행렬
	Matrix4x4					m_tmWorld;					/// World TM 행렬
	std::vector<Vector3>		m_vertex;					/// 정점의 위처정보
	std::vector<Vector3>		m_normal;					/// 정점의 노멀정보
	std::vector<Vector2>		m_tvertex;					/// 텍스쳐 정보

	int							m_nMaterialID;				/// 재질의 ID
	int							m_nMaterialCount;			/// 메시에서 사용중인 재질의 개수
	std::vector<IndexWidthID>	m_triIndex;					/// 삼각형의 인덱스
	std::vector<Index3i>		m_texIndex;					/// 텍스쳐의 인덱스
	std::vector<VertWeight>		m_vertWeight;				/// 정점의 가중치값
	Track						m_track;					/// 애니메이션 트랙정보
public:
	std::vector<VertMerged>		m_vtxFinal;					/// 정점관련 정보들을 종합한 최종정점
	std::vector<Index3i>		m_idxFinal;					/// 인덱스
public:
	KParsedMesh(){
		m_nParentID = -1;
		m_nObjectID = -1;
		m_nObjectHashID = -1;
		m_isSkinned = false;
	}

	~KParsedMesh(){
//		stl_wipe_vector(m_nChildIDs);
		stl_wipe_vector(m_vertex);
		stl_wipe_vector(m_normal);
		stl_wipe_vector(m_tvertex);
		stl_wipe_vector(m_triIndex);
		stl_wipe_vector(m_texIndex);
		stl_wipe_vector(m_vertWeight);
		stl_wipe_vector(m_vtxFinal);
		stl_wipe_vector(m_idxFinal);
	}
};

#endif