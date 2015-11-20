#include "DInput.h"

DInput::DInput(HINSTANCE hInstance, HWND hwnd){
	assert(CreateDirectInput(hInstance, hwnd));

	m_pKeyboardBuffer = new DKeyboardBuffer(m_directInput, hwnd);
	m_pMouseBuffer = new DMouseBuffer(m_directInput, hwnd);
	m_pJoystick = new DJoystick(m_directInput, hwnd);
}
DInput::~DInput(){
	DeleteDirectInput();
}

void DInput::Update(){
	m_pKeyboardBuffer->Update();
	m_pMouseBuffer->Update();
	m_pJoystick->Update();
}

bool DInput::GetKeyDown(unsigned char keycode){
	return m_pKeyboardBuffer->GetKeyStateDown(keycode);
}
bool DInput::GetKeyUp(unsigned char keycode){
	return m_pKeyboardBuffer->GetKeyStateUp(keycode);
}
bool DInput::GetKeyTrigger(unsigned char keycode){
	return m_pKeyboardBuffer->GetKeyStateTrigger(keycode);
}
bool DInput::GetKeyDetach(unsigned char keycode){
	return m_pKeyboardBuffer->GetKeyStateDetach(keycode);
}

const Vector2& DInput::GetMousePos(){
	return m_pMouseBuffer->GetPosition();
}
Vector2 DInput::GetMouseDeltaPos(){
	return m_pMouseBuffer->GetDeltaPos();
}

bool DInput::GetButtonDown(int button){
	return m_pMouseBuffer->GetButtonDown(button);
}
bool DInput::GetButtonup(int button){
	return m_pMouseBuffer->GetButtonUp(button);
}
bool DInput::GetButtonTrigger(int button){
	return m_pMouseBuffer->GetButtonTrigger(button);
}
bool DInput::GetButtonDetach(int button){
	return m_pMouseBuffer->GetButtonDetach(button);
}

bool DInput::GetJoystickDown(unsigned int index, unsigned char keycode){
	return m_pJoystick->GetButtonStateDown(index, keycode);
}
bool DInput::GetJoystickUp(unsigned int index, unsigned char keycode){
	return m_pJoystick->GetButtonStateUp(index, keycode);
}
bool DInput::GetJoystickTrigger(unsigned int index, unsigned char keycode){
	return m_pJoystick->GetButtonStateTrigger(index, keycode);
}
bool DInput::GetJoystickDetach(unsigned int index, unsigned char keycode){
	return m_pJoystick->GetButtonStateDetach(index, keycode);
}

Vector2 DInput::GetJoystickLeftAxis(unsigned int index){
	return m_pJoystick->GetLeftAxis(index);
}
Vector2 DInput::GetJoystickRightAxis(unsigned int index){
	return m_pJoystick->GetRightAxis(index);
}

float DInput::GetJoystickLeftTrigger(unsigned int index){
	return m_pJoystick->GetLeftTrigger(index);
}
float DInput::GetJoystickRightTrigger(unsigned int index){
	return m_pJoystick->GetRightTrigger(index);
}

float DInput::GetJoystickCrossButton(unsigned int index){
	return m_pJoystick->GetCrossButton(index);
}

bool DInput::CreateDirectInput(HINSTANCE hInstance, HWND hwnd){
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)& m_directInput, NULL)))
		return false;

	return true;
}
void DInput::DeleteDirectInput(){
	REL(m_directInput);
	DEL(m_pKeyboardBuffer);
	DEL(m_pMouseBuffer);
	DEL(m_pJoystick);
}