#ifndef VS_MGR_H
#define VS_MGR_H

#include "../DirectDefine.h"
#include "../Define.h"

struct VSTable{
	std::string							name;
	LPDIRECT3DVERTEXDECLARATION9		pDecl;
	LPDIRECT3DVERTEXSHADER9				pShader;
	LPD3DXCONSTANTTABLE					pConstantTable;
};

class VSMgr{
	LPDIRECT3DDEVICE9			m_pDev;
	VSTable*					m_pVSTable;
public:
	VSMgr(LPDIRECT3DDEVICE9 pDev) : m_pDev(pDev){}
	~VSMgr();

	bool Load(std::string filename);
	VSTable* GetVSTable(){ return m_pVSTable; }

	bool SetMatrix(std::string regName, DMatrix* m);
	bool SetVector4(std::string regName, DVector4* v);
	bool SetVector3(std::string regName, DVector3* v);
	bool SetVector2(std::string regName, DVector2* v);
	bool SetFloat(std::string regName, float f);
	bool SetTexture(std::string regName, LPDIRECT3DTEXTURE9 pTex);
	bool SetMatrix(std::string regName, float* f);
	bool SetVector4(std::string regName, float* f);
	bool SetVector3(std::string regName, float* f);
	bool SetVector2(std::string regName, float* f);
};

#endif