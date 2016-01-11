#ifndef D_SOUND_H
#define D_SOUND_H

#include <dsound.h>
#include "../../DirectDefine.h"
#include "../../Interface/ISound.h"

#define DSBCAPS_CTRLDEFAULT (DSBCAPS_CTRLFREQUENCY|DSBCAPS_CTRLPAN|DSBCAPS_CTRLVOLUME)
#define DSVOLUME_TO_DB(volume) ((unsigned long)(-30*(100 - volume)))

class DSound : public ISound{
public:
	DSound(LPDIRECTSOUND8 pdirectSound);
	virtual ~DSound();
	virtual void LoadWave(std::string filename) override;
	virtual void SetVolume(long lVolume) override;
	virtual void Play(bool bLoop) override;
	virtual void Stop() override;
	virtual void SetPan(long lPan) override;
private:
	bool	LoadWaveBuffer(std::string filename);
	bool	SetWaveVolume(long lVolume);
	bool	SetWavePan(long lPan);

	void	Clear();
private:
	LPDIRECTSOUND8 m_pdirectSound;
	LPDIRECTSOUNDBUFFER	m_soundBuffer;
};

#endif