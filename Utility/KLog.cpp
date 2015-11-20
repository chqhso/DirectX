#include "KLog.h"
#include <time.h>
#include <stdio.h>

KLog::KLog(){
	m_nTarget = K_LOG_TARGET_UNDEFINED;
	m_szFilename[0] = NULL;
}
KLog::~KLog(){
	DestroyWindow(m_hwnd);
}
void KLog::SetTarget(UINT32 nTarget, LPSTR szFilename){
	m_nTarget = nTarget;

	if (nTarget & K_LOG_TARGET_FILE)
		lstrcpy(m_szFilename, szFilename);
	else
		m_szFilename[0] = NULL;

	if (nTarget & K_LOG_TARGET_WINDOW)
		CreateLogWindow();
	else
		m_hwnd = NULL;
	Log("KLog Logging Started");
}
void KLog::CreateLogWindow(){
	int x, y, cx, cy;
	WNDCLASS wc;
	RECT rc;

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)KLog::WndProcKLog;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "KLogWindow";

	RegisterClass(&wc);

	cx = K_LOG_WINDOW_CX;
	cy = K_LOG_WINDOW_CY;
	x = GetSystemMetrics(SM_CXSCREEN) - cx;
	y = 0;

	m_hwnd = CreateWindow("KLogWindow", K_LOG_WINDOW_TITLE, WS_POPUP | WS_CAPTION, x, y, cx, cy, NULL, NULL, GetModuleHandle(NULL), NULL);
	GetClientRect(m_hwnd, &rc);
	m_hwndList = CreateWindow("LISTBOX", "", WS_CHILD | WS_VSCROLL, 0, 0, rc.right, rc.bottom, m_hwnd, NULL, GetModuleHandle(NULL), NULL);
	ShowWindow(m_hwnd, SW_SHOW);
	ShowWindow(m_hwndList, SW_SHOW);
}

int KLog::Log(LPSTR fmt, ...){

	if (m_nTarget & K_LOG_TARGET_UNDEFINED){
		return 0;
	}

	char buff[1024];
	char date[128];
	char time[128];

	_strdate_s(date);
	_strtime_s(time);
	vsprintf_s(buff, fmt, (char*)(&fmt + 1));

	// Console에 출력할 경우
	if (m_nTarget & K_LOG_TARGET_CONSOLE){
		printf("(date[%s] time[%s]) : %s\n", date, time, buff);
	}

	// Log File에 출력할 경우
	if (m_nTarget & K_LOG_TARGET_FILE){
		FILE* fp = NULL;
		fopen_s(&fp, m_szFilename, "a+");
		if (fp){
			fprintf(fp, "(date[%s] time[%s] : %s\n", date, time, buff);
			fclose(fp);
		}
	}

	//Log Window에 출력할 경우
	if (m_nTarget& K_LOG_TARGET_WINDOW){
		SendMessage(m_hwndList, LB_ADDSTRING, 0, (LPARAM)buff);
		UINT32 n = SendMessage(m_hwndList, LB_GETCOUNT, 0, 0L) - 1;
		SendMessage(m_hwndList, LB_SETCURSEL, (WPARAM)n, 0L);
	}
	return 1;
}

LRESULT CALLBACK
KLog::WndProcKLog(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}