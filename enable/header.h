#pragma once
#include <iostream>
#include <Windows.h>

#define WIN32_LEAN_AND_MEAN
#pragma warning(disable:4129)

class Registry {
private:

	LPCWSTR DisableTaskMgr = TEXT("DisableTaskMgr");
	HKEY hKey = HKEY_CURRENT_USER;
	LPCWSTR TMGR_PATH = (L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System\\");
	DWORD val_disable = 1;
	DWORD val_enable = 0;

public:
	void EnableT_MGR();
};

void Registry::EnableT_MGR()
{
	RegOpenKeyEx(hKey, TMGR_PATH, 0, KEY_ALL_ACCESS, &hKey);

	if (RegQueryValueEx(hKey, DisableTaskMgr, NULL, NULL, NULL, NULL) == ERROR_FILE_NOT_FOUND)
	{

		if (RegSetValueEx(hKey, DisableTaskMgr, 0, REG_DWORD, (const BYTE*)&val_enable, sizeof(val_enable)) != ERROR_SUCCESS)
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
		RegSetValueEx(hKey, DisableTaskMgr, 0, REG_DWORD, (const BYTE*)&val_enable, sizeof(val_enable));
		RegCloseKey(hKey);
		return;
	}

	return;
}
