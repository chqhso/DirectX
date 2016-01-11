#ifndef TEXTURE_MGR_H
#define TEXTURE_MGR_H

#include "../Define.h"
#include "../DirectDefine.h"

enum class TextureID;

class TextureMgr{
public:
	TextureMgr(LPDIRECT3DDEVICE9 pDev);
	~TextureMgr();
	void Regist(TextureID id, std::string filename);
	void Load();
	void ShutDown();
	LPDIRECT3DTEXTURE9* GetTexture(TextureID id);
private:
	LPDIRECT3DDEVICE9 m_pDev;
	std::map<TextureID, std::string> m_Data;
	std::map<TextureID, LPDIRECT3DTEXTURE9> m_TextureBuff;
};

#endif