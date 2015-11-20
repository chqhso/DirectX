#include "ResourcesMgr.h"
#include "SoundMgr.h"
#include "XMLMgr.h"
#include "ShaderMgr.h"

ResourcesMgr::ResourcesMgr(LPDIRECT3DDEVICE9 pDev, HWND hWnd) : m_pDev(pDev), m_TextureMgr(pDev){
	m_pSoundMgr = new SoundMgr(hWnd);
	m_pXMLMgr = new XMLMgr(pDev);
	m_pShaderMgr = new ShaderMgr(pDev);
}
ResourcesMgr::~ResourcesMgr(){
	ShutDown();
	DEL(m_pSoundMgr);
	DEL(m_pXMLMgr);
	DEL(m_pShaderMgr);
}
void ResourcesMgr::Regist(TextureID id, std::string filename){
	m_TextureMgr.Regist(id, filename);
}
void ResourcesMgr::Regist(XMLID id, std::string filename){
	m_pXMLMgr->Regist(id, filename);
}
void ResourcesMgr::Regist(PS_ID id, std::string filename){
	m_pShaderMgr->Regist(id, filename);
}
void ResourcesMgr::Regist(VS_ID id, std::string filename){
	m_pShaderMgr->Regist(id, filename);
}
void ResourcesMgr::Regist(SoundID id, std::string filename){
	m_pSoundMgr->Regist(id, filename);
}
void ResourcesMgr::Load(){
	m_TextureMgr.Load();
	m_pXMLMgr->Load();
	m_pShaderMgr->Load();
	m_pSoundMgr->Load();
}
void ResourcesMgr::ShutDown(){
	m_TextureMgr.ShutDown();
	m_pShaderMgr->ShutDown();
	m_pXMLMgr->ShutDown();
	m_pSoundMgr->ShutDown();
}
TextureMgr& ResourcesMgr::GetTextureMgr(){
	return m_TextureMgr;
}
IShaderMgr& ResourcesMgr::GetShaderMgr(){
	return *m_pShaderMgr;
}
IXMLMgr& ResourcesMgr::GetXMLMgr(){
	return *m_pXMLMgr;
}
ISoundMgr& ResourcesMgr::GetSoundMgr(){
	return *m_pSoundMgr;
}