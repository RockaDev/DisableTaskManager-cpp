#include "header.h"
#include "cmd.h"

int main(int args, char * argv[])
{
	Registry reg;
	WinRegistry winreg;

	reg.ModifyRegistry();
	winreg._disableCMD();

	return 0;
}