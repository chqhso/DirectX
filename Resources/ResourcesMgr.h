#ifndef RESOURCES_MGR_H
#define RESOURCES_MGR_H

#include "../Interface/IResourcesMgr.h"
#include "TextureMgr.h"
#include "../Interface/ISoundMgr.h"
#include "../Interface/IXMLMgr.h"
#include "../Interface/IShaderMgr.h"

class ResourcesMgr : public IResourcesMgr{
public:
	ResourcesMgr(LPDIRECT3DDEVICE9 pDev, HWND hWnd);
	~ResourcesMgr();
	virtual void Regist(TextureID id, std::string filename) override;
	virtual void Regist(XMLID id, std::string filename) override;
	virtual void Regist(PS_ID id, std::string filename) override;
	virtual void Regist(VS_ID id, std::string filename) override;
	virtual void Regist(SoundID id, std::string filename) override;
	virtual void Load() override;
	virtual void ShutDown() override;
	// TODO : �������̽� ����� �������̽��� ����
	TextureMgr& GetTextureMgr();
	//ShaderMgr& GetShaderMgr();
	//XMLMgr& GetXMLMgr();
	virtual ISoundMgr& GetSoundMgr() override;
	virtual IXMLMgr& GetXMLMgr() override;
	virtual IShaderMgr& GetShaderMgr() override;
private:
	LPDIRECT3DDEVICE9 m_pDev;
	TextureMgr m_TextureMgr;
	//ShaderMgr m_ShaderMgr;
	//XMLMgr m_XMLMgr;
	ISoundMgr* m_pSoundMgr;
	IXMLMgr* m_pXMLMgr;
	IShaderMgr* m_pShaderMgr;
};

#endif