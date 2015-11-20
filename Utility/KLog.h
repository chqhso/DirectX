#ifndef K_LOG_H
#define K_LOG_H

#include <Windows.h>
#include "CodeProjectSingleton.h"

#define K_LOG_TARGET_UNDEFINED			0x00000001
#define K_LOG_TARGET_CONSOLE			0x00000002
#define K_LOG_TARGET_FILE				0x00000004
#define K_LOG_TARGET_WINDOW				0x00000008
#define K_LOG_TARGET_ALL				(K_LOG_TARGET_CONSOLE|K_LOG_TARGET_FILE|K_LOG_TARGET_WINDOW)
#define K_LOG_WINDOW_TITLE				"Kib Log"
#define K_LOG_WINDOW_CX					300
#define K_LOG_WINDOW_CY					600

class KLog : public CodeProjectSingleton<KLog>{
	unsigned int	m_nTarget;
	char			m_szFilename[MAX_PATH];
	HWND			m_hwnd;
	HWND			m_hwndList;
public:
	KLog();
//	KLog(UINT32 nTarget, LPSTR szFilename = NULL);
	~KLog();
	void SetTarget(UINT32 nTarget, LPSTR szFilename = NULL);
	int Log(LPSTR fmt, ...);
private:
	void CreateLogWindow();
	static LRESULT CALLBACK
		KLog::WndProcKLog(HWND hwnd, UINT hMsg, WPARAM wParam, LPARAM lParam);
};

#endif