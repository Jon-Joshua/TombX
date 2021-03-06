// dllmain.cpp : Defines the entry point for the DLL application.

#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN 

#include "Addresses.hpp"
#include "Game.hpp"
#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_syswm.h>
#include <time.h>

using namespace std;

int load_libs() {
	HMODULE ddraw = LoadLibraryA("DDRAW");
	TOMB_GLOBAL(0x0045A3D0, HMODULE) = ddraw;

	if (!ddraw) {
		std::cout << "ERROR: Loading DDRAW failed, exiting..." << std::endl;
		return 0;
	}

	FARPROC ddrawCreate = GetProcAddress(ddraw, "DirectDrawCreate");
	TOMB_GLOBAL(0x0045A3CC, FARPROC) = ddrawCreate;
	
	if (!ddrawCreate) {
		std::cout << "ERROR: Failed to find DirectDrawCreate, exiting..." << std::endl;
		return 0;
	}

	TOMB_PROC_PTR<int, int, int*, int>((int)ddrawCreate)(0, TOMB_ADDRESS(0x0045A998, int), 0);
	TOMB_CALLPROC(0x00450510); // load ati3d lib
	TOMB_GLOBAL(0x0045A994, int) = TOMB_CALLFUNC(0x00450820, int); //create render context
	TOMB_GLOBAL(0x0045A960, int) = 48;
	//std::cout << TOMB_PROC_PTR<int, int>(0x004507B0)(48) << std::endl;
	TOMB_PROC_PTR<int, int*>(0x004507B0)(TOMB_ADDRESS(0x0045A960, int));

	return 1;
}

//int init_hardware() {
//	time_t rawtime;
//	struct tm * timeinfo;
//
//	time(&rawtime);
//	timeinfo = localtime(&rawtime);
//
//	(((int(*)(int))0x0041D910)(timeinfo->tm_sec + 57 * timeinfo->tm_min + 3543 * timeinfo->tm_hour));
//	(((int(*)(int))0x0041D940)(timeinfo->tm_sec + 43 * timeinfo->tm_min + 3477 * timeinfo->tm_hour));
//	
//	//TOMB_CALLPROC(0x0041C020); // CD Check
//
//	TOMB_GLOBAL(0x004546D2, int) = 480;
//	TOMB_GLOBAL(0x004546E6, int) = 480;
//	TOMB_GLOBAL(0x004546D0, int) = 640;
//	TOMB_GLOBAL(0x004546E0, int) = 0;
//	TOMB_GLOBAL(0x004546E2, int) = 0;
//	TOMB_GLOBAL(0x004546E4, int) = 640;
//	((void(*)(int*))0x004380E0)(TOMB_ADDRESS(0x004546D0, int));
//
//	TOMB_CALLPROC(0x0041CDA0);
//	
//	if (TOMB_CALLFUNC(0x00437E00, int) == -1) {
//		TOMB_GLOBAL(0x00456688, int) = 0;
//	}
//
//	int i = 0;
//
//	int* lol = TOMB_ADDRESS(0x006E8060, int);
//	int* lol2 = TOMB_ADDRESS(0x006D4E00, int);
//	int* lol3 = TOMB_ADDRESS(0x006CAD20, int);
//
//	for (int x = 0; x < 32; x++) {
//		//lol[x] = 2 * ((signed __int16(*)(DWORD))0x0042A850)(i / 32) >> 14;
//		//lol2[x] = 768 * ((signed __int16(*)(DWORD))0x0042A850)(i / 32) >> 14;
//		//lol3[x] = (TOMB_CALLFUNC(0x0041D920, int) >> 5) - 511;
//		i += 0x10000;
//		lol[x] = 1;
//		lol2[x] = 1;
//		lol3[x] = 1;
//
//		std::cout << x << " " << lol[x] << " " << lol3[x] << " " << i << std::endl;
//
//	}
//
//	TOMB_GLOBAL(0x0045EEF8, int) = 0x380000;
//
//
//	TOMB_CALLPROC(0x00408005);
//	return 1;
//}

extern "C"
__declspec(dllexport) int __cdecl StartTombX(HINSTANCE hInstance, DWORD dword, int y, int nCmdShow) {
	std::cout << "Starting TombX" << std::endl;

	SDL_Window *window;
	window = SDL_CreateWindow("TombX", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 900, SDL_WINDOW_SHOWN);
	SDL_SetWindowBordered(window, SDL_TRUE);
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(window, &wmInfo);

	TOMB_GLOBAL(0x00463600, HWND) = wmInfo.info.win.window;

	if (!load_libs()) {
		exit(1);
	}

	init_game();
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
	}
	return TRUE;
}