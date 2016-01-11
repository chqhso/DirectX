#ifndef I_INPUT_H
#define I_INPUT_H

#include "../Define.h"

class IInput{
public:
	IInput() {}
	virtual ~IInput() {}

	virtual void Update() = 0;

	virtual bool GetKeyDown(unsigned char keycode) = 0;
	virtual bool GetKeyUp(unsigned char keycode) = 0;
	virtual bool GetKeyTrigger(unsigned char keycode) = 0;
	virtual bool GetKeyDetach(unsigned char keycode) = 0;

	virtual const Vector2& GetMousePos() = 0;
	virtual Vector2 GetMouseDeltaPos() = 0;

	virtual bool GetButtonDown(int button) = 0;
	virtual bool GetButtonup(int button) = 0;
	virtual bool GetButtonTrigger(int button) = 0;
	virtual bool GetButtonDetach(int button) = 0;

	virtual bool GetJoystickDown(unsigned int index, unsigned char keycode) = 0;
	virtual bool GetJoystickUp(unsigned int index, unsigned char keycode) = 0;
	virtual bool GetJoystickTrigger(unsigned int index, unsigned char keycode) = 0;
	virtual bool GetJoystickDetach(unsigned int index, unsigned char keycode) = 0;
	
	virtual Vector2 GetJoystickLeftAxis(unsigned int index) = 0;
	virtual Vector2 GetJoystickRightAxis(unsigned int index) = 0;

	virtual float GetJoystickLeftTrigger(unsigned int index) = 0;
	virtual float GetJoystickRightTrigger(unsigned int index) = 0;

	virtual float GetJoystickCrossButton(unsigned int index) = 0;
};

#endif