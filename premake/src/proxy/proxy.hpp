#pragma once

#include <unordered_map>

#define EXPORT(DLL, X) extern "C" __declspec(naked) __declspec(dllexport) void X() { proxy::get(DLL, __FUNCTION__); __asm { jmp eax } }

class proxy final
{
	public:
		static FARPROC get(const char* lib, const char* func);

	private:
		static void load(const char* lib);
		static bool is_loaded(const char* lib);

		static std::unordered_map<const char*, HMODULE> libraries;
};
