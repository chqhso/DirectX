#include "DJoystick.h"
#include "../../Define.h"

DJoystick::DJoystick(LPDIRECTINPUT8 directInput, HWND hwnd) : m_pDI(directInput), m_pHwnd(hwnd){
	CreateDirectJoystickDevice(directInput, hwnd);
}
DJoystick::~DJoystick(){
	DeleteInputDevice();
}
bool DJoystick::Update(){
	return PollingJoystick();
}
// TODO : 파라메터 필요없음
bool DJoystick::CreateDirectJoystickDevice(LPDIRECTINPUT8 directInput, HWND hwnd){
	//if (FAILED(directInput->EnumDevices(DI8DEVCLASS_GAMECTRL, enumCallback, NULL, DIEDFL_ATTACHEDONLY))){
	if (FAILED(directInput->EnumDevices(DI8DEVCLASS_GAMECTRL, enumCallback, this, DIEDFL_ATTACHEDONLY))){
		return false;
	}
	return true;
}
void DJoystick::DeleteInputDevice(){
	for (auto i : m_pDeviceBuffer){
		i->device->Unacquire();
		REL(i->device);
		DEL(i);
	}
	m_pDeviceBuffer.clear();
}

//KLog::Instance()->Log("%ld", m_joyCur.lX); 왼쪽 좌우
//KLog::Instance()->Log("%ld", m_joyCur.lY); 왼쪽 상하
//KLog::Instance()->Log("%ld", m_joyCur.lZ); +왼쪽 트리거 -오른쪽트리거
//KLog::Instance()->Log("%ld", m_joyCur.lRx); 오른쪽 좌우
//KLog::Instance()->Log("%ld", m_joyCur.lRy); 오른쪽 상하
//KLog::Instance()->Log("%ld", m_joyCur.rgdwPOV[0]); 왼쪽 십자키

bool DJoystick::PollingJoystick(){

	for (auto i : m_pDeviceBuffer){
		HRESULT hr = i->device->Poll();
		if (FAILED(hr)){
			if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED)){
				i->device->Acquire();
			}
			else if (hr == DIERR_OTHERAPPHASPRIO){
				return true;
			}
			else{
				return false;
			}
		}
		memcpy(&i->joystickOldBuffer, &i->joystickNewBuffer, sizeof(DIJOYSTATE2));
		i->device->GetDeviceState(sizeof(DIJOYSTATE2), &i->joystickCurrentBuffer);
		memcpy(&i->joystickNewBuffer, &i->joystickCurrentBuffer, sizeof(DIJOYSTATE2));

		return true;
	}

	//HRESULT result = m_device->Poll();
	//if (FAILED(result)){
	//	result = m_device->Acquire();
	//	if (result == DIERR_INPUTLOST){
	//		m_device->Acquire();
	//	}
	//	else if (result == DIERR_OTHERAPPHASPRIO){
	//		return true;
	//	}
	//	else{
	//		return false;
	//	}
	//	//while (result == DIERR_INPUTLOST)
	//	//{
	//	//	result = m_device->Acquire();
	//	//}
	//	//if ((result == DIERR_INVALIDPARAM) || (result == DIERR_NOTINITIALIZED)){
	//	//	return false;
	//	//}
	//	//if (result == DIERR_OTHERAPPHASPRIO)
	//	//{
	//	//	return true;
	//	//}
	//}
	//memcpy(&m_joyOld, &m_joyNew, sizeof(DIJOYSTATE2));
	//m_device->GetDeviceState(sizeof(DIJOYSTATE2), &m_joyCur);
	//memcpy(&m_joyNew, &m_joyCur, sizeof(DIJOYSTATE2));
	//
	//
	//return true;
}
void DJoystick::AddJoystick(JoystickBuffer* joystick){
	m_pDeviceBuffer.push_back(joystick);
}

bool DJoystick::GetButtonStateDown(unsigned int index, unsigned char keycode){
	return GetButtonStateNewBufferDown(index, keycode);
}
bool DJoystick::GetButtonStateUp(unsigned int index, unsigned char keycode){
	return GetButtonStateNewBufferUp(index, keycode);
}
bool DJoystick::GetButtonStateTrigger(unsigned int index, unsigned char keycode){
	return GetButtonStateNewBufferDown(index, keycode) && GetButtonStateOldBufferUp(index, keycode);
}
bool DJoystick::GetButtonStateDetach(unsigned int index, unsigned char keycode){
	return GetButtonStateNewBufferUp(index, keycode) && GetButtonStateOldBufferDown(index, keycode);
}
//Vector2 DJoystick::GetAxis(){
//	return GetJoystickAxis();
//}

bool DJoystick::GetButtonStateNewBufferDown(unsigned int index, unsigned char keycode){
	//if (m_joyNew.rgbButtons[keycode] & 0x80)
	//	return true;
	//return false;
	//return m_joyNew.rgbButtons[keycode] & 0x80;
	return m_pDeviceBuffer[index]->joystickNewBuffer.rgbButtons[keycode] & 0x80;
}
bool DJoystick::GetButtonStateNewBufferUp(unsigned int index, unsigned char keycode){
	return !GetButtonStateNewBufferDown(index, keycode);
}
bool DJoystick::GetButtonStateOldBufferDown(unsigned int index, unsigned char keycode){
	//if (m_joyOld.rgbButtons[keycode] & 0x80)
	//	return true;
	//return false;
	//return m_joyOld.rgbButtons[keycode] & 0x80;
	return m_pDeviceBuffer[index]->joystickOldBuffer.rgbButtons[keycode] & 0x80;
}
bool DJoystick::GetButtonStateOldBufferUp(unsigned int index, unsigned char keycode){
	return !GetButtonStateOldBufferDown(index, keycode);
}

Vector2 DJoystick::GetLeftAxis(unsigned int index){
	return Vector2(m_pDeviceBuffer[index]->joystickNewBuffer.lX, m_pDeviceBuffer[index]->joystickNewBuffer.lY);
}
Vector2 DJoystick::GetRightAxis(unsigned int index){
	return Vector2(m_pDeviceBuffer[index]->joystickNewBuffer.lRx, m_pDeviceBuffer[index]->joystickNewBuffer.lRy);
}

float DJoystick::GetLeftTrigger(unsigned int index){
	float trigger = m_pDeviceBuffer[index]->joystickNewBuffer.lZ;
	return max(trigger, 0.0f);
}
float DJoystick::GetRightTrigger(unsigned int index){
	float trigger = m_pDeviceBuffer[index]->joystickNewBuffer.lZ;
	return abs(min(trigger, 0.0f));
}

float DJoystick::GetCrossButton(unsigned int index){
	return m_pDeviceBuffer[index]->joystickNewBuffer.rgdwPOV[0];
}

BOOL CALLBACK DJoystick::enumCallback(const DIDEVICEINSTANCE* instance, LPVOID context){
	DJoystick* dJoystick = (DJoystick*)context;
	JoystickBuffer* joyBuff = new JoystickBuffer;

	if (FAILED(dJoystick->m_pDI->CreateDevice(instance->guidInstance, &joyBuff->device, NULL))){
		return DIENUM_CONTINUE;
	}
	if (FAILED(joyBuff->device->SetDataFormat(&c_dfDIJoystick2))){
		return DIENUM_CONTINUE;
	}
	if (FAILED(joyBuff->device->SetCooperativeLevel(dJoystick->m_pHwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE))){
		return DIENUM_CONTINUE;
	}

	DIDEVCAPS capabilities;
	capabilities.dwSize = sizeof(DIDEVCAPS);
	if (FAILED(joyBuff->device->GetCapabilities(&capabilities))){
		return DIENUM_CONTINUE;
	}
	joyBuff->capabilities = capabilities;

	if (FAILED(joyBuff->device->EnumObjects(enumAxesCallback, joyBuff, DIDFT_AXIS))){
		return DIENUM_CONTINUE;
	}

	dJoystick->AddJoystick(joyBuff);

	return DIENUM_CONTINUE;
}
BOOL CALLBACK DJoystick::enumAxesCallback(const DIDEVICEOBJECTINSTANCE* instance, LPVOID context){
	JoystickBuffer* joyBuff = (JoystickBuffer*)context;

	DIPROPRANGE propRange;
	propRange.diph.dwSize = sizeof(DIPROPRANGE);
	propRange.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	propRange.diph.dwHow = DIPH_BYID;
	propRange.diph.dwObj = instance->dwType;
	//propRange.diph.dwHow = DIPH_BYOFFSET;
	propRange.lMin = -1000;
	propRange.lMax = 1000;

	joyBuff->device->SetProperty(DIPROP_RANGE, &propRange.diph);

	//propRange.diph.dwObj = DIJOFS_X;
	//dJoystick->m_device->SetProperty(DIPROP_RANGE, &propRange.diph);
	//propRange.diph.dwObj = DIJOFS_Y;
	//dJoystick->m_device->SetProperty(DIPROP_RANGE, &propRange.diph);
	//propRange.diph.dwObj = DIJOFS_Z;
	//dJoystick->m_device->SetProperty(DIPROP_RANGE, &propRange.diph);
	//propRange.diph.dwObj = DIJOFS_RX;
	//dJoystick->m_device->SetProperty(DIPROP_RANGE, &propRange.diph);
	//propRange.diph.dwObj = DIJOFS_RY;
	//dJoystick->m_device->SetProperty(DIPROP_RANGE, &propRange.diph);
	//propRange.diph.dwObj = DIJOFS_RZ;
	//dJoystick->m_device->SetProperty(DIPROP_RANGE, &propRange.diph);

	//propRange.diph.dwObj = DIJOFS_X;
	//if (FAILED(dJoystick->m_device->SetProperty(DIPROP_RANGE, &propRange.diph))){
	//	return DIENUM_STOP;
	//}
	//propRange.diph.dwObj = DIJOFS_Y;
	//if (FAILED(dJoystick->m_device->SetProperty(DIPROP_RANGE, &propRange.diph))){
	//	return DIENUM_STOP;
	//}
	//propRange.diph.dwObj = DIJOFS_Z;
	//if (FAILED(dJoystick->m_device->SetProperty(DIPROP_RANGE, &propRange.diph))){
	//	return DIENUM_STOP;
	//}
	//propRange.diph.dwObj = DIJOFS_RX;
	//if (FAILED(dJoystick->m_device->SetProperty(DIPROP_RANGE, &propRange.diph))){
	//	return DIENUM_STOP;
	//}
	//propRange.diph.dwObj = DIJOFS_RY;
	//if (FAILED(dJoystick->m_device->SetProperty(DIPROP_RANGE, &propRange.diph))){
	//	return DIENUM_STOP;
	//}
	//propRange.diph.dwObj = DIJOFS_RZ;
	//HRESULT hr = dJoystick->m_device->SetProperty(DIPROP_RANGE, &propRange.diph);
	//if (FAILED(hr)){
	////if (FAILED(dJoystick->m_device->SetProperty(DIPROP_RANGE, &propRange.diph))){
	//	return DIENUM_STOP;
	//}

	return DIENUM_CONTINUE;
}