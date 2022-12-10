#pragma once

#include <cstdint>

enum opcode : std::uint8_t
{
	nop = 0x90,
	jmp = 0xE9,
	mov = 0xB8,
	retn = 0xC3,
};

#ifdef _WIN32
#include <utility>
#include <functional>
#include <initializer_list>

template <typename T> static void jump(std::uint32_t address, T function)
{
	//Un-protection of memory segment being accessed
	DWORD protecc;
	VirtualProtect(reinterpret_cast<void*>(address), 5, PAGE_EXECUTE_READWRITE, &protecc);

	//Place our jump...
	*(std::uint8_t*)(address) = opcode::jmp;
	//...to our function
	//we +1 because we are setting the jmp to our function pointer
	//and don't want to overwrite the jmp
	*(std::uint32_t*)(address + 1) = (std::uint32_t(function) - address - 5);

	//Re-protect it as we are done
	VirtualProtect(reinterpret_cast<void*>(address), 5, protecc, &protecc);
};

template <typename T> void set(std::uint32_t address, T value)
{
	//Un-protection of memory segment being accessed
	DWORD protecc;
	VirtualProtect(reinterpret_cast<void*>(address), sizeof(T), PAGE_EXECUTE_READWRITE, &protecc);
	
	//Emplace our value at address
	*reinterpret_cast<T*>(address) = value;

	//Re-protect it as we are done
	VirtualProtect(reinterpret_cast<void*>(address), sizeof(T), protecc, &protecc);
}

template <typename T> static void retn_value(std::uint32_t address, T value)
{
	set(address, opcode::mov);
	set(address + 1, std::uint32_t(value));
	set(address + 5, opcode::retn);
}

static void write_bytes(std::uint32_t address, const std::initializer_list<std::uint8_t>& bytes)
{
	std::memcpy(reinterpret_cast<std::uint8_t*>(address), bytes.begin(), bytes.size());
}

#endif
