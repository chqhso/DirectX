#include <Windows.h>
#include <cassert>
#include "KParser.h"

KParser::KParser(){
	m_pKXML = new KXML();
}
KParser::~KParser(){
	m_pKXML->Close();
	DEL(m_pKXML);
}
int KParser::Parse_XML(KParsedData* pData, const char* lpszFilename){
	if (!m_pKXML->Open(lpszFilename)){
		return 0;
	}
	try{
		if (!_ParseInfo(pData)){
			throw;
		}
		if (!_ParseMaterial(pData)){
			throw;
		}
		if (!_ParseObject(pData)){
			throw;
		}
		return 1;
	}
	catch (...){
		return 0;
	}
}

/// TriIndex�� ���� �ﰢ���� sub material������ ���ο� ZCMesh������Ʈ�� �и��Ѵ�.
int KParser::_SplitMeshByFaceMaterial(KParsedData* pData){
	int								i, j, cnt;
	std::list<KParsedMesh*>::iterator	it, jt;
	KParsedMesh*							pMesh;
	KParsedMesh*							pOrig;

	for (it = pData->m_meshList.begin(); it != pData->m_meshList.end(); it++){
		/// Sub-Material�� �ִ°�??
		if ((*it)->m_nMaterialCount > 1){
			// sub-material������ŭ sub-mesh�� �����ǹǷ�
			// strobjectnameTable�� sub-mesh������ŭ �÷��ش�.
			// �̶�, id�� �迭�� ��ġ�� ��Ī�ǵ��� �ϴ°��� �߿��ϴ�
			// sub-mesh�� �̸����� ���δ� ���鹮�� " " �̴�.
			pData->m_info.strObjectNameTable.insert(pData->m_info.strObjectNameTable.begin() + (*it)->m_nObjectID + 1, (*it)->m_nMaterialCount - 1, " ");

			// sub-material������ŭ sub-mesh�� �����ǹǷ�
			// BoneTables�� ����Ű�� ������ ��ȣ�� �����Ǵ� sub-mesh�� �ش��ϴ� ��ȣ��
			// �׸�ŭ �ڷ� �о���Ѵ�.
			for (i = 0; i < pData->m_info.BoneTable.size(); i++){
				if (pData->m_info.BoneTable[i] >(*it)->m_nObjectID)
					pData->m_info.BoneTable[i] += ((*it)->m_nMaterialCount - 1);
			}

			// sub-material������ŭ sub-mesh�� �����ǹǷ�
			// object id�� parent id������ �߰��� ����ִ� sub-mesh������ŭ �߰���Ų��
			for (jt = pData->m_meshList.begin(); jt != pData->m_meshList.end(); jt++){
				if ((*jt)->m_nObjectID > (*it)->m_nObjectID)
					(*jt)->m_nObjectID += ((*it)->m_nMaterialCount - 1);
				if ((*jt)->m_nParentID > (*it)->m_nObjectID)
					(*jt)->m_nParentID += ((*it)->m_nMaterialCount - 1);
			}

			j = 0;
			pOrig = *it;
			it = pData->m_meshList.erase(it);	// ���� mesh�� ����Ʈ������ �����Ѵ�.
			// ���� pOrig�� ��ȿ�ϴ�
			for (i = 0; i < pOrig->m_nMaterialCount; i++){
				pMesh = new KParsedMesh();
				pMesh->m_strNodeType = pOrig->m_strNodeType;
				pMesh->m_nObjectID = pOrig->m_nObjectID + i;	// object id�� ������Ű�� submesh���
				pMesh->m_nObjectHashID = pOrig->m_nObjectHashID;
				pMesh->m_nParentID = pOrig->m_nParentID;
				pMesh->m_bboxMax = pOrig->m_bboxMax;
				pMesh->m_bboxMin = pOrig->m_bboxMin;
				pMesh->m_tmLocal = pOrig->m_tmLocal;
				pMesh->m_tmWorld = pOrig->m_tmWorld;
				pMesh->m_vertex = pOrig->m_vertex;
				pMesh->m_normal = pOrig->m_normal;
				pMesh->m_tvertex = pOrig->m_tvertex;
				pMesh->m_nMaterialCount = 1;
				//				pMesh->m_texindex = pOrig->m_texindex;
				pMesh->m_vertWeight = pOrig->m_vertWeight;
				pMesh->m_track = pOrig->m_track;
				pMesh->m_isSkinned = pOrig->m_isSkinned;
				cnt = pOrig->m_triIndex.size() - 1;
				for (; j < cnt;){
					if (pOrig->m_triIndex[j].ID == pOrig->m_triIndex[j + 1].ID){
						pMesh->m_triIndex.push_back(pOrig->m_triIndex[j]);
						if (pOrig->m_texIndex.size())
							pMesh->m_texIndex.push_back(pOrig->m_texIndex[j]);
					}
					else{
						j++;
						if (j == cnt){ /// ���� ������ index������ �����Ѵ�.
							pMesh->m_triIndex.push_back(pOrig->m_triIndex[j]);
							if (pOrig->m_texIndex.size())
								pMesh->m_texIndex.push_back(pOrig->m_texIndex[j]);
						}
						break;
					}
					j++;
				}
				// ������ sub-mesh�� child�� ���
				// (STL�� insert��it�տ� insert�Ѵ�.)
				pData->m_meshList.insert(it, pMesh);	/// ������ sub-mesh�� child�� ���
			}
			DEL(pOrig);
		}
	}
	pData->m_info.nObjectCount = pData->m_meshList.size();
	return 1;
}

void KParser::_MergeBlendWeight(VertMerged& vm, VertWeight& vw){
	int i;
	VertWeight t = vw;
	int cnt = t.ID.size();

	/// blend weight�� 4�����϶�� ������ 4���� �����.
	if (cnt < 4){
		t.ID.resize(4);
		t.fWeight.resize(4);
		for (i = cnt; i < 4; i++){
			t.ID[i] = 0;
			t.fWeight[i] = 0;
		}
	}

	/// script���� ����� ����ġ���� ū��������(�ø�����) ���ĵǾ��ִ�.
	/// ������ �տ��� 4���� ���� ���ϸ� �ȴ�.
	//TODO : 4������ �ƴ϶� 3����??
	for (i = 0; i < 3; i++){
		vm.b[i] = t.fWeight[i];
	}
	vm.i = BLENDINDEX(t.ID[3], t.ID[2], t.ID[1], t.ID[0]);
}

int KParser::_MergeVertex(KParsedData* pData){
	int			i, j, cnt;
	std::list<KParsedMesh*>::iterator it, jt;
	KParsedMesh*			pMesh;
	VertMerged*		pVert;
	Index3i*		pIndex;
	DWORD			vindex, tindex;

	for (it = pData->m_meshList.begin(); it != pData->m_meshList.end(); it++){
		pMesh = *it;
		pVert = new VertMerged[pMesh->m_vertex.size() + pMesh->m_triIndex.size() * 3];
		pIndex = new Index3i[pMesh->m_triIndex.size()];
		for (i = 0; i < pMesh->m_vertex.size(); i++){
			pVert[i].p = pMesh->m_vertex[i];
			pVert[i].n = pMesh->m_normal[i];

			// BlendWeight�� �ִ� ������Ʈ ó��
			if ((*it)->m_isSkinned)
				_MergeBlendWeight(pVert[i], pMesh->m_vertWeight[i]);

			pVert[i].t.x = BIGFLOAT;
			pVert[i].t.y = BIGFLOAT;
		}

		for (i = 0; i < pMesh->m_triIndex.size(); i++){
			pIndex[i] = pMesh->m_triIndex[i].index;
		}
		cnt = pMesh->m_vertex.size();

		/// �ؽ��İ� �ִ� ������Ʈ�ΰ�?
		if (pMesh->m_texIndex.size()){
			for (i = 0; i < pMesh->m_triIndex.size(); i++){
				for (j = 0; j < 3; j++){
					vindex = pIndex[i].i[j];				// ������ �ε���
					tindex = pMesh->m_texIndex[i].i[j];		// �ؽ����� �ε���
					// ���� ���� ���Ե����� �ʾ����� �ؽ��� ��ǥ �Է�
					if (pVert[vindex].t.x == BIGFLOAT || pVert[vindex].t.y == BIGFLOAT){
						pVert[vindex].t = pMesh->m_tvertex[tindex];
					}
					else{ // ���� �ؽ��� ���� �̹� ������ ���ο� ���� ����
						pIndex[i].i[j] = cnt;
						pVert[cnt] = pVert[vindex];
						pVert[cnt].t = pMesh->m_tvertex[tindex];
						cnt++;
					}
				}
			}
		}
		pMesh->m_nMaterialID = pMesh->m_triIndex.size() ? max(pMesh->m_triIndex[0].ID, 0) : 0;
		pMesh->m_vtxFinal.resize(cnt);
		pMesh->m_idxFinal.resize(pMesh->m_triIndex.size());
		for (i = 0; i < cnt; i++) pMesh->m_vtxFinal[i] = pVert[i];
		for (i = 0; i < pMesh->m_triIndex.size(); i++) pMesh->m_idxFinal[i] = pIndex[i];
		DELS(pVert);
		DELS(pIndex);
	}
	return 1;
}

int KParser::_ParseInfo(KParsedData* pData){
	int					i;
	char				str[128];
	long				nCount = 0;
	IXMLDOMNodeList*	pList = NULL;
	IXMLDOMNode*		pNode = NULL;

	try{
		pList = m_pKXML->FindElement("Body/Info/ObjectCount"); pList->get_item(0, &pNode); m_pKXML->GetElementText(pNode, str);
		pData->m_info.nObjectCount = atoi(str);

		pList = m_pKXML->FindElement("Body/Info/MeshCount"); pList->get_item(0, &pNode); m_pKXML->GetElementText(pNode, str);
		pData->m_info.nMeshCount = atoi(str);

		pList = m_pKXML->FindElement("Body/Info/AnimationStart"); pList->get_item(0, &pNode); m_pKXML->GetElementText(pNode, str);
		pData->m_info.fAnimationStart = atoi(str);

		pList = m_pKXML->FindElement("Body/Info/AnimationEnd");	pList->get_item(0, &pNode);	m_pKXML->GetElementText(pNode, str);
		pData->m_info.fAnimationEnd = atoi(str);

		pList = m_pKXML->FindElement("Body/Info/KeyType"); pList->get_item(0, &pNode); m_pKXML->GetElementText(pNode, str);
		pData->m_info.nKeyType = 1; // atoi(str); /// must be completed later.

		pList = m_pKXML->FindElement("Body/Info/Object/Value");
		pList->get_length(&nCount);
		pData->m_info.strObjectNameTable.resize(nCount);
		for (i = 0; i < nCount; i++){
			pList->get_item(i, &pNode);
			m_pKXML->GetElementText(pNode, str);
			pData->m_info.strObjectNameTable[i] = str;
		}

		pList = m_pKXML->FindElement("Body/Info/Bone/Value");
		pList->get_length(&nCount);
		pData->m_info.BoneTable.resize(nCount);
		for (i = 0; i < nCount; i++){
			pList->get_item(i, &pNode);
			m_pKXML->GetElementText(pNode, str);
			m_pKXML->GetAttributeText(pNode, "ID", str);
			pData->m_info.BoneTable[i] = atoi(str);
		}
		return 1;
	}
	catch (...){
		return 0;
	}
}

int KParser::_ParseMaterial(KParsedData* pData){
	int					i;
	char				str[128];
	long				nCount = 0;
	IXMLDOMNodeList*	pList = NULL;
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNode = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	try{
		//		pList = m_xml.FindElement( "Body/Material/Slot" );
		pList = m_pKXML->FindElement("Body/Material/Slot");
		pList->get_length(&nCount);
		pData->m_materialTable.resize(nCount);
		for (i = 0; i < nCount; i++){

			pList->get_item(i, &pNode);
			pListChild = m_pKXML->FindElement(pNode, "Diffuse");
			pListChild->get_item(0, &pNodeChild);
			m_pKXML->GetElementText(pNodeChild, str);
			pData->m_materialTable[i].diffuse = _StrToColor3(str);

			pListChild = m_pKXML->FindElement(pNode, "Ambient");
			pListChild->get_item(0, &pNodeChild);
			m_pKXML->GetElementText(pNodeChild, str);
			pData->m_materialTable[i].ambient = _StrToColor3(str);

			pListChild = m_pKXML->FindElement(pNode, "Specular");
			pListChild->get_item(0, &pNodeChild);
			m_pKXML->GetElementText(pNodeChild, str);
			pData->m_materialTable[i].specular = _StrToColor3(str);

			pListChild = m_pKXML->FindElement(pNode, "Emissive");
			pListChild->get_item(0, &pNodeChild);
			m_pKXML->GetElementText(pNodeChild, str);
			pData->m_materialTable[i].emissive = _StrToColor3(str);

			pListChild = m_pKXML->FindElement(pNode, "Opacity");
			pListChild->get_item(0, &pNodeChild);
			m_pKXML->GetElementText(pNodeChild, str);
			pData->m_materialTable[i].opacity = atof(str);

			pListChild = m_pKXML->FindElement(pNode, "Power");
			pListChild->get_item(0, &pNodeChild);
			m_pKXML->GetElementText(pNodeChild, str);
			pData->m_materialTable[i].power = atof(str);

			pListChild = m_pKXML->FindElement(pNode, "DiffuseMap");
			if (S_OK == pListChild->get_item(0, &pNodeChild)){
				m_pKXML->GetElementText(pNodeChild, str);
				pData->m_materialTable[i].strMapDiffuse = str;
			}

			pListChild = m_pKXML->FindElement(pNode, "SpecularMap");
			if (S_OK == pListChild->get_item(0, &pNodeChild)){
				m_pKXML->GetElementText(pNodeChild, str);
				pData->m_materialTable[i].strMapSpecular = str;
			}

			pListChild = m_pKXML->FindElement(pNode, "BumpMap");
			if (S_OK == pListChild->get_item(0, &pNodeChild)){
				m_pKXML->GetElementText(pNodeChild, str);
				pData->m_materialTable[i].strMapBump = str;
			}

			pListChild = m_pKXML->FindElement(pNode, "DisplacementMap");
			if (S_OK == pListChild->get_item(0, &pNodeChild)){
				m_pKXML->GetElementText(pNodeChild, str);
				pData->m_materialTable[i].strMapDisplace = str;
			}
		}
		return 1;
	}
	catch (...){
		return 0;
	}
}

int KParser::_ParseObject(KParsedData* pData){
	int						i;
	char					str[128];
	long					nCount = 0;
	IXMLDOMNodeList*		pList = NULL;
	IXMLDOMNode*			pNode = NULL;
	KParsedMesh*					pMesh;

	try{
		pList = m_pKXML->FindElement("Body/Object");
		pList->get_length(&nCount);
		for (i = 0; i < nCount; i++){
			pMesh = new KParsedMesh();
			pData->m_meshList.push_back(pMesh);

			pList->get_item(i, &pNode);
			m_pKXML->GetAttributeText(pNode, "ID", str);
			pMesh->m_nObjectID = atoi(str);
			m_pKXML->GetAttributeText(pNode, "Class", str);
			pMesh->m_strNodeType = str;

			if (!_ParseObjectParent(pMesh, pNode))throw;
			if (!_ParseObjectBBox(pMesh, pNode))throw;
			if (!_ParseObjectTM(pMesh, pNode))throw;
			if (!_ParseObjectVertex(pMesh, pNode))throw;
			if (!_ParseObjectVertexNormal(pMesh, pNode))throw;
			if (!_ParseObjectTVertex(pMesh, pNode))throw;
			if (!_ParseObjectTriIndex(pMesh, pNode))throw;
			if (!_ParseObjectTexIndex(pMesh, pNode))throw;
			if (!_ParseObjectVertWeight(pMesh, pNode))throw;
			if (!_ParseObjectKey(pMesh, pNode))throw;

			pMesh->m_track.start = pData->m_info.fAnimationStart;
			pMesh->m_track.end = pData->m_info.fAnimationEnd;
		}
		return 1;
	}
	catch (...){
		return 0;
	}
}

int KParser::_ParseObjectParent(KParsedMesh* pMesh, IXMLDOMNode* pNode){
	char				str[128];
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	try{
		pListChild = m_pKXML->FindElement(pNode, "Parent");
		pListChild->get_item(0, &pNodeChild);
		m_pKXML->GetAttributeText(pNodeChild, "ID", str);
		pMesh->m_nParentID = atoi(str);
		return 1;
	}
	catch (...){
		return 0;
	}
}

int KParser::_ParseObjectBBox(KParsedMesh* pMesh, IXMLDOMNode* pNode){
	char				str[128];
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	try{
		pListChild = m_pKXML->FindElement(pNode, "BoundingBox/Max");
		pListChild->get_item(0, &pNodeChild);
		m_pKXML->GetElementText(pNodeChild, str);
		pMesh->m_bboxMax = _StrToVector3(str);

		pListChild = m_pKXML->FindElement(pNode, "BoundingBox/Min");
		pListChild->get_item(0, &pNodeChild);
		m_pKXML->GetElementText(pNodeChild, str);
		pMesh->m_bboxMin = _StrToVector3(str);

		return 1;
	}
	catch (...){
		return 0;
	}
}

int KParser::_ParseObjectTM(KParsedMesh* pMesh, IXMLDOMNode* pNode){
	int					i;
	char				str[128];
	long				nCount = 0;
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	try{
		pListChild = m_pKXML->FindElement(pNode, "LocalTM/Value");
		pListChild->get_length(&nCount);

		for (i = 0; i < nCount; i++){
			pListChild->get_item(i, &pNodeChild);
			m_pKXML->GetElementText(pNodeChild, str);
			//pMesh->m_tmLocal.row[i] = _StrToVector4(str);
			pMesh->m_tmLocal.SetRow(i, _StrToVector4(str));
		}

		pListChild = m_pKXML->FindElement(pNode, "WorldTM/Value");
		pListChild->get_length(&nCount);
		for (i = 0; i < nCount; i++){
			pListChild->get_item(i, &pNodeChild);
			m_pKXML->GetElementText(pNodeChild, str);
			//pMesh->m_tmWorld.row[i] = _StrToVector4(str);
			pMesh->m_tmWorld.SetRow(i, _StrToVector4(str));
		}

		return 1;
	}
	catch (...){
		return 0;
	}
}

int KParser::_ParseObjectVertex(KParsedMesh* pMesh, IXMLDOMNode* pNode){
	int					i;
	char				str[128];
	long				nCount = 0;
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	try{
		pListChild = m_pKXML->FindElement(pNode, "Vertex/Value");
		pListChild->get_length(&nCount);
		pMesh->m_vertex.resize(nCount);
		for (i = 0; i < nCount; i++){
			pListChild->get_item(i, &pNodeChild);
			m_pKXML->GetElementText(pNodeChild, str);
			pMesh->m_vertex[i] = _StrToVector3(str);
		}
		return 1;
	}
	catch (...){
		return 0;
	}
}

int KParser::_ParseObjectVertexNormal(KParsedMesh* pMesh, IXMLDOMNode* pNode){
	int					i;
	char				str[128];
	long				nCount = 0;
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNode*		pNodeChild = NULL;

	try{
		pListChild = m_pKXML->FindElement(pNode, "VertexNormal/Value");
		pListChild->get_length(&nCount);
		pMesh->m_normal.resize(nCount);
		for (i = 0; i < nCount; i++){
			pListChild->get_item(i, &pNodeChild);
			m_pKXML->GetElementText(pNodeChild, str);
			pMesh->m_normal[i] = _StrToVector3(str);
		}
		return 1;
	}
	catch (...){
		return 0;
	}
}

int KParser::_ParseObjectTVertex(KParsedMesh* pMesh, IXMLDOMNode* pNode){
	int						i;
	char					str[128];
	long					nCount = 0;
	IXMLDOMNodeList*		pListChild = NULL;
	IXMLDOMNode*			pNodeChild = NULL;

	try{
		pListChild = m_pKXML->FindElement(pNode, "TexVertex/Value");
		pListChild->get_length(&nCount);
		pMesh->m_tvertex.resize(nCount);
		for (i = 0; i < nCount; i++){
			pListChild->get_item(i, &pNodeChild);
			m_pKXML->GetElementText(pNodeChild, str);
			pMesh->m_tvertex[i] = _StrToVector2(str);
		}
		return 1;
	}
	catch (...){
		return 0;
	}
}

int KParser::_ParseObjectTriIndex(KParsedMesh* pMesh, IXMLDOMNode* pNode){
	int						i;
	char					str[128];
	long					nCount = 0;
	IXMLDOMNodeList*		pListChild = NULL;
	IXMLDOMNode*			pNodeChild = NULL;

	try{
		/// Get Material count
		pListChild = m_pKXML->FindElement(pNode, "TriIndex");
		pListChild->get_item(0, &pNodeChild);
		if (pNodeChild == NULL){
			pMesh->m_nMaterialCount = 0;
			return 1;
		}
		m_pKXML->GetAttributeText(pNodeChild, "MaterialCount", str);
		pMesh->m_nMaterialCount = atoi(str);

		pListChild = m_pKXML->FindElement(pNode, "TriIndex/Value");
		pListChild->get_length(&nCount);
		pMesh->m_triIndex.resize(nCount);

		for (i = 0; i < nCount; i++){
			pListChild->get_item(i, &pNodeChild);
			m_pKXML->GetAttributeText(pNodeChild, "MaterialID", str);
			pMesh->m_triIndex[i].ID = atoi(str);
			m_pKXML->GetElementText(pNodeChild, str);
			pMesh->m_triIndex[i].index = _StrToIndex3i(str);
		}
		return 1;
	}
	catch (...){
		return 0;
	}
}

int KParser::_ParseObjectTexIndex(KParsedMesh* pMesh, IXMLDOMNode* pNode){
	int						i;
	char					str[128];
	long					nCount = 0;
	IXMLDOMNodeList*		pListChild = NULL;
	IXMLDOMNode*			pNodeChild = NULL;

	try{
		pListChild = m_pKXML->FindElement(pNode, "TexIndex/Value");
		pListChild->get_length(&nCount);
		pMesh->m_texIndex.resize(nCount);
		for (i = 0; i < nCount; i++){
			pListChild->get_item(i, &pNodeChild);
			m_pKXML->GetElementText(pNodeChild, str);
			pMesh->m_texIndex[i] = _StrToIndex3i(str);
		}
		return 1;
	}
	catch (...){
		return 0;
	}
}

int KParser::_ParseObjectVertWeight(KParsedMesh* pMesh, IXMLDOMNode* pNode){
	int					i, j;
	char				str[128];
	long				nCount = 0;
	long				nCount2 = 0;
	IXMLDOMNodeList*	pListChild = NULL;
	IXMLDOMNodeList*	pListChild2 = NULL;
	IXMLDOMNode*		pNodeChild = NULL;
	IXMLDOMNode*		pNodeChild2 = NULL;

	try{
		pListChild = m_pKXML->FindElement(pNode, "VertexWeight/Vertex");
		pListChild->get_length(&nCount);
		if (0 == nCount) { pMesh->m_isSkinned = false; return 1; }
		pMesh->m_isSkinned = true;

		pMesh->m_vertWeight.resize(nCount);
		for (i = 0; i < nCount; i++){
			pListChild->get_item(i, &pNodeChild);
			pListChild2 = m_pKXML->FindElement(pNodeChild, "Value");
			pListChild2->get_length(&nCount2);
			pMesh->m_vertWeight[i].ID.resize(nCount2);
			pMesh->m_vertWeight[i].fWeight.resize(nCount2);
			for (j = 0; j < nCount2; j++){
				pListChild2->get_item(j, &pNodeChild2);
				m_pKXML->GetAttributeText(pNodeChild2, "BoneID", str);
				pMesh->m_vertWeight[i].ID[j] = atoi(str);
				//				assert(g_pLog->Log("vertex[%d] Bone ID=%d", i, pMesh->m_vertweight[i].ID[j]));

				pListChild2->get_item(j, &pNodeChild2);
				m_pKXML->GetElementText(pNodeChild2, str);
				pMesh->m_vertWeight[i].fWeight[j] = (float)atof(str);
				//				assert(g_pLog->Log("vertex[%d] Bone Weight=%f". i, pMesh->m_vertweight[i].fWeight[j]));
			}
		}
		return 1;
	}
	catch (...){
		return 0;
	}
}

int KParser::_ParseObjectKey(KParsedMesh* pMesh, IXMLDOMNode* pNode){
	int						i;
	char					str[128];
	long					nCount = 0;
	IXMLDOMNodeList*		pListChild = NULL;
	IXMLDOMNode*			pNodeChild = NULL;

	try{
		pListChild = m_pKXML->FindElement(pNode, "Key/Position/Value");
		pListChild->get_length(&nCount);
		pMesh->m_track.pos.resize(nCount);
		for (i = 0; i < nCount; i++){
			pListChild->get_item(i, &pNodeChild);
			m_pKXML->GetAttributeText(pNodeChild, "Frame", str);
			pMesh->m_track.pos[i].frame = (float)atof(str);
			m_pKXML->GetElementText(pNodeChild, str);
			//			assert(g_pLog->Log("[%d]th [%f]frame key=%s", i, pMesh->m_track.pos[i].frame, str));
			pMesh->m_track.pos[i].value = _StrToVector3(str);
		}

		pListChild = m_pKXML->FindElement(pNode, "Key/Quaternion/Value");
		pListChild->get_length(&nCount);
		pMesh->m_track.rot.resize(nCount);
		for (i = 0; i < nCount; i++){
			pListChild->get_item(i, &pNodeChild);
			m_pKXML->GetAttributeText(pNodeChild, "Frame", str);
			pMesh->m_track.rot[i].frame = (float)atof(str);
			m_pKXML->GetElementText(pNodeChild, str);
			//			assert(g_pLog->Log("[%d]th [%f]frame key=%s", i, pMesh->m_track.rot[i].frame, str));
			pMesh->m_track.rot[i].value = _StrToVector4(str);
		}

		pListChild = m_pKXML->FindElement(pNode, "Key/Scale/Value");
		pListChild->get_length(&nCount);
		pMesh->m_track.scl.resize(nCount);
		for (i = 0; i < nCount; i++){
			pListChild->get_item(i, &pNodeChild);
			m_pKXML->GetAttributeText(pNodeChild, "Frame", str);
			pMesh->m_track.scl[i].frame = (float)atof(str);
			m_pKXML->GetElementText(pNodeChild, str);
			//			assert(g_pLog->Log("[%d]th [%f]frame key=%s", i, pMesh->m_track.scl[i].frame, str));
			pMesh->m_track.scl[i].value = _StrToVector3(str);
		}
		return 1;
	}
	catch (...){
		return 0;
	}
}

Index3i KParser::_StrToIndex3i(char str[]){
	Index3i		val;
	char*		sep = " [],\n";
	char*		context;

	//val.i[0] = atoi(strtok(str, sep));
	val.i[0] = atoi(strtok_s(str, sep, &context));
	val.i[1] = atoi(strtok_s(context, sep, &context));
	val.i[2] = atoi(strtok_s(context, sep, &context));

	return val;
}

Color3 KParser::_StrToColor3(char str[]){
	Color3		val;
	char*		sep = " [],\n";
	char*		context;

	strtok_s(str, sep, &context);		// skip 'Color' string
	val.r = (float)atof(strtok_s(context, sep, &context)) / 255.0f;
	val.g = (float)atof(strtok_s(context, sep, &context)) / 255.0f;
	val.b = (float)atof(strtok_s(context, sep, &context)) / 255.0f;

	return val;
}

Vector2 KParser::_StrToVector2(char str[]){
	Vector2		val;
	char*			sep = " [],\n";
	char*			context;

	val.x = (float)atof(strtok_s(str, sep, &context));
	val.y = (float)atof(strtok_s(context, sep, &context));

	return val;
}

Vector3 KParser::_StrToVector3(char str[]){
	Vector3		val;
	char*			sep = " [],\n";
	char*			context;

	val.x = (float)atof(strtok_s(str, sep, &context));
	val.y = (float)atof(strtok_s(context, sep, &context));
	val.z = (float)atof(strtok_s(context, sep, &context));

	return val;
}

Vector4 KParser::_StrToVector4(char str[]){
	Vector4		val;
	char*			sep = " [], \n";
	char*			context;

	val.x = (float)atof(strtok_s(str, sep, &context));
	val.y = (float)atof(strtok_s(context, sep, &context));
	val.z = (float)atof(strtok_s(context, sep, &context));
	val.w = (float)atof(strtok_s(context, sep, &context));

	return val;
}