#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int main() {

    Sleep(10000);
    // Register the window class
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"PopupWindowClass";
    wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);

    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,
        L"PopupWindowClass",
        L"Peter Alert",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
        0,
        0,
        GetModuleHandle(NULL),
        0);

    // Load the BMP image from the resource (assuming IDB_BITMAP1 is the resource ID)
    HBITMAP hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(102), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);

    // Create a static control to display the image
    HWND hImage = CreateWindow(
        L"STATIC",
        L"",
        WS_CHILD | WS_VISIBLE | SS_BITMAP,
        10, 10, 300, 200,
        hwnd,
        (HMENU)1,
        GetModuleHandle(NULL),
        0);

    // Set the image for the static control
    SendMessage(hImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);

    // Create an "OK" button
    CreateWindow(
        L"BUTTON",
        L"OK",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        160, 230, 80, 25,
        hwnd,
        (HMENU)2,
        GetModuleHandle(NULL),
        NULL);

    // Run the message loop
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == 2) {
            // OK button pressed
            DestroyWindow(hwnd);
        }
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
