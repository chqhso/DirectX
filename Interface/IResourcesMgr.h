#ifndef I_RESOURCES_MGR_H
#define I_RESOURCES_MGR_H

#include "../Define.h"

enum class TextureID;
enum class XMLID;
enum class PS_ID;
enum class VS_ID;
enum class SoundID;

class ISoundMgr;
class IXMLMgr;
class IShaderMgr;

class IResourcesMgr{
public:
	IResourcesMgr(){}
	virtual ~IResourcesMgr(){}
	virtual void Regist(TextureID id, std::string filename) = 0;
	virtual void Regist(XMLID id, std::string filename) = 0;
	virtual void Regist(PS_ID id, std::string filename) = 0;
	virtual void Regist(VS_ID id, std::string filename) = 0;
	virtual void Regist(SoundID id, std::string filename) = 0;
	virtual void Load() = 0;
	virtual void ShutDown() = 0;
	virtual ISoundMgr& GetSoundMgr() = 0;
	virtual IXMLMgr& GetXMLMgr() = 0;
	virtual IShaderMgr& GetShaderMgr() = 0;
};

#endif