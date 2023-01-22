//
// Created by lkapi on 22.01.2023.
//

#include "Utils.hpp"
#include <thread>
#include <fstream>
#include <iostream>

namespace WindowsUtils {
    void send_key_with_delay(int key_code, int delay_ms) {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
        keybd_event(key_code, 0, 0, 0);
        keybd_event(key_code, 0, KEYEVENTF_KEYUP, 0);
    }
    std::string get_keycodes(const std::string& input) {
        std::string keycodes;
        for (char c : input) {
            int keycode = VkKeyScan(c);
            keycodes += std::to_string(keycode) + " ";
        }
        return keycodes;
    }

    [[noreturn]] void send_keycode(int keys_to_send[]) {
        // TODO: Send all values from array
//            keybd_event(key_to_send, 0, 0, 0);
//            keybd_event(key_to_send, 0, KEYEVENTF_KEYUP, 0);

    }

    void process(std::string textFieldValue) {
        // TODO: open File, then read File, then listener on key presses, then send keycodes!

        // Register the F8 key as a hotkey
        RegisterHotKey(nullptr, 1, MOD_ALT | MOD_NOREPEAT, VK_F8);

        // Wait for the hotkey to be pressed
        MSG msg = { nullptr };
        while (GetMessage(&msg, nullptr, 0, 0) != 0) {
            if (msg.message == WM_HOTKEY) {
                // The F8 key has been pressed
                // Perform the desired action here
                break;
            }
        }

        // Unregister the hotkey
        UnregisterHotKey(nullptr, 1);

        exit(EXIT_SUCCESS);
    }

}