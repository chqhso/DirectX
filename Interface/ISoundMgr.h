#ifndef I_SOUND_MGR_H
#define I_SOUND_MGR_H

#include "../Define.h"

enum class SoundID;
class ISound;

class ISoundMgr{
public:
	ISoundMgr(){}
	virtual ~ISoundMgr(){}
	virtual void Regist(SoundID id, std::string filename) = 0;
	virtual void Load() = 0;
	virtual void ShutDown() = 0;
	virtual ISound* GetSound(SoundID id) = 0;
};

#endif