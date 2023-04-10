#ifndef UNICODE
#define UNICODE
#endif 

#include "Function.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    WNDCLASS wc = NewWindowClass((HBRUSH)(COLOR_WINDOW + 2), LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1)), hInstance,
                                 LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_ICON1)), L"MainWindowClass", WindowProc);

    if (!RegisterClass(&wc)) {
        return -1;
    }

    hInstance_app = hInstance;
    MSG msg = { 0 };

    if (!(main_window_handle =
    CreateWindow(
        L"MainWindowClass",
        L"Function graph",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        200,
        200,
        800,
        600,
        NULL, NULL, hInstance, NULL)))
        return 0;

    while (TRUE) {

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (msg.wParam);
}

WNDCLASS NewWindowClass(HBRUSH BGcolor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure) {

    WNDCLASS wc = {};

    wc.hbrBackground = BGcolor;
    wc.hCursor = Cursor;
    wc.hInstance = hInst;
    wc.hIcon = Icon;
    wc.lpszClassName = Name;
    wc.lpfnWndProc = WindowProc;

    return wc;
}

void MainWndAddWudgets(HWND hwnd) {

    ChecSin = CreateWindowA("Button", "sin", WS_VISIBLE | WS_CHILD | ES_CENTER | BS_CHECKBOX, 80, 510, 50, 50, hwnd, (HMENU)CHEC_SIN, hInstance_app, NULL);
    ChecCos = CreateWindowA("Button", "cos", WS_VISIBLE | WS_CHILD | ES_CENTER | BS_CHECKBOX, 180, 510, 50, 50, hwnd, (HMENU)CHEC_COS, hInstance_app, NULL);
    ChecX2= CreateWindowA("Button", "X2", WS_VISIBLE | WS_CHILD | ES_CENTER | BS_CHECKBOX, 280, 510, 50, 50, hwnd, (HMENU)CHEC_X2, hInstance_app, NULL);
    ChecSqrtX = CreateWindowA("Button", "sqrt", WS_VISIBLE | WS_CHILD | ES_CENTER | BS_CHECKBOX, 380, 510, 50, 50, hwnd, (HMENU)CHEC_SQRT, hInstance_app, NULL);
    ChecLab = CreateWindowA("Button", "Lab", WS_VISIBLE | WS_CHILD | ES_CENTER | BS_CHECKBOX, 480, 510, 50, 50, hwnd, (HMENU)CHEC_LAB, hInstance_app, NULL);

}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    PAINTSTRUCT ps;
    HDC hdc;

    RECT rect;//{ 50, 50, 730, 500 };
    GetClientRect(hwnd, &rect);

    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    int xCenter = width / 2;
    int yCenter = height / 2;

    int xOffset = xCenter;
    int yOffset = yCenter;

    int scale = min(xCenter, yCenter) / 5;
    HPEN hPen;

    switch (uMsg) {

        case WM_CREATE:{
            RECT rect;
            HDC hdc = GetDC(hwnd);
            GetClientRect(hwnd, &rect);
            MainWndAddWudgets(hwnd); // створюємо віджети
            ReleaseDC(hwnd, hdc);
            ValidateRect(hwnd, &rect);
            break; }

        case WM_PAINT:{ 

            hdc = BeginPaint(hwnd, &ps);

            GetClientRect(hwnd, &rect);
            
            SetBkColor(hdc, RGB(100, 100, 100));
            SetTextColor(hdc, RGB(0, 0, 0));

            HPEN hPen = CreatePen(PS_DASH, 1, RGB(0, 0, 0)); 
            SelectObject(hdc, hPen); 

            // малюємо сітку для графіка
            
            for (int i = 0; i < 13; i++) {
                MoveToEx(hdc, xCenter - scale * (6-i), yCenter - scale * 4, NULL);
                LineTo(hdc, xCenter - scale * (6-i), yCenter + scale * 4);
            }
            for (int i = 0; i < 9; i++) {
                MoveToEx(hdc, xCenter - scale * 6, yCenter - scale * (4-i), NULL);
                LineTo(hdc, xCenter + scale * 6, yCenter - scale * (4-i));
            }

            DeleteObject(hPen); 
            hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); 
            SelectObject(hdc, hPen);
            
            // малюємо основні координатні вісі х та y

            MoveToEx(hdc, xCenter - scale * 6, yCenter, NULL);
            LineTo(hdc, xCenter + scale * 6, yCenter);
            MoveToEx(hdc, xCenter, yCenter - scale * 4, NULL);
            LineTo(hdc, xCenter, yCenter + scale * 4);


            BOOL isChecSin = SendMessage(ChecSin, BM_GETCHECK, 0, 0);
            BOOL isChecCos = SendMessage(ChecCos, BM_GETCHECK, 0, 0);
            BOOL isChecX2 = SendMessage(ChecX2, BM_GETCHECK, 0, 0);
            BOOL isChecSqrtX = SendMessage(ChecSqrtX, BM_GETCHECK, 0, 0);
            BOOL isChecLab = SendMessage(ChecLab, BM_GETCHECK, 0, 0);

            if (sinX) {

                DeleteObject(hPen);
                hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 255));
                SelectObject(hdc, hPen);
                DrawSin(hdc, xCenter, scale, yCenter);
                DeleteObject(hPen);

            }

            if(cosX){

                DeleteObject(hPen);
                hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
                SelectObject(hdc, hPen);
                DrawCos(hdc, xCenter, scale, yCenter);
                DeleteObject(hPen);

            }
            if (x2) {

                DeleteObject(hPen);
                hPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
                SelectObject(hdc, hPen);
                DrawX2(hdc, xCenter, scale, yCenter);
                DeleteObject(hPen);

            } if (sqrtX) {

                DeleteObject(hPen);
                hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
                SelectObject(hdc, hPen);
                DrawSqrtX(hdc, xCenter, scale, yCenter);
                DeleteObject(hPen);

            } if (lab) {

                DeleteObject(hPen);
                hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));
                SelectObject(hdc, hPen);
                DrawLab(hdc, xCenter, scale, yCenter);
                DeleteObject(hPen);

            }
            EndPaint(hwnd, &ps);
            return 0; }
            break;

        case WM_CTLCOLORSTATIC:
            
            SetBkColor((HDC)wParam, RGB(100, 100, 100));  // Я не знаю як, але тут можна вказати колір такий же як у самого вікна
            return (LRESULT)CreateSolidBrush(RGB(100, 100, 100));
            break;

        case WM_COMMAND:
            
            switch (wParam) {
                case CHEC_SIN:
                    if (HIWORD(wParam) == BN_CLICKED) {
                        int state = SendMessage(ChecSin, BM_GETCHECK, 0, 0);
                        sinX = (state == BST_CHECKED) ? true : false;
                        InvalidateRect(hwnd, NULL, TRUE);
                    }break;
                case CHEC_COS:
                    if (HIWORD(wParam) == BN_CLICKED) {
                        int state = SendMessage(ChecCos, BM_GETCHECK, 0, 0);
                        cosX = (state == BST_CHECKED) ? true : false;
                        InvalidateRect(hwnd, NULL, TRUE); 
                    }break;
                case CHEC_X2:
                    if (HIWORD(wParam) == BN_CLICKED) {
                        int state = SendMessage(ChecX2, BM_GETCHECK, 0, 0);
                        x2 = (state == BST_CHECKED) ? true : false;
                        InvalidateRect(hwnd, NULL, TRUE);
                    }
                case CHEC_SQRT:
                    if (HIWORD(wParam) == BN_CLICKED) {
                        int state = SendMessage(ChecSqrtX, BM_GETCHECK, 0, 0);
                        sqrtX = (state == BST_CHECKED) ? true : false;
                        InvalidateRect(hwnd, NULL, TRUE);
                    }
                case CHEC_LAB:
                    if (HIWORD(wParam) == BN_CLICKED) {
                        int state = SendMessage(ChecLab, BM_GETCHECK, 0, 0);
                        lab = (state == BST_CHECKED) ? true : false;
                        InvalidateRect(hwnd, NULL, TRUE); 
                    }
            }
            break;

        case WM_DESTROY: // вихід з програми

            PostQuitMessage(0);
            break;

        default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

void DrawSin(HDC hdc, int xCenter, int scale, int yCenter) {

    int start = xCenter - scale * 6;
    int end = xCenter + scale * 6;

    MoveToEx(hdc, start, scale * sin((start - xCenter) * 3.14159 / 40) + yCenter, NULL);

    for (int i = start; i < end; i++) {
        
        double x = (i - xCenter) * 3.14159 / 40;
        double y = scale * sin(x) + yCenter;
        
        LineTo(hdc, i, y);
    }
}

void DrawCos(HDC hdc, int xCenter, int scale, int yCenter) {

    int start = xCenter - scale * 6;
    int end = xCenter + scale * 6;

    MoveToEx(hdc, start, scale * cos((start - xCenter) * 3.14159 / 40) + yCenter, NULL);

    for (int i = start; i < end; i++) {

        double x = (i - xCenter) * 3.14159 / 40;
        double y = scale * cos(x) + yCenter;

        LineTo(hdc, i, y);
    }
}

void DrawX2(HDC hdc, int xCenter, int scale, int yCenter) {

    int start = xCenter - scale * 6;
    int end = xCenter + scale * 6;
    
    bool state = true;

    for (int i = start; i < end; i++) {

        double x = (i - xCenter)/10.0;
        double y = -(x * x) + yCenter;

        if(y > yCenter - scale * 4 && state){
            MoveToEx(hdc, i, y, NULL);
            LineTo(hdc, i, y);
            state = false;
        } else if(y > yCenter - scale * 4){
            LineTo(hdc, i, y);
        }
    } 
}

void DrawSqrtX(HDC hdc, int xCenter, int scale, int yCenter) {

    int start = xCenter - scale * 6;
    int end = xCenter + scale * 6;

    bool state = true;

    for (int i = start; i < end; i++) {

        double x = i-xCenter;
        if(x < 0) continue;
        double y = -sqrt(x)*4+yCenter;

        if (state) {
            MoveToEx(hdc, i, y, NULL);
            LineTo(hdc, i, y);
            state = false;
        } else {
            LineTo(hdc, i, y);
        }

    }

}

void DrawLab(HDC hdc, int xCenter, int scale, int yCenter) {

    int start = xCenter - scale * 6;
    int end = xCenter + scale * 6;

    bool state = true;

    for (int i = 5; i < 180; i++) {
        double y = ((cos(i)*((pow(2.71, sin(i)))) - 2*sin(4* i) + pow(cos(5* i), 3)))*scale + yCenter;

        if (state) {
            MoveToEx(hdc, 50+i, y, NULL);
            LineTo(hdc, 50+i, y);
            state = false;
        } else {
            LineTo(hdc, 50+i*3.8, y);
        }

    }

}


