//
// Created by lkapi on 22.01.2023.
//

#include <Windows.h>
#include "../file/FileManager.hpp"

using namespace FileUtils;

#ifndef WPMSENDER_WINDOWUTILS_HPP
#define WPMSENDER_WINDOWUTILS_HPP

static std::string textFieldValue;
static std::string iconUrl;

static void setFieldValue(std::string value) {
    textFieldValue = std::move(value);
}

[[maybe_unused]] LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            // Create a text field
            HWND hTextField = CreateWindowEx(
                    WS_EX_CLIENTEDGE,
                    "EDIT",
                    "",
                    WS_CHILD | WS_VISIBLE | ES_LEFT,
                    10, 10, 360, 20,
                    hwnd,
                    (HMENU)1,
                    GetModuleHandle(nullptr),
                    nullptr
            );

            // Create a button
            CreateWindowEx(
                    0,
                    "BUTTON",
                    "Submit",
                    WS_CHILD | WS_VISIBLE,
                    140, 180, 100, 20,
                    hwnd,
                    (HMENU)2,
                    GetModuleHandle(nullptr),
                    nullptr
            );
            break;
        }
        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case 2: {
                    // Get the value from the text field
                    int len = SendMessage(GetDlgItem(hwnd, 1), WM_GETTEXTLENGTH, 0, 0);
                    char* buffer = new char[len + 1];
                    SendMessage(GetDlgItem(hwnd, 1), WM_GETTEXT, len + 1, (LPARAM)buffer);
                    ShowWindow(hwnd, HIDE_WINDOW);
                    WindowsUtils::process(buffer);
                    delete[] buffer;
                    break;
                }
            }
            break;
        }
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}

extern WPARAM createWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    // Register the window class
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = "myWindowClass";
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
    if (!RegisterClassEx(&wc)) {
        MessageBox(nullptr, "Window Registration Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int windowWidth = 400;
    int windowHeight = 250;

    // Create the window
    hwnd = CreateWindowEx(
            WS_EX_CLIENTEDGE,
            "myWindowClass",
            "Input text for replace!",
            WS_OVERLAPPEDWINDOW,
            (screenWidth - windowWidth) / 2, (screenHeight - windowHeight) / 2,
            windowWidth, windowHeight,
            nullptr, nullptr, hInstance, nullptr);

    if (hwnd == nullptr) {
        MessageBox(nullptr, "Window Creation Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Main message loop
    while (GetMessage(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;

    DestroyWindow(hwnd);
}

#endif //WPMSENDER_WINDOWUTILS_HPP
