#ifndef D_INPUT_H
#define D_INPUT_H

#define DIRECTINPUT_VERSION 0x0800

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#include <dinput.h>
#include "../../Interface/IInput.h"
#include "DKeyboardBuffer.h"
#include "DMouseBuffer.h"
#include "DJoystick.h"

class DInput : public IInput{
public:
	DInput(HINSTANCE hInstance, HWND hwnd);
	~DInput();

	virtual void Update() override;

	virtual bool GetKeyDown(unsigned char keycode) override;
	virtual bool GetKeyUp(unsigned char keycode) override;
	virtual bool GetKeyTrigger(unsigned char keycode) override;
	virtual bool GetKeyDetach(unsigned char keycode) override;

	virtual const Vector2& GetMousePos() override;
	virtual Vector2 GetMouseDeltaPos() override;

	virtual bool GetButtonDown(int button) override;
	virtual bool GetButtonup(int button) override;
	virtual bool GetButtonTrigger(int button) override;
	virtual bool GetButtonDetach(int button) override;

	virtual bool GetJoystickDown(unsigned int index, unsigned char keycode) override;
	virtual bool GetJoystickUp(unsigned int index, unsigned char keycode) override;
	virtual bool GetJoystickTrigger(unsigned int index, unsigned char keycode) override;
	virtual bool GetJoystickDetach(unsigned int index, unsigned char keycode) override;

	virtual Vector2 GetJoystickLeftAxis(unsigned int index) override;
	virtual Vector2 GetJoystickRightAxis(unsigned int index) override;

	virtual float GetJoystickLeftTrigger(unsigned int index) override;
	virtual float GetJoystickRightTrigger(unsigned int index) override;

	virtual float GetJoystickCrossButton(unsigned int index) override;
private:
	bool CreateDirectInput(HINSTANCE hInstance, HWND hwnd);
	void DeleteDirectInput();
private	:
	LPDIRECTINPUT8		m_directInput;
	DKeyboardBuffer*	m_pKeyboardBuffer;
	DMouseBuffer*		m_pMouseBuffer;
	DJoystick*			m_pJoystick;
};

#endif