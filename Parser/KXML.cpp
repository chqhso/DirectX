#include "KXML.h"
#include "../Define.h"
#include <stdio.h>

KXML::KXML(){
	m_pXMLDoc = NULL;
	CoInitialize(NULL);
	CoCreateInstance(CLSID_DOMDocument, NULL, CLSCTX_ALL, IID_IXMLDOMDocument, (void**)&m_pXMLDoc);
}
KXML::KXML(LPCTSTR url){}
KXML::~KXML(){
	CoUninitialize();
}
int KXML::Open(LPCTSTR url){
	HRESULT hr;
	BOOL bRet = TRUE;

	try{
		FILE* fp;
		fopen_s(&fp, url, "rt");
		if (!fp) return FALSE;
		fclose(fp);

		short sResult = FALSE;

		m_pXMLDoc->put_async(FALSE);

		_bstr_t varString = (LPCSTR)url;
		VARIANT path;
		path.vt = VT_BSTR;
		path.bstrVal = varString;

		hr = m_pXMLDoc->load(path, &sResult);
		if (FAILED(hr)) return FALSE;
	}
	catch (...){
		m_pXMLDoc->Release();
		m_pXMLDoc = NULL;
		bRet = FALSE;
	}

	return bRet;
}
int KXML::Close(){
	m_pXMLDoc->Release();
	return 1;
}
IXMLDOMNodeList* KXML::FindElement(LPCTSTR strElement){
	IXMLDOMNodeList* pNodeList = NULL;

	if (m_pXMLDoc == NULL){
		return pNodeList;
	}
	try{
		_bstr_t bstrPath = strElement;
		m_pXMLDoc->selectNodes(bstrPath, &pNodeList);
	}
	catch (...){

	}
	return pNodeList;
}
IXMLDOMNodeList* KXML::FindElement(IXMLDOMNode* pNode, LPCTSTR strElement){
	IXMLDOMNodeList* pNodeList = NULL;

	if (pNode == NULL){
		return pNodeList;
	}

	try{
		_bstr_t bstrPath = strElement;
		pNode->selectNodes(bstrPath, &pNodeList);
	}
	catch (...){

	}
	return pNodeList;
}
int KXML::GetElementText(IXMLDOMNode* pNode, LPSTR strRet){
	BSTR		bstr = NULL;

	pNode->get_text(&bstr);
	//strcpy_s(strRet, sizeof(bstr), (const char*)_bstr_t(bstr, FALSE));
	strcpy_s(strRet, 128, (const char*)_bstr_t(bstr, FALSE));
//	strcpy_s(strRet, sizeof(bstr), (const char*)_bstr_t(bstr, FALSE));
//	wcstombs(strRet, bstr, 128);
//	::SysFreeString(bstr);

	return 1;
}
int KXML::GetAttributeText(IXMLDOMNode* pNode, LPSTR strAttrName, LPSTR strRet){
	wchar_t					wstrAttr[128];
	IXMLDOMNode*			pAttrNode = NULL;
	IXMLDOMNamedNodeMap*	pMap = NULL;
	VARIANT					varValue;

	try{
		//int n = mbstowcs(wstrAttr, strAttrName, 128);
		//int n = mbstowcs_s(wstrAttr, strAttrName, 128);
		// TODO : error test
		size_t convertedSize;
		int n = mbstowcs_s(&convertedSize, wstrAttr, strlen(strAttrName) + 1, strAttrName, 128);
		pNode->get_attributes(&pMap);
		pMap->getNamedItem(wstrAttr, &pAttrNode);
		pAttrNode->get_nodeValue(&varValue);
		strcpy_s(strRet, 128, (const char*)_bstr_t(varValue.bstrVal, FALSE));
//		wcstombs(strRet, varValue.bstrVal, 128)

		REL(pAttrNode);
		REL(pMap);

		return TRUE;
	}
	catch (...){
		REL(pAttrNode);
		REL(pMap);
		return FALSE;
	}
}