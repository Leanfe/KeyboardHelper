//
// Created by lkapi on 22.01.2023.
//

#include <Windows.h>
#include <string>
#include <utility>

#ifndef WPMSENDER_UTILS_HPP
#define WPMSENDER_UTILS_HPP

namespace WindowsUtils {
    extern void send_key_with_delay(int key_code, int delay_ms);

    extern std::string get_keycodes(const std::string& input);

    extern void process(std::string textFieldValue);

}

#endif //WPMSENDER_UTILS_HPP
