#ifndef FX_MGR_H
#define FX_MGR_H

#include "../DirectDefine.h"
#include "../Define.h"

struct FXTable{
	std::string						name;
	LPDIRECT3DVERTEXDECLARATION9	pDecl;
	LPD3DXEFFECT					pShader;
};

class FXMgr{
	LPDIRECT3DDEVICE9	m_pDev;
	FXTable*			m_pFXTable;
public:
	FXMgr(LPDIRECT3DDEVICE9 pDev) : m_pDev(pDev){}
	~FXMgr();

	bool Load(std::string filename);
	FXTable* GetFXTable(){ return m_pFXTable; }
};

#endif