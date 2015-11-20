#include "DSound.h"
#include <cassert>

DSound::DSound(LPDIRECTSOUND8 pdirectSound) : m_pdirectSound(pdirectSound){

}
DSound::~DSound(){
	Clear();
}
void	DSound::LoadWave(std::string filename){
	assert(LoadWaveBuffer(filename));
}
void	DSound::SetVolume(long lVolume){
	assert(SetWaveVolume(lVolume));
}
void	DSound::Play(bool bLoop){
	if (m_soundBuffer == NULL)
		return;
	m_soundBuffer->Play(0, 0, bLoop);
}
void	DSound::Stop(){
	if (m_soundBuffer == NULL)
		return;
	m_soundBuffer->Stop();
	m_soundBuffer->SetCurrentPosition(0L);
}
void	DSound::SetPan(long lPan){
	assert(SetWavePan(lPan));
}

bool	DSound::LoadWaveBuffer(std::string filename){
	HMMIO			hmmio;
	MMCKINFO		ckInRIFF, ckIn;
	PCMWAVEFORMAT	pcmWaveFormat;
	WAVEFORMATEX*	pWaveFormat;

	hmmio = mmioOpen(const_cast<LPSTR>(filename.c_str()), NULL, MMIO_ALLOCBUF | MMIO_READ);
	if (hmmio == NULL)
		return false;

	ckInRIFF.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if ((mmioDescend(hmmio, &ckInRIFF, NULL, MMIO_FINDRIFF)) != 0){
		mmioClose(hmmio, 0);
		return false;
	}

	ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (mmioDescend(hmmio, &ckIn, &ckInRIFF, MMIO_FINDCHUNK) != 0){
		mmioClose(hmmio, 0);
		return false;
	}

	if (mmioRead(hmmio, (HPSTR)&pcmWaveFormat, sizeof(pcmWaveFormat)) != sizeof(pcmWaveFormat)){
		mmioClose(hmmio, 0);
		return false;
	}

	pWaveFormat = new WAVEFORMATEX;

	memcpy(pWaveFormat, &pcmWaveFormat, sizeof(pcmWaveFormat));
	pWaveFormat->cbSize = 0;

	if (mmioAscend(hmmio, &ckIn, 0)){
		mmioClose(hmmio, 0);
		return false;
	}

	ckIn.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (mmioDescend(hmmio, &ckIn, &ckInRIFF, MMIO_FINDCHUNK) != 0){
		mmioClose(hmmio, 0);
		return false;
	}

	BYTE* pData = NULL;
	pData = new BYTE[ckIn.cksize];
	mmioRead(hmmio, (LPSTR)pData, ckIn.cksize);
	mmioClose(hmmio, 0);

	DSBUFFERDESC dsbd;
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = DSBCAPS_CTRLDEFAULT | DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE;
	dsbd.dwBufferBytes = ckIn.cksize;
	dsbd.lpwfxFormat = pWaveFormat;

	if (m_pdirectSound->CreateSoundBuffer(&dsbd, &m_soundBuffer, NULL) != DS_OK)
		return false;

	VOID* pBuff1 = NULL;
	VOID* pBuff2 = NULL;
	DWORD dwLength;
	DWORD dwLength2;

	if (m_soundBuffer->Lock(0, dsbd.dwBufferBytes, &pBuff1, &dwLength, &pBuff2, &dwLength2, 0L) != DS_OK){
		REL(m_soundBuffer);
		return false;
	}

	memcpy(pBuff1, pData, dwLength);
	memcpy(pBuff2, (pData + dwLength), dwLength2);

	m_soundBuffer->Unlock(pBuff1, dwLength, pBuff2, dwLength2);
	pBuff1 = pBuff2 = NULL;

	DELS(pData);
	DEL(pWaveFormat);

	return true;
}
bool	DSound::SetWaveVolume(long lVolume){
	if (m_soundBuffer->SetVolume(DSVOLUME_TO_DB(lVolume)) != DS_OK)
		return false;
	return true;
}
bool	DSound::SetWavePan(long lPan){
	if (m_soundBuffer->SetPan(lPan) != DS_OK)
		return false;
	return true;
}
void	DSound::Clear(){
	REL(m_soundBuffer);
}