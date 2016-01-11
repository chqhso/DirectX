#include "FXMgr.h"

FXMgr::~FXMgr(){
	REL(m_pFXTable->pDecl);
	REL(m_pFXTable->pShader);
	DEL(m_pFXTable);
}
// TODO : »èÁ¦??
bool FXMgr::Load(std::string filename){
	D3DVERTEXELEMENT9		decl[MAX_FVF_DECL_SIZE];

	m_pFXTable = new FXTable();
	m_pFXTable->name = filename;

	D3DXDeclaratorFromFVF(CustomVertex::FVF, decl);

	m_pDev->CreateVertexDeclaration(decl, &m_pFXTable->pDecl);

	if (FAILED(D3DXCreateEffectFromFile(m_pDev, filename.c_str(), NULL, NULL, 0, NULL, &m_pFXTable->pShader, NULL)))
		return false;
	return true;
}