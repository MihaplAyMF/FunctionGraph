#pragma once

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include "resource.h"

#define TEXT_BUFFER 10
#define CHEC_SIN 101
#define CHEC_COS 102
#define CHEC_X2 103
#define CHEC_SQRT 104
#define CHEC_LAB 105

#define KEYDOWN(vk_code) \
 ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code) \
 ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

char buffer[TEXT_BUFFER];
HINSTANCE hInstance_app;
HWND main_window_handle; // дескриптор вікна
HWND ChecSin, ChecCos, ChecX2, ChecSqrtX, ChecLab;

bool sinX, cosX, x2, sqrtX, lab;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
WNDCLASS NewWindowClass(HBRUSH BGcolor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);
void MainWndAddWudgets(HWND hwnd);

void DrawSin(HDC hdc, int xCenter, int scale, int yCenter);
void DrawCos(HDC hdc, int xCenter, int scale, int yCenter);
void DrawX2(HDC hdc, int xCenter, int scale, int yCenter);
void DrawSqrtX(HDC hdc, int xCenter, int scale, int yCenter);
void DrawLab(HDC hdc, int xCenter, int scale, int yCenter);

int randint(int start, int end) {
	return rand() % end + start;
}

double function(double x) {
	return sin(x);
}
