#ifndef K_PARSED_MESH_H
#define K_PARSED_MESH_H

#include "../Define.h"

/// �Ľ̵� �޽�����
class KParsedMesh{
public:
	std::string					m_strNodeType;
	int							m_nObjectID;				/// ������Ʈ ID, ������Ʈ���� ZParser.Info.strObjectNameTable�� �ִ�.
	int							m_nObjectHashID;			/// hashed string �˰����� ����ϱ� ���� ����
	int							m_nParentID;				/// �θ��� ID

	bool						m_isSkinned;				/// skinned mesh == true
	Vector3						m_bboxMax;					/// �ٿ�� �ڽ��� �ִ밪(max)
	Vector3						m_bboxMin;					/// �ٿ�� �ڽ��� �ּҰ�(min)
	Matrix4x4					m_tmLocal;					/// Local TM ���
	Matrix4x4					m_tmWorld;					/// World TM ���
	std::vector<Vector3>		m_vertex;					/// ������ ��ó����
	std::vector<Vector3>		m_normal;					/// ������ �������
	std::vector<Vector2>		m_tvertex;					/// �ؽ��� ����

	int							m_nMaterialID;				/// ������ ID
	int							m_nMaterialCount;			/// �޽ÿ��� ������� ������ ����
	std::vector<IndexWidthID>	m_triIndex;					/// �ﰢ���� �ε���
	std::vector<Index3i>		m_texIndex;					/// �ؽ����� �ε���
	std::vector<VertWeight>		m_vertWeight;				/// ������ ����ġ��
	Track						m_track;					/// �ִϸ��̼� Ʈ������
public:
	std::vector<VertMerged>		m_vtxFinal;					/// �������� �������� ������ ��������
	std::vector<Index3i>		m_idxFinal;					/// �ε���
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