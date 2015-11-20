#ifndef SOUND_MGR_H
#define SOUND_MGR_H

#include "../Interface/ISoundMgr.h"
#include "../DirectDefine.h"
#include <dsound.h>

class SoundMgr : public ISoundMgr{
public:
	SoundMgr(HWND hWnd);
	virtual ~SoundMgr();
	virtual void Regist(SoundID id, std::string filename) override;
	virtual void Load() override;
	virtual void ShutDown() override;
	virtual ISound* GetSound(SoundID id) override;
private:
	bool CreateDirectSound(HWND hwnd);
	void DeleteDirectSound();
private:
	LPDIRECTSOUND8 m_pDirectSound;
	std::map<SoundID, std::string> m_Data;
	std::map<SoundID, ISound*> m_SoundBuffer;
};

#endif