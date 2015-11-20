#ifndef D_MOUSE_BUFFER_H
#define D_MOUSE_BUFFER_H

#include <dinput.h>
#include "../../Define.h"

#define MOUSE_SPEED 1;

class DMouseBuffer{
public:
	DMouseBuffer(LPDIRECTINPUT8 directInput, HWND hwnd);
	~DMouseBuffer();
	bool Update();
	bool GetButtonDown(int button);
	bool GetButtonUp(int button);
	bool GetButtonTrigger(int button);
	bool GetButtonDetach(int button);

	const Vector2& GetPosition();
	Vector2 GetDeltaPos();

private:
	bool CreateDirectMouseDevice(LPDIRECTINPUT8 directInput, HWND hwnd);

	bool GetButtonStateNewBufferDown(int button);
	bool GetButtonStateNewBufferUp(int button);
	bool GetButtonStateOldBufferDown(int button);
	bool GetButtonStateOldBufferUp(int button);

	void DeleteInputDevice();

	void ProcessMouseInput();
private:
	LPDIRECTINPUTDEVICE8	m_device;
	Vector2 m_position;

	DIMOUSESTATE m_oldBuffer;
	DIMOUSESTATE m_newBuffer;
	DIMOUSESTATE m_currentBuffer;
};

#endif