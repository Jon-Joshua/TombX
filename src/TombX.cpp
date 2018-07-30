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