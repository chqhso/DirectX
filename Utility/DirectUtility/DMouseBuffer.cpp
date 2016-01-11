#include "DMouseBuffer.h"
#include <cassert>

DMouseBuffer::DMouseBuffer(LPDIRECTINPUT8 directInput, HWND hwnd){
	assert(CreateDirectMouseDevice(directInput, hwnd));
}
DMouseBuffer::~DMouseBuffer(){
	DeleteInputDevice();
}
bool DMouseBuffer::Update(){
	m_oldBuffer = m_newBuffer;

	HRESULT result = m_device->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_currentBuffer);
	if (FAILED(result)){
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED)){
			m_device->Acquire();
		}
		else{
			return false;
		}
	}

	m_newBuffer = m_currentBuffer;

	ProcessMouseInput();

	return true;
}
bool DMouseBuffer::GetButtonDown(int button){
	return GetButtonStateNewBufferDown(button);
}
bool DMouseBuffer::GetButtonUp(int button){
	return GetButtonStateNewBufferUp(button);
}
bool DMouseBuffer::GetButtonTrigger(int button){
	return GetButtonStateNewBufferDown(button) && GetButtonStateOldBufferUp(button);
}
bool DMouseBuffer::GetButtonDetach(int button){
	return GetButtonStateNewBufferUp(button) && GetButtonStateOldBufferDown(button);
}

const Vector2& DMouseBuffer::GetPosition(){
	return m_position;
}
Vector2 DMouseBuffer::GetDeltaPos(){
	return Vector2(m_newBuffer.lX, m_newBuffer.lY);
}

bool DMouseBuffer::CreateDirectMouseDevice(LPDIRECTINPUT8 directInput, HWND hwnd){
	if (FAILED(directInput->CreateDevice(GUID_SysMouse, &m_device, NULL)))
		return false;
	if (FAILED(m_device->SetDataFormat(&c_dfDIMouse)))
		return false;
	if (FAILED(m_device->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		return false;
	// TODO : 정확한 원인 진단
	HRESULT hr = m_device->Acquire();
	if (FAILED(hr) && hr != DIERR_OTHERAPPHASPRIO)
		return false;
	//if (FAILED(m_device->Acquire()))
	//	return false;

	return true;
}
bool DMouseBuffer::GetButtonStateNewBufferDown(int button){
	if (m_newBuffer.rgbButtons[button] & 0x80)
		return true;
	return false;
}
bool DMouseBuffer::GetButtonStateNewBufferUp(int button){
	return !GetButtonStateNewBufferDown(button);
}
bool DMouseBuffer::GetButtonStateOldBufferDown(int button){
	if (m_oldBuffer.rgbButtons[button] & 0x80)
		return true;
	return false;
}
bool DMouseBuffer::GetButtonStateOldBufferUp(int button){
	return !GetButtonStateOldBufferDown(button);
}
void DMouseBuffer::DeleteInputDevice(){
	if (!m_device)
		return;
	m_device->Unacquire();
	REL(m_device);
}
void DMouseBuffer::ProcessMouseInput(){
	m_position.x += GetDeltaPos().x * MOUSE_SPEED;
	m_position.y += GetDeltaPos().y * MOUSE_SPEED;

	if (m_position.x < 0){ m_position.x = 0; }
	if (m_position.y < 0){ m_position.y = 0; }

	/// TODO : 마우스최대위치를 화면 가장끝으로하기
	//if (m_position.x > 화면 가로){ m_position.x = 화면 가로; }
}	//if (m_position.y > 화면 세로){ m_position.y = 화면 세로; }