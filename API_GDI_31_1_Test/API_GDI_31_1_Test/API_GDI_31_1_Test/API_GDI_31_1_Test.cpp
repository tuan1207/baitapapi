// API_GDI_31_1_Test.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "API_GDI_31_1_Test.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HMENU hMenu;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_APIGDI311TEST, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_APIGDI311TEST));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APIGDI311TEST));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_APIGDI311TEST);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
   hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDC_APIGDI311TEST));
   HWND hWnd = CreateWindowW(szWindowClass, TEXT("Bai thi thu"), WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, hMenu, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    
    static int luu = -1; // lưu hình
    static int luumn = -1;
    static int luumv = -1;
    static int x, y, x1, y1, m=90,s;
    POINT point8[8];
    static POINT pT[1000];
    static int n = 0;
    static TCHAR text[100];
    HBRUSH hBrush;
    HPEN hPen;
    HDC hdc;
    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, 9999, 1000, NULL);
        break;
    case WM_TIMER:
        if (s == 0 && m == 0) {
            MessageBox(NULL, TEXT("Time up"), TEXT("Thông báo"), MB_OK | MB_ICONINFORMATION);
            KillTimer(hWnd, 9999);
        }
        if (s > 0 && s <= 59)
        {
            s--;
        }
        else {
            if (s == 0) {
                m--;
                s = 59;
            }
        }
        wsprintf(text, L"Time %d : %d", m, s);
        hdc = GetDC(hWnd);
        TextOut(hdc, 0, 0, text, 100);
        ReleaseDC(hWnd, hdc);
        break;
    case WM_LBUTTONDOWN:
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        pT[n].x = x;
        pT[n].y = y;
        n++;
        hdc = GetDC(hWnd);
        if (luu == 2)
        {
            if (luumv == 0)
            {
                SetPixel(hdc, x, y, RGB(153, 255, 204));
                ReleaseDC(hWnd, hdc);
            }
            else if (luumv == 1)
            {
                SetPixel(hdc, x, y, RGB(255, 0, 0));
                ReleaseDC(hWnd, hdc);
            }
        }
        break;
    case WM_RBUTTONDOWN:
        hdc = GetDC(hWnd);
        if (luu == 2)
        {
            Polyline(hdc, pT, n);
        }
        break;
    case WM_RBUTTONDBLCLK:
        n = 0;
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_LBUTTONUP:
        x1 = LOWORD(lParam);
        y1 = HIWORD(lParam);
        hdc = GetDC(hWnd);
        if (luu == 0) {
            if (luumn == 0) {
                hBrush = CreateSolidBrush(RGB(0, 204, 0));
                SelectObject(hdc, hBrush);
                if (luumv == 0)
                {
                    hPen = CreatePen(PS_SOLID, 3, RGB(153,255,204) );
                    SelectObject(hdc, hPen);
                }
                else if (luumv == 1)
                {
                    hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
                    SelectObject(hdc, hPen);
                }
            }
            else if (luumn == 1) {
                hBrush = CreateSolidBrush(RGB(0, 0, 204));
                SelectObject(hdc, hBrush);
                if (luumv == 0)
                {
                    hPen = CreatePen(PS_SOLID, 3, RGB(153, 255, 204));
                    SelectObject(hdc, hPen);
                }
                else if (luumv == 1)
                {
                    hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
                    SelectObject(hdc, hPen);
                }
            }
            Rectangle(hdc, x, y, x1, y1);
        }
        else if (luu == 1) {
            if (luumn == 0) {
                hBrush = CreateSolidBrush(RGB(0, 204, 0));
                SelectObject(hdc, hBrush);
                if (luumv == 0)
                {
                    hPen = CreatePen(PS_SOLID, 3, RGB(153, 255, 204));
                    SelectObject(hdc, hPen);
                }
                else if (luumv == 1)
                {
                    hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
                    SelectObject(hdc, hPen);
                }
            }
            else if (luumn == 1) {
                hBrush = CreateSolidBrush(RGB(0, 0, 204));
                SelectObject(hdc, hBrush);
                if (luumv == 0)
                {
                    hPen = CreatePen(PS_SOLID, 3, RGB(153, 255, 204));
                    SelectObject(hdc, hPen);
                }
                else if (luumv == 1)
                {
                    hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
                    SelectObject(hdc, hPen);
                }
            }
            point8[0] = { x ,(y1 + y) / 2 };
            point8[1] = { x + (x1 - x) / 3, y + (y1 - y) / 3 };
            point8[2] = { (x1 + x) / 2,y };
            point8[3] = { x1 - (x1 - x) / 3,y + (y1 - y) / 3 };
            point8[4] = { x1, (y1 + y) / 2 };
            point8[5] = { x1 - (x1 - x) / 3,y1 - (y1 - y) / 3 };
            point8[6] = { (x1 + x) / 2, y1 };
            point8[7] = { x + (x1 - x) / 3, y1 - (y1 - y) / 3 };
            Polygon(hdc, point8, 8);
        }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:

            break;
        case ID_Thoat:
            if (MessageBox(NULL, TEXT("Bạn có muốn thoát không?"), TEXT("Thông báo"), MB_YESNO) == IDYES) {
                DestroyWindow(hWnd);
            }
            break;
        case IDM_ChuNhat:
            luu = 0;
            break;
        case ID_Sao:
            luu = 1;
            break;
        case ID_TuDo:
            luu = 2;
        case IDM_Green:
            luumn = 0;
            break;
        case ID_Blue:
            luumn = 1;
            break;
        case ID_XanhNgoc:
            luumv = 0;
            break;
        case ID_Red:
            luumv = 1;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
