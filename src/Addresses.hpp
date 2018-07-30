#include "stdafx.h"
#include <cstdint>

#ifndef _ADDRESSES_H_
#define _ADDRESSES_H_

#define TOMB_ADDRESS(address, type)				((type*)address)
#define TOMB_GLOBAL(address, type)				(*((type*)address))
#define TOMB_CALLPROC(address)					(((void(*)())address)())
#define TOMB_CALLFUNC(address, returnType)		(((returnType(*)())address)())

template<class T, class... Types>
inline T(*TOMB_PROC_PTR(const std::uintptr_t address))(Types...) {
	return reinterpret_cast<T(__cdecl *)(Types...)>(address);
}

#define TOMB_SUB_LOAD_PCX (TOMB_PROC_PTR<void, char[]>(TOMB_ADDRESS_LOAD_PCX))
#define TOMB_SUB_PLAY_FMV (TOMB_PROC_PTR<void, int, int>(TOMB_ADDRESS_PLAY_FMV))
#define TOMB_SUB_416550 (TOMB_PROC_PTR<void, int, double>(0x00416550))
#define TOMB_SUB_4344D0 (TOMB_PROC_PTR<void, int, int>(0x004344D0))
#define TOMB_SUB_KEYBOARDHOOK (TOMB_PROC_PTR<void, int, WPARAM, LPARAM>(0x0043D8C0))

#define TOMB_ADDRESS_PLAY_FMV					0x0041CDF0
#define TOMB_ADDRESS_LOAD_PCX					0x00430CE0
#define TOMB_ADDRESS_CONTROLS					0x00454A22
#endif