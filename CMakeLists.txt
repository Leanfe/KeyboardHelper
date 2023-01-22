cmake_minimum_required(VERSION 3.24)
project(WPMSender)

set(CMAKE_CXX_STANDARD 20)

add_executable(WPMSender src/main.cpp src/windows/Utils.cpp src/windows/Utils.hpp src/window/WindowUtils.hpp src/file/FileManager.cpp src/file/FileManager.hpp src/file/FileManager.hpp)

target_link_libraries(WPMSender
        wininet)
