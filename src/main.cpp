#include <iostream>
#include "windows/Utils.hpp"
#include "window/WindowUtils.hpp"

using namespace WindowsUtils;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    /*
     *     sendGreeting();

            process();
     */

    return createWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}

