#pragma once
#include <cstdint>

#ifndef _ADDRESSES_H_
#define _ADDRESSES_H_

#define TOMB_ADDRESS(address, type)						((type*)address)
#define TOMB_GLOBAL(address, type)						(*((type*)address))
#define TOMB_CALLPROC(address)							(((void(*)())address)())
#define TOMB_CALLFUNC(address, returnType)				(((returnType(*)())address)())
#define SHIWORD(x)   (*((__int16*)&(x)+1))

template<class T, class... Types>
inline T(*TOMB_PROC_PTR(const std::uintptr_t address))(Types...) {
	return reinterpret_cast<T(__cdecl *)(Types...)>(address);
}

#define TOMB_ADDRESS_PLAY_FMV							0x0041CDF0
#define TOMB_ADDRESS_LOAD_PCX							0x00430CE0
#define TOMB_ADDRESS_CONTROLS							0x00454A22
#define TOMB_ADDRESS_INIT_LIB							0x0043D070
#define TOMB_ADDRESS_INIT_GAME							0x00438410
#define TOMB_ADDRESS_LOAD_SAVE							0x0041DA20
#define TOMB_ADDRESS_INIT_HW							0x0041E100
#define TOMB_ADDRESS_PREP_PCX							0x00416550
#define TOMB_ADDRESS_START_DEMO							0x00415B70
#endif