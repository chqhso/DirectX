#include "DKeyboardBuffer.h"
#include <cassert>
#include "../../Define.h"
DKeyboardBuffer::DKeyboardBuffer(LPDIRECTINPUT8 directInput, HWND hwnd){
	ZeroMemory(m_ucOldBuffer, sizeof(m_ucOldBuffer));
	ZeroMemory(m_ucCurrentBuffer, sizeof(m_ucCurrentBuffer));
	ZeroMemory(m_ucNewBuffer, sizeof(m_ucNewBuffer));
	assert(CreateDirectKeyboardDevice(directInput, hwnd));
}

DKeyboardBuffer::~DKeyboardBuffer(){
	DeleteInputDevice();
}
bool DKeyboardBuffer::Update(){
	memcpy(m_ucOldBuffer, m_ucNewBuffer, sizeof(m_ucOldBuffer));

	HRESULT result = m_device->GetDeviceState(sizeof(m_ucCurrentBuffer), (LPVOID)&m_ucCurrentBuffer);

	if (FAILED(result)){
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED)){
			m_device->Acquire();
		}
		else if (result == DIERR_OTHERAPPHASPRIO){
			return true;
		}
		else{
			return false;
		}
	}
	memcpy(m_ucNewBuffer, m_ucCurrentBuffer, sizeof(m_ucNewBuffer));

	return true;
}
bool DKeyboardBuffer::GetKeyStateDown(unsigned char keycode){
	return GetKeyStateNewBufferDown(keycode);
}
bool DKeyboardBuffer::GetKeyStateUp(unsigned char keycode){
	return GetKeyStateNewBufferUp(keycode);
}
bool DKeyboardBuffer::GetKeyStateTrigger(unsigned char keycode){
	return GetKeyStateNewBufferDown(keycode) && GetKeyStateOldBufferUp(keycode);
}
bool DKeyboardBuffer::GetKeyStateDetach(unsigned char keycode){
	return GetKeyStateNewBufferUp(keycode) && GetKeyStateOldBufferDown(keycode);
}
bool DKeyboardBuffer::CreateDirectKeyboardDevice(LPDIRECTINPUT8 directInput, HWND hwnd){
	if (FAILED(directInput->CreateDevice(GUID_SysKeyboard, &m_device, NULL)))
		return false;
	if (FAILED(m_device->SetDataFormat(&c_dfDIKeyboard)))
		return false;
	if (FAILED(m_device->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
		return false;
	HRESULT hr = m_device->Acquire();
	if (FAILED(hr) && hr != DIERR_OTHERAPPHASPRIO)
		return false;
	return true;
}
bool DKeyboardBuffer::GetKeyStateNewBufferDown(unsigned char keycode){
	if (m_ucNewBuffer[keycode] & 0x80)
		return true;
	return false;
}
bool DKeyboardBuffer::GetKeyStateNewBufferUp(unsigned char keycode){
	return !GetKeyStateNewBufferDown(keycode);
}
bool DKeyboardBuffer::GetKeyStateOldBufferDown(unsigned char keycode){
	if (m_ucOldBuffer[keycode] & 0x80)
		return true;
	return false;
}
bool DKeyboardBuffer::GetKeyStateOldBufferUp(unsigned char keycode){
	return !GetKeyStateOldBufferDown(keycode);
}
void DKeyboardBuffer::DeleteInputDevice(){
	if (!m_device)
		return;
	m_device->Unacquire();
	REL(m_device);
}