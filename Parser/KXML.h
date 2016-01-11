#ifndef KXML_H
#define KXML_H

/** \bried easy XML??
 *
 */

#include <Windows.h>
#include <tchar.h>
#include <MsXml2.h>
#include <comdef.h>
#include "../Define.h"

#pragma comment(lib, "msxml2")

class KXML{
	IXMLDOMDocument*			m_pXMLDoc;
public:
						KXML			();
						KXML			(LPCTSTR url);
						~KXML			();

	int					Open			(LPCTSTR url);
	int					Close			();
	IXMLDOMNodeList*	FindElement		(LPCSTR strElement);
	IXMLDOMNodeList*	FindElement		(IXMLDOMNode* pNode, LPCSTR strElement);
	int					GetElementText	(IXMLDOMNode* pNode, LPSTR strRet);
	int					GetAttributeText(IXMLDOMNode* pNode, LPSTR strAttrName, LPSTR strRet);
};

#endif