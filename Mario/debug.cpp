#include <Windows.h>
#include "debug.h"

HWND _hwnd = NULL;

void DebugOut(const wchar_t *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	wchar_t dbg_out[4096];
	vswprintf_s(dbg_out, fmt, argp);
	va_end(argp);
	OutputDebugString(dbg_out);
}

void DebugOutTitle(const wchar_t* fmt, ...)
{
	wchar_t s[1024];
	VA_PRINTS(s);
	SetWindowText(_hwnd, s);
}

void SetDebugWindow(HWND hwnd)
{
	_hwnd = hwnd;
}

LPCWSTR ToLPCWSTR(string st)
{
	const char* str = st.c_str();

	size_t newsize = strlen(str) + 1;
	wchar_t* wcstring = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, str, _TRUNCATE);

	wstring* w = new wstring(wcstring);
	return w->c_str();
}