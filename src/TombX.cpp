// dllmain.cpp : Defines the entry point for the DLL application.

#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "Addresses.hpp"
#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

using namespace std;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void read_ati() {

}

//void load_pcx(char *file) {
//	char full_file[100];
//	strcpy(full_file, file);
//	strcpy(full_file, ".pcx");
//
//	FILE *pcx = fopen(full_file, "rb");
//
//	if (pcx) {
//		fseek(pcx, 0, 2);
//		int tell = ftell(pcx);
//		rewind(pcx);
//
//		fclose(pcx);
//	}
//
//}
//
//void init_game()
//{
//	TOMB_GLOBAL(0x00453530, int) = 1;
//	TOMB_GLOBAL(0x00456688, int) = 1;
//	TOMB_GLOBAL(0x00459F64, int) = 0;
//	TOMB_GLOBAL(0x00459F60, int) = 0;
//
//	TOMB_GLOBAL(0x00453558, double) = 4607182418800017408;
//	TOMB_GLOBAL(0x00453560, double) = 4607182418800017408;
//
//	TOMB_CALLPROC(0x0041E100); // init hardware
//	//TOMB_CALLPROC(0x004344D0);
//
//	TOMB_SUB_4344D0(0x2964, TOMB_GLOBAL(0x0045B9C0, int));
//	
//	TOMB_CALLPROC(0x0041DA20);
//
//	FILE *atiset = fopen("atiset.dat", "rb");
//
//	if (atiset) {
//		fread(TOMB_ADDRESS(0x00456334, int), 2u, 1u, atiset);
//		fread(TOMB_ADDRESS(0x00456330, __int16), 2u, 1u, atiset);
//		fread(TOMB_ADDRESS(TOMB_ADDRESS_CONTROLS, __int16), 2u, 13u, atiset);
//		fread(TOMB_ADDRESS(0x0045A240, int), 4u, 1u, atiset);
//		fread(TOMB_ADDRESS(0x00459F60, int), 4u, 1u, atiset);
//		fread(TOMB_ADDRESS(0x00453560, int), 8u, 1u, atiset);
//		fclose(atiset);
//	}
//
//	TOMB_GLOBAL(0x00453560, double) = 4607182418800017408;
//	TOMB_GLOBAL(0x0045E960, int) = TOMB_GLOBAL(0x0045A240, int);
//
//	TOMB_GLOBAL(0x00459F64, int) = 1;
//	TOMB_SUB_416550(2, 1.0);
//
//	//TOMB_SUB_LOAD_PCX(TOMB_ADDRESS(0x00456B8C, char));
//
//	TOMB_CALLPROC(0x00408E41);
//
//	TOMB_CALLPROC(0x0040834C);
//
//	TOMB_SUB_PLAY_FMV(1, 1);
//
//	while (1)
//	{
//		TOMB_CALLPROC(0x004167D0);
//	}
//
//}

extern "C"
__declspec(dllexport) int __cdecl StartTombX(HINSTANCE hInstance, DWORD dword, int y, int nCmdShow)
{
	WNDCLASSEX WndClass = { 0 };
	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WindowProc;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(4);
	WndClass.hInstance = GetModuleHandleA(0);
	WndClass.lpszClassName = TEXT("TRClass");
	WndClass.lpszMenuName = 0;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hCursor = LoadCursorA(0, (LPCSTR)0x7F00);
	WndClass.hIcon = LoadIconA(hInstance, (LPCSTR)0x7F00);

	if (!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("Window Registration Failed!"), TEXT("Error!"),
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	HWND hWnd = CreateWindowEx(0, TEXT("TRClass"), TEXT("TombX"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
		GetModuleHandleA(0), NULL);

	ShowWindow(hWnd, 5);
	UpdateWindow(hWnd);

	TOMB_GLOBAL(0x00463600, HWND) = hWnd;

	int thread = GetCurrentThreadId();

	HOOKPROC hook = TOMB_GLOBAL(0x0043D8C0, HOOKPROC);

	//TOMB_GLOBAL(0x0045A93C, HHOOK) = SetWindowsHookExA(2, hook, 0, thread);

	TOMB_CALLPROC(0x0043D070);
	TOMB_CALLPROC(0x00438410);
	//init_game();

	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}