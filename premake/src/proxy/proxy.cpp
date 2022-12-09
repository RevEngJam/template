#include "proxy.hpp"

std::unordered_map<const char*, HMODULE> proxy::libraries;

FARPROC proxy::get(const char* lib, const char* func)
{
	if (!proxy::is_loaded(lib))
	{
		proxy::load(lib);
	}

	return GetProcAddress(proxy::libraries[lib], func);
}

void proxy::load(const char* lib)
{
	char path[MAX_PATH];
	GetSystemDirectoryA(path, MAX_PATH);

	std::strcat(path, "\\");
	std::strcat(path, lib);

	proxy::libraries[lib] = LoadLibraryA(path);
}

bool proxy::is_loaded(const char* lib)
{
	return proxy::libraries.find(lib) != proxy::libraries.end();
}

EXPORT("ddraw.dll", DirectDrawCreate)
