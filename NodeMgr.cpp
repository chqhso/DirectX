#include "NodeMgr.h"
#include "Node.h"
#include "Bone.h"
#include "RigidMesh.h"
#include "SSkinnedMesh.h"
#include "Parser\KParsedData.h"
#include "Utility\DirectUtility\DMaterial.h"
#include "Resources\VSMgr.h"
#include "Resources\PSMgr.h"

NodeMgr::NodeMgr(LPDIRECT3DDEVICE9 pDev, KParsedData* pData){
	m_pDev = pDev;

	D3DXMatrixIdentity(&m_matTM.matrix);

	// copy info
	m_info.nObjectCount = pData->m_info.nObjectCount;
	m_info.nSkinType = pData->m_info.nSkinType;
	m_info.nMeshCount = pData->m_info.nMeshCount;
	m_info.nKeyType = pData->m_info.nKeyType;
	m_info.BoneTable = pData->m_info.BoneTable;
	m_info.strObjectNameTable = pData->m_info.strObjectNameTable;
	m_info.fAnimationStart = pData->m_info.fAnimationStart;
	m_info.fAnimationEnd = pData->m_info.fAnimationEnd;

	for (int i = 0; i < pData->m_meshList.size(); i++){
		if (!IsBone(i)){
			m_info.MeshTable.push_back(i);
		}
	}

	CopyMaterial(pData);

	CopyMesh(pData);

	//SetPalette();
	int size = m_info.BoneTable.size();
	m_matPalette.resize(size);
}
NodeMgr::~NodeMgr(){
	stl_wipe_vector(m_matPalette);
	stl_wipe_vector(m_materials);
	for (int i = 0; i < m_nodes.size(); i++) DEL(m_nodes[i]);
	stl_wipe_vector(m_nodes);
	for (int i = 0; i < m_tracks.size(); i++) DEL(m_tracks[i]);
	stl_wipe_vector(m_tracks);
}
void NodeMgr::Animate(std::vector<DMatrix*> trackMats){
	int size = m_info.BoneTable.size();
	for (int i = 0; i < size; i++){
		int id = m_nodes[m_info.BoneTable[i]]->GetParentID();
		DMatrix* pTM = m_nodes[id]->GetMatrixTMPtr();
		((Bone*)m_nodes[m_info.BoneTable[i]])->Animate(pTM, trackMats[i]);
		pTM = ((Bone*)m_nodes[m_info.BoneTable[i]])->GetMatrixSkin();
		// regist skin matrix to palette for skinning
		m_matPalette[i] = *pTM;
	}
	// make other node's animation Matrix 
	for (auto i : m_info.MeshTable){
		int id = m_nodes[i]->GetParentID();
		DMatrix* pTM = m_nodes[id]->GetMatrixTMPtr();
		m_nodes[i]->Animate(pTM);
	}
}
void NodeMgr::Animate(std::vector<DTrack*> tracks, float fFrame){
	int size = m_info.BoneTable.size();
	for (int i = 0; i < size; i++){
		int id = m_nodes[m_info.BoneTable[i]]->GetParentID();
		DMatrix* pTM = m_nodes[id]->GetMatrixTMPtr();
//		((Bone*)m_nodes[m_info.BoneTable[i]])->Animate(pTM, trackMats[i]);
		((Bone*)m_nodes[m_info.BoneTable[i]])->Animate(pTM, tracks[i], fFrame);
		pTM = ((Bone*)m_nodes[m_info.BoneTable[i]])->GetMatrixSkin();
		// regist skin matrix to palette for skinning
		m_matPalette[i] = *pTM;
	}
	// make other node's animation Matrix 
	for (auto i : m_info.MeshTable){
		int id = m_nodes[i]->GetParentID();
		DMatrix* pTM = m_nodes[id]->GetMatrixTMPtr();
		m_nodes[i]->Animate(pTM);
	}
}
void NodeMgr::Animate(std::vector<DTrack*> tracks1, std::vector<DTrack*> tracks2, float fFrame1, float fFrame2, float blendFrame){
	int size = m_info.BoneTable.size();
	for (int i = 0; i < size; i++){
		int id = m_nodes[m_info.BoneTable[i]]->GetParentID();
		DMatrix* pTM = m_nodes[id]->GetMatrixTMPtr();
		((Bone*)m_nodes[m_info.BoneTable[i]])->Animate(pTM, tracks1[i], tracks2[i], fFrame1, fFrame2, blendFrame);
		pTM = ((Bone*)m_nodes[m_info.BoneTable[i]])->GetMatrixSkin();
		// regist skin matrix to palette for skinning
		m_matPalette[i] = *pTM;
	}
	// make other node's animation Matrix 
	for (auto i : m_info.MeshTable){
		int id = m_nodes[i]->GetParentID();
		DMatrix* pTM = m_nodes[id]->GetMatrixTMPtr();
		m_nodes[i]->Animate(pTM);
	}
}
int	NodeMgr::Draw(int nNodeType){

	if (nNodeType == Node::NODE_MESH){
		for (auto i : m_info.MeshTable){
			//m_pDev->SetMaterial(&m_materials[m_nodes[m_info.MeshTable[i]]->GetMaterialID()].material);
			//m_pDev->SetTexture(0, m_materials[m_nodes[m_info.MeshTable[i]]->GetMaterialID()].pTex[0]);
			m_pDev->SetMaterial(&m_materials[m_nodes[i]->GetMaterialID()].material);
			m_pDev->SetTexture(0, m_materials[m_nodes[i]->GetMaterialID()].pTex[0]);
			m_pDev->SetTransform(D3DTS_WORLD, &m_matTM.matrix);
			m_nodes[i]->Draw(&m_matTM);
		}
	}
	else if (nNodeType == Node::NODE_BONE){
		for (auto i : m_info.BoneTable){
			m_pDev->SetMaterial(&m_materials[m_nodes[i]->GetMaterialID()].material);
			m_pDev->SetTexture(0, m_materials[m_nodes[i]->GetMaterialID()].pTex[0]);
			m_pDev->SetTransform(D3DTS_WORLD, &m_matTM.matrix);
			m_nodes[i]->Draw(&m_matTM);
		}
	}
	else{
		for (auto i : m_nodes){
			m_pDev->SetMaterial(&m_materials[i->GetMaterialID()].material);
			m_pDev->SetTexture(0, m_materials[i->GetMaterialID()].pTex[0]);
			m_pDev->SetTransform(D3DTS_WORLD, &m_matTM.matrix);
			i->Draw(&m_matTM);
		}
	}
	return 0;
}
void NodeMgr::Draw(VSMgr* pVSMgr, PSMgr* pPSMgr){
	pVSMgr->SetMatrix("matWorld", &m_matTM);
	for (auto i : m_info.MeshTable){
		pPSMgr->SetTexture("DiffuseSampler", m_materials[m_nodes[i]->GetMaterialID()].pTex[0]);
		m_nodes[i]->Draw(pVSMgr, pPSMgr);
		pPSMgr->SetTexture("DiffuseSampler", NULL);
	}
}
int	NodeMgr::DrawBBox(int nNodeType){

	m_pDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	for (auto i : m_nodes){
		m_pDev->SetTransform(D3DTS_WORLD, &m_matTM.matrix);
		if (nNodeType == Node::NODE_NODE) i->DrawBBox(&m_matTM);
		else if (nNodeType == Node::NODE_BONE) { if (i->GetNodeType() == Node::NODE_BONE) i->DrawBBox(&m_matTM); }
		else if (nNodeType == Node::NODE_MESH) { if (i->GetNodeType() == Node::NODE_MESH) i->DrawBBox(&m_matTM); }
	}
	m_pDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	return 0;
}
void NodeMgr::CopyMaterial(KParsedData* pData){
	int size = pData->m_materialTable.size();
	m_materials.resize(size);
	for (int i = 0; i < size; i++){
		m_materials[i].SetMaterial(m_pDev, pData->m_materialTable[i]);
	}
}
void NodeMgr::CopyMesh(KParsedData* pData){
	DVector3 minBox, maxBox;
	Node* pNode;

	for (auto i : pData->m_meshList){
		// 부모가 없는 노드는 0번노드를 부모로 한다.
		if ((*i).m_nParentID == -1)
			(*i).m_nParentID = 0;

		// Bone이나 Biped라면 Bone로 생성
		if (!((*i).m_strNodeType.compare("BoneGeometry")) ||
			!((*i).m_strNodeType.compare("Biped_Object")) ||
			!((*i).m_strNodeType.compare("Bone")) ||
			((*i).m_nObjectID == 0)){
			//m_bones.push_back(new Bone(m_pDev, i));
			//Bone* n = new Bone(m_pDev, i);
			pNode = new Bone(m_pDev, i);
			CreateTrack(i);
			//CheckBox(&minBox, &maxBox, (*n));
			CheckBox(&minBox, &maxBox, (*pNode));
			//m_bones.push_back(n);
			m_nodes.push_back(pNode);
		}
		else if ( !((*i).m_strNodeType.compare("Editable_mesh"))){ // Editable_Mesh라면 Mesh로 생성
			if ((*i).m_isSkinned){ // Skin이 있으면 SkinnedMesh로 생성
				//m_nodes.push_back(new SSkinnedMesh(m_pDev, i));
				//SSkinnedMesh* n = new SSkinnedMesh(m_pDev, i);
				pNode = new SSkinnedMesh(m_pDev, i);
				CheckBox(&minBox, &maxBox, (*pNode));
				((SkinnedMesh*)pNode)->SetMatrixPalette(&m_matPalette);
				m_nodes.push_back(pNode);
			}
			else{
				//m_nodes.push_back(new RigidMesh(m_pDev, i));
				//RigidMesh* n = new RigidMesh(m_pDev, i);
				pNode = new RigidMesh(m_pDev, i);
				//CheckBox(&minBox, &maxBox, (*n));
				CheckBox(&minBox, &maxBox, (*pNode));
				m_nodes.push_back(pNode);
			}
		}
		else{ // 어느쪽도 포함되지 않으면 Node로 생성
			//m_nodes.push_back(new Node(m_pDev, i));
			pNode = new Node(m_pDev, i);
			CheckBox(&minBox, &maxBox, (*pNode));
			m_nodes.push_back(pNode);
		}
	}
	m_bboxMinOrig = minBox;
	m_bboxMaxOrig = maxBox;
	float fmin = D3DXVec3Length(&minBox.vector);
	float fmax = D3DXVec3Length(&maxBox.vector);
	m_fRadius = (fmin > fmax) ? fmin : fmax;
}
void NodeMgr::CheckBox(DVector3* minBox, DVector3* maxBox, Node& pNode){
	DVector3 min, max;
	pNode.GetBBox(&min, &max);
	if (D3DXVec3Length(&(minBox->vector)) < D3DXVec3Length(&(min.vector))) minBox->vector = min.vector;
	if (D3DXVec3Length(&(maxBox->vector)) < D3DXVec3Length(&(max.vector))) maxBox->vector = max.vector;
}
void NodeMgr::CreateTrack(KParsedMesh* pMesh){
	DTrack* track = new DTrack(pMesh->m_track);
	m_tracks.push_back(track);
}
void NodeMgr::SetPalette(){
	int size = m_info.BoneTable.size();
	m_matPalette.resize(size);
	for (int i = 0; i < size; i++){
		int id = m_nodes[m_info.BoneTable[i]]->GetParentID();
		DMatrix* pTM = m_nodes[id]->GetMatrixTMPtr();
		m_nodes[m_info.BoneTable[i]]->Animate(pTM);
		pTM = m_nodes[m_info.BoneTable[i]]->GetMatrixTMPtr();
		m_matPalette[i] = *pTM;
	}
}