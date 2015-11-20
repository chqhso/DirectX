#ifndef I_SOUND_H
#define I_SOUND_H

#include <string>

class ISound{
public:
	ISound(){}
	virtual ~ISound(){}
	virtual void LoadWave(std::string filename) = 0;
	virtual void SetVolume(long lVolume) = 0;
	virtual void Play(bool bLoop) = 0;
	virtual void Stop() = 0;
	virtual void SetPan(long lPan) = 0;
};

#endif