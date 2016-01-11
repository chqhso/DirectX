#ifndef NODE_MGR_H
#define NODE_MGR_H

//#include "Define.h"
//#include "DirectDefine.h"
#include "Interface\INodeMgr.h"
#include "Node.h"
//#include "Utility\DirectUtility\DTrack.h"

struct KParsedData;

class NodeMgr : public INodeMgr{
protected:
	ObjectInfo					m_info;			/// 현재 노드전체에 대한 정보
	std::vector<DMaterial>		m_materials;	/// 재질배열
	std::vector<Node*>			m_nodes;		/// 노드들
	std::vector<DTrack*>		m_tracks;		/// track들
	LPDIRECT3DDEVICE9			m_pDev;			
	Matrix4x4						m_matTM;		/// 자식노드 전체에 적용될 TM
	std::vector<Matrix4x4>		m_matPalette;	/// 좀 확인이 필요함
	Vector3					m_bboxMaxOrig;	/// 바운딩 박스의 최초 최대값(max)
	Vector3					m_bboxMinOrig;	/// 바운딩 박스의 최초 최소값(min)
	float						m_fRadius;		/// 나중에 다른곳으로 옮기자
	
	bool IsBone(int n){
		for (unsigned int i = 0; i < m_info.BoneTable.size(); i++){
			if (m_info.BoneTable[i] == n) return true;
		}
		return false;
	}
public:
	NodeMgr(LPDIRECT3DDEVICE9 pDev, KParsedData* pData);
	virtual ~NodeMgr();

	/// 정보구조체의 포인터를 반환한다.
	virtual ObjectInfo&				GetInfo() override { return m_info; }
	/// TM을 얻어온다
	virtual Matrix4x4*				GetTM() override { 
		return &m_matTM; 
	}
	/// TM을 설정한다.
	virtual void					SetTM(Matrix4x4& tm) override { m_matTM = tm; }
	virtual float					GetRadius() override { return m_fRadius; }
	/// 애니메이션 행렬을 만든다.
	virtual void					Animate(std::vector<DTrack*> tracks, float fFrame) override;
	virtual void					Animate(std::vector<DTrack*> tracks1, std::vector<DTrack*> tracks2, float fFrame1, float fFrame2, float blendFrame) override;
	/// 노드전체를 그린다.
	virtual void					Draw(VSMgr* pVSMgr, PSMgr* pPSMgr) override;
	int						DrawBBox(int nNodeType);
	/// 애니메이션 Track을 설정한다.
//	void					SetAni(KParsedData* pData);
	virtual std::vector<DTrack*>&	GetTracks() override { return m_tracks; }
	virtual Matrix4x4*				GetBoneMatrix(std::string boneName) override {
		for (auto i : m_info.BoneTable){
			if (!(m_info.strObjectNameTable[m_nodes[i]->GetObjectID()]).compare(boneName.c_str())){
				//Matrix4x4 mat;
				//m_nodes[i]->GetMatrixTMPtr()->Copy(mat);
				//return mat;
				return m_nodes[i]->GetMatrixTMPtr();
			}
		}
		return nullptr;
	}
	//virtual Matrix4x4*				GetBoneDMatrixPtr(std::string boneName) override {
	//	for (auto i : m_info.BoneTable){
	//		if (!(m_info.strObjectNameTable[m_nodes[i]->GetObjectID()]).compare(boneName.c_str())){
	//			return m_nodes[i]->GetMatrixTMPtr();
	//		}
	//	}
	//}
private:
	void					CopyMaterial(KParsedData* pData);
	void					CopyMesh(KParsedData* pData);
	void					CheckBox(Vector3* minBox, Vector3* maxBox, Node& pNode);
	void					CreateTrack(KParsedMesh* pMesh);
	void					SetPalette();
};


#endif