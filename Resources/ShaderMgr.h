#ifndef SHADER_MGR_H
#define SHADER_MGR_H

#include "../Interface/IShaderMgr.h"

//#include "FXMgr.h"

//enum class FX_ID;

class ShaderMgr : public IShaderMgr{
public:
	ShaderMgr(LPDIRECT3DDEVICE9 pDev);
	virtual ~ShaderMgr();
//	void Regist(FX_ID id, std::string filename);
	virtual void Regist(PS_ID id, std::string filename) override;
	virtual void Regist(VS_ID id, std::string filename) override;
	virtual void Load() override;
	virtual void ShutDown() override;
	virtual VSMgr* GetVSMgr(VS_ID id) override;
	virtual PSMgr* GetPSMgr(PS_ID id) override;
//	FXMgr* GetFXMgr(FX_ID id);
private:
	LPDIRECT3DDEVICE9 m_pDev;
	std::map<PS_ID, std::string> m_PSData;
	std::map<VS_ID, std::string> m_VSData;
//	std::map<FX_ID, std::string> m_FXData;
	std::map<VS_ID, VSMgr*> m_VSBuff;
	std::map<PS_ID, PSMgr*> m_PSBuff;
//	std::map<FX_ID, FXMgr*> m_FXBuff;
};

#endif