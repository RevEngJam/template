#include "proxy/proxy.hpp"
#include "memory/memory.hpp"

//
// You will need to figure out what module and functions to export for your application
// 
// ex ddraw usage:
// EXPORT("ddraw.dll", DirectDrawCreate)
// 
// When you build this DLL, rename it to what you will be proxying, in this case,
// rename "RevEngJam Template.dll" to "ddraw.dll" and place it next to the application you are modifying
// you should see the MessageBox appear on launch
//

void initalize()
{
	//Your code here, you can ignore the rest unless you wanna know how it works
	MessageBoxA(nullptr, "Woah! Your code was loaded into the application.", "RevEngJam", 0);
}

DWORD WINAPI OnAttachImpl(LPVOID lpParameter)
{
	initalize();
	return 0;
}

//Our new thread for when the DLL gets attached
DWORD WINAPI OnAttach(LPVOID lpParameter)
{
	__try
	{
		return OnAttachImpl(lpParameter);
	}
	__except (0)
	{
		FreeLibraryAndExitThread((HMODULE)lpParameter, 0xDECEA5ED);
	}

	return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		//https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-disablethreadlibrarycalls
		DisableThreadLibraryCalls(hModule);
		//Create a new thread to not freeze the base application thread when performing operations
		CreateThread(nullptr, 0, OnAttach, hModule, 0, nullptr);
		return true;
	}

	return false;
}