#include "SoundMgr.h"
#include "../Utility/DirectUtility/DSound.h"
#include <cassert>

#pragma comment(lib, "dsound.lib")

SoundMgr::SoundMgr(HWND hWnd){
	m_Data.clear();
	m_SoundBuffer.clear();
	assert(CreateDirectSound(hWnd));
}
SoundMgr::~SoundMgr(){
	ShutDown();
	DeleteDirectSound();
}
void SoundMgr::Regist(SoundID id, std::string filename){
	m_Data.emplace(id, filename);
}
void SoundMgr::Load(){
	for (auto i : m_Data){
		if (m_SoundBuffer.find(i.first) != m_SoundBuffer.end())
			continue;
		ISound* pSound = new DSound(m_pDirectSound);
		pSound->LoadWave(i.second);
		m_SoundBuffer.emplace(i.first, pSound);
	}
}
void SoundMgr::ShutDown(){
	for (auto i : m_SoundBuffer){
		DEL(i.second);
	}
	m_SoundBuffer.clear();
	m_Data.clear();
}
ISound* SoundMgr::GetSound(SoundID id){
	return m_SoundBuffer[id];
}

bool SoundMgr::CreateDirectSound(HWND hwnd){
	if (DirectSoundCreate8(NULL, &m_pDirectSound, NULL) != DS_OK)
		return false;
	if (m_pDirectSound->SetCooperativeLevel(hwnd, DSSCL_NORMAL) != DS_OK)
		return false;
	return true;
}
void SoundMgr::DeleteDirectSound(){
	REL(m_pDirectSound);
}