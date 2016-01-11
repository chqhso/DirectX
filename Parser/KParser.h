#ifndef K_PARSER_H
#define K_PARSER_H

#include "KXML.h"
#include "../Define.h"
#include "KParsedMesh.h"
#include "KParsedData.h"

#define BIGFLOAT			999.0f

/// Parser
class KParser{
	KXML*				m_pKXML;					/// XML������ �Ľ��ϱ� ���� �⺻ ��ü
public:
	KParser();
	~KParser();
private:
	Index3i				_StrToIndex3i(char str[]);	/// ���ڿ��� Index3i�� ����
	Color32				_StrToColor3(char str[]);	/// ���ڿ��� Color3�� ����
	Vector2				_StrToVector2(char str[]);	/// ���ڿ��� Vector2�� ����
	Vector3				_StrToVector3(char str[]);	/// ���ڿ��� Vector3�� ����
	Vector4				_StrToVector4(char str[]);	/// ���ڿ��� Vector4�� ����

	int					_SplitMeshByFaceMaterial(KParsedData* pData);
	void				_MergeBlendWeight(VertMerged& vm, VertWeight& vw);
	int					_MergeVertex(KParsedData* pData);
	int					_ParseInfo(KParsedData* pData);
	int					_ParseMaterial(KParsedData* pData);
	int					_ParseObject(KParsedData* pData);
	int					_ParseObjectParent(KParsedMesh* pMesh, IXMLDOMNode* pNode);
	int					_ParseObjectBBox(KParsedMesh* pMesh, IXMLDOMNode* pNode);
	int					_ParseObjectTM(KParsedMesh* pMesh, IXMLDOMNode* pNode);
	int					_ParseObjectVertex(KParsedMesh* pMesh, IXMLDOMNode* pNode);
	int					_ParseObjectVertexNormal(KParsedMesh* pMesh, IXMLDOMNode* pNode);
	int					_ParseObjectTVertex(KParsedMesh* pMesh, IXMLDOMNode* pNode);
	int					_ParseObjectTriIndex(KParsedMesh* pMesh, IXMLDOMNode* pNode);
	int					_ParseObjectTexIndex(KParsedMesh* pMesh, IXMLDOMNode* pNode);
	int					_ParseObjectVertWeight(KParsedMesh* pMesh, IXMLDOMNode* pNode);
	int					_ParseObjectKey(KParsedMesh* pMesh, IXMLDOMNode* pNode);

public:
	int					Parse_XML(KParsedData* pData, const char* lpszFilename);
	int					Parse_Split(KParsedData* pData) { return _SplitMeshByFaceMaterial(pData); }
	int					Parse_Merge(KParsedData* pData) { return _MergeVertex(pData); }

	int					Parse(KParsedData* pData, const char* lpszFilename){
		if (!Parse_XML(pData, lpszFilename)) return 0;
		if (!Parse_Split(pData)) return 0;	// ����� sub-material�� �������� ����
		if (!Parse_Merge(pData)) return 0;

		return 1;
	}
};

#endif