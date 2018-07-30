#include "stdafx.h"
#include <cstdint>

#ifndef _ADDRESSES_H_
#define _ADDRESSES_H_

#define TOMB_ADDRESS(address, type)				((type*)address)
#define TOMB_GLOBAL(address, type)				(*((type*)address))
#define TOMB_CALLPROC(address)					(((void(*)())address)())
#define TOMB_CALLFUNC(address, returnType)		(((returnType(*)())address)())

#define TOMB_ADDRESS_PLAY_FMV					0x0041CDF0
#define TOMB_ADDRESS_LOAD_PCX					0x00430CE0
#define TOMB_ADDRESS_CONTROLS					0x00454A22
#endif