#ifndef APPLICATION_H
#define APPLICATION_H

#include <d3d9.h>
#include <d3dx9.h>
#include <memory>

class Application{
public:
	HINSTANCE			m_hInstance = NULL;
	HWND				m_hWnd = NULL;
	LPDIRECT3D9			m_pD3D = NULL;
	LPDIRECT3DDEVICE9	m_pDev = NULL;
public:
	void run();
protected:
	Application(HINSTANCE);
	virtual ~Application();
	virtual void initialize(){}
	virtual void update(float frameTimer){ (void)frameTimer; }
	virtual void draw(){}
	virtual void finish(){}
private:
	HRESULT InitD3D(HWND hwnd);
	static LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void display();
};

#endif