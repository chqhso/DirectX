#include "Application.h"
#include "Define.h"

Application::Application(HINSTANCE hInstance) : m_hInstance(hInstance){
}
Application::~Application(){
	REL(m_pDev);
	REL(m_pD3D);
}

HRESULT Application::InitD3D(HWND hwnd){
	// D3D Object for Create Device
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// struct for Create Device
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = 800;
	d3dpp.BackBufferHeight = 600;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// Create Device
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pDev)))
	/// 셰이더 디버그용
	//if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pDev)))
		return E_FAIL;

	// default seting
	//m_pDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// enable zbuffer
	m_pDev->SetRenderState(D3DRS_ZENABLE, TRUE);

	m_pDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}

void Application::run(){
	static DWORD preTime = GetTickCount();

	//WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
	//	GetModuleHandle(NULL), NULL, NULL, NULL, NULL, "BasicFrame", NULL };

	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		NULL, NULL, NULL, NULL, NULL, "BasicFrame", NULL };

	RegisterClassEx(&wc);

	/// Create Window
	HWND hWnd = CreateWindow("BasicFrame", "Test",
		(false) ? WS_EX_TOPMOST | WS_POPUP : WS_OVERLAPPEDWINDOW,
		0, 0, 500, 500,
		GetDesktopWindow(), NULL, wc.hInstance, NULL);

	m_hWnd = hWnd;

	//ShowCursor(false);

	if (SUCCEEDED(InitD3D(m_hWnd))){
		initialize();
		ShowWindow(m_hWnd, SW_SHOWDEFAULT);
		UpdateWindow(m_hWnd);

		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		//while (msg.message != WM_QUIT){
		while (GetAsyncKeyState(VK_ESCAPE) == 0){
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)){
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else{
				update((GetTickCount() - preTime) * 0.001f);
				preTime = GetTickCount();
				display();
			}
		}
	}

	finish();

	UnregisterClass("BasicFrame", wc.hInstance);
}
LRESULT WINAPI Application::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0L);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
void Application::display(){
	m_pDev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(150, 150, 150), 1.0f, 0);
	m_pDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	if (SUCCEEDED(m_pDev->BeginScene())){
		draw();
		m_pDev->EndScene();
	}
	m_pDev->Present(NULL, NULL, NULL, NULL);
}