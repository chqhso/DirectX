#ifndef D_JOYSTICK_H
#define D_JOYSTICK_H

#define JOYSTICK_BUFFER_SIZE 128
#define MAX_JOYSTICK_COUNT 4

#include <dinput.h>
#include <vector>

struct Vector2;

struct JoystickBuffer{
	LPDIRECTINPUTDEVICE8	device;
	DIDEVCAPS				capabilities;
	DIJOYSTATE2				joystickOldBuffer;
	DIJOYSTATE2				joystickCurrentBuffer;
	DIJOYSTATE2				joystickNewBuffer;
};

class DJoystick{
public:
	DJoystick(LPDIRECTINPUT8 directInput, HWND hwnd);
	~DJoystick();
	bool Update();
	bool GetButtonStateDown(unsigned int index, unsigned char keycode);
	bool GetButtonStateUp(unsigned int index, unsigned char keycode);
	bool GetButtonStateTrigger(unsigned int index, unsigned char keycode);
	bool GetButtonStateDetach(unsigned int index, unsigned char keycode);
	void AddJoystick(JoystickBuffer* joystick);
	Vector2 GetLeftAxis(unsigned int index);
	Vector2 GetRightAxis(unsigned int index);
	float GetLeftTrigger(unsigned int index);
	float GetRightTrigger(unsigned int index);
	float GetCrossButton(unsigned int index);
private:
	bool CreateDirectJoystickDevice(LPDIRECTINPUT8 directInput, HWND hwnd);
	void DeleteInputDevice();
	bool PollingJoystick();

	bool GetButtonStateNewBufferDown(unsigned int index, unsigned char keycode);
	bool GetButtonStateNewBufferUp(unsigned int index, unsigned char keycode);
	bool GetButtonStateOldBufferDown(unsigned int index, unsigned char keycode);
	bool GetButtonStateOldBufferUp(unsigned int index, unsigned char keycode);

//	Vector2 GetJoystickAxis();

	static BOOL CALLBACK
		enumCallback(const DIDEVICEINSTANCE* instance, LPVOID context);
	static BOOL CALLBACK
		enumAxesCallback(const DIDEVICEOBJECTINSTANCE* instance, LPVOID context);
private:
	std::vector<JoystickBuffer*>	m_pDeviceBuffer;
//	LPDIRECTINPUTDEVICE8	m_device;
	LPDIRECTINPUT8			m_pDI;
	HWND					m_pHwnd;

	//signed long	m_joyOldBuffer[JOYSTICK_BUFFER_SIZE];
	//signed long	m_joyCurrentBuffer[JOYSTICK_BUFFER_SIZE];
	//signed long	m_joyNewBuffer[JOYSTICK_BUFFER_SIZE];

	//std::vector<DIJOYSTATE2> m_joyOldBuffer;
	//std::vector<DIJOYSTATE2> m_joyCurBuffer;
	//std::vector<DIJOYSTATE2> m_joyNewBuffer;
//	DIJOYSTATE2 m_joyOld;
//	DIJOYSTATE2 m_joyCur;
//	DIJOYSTATE2 m_joyNew;
};

#endif