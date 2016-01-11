#ifndef K_PARSER_H
#define K_PARSER_H

#include "KXML.h"
#include "../Define.h"
#include "KParsedMesh.h"
#include "KParsedData.h"

#define BIGFLOAT			999.0f

/// Parser
class KParser{
	KXML*				m_pKXML;					/// XML파일을 파싱하기 위한 기본 객체
public:
	KParser();
	~KParser();
private:
	Index3i				_StrToIndex3i(char str[]);	/// 문자열을 Index3i로 변형
	Color32				_StrToColor3(char str[]);	/// 문자열을 Color3로 변형
	Vector2				_StrToVector2(char str[]);	/// 문자열을 Vector2로 변형
	Vector3				_StrToVector3(char str[]);	/// 문자열을 Vector3로 변형
	Vector4				_StrToVector4(char str[]);	/// 문자열을 Vector4로 변형

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
		if (!Parse_Split(pData)) return 0;	// 현재는 sub-material을 지원하지 않음
		if (!Parse_Merge(pData)) return 0;

		return 1;
	}
};

#endif