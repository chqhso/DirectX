#ifndef D_KEYBOARD_BUFFER_H
#define D_KEYBOARD_BUFFER_H

#define KEYBOARD_BUFFER_SIZE 256

#include <dinput.h>
#include "DKeyCode.h"

class DKeyboardBuffer{
public:
	DKeyboardBuffer(LPDIRECTINPUT8 directInput, HWND hwnd);
	~DKeyboardBuffer();
	bool Update();
	bool GetKeyStateDown(unsigned char keycode);
	bool GetKeyStateUp(unsigned char keycode);
	bool GetKeyStateTrigger(unsigned char keycode);
	bool GetKeyStateDetach(unsigned char keycode);
private:
	bool CreateDirectKeyboardDevice(LPDIRECTINPUT8 directInput, HWND hwnd);

	bool GetKeyStateNewBufferDown(unsigned char keycode);
	bool GetKeyStateNewBufferUp(unsigned char keycode);
	bool GetKeyStateOldBufferDown(unsigned char keycode);
	bool GetKeyStateOldBufferUp(unsigned char keycode);

	void DeleteInputDevice();
private:
	LPDIRECTINPUTDEVICE8	m_device;

	unsigned char m_ucOldBuffer[KEYBOARD_BUFFER_SIZE];
	unsigned char m_ucCurrentBuffer[KEYBOARD_BUFFER_SIZE];
	unsigned char m_ucNewBuffer[KEYBOARD_BUFFER_SIZE];
};

#endif