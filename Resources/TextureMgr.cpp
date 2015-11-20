#include "TextureMgr.h"

TextureMgr::TextureMgr(LPDIRECT3DDEVICE9 pDev) : m_pDev(pDev){
	m_Data.clear();
	m_TextureBuff.clear();
}
TextureMgr::~TextureMgr(){
	ShutDown();
}
void TextureMgr::Regist(TextureID id, std::string filename){
	m_Data.emplace(id, filename);
}
void TextureMgr::Load(){
	for (auto i : m_Data){
		if (m_TextureBuff.find(i.first) != m_TextureBuff.end()){
			//return;
			continue;
		}
		LPDIRECT3DTEXTURE9 tex;
		D3DXCreateTextureFromFile(m_pDev, i.second.c_str(), &tex);
		m_TextureBuff.emplace(i.first, tex);
	}
}
void TextureMgr::ShutDown(){
	for (auto i : m_TextureBuff){
		REL(i.second);
	}
	m_TextureBuff.clear();
	m_Data.clear();
}
LPDIRECT3DTEXTURE9* TextureMgr::GetTexture(TextureID id){
	return &m_TextureBuff[id];
}