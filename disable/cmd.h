#pragma once
#include <iostream>
#include <windows.h>
typedef long _L32;
#define WIN32_LEAN_AND_MEAN
#pragma warning(disable:4129)

namespace CMD
{
	class WinRegistry
	{
	protected:

		LPCWSTR DisableCommandPrompt = L"DisableCMD";
		HKEY hKey = HKEY_CURRENT_USER;
		LPCWSTR CMD_PATH = (L"SOFTWARE\\Policies\\Microsoft\\Windows\\");
		DWORD val_disable = 1;
		DWORD val_enable = 0;

	public:
		void ProcessValueCMD();
		void _disableCMD();
	};

}
