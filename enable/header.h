#pragma once
#include <iostream>
#include <Windows.h>

#define WIN32_LEAN_AND_MEAN
#pragma warning(disable:4129)

class Registry {
private:
	HKEY hKey = HKEY_CURRENT_USER;
	LPCWSTR TMGR_PATH = (L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\");

public:
	void ModifyRegistry();
};

void Registry::ModifyRegistry()
{
	RegOpenKeyEx(hKey, TMGR_PATH, 0, KEY_ALL_ACCESS, &hKey);

	RegDeleteKeyEx(hKey, L"System", KEY_WOW64_64KEY, NULL);

	return;
}