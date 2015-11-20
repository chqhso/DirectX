#ifndef NODE_MGR_H
#define NODE_MGR_H

//#include "Define.h"
//#include "DirectDefine.h"
#include "Interface\INodeMgr.h"
#include "Node.h"
//#include "Utility\DirectUtility\DTrack.h"


class NodeMgr : public INodeMgr{
protected:
	ObjectInfo					m_info;			/// ���� �����ü�� ���� ����
	std::vector<DMaterial>		m_materials;	/// �����迭
	std::vector<Node*>			m_nodes;		/// ����
	std::vector<DTrack*>		m_tracks;		/// track��
	LPDIRECT3DDEVICE9			m_pDev;			
	DMatrix						m_matTM;		/// �ڽĳ�� ��ü�� ����� TM
	std::vector<DMatrix>		m_matPalette;	/// �� Ȯ���� �ʿ���
	DVector3					m_bboxMaxOrig;	/// �ٿ�� �ڽ��� ���� �ִ밪(max)
	DVector3					m_bboxMinOrig;	/// �ٿ�� �ڽ��� ���� �ּҰ�(min)
	float						m_fRadius;		/// ���߿� �ٸ������� �ű���
	
	bool IsBone(int n){
		for (unsigned int i = 0; i < m_info.BoneTable.size(); i++){
			if (m_info.BoneTable[i] == n) return true;
		}
		return false;
	}
public:
	NodeMgr(LPDIRECT3DDEVICE9 pDev, KParsedData* pData);
	virtual ~NodeMgr();

	/// ��������ü�� �����͸� ��ȯ�Ѵ�.
	virtual ObjectInfo&				GetInfo() override { return m_info; }
	/// TM�� ���´�
	virtual Matrix4x4				GetTM() override { 
		Matrix4x4 mat;
		m_matTM.Copy(mat);
		return mat; 
	}
	/// TM�� �����Ѵ�.
	virtual void					SetTM(Matrix4x4& tm) override { m_matTM = tm; }
	virtual void					SetTM(DMatrix& tm) override { m_matTM = tm; }
	virtual float					GetRadius() override { return m_fRadius; }
	/// �ִϸ��̼� ����� �����.
	void					Animate(std::vector<DMatrix*> trackMats);
	virtual void					Animate(std::vector<DTrack*> tracks, float fFrame) override;
	virtual void					Animate(std::vector<DTrack*> tracks1, std::vector<DTrack*> tracks2, float fFrame1, float fFrame2, float blendFrame) override;
	/// �����ü�� �׸���.
	int						Draw(int nNodeType);
	virtual void					Draw(VSMgr* pVSMgr, PSMgr* pPSMgr) override;
	int						DrawBBox(int nNodeType);
	/// �ִϸ��̼� Track�� �����Ѵ�.
//	void					SetAni(KParsedData* pData);
	virtual std::vector<DTrack*>&	GetTracks() override { return m_tracks; }
	virtual Matrix4x4				GetBoneMatrix(std::string boneName) override {
		for (auto i : m_info.BoneTable){
			if (!(m_info.strObjectNameTable[m_nodes[i]->GetObjectID()]).compare(boneName.c_str())){
				Matrix4x4 mat;
				m_nodes[i]->GetMatrixTMPtr()->Copy(mat);
				return mat;
			}
		}
	}
	virtual DMatrix*				GetBoneDMatrixPtr(std::string boneName) override {
		for (auto i : m_info.BoneTable){
			if (!(m_info.strObjectNameTable[m_nodes[i]->GetObjectID()]).compare(boneName.c_str())){
				return m_nodes[i]->GetMatrixTMPtr();
			}
		}
	}
private:
	void					CopyMaterial(KParsedData* pData);
	void					CopyMesh(KParsedData* pData);
	void					CheckBox(DVector3* minBox, DVector3* maxBox, Node& pNode);
	void					CreateTrack(KParsedMesh* pMesh);
	void					SetPalette();
};


#endif