//
// Created by lkapi on 22.01.2023.
//

#include <string>
#include <utility>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <wininet.h>


#ifndef WPMSENDER_FILEMANAGER_H
#define WPMSENDER_FILEMANAGER_H

namespace FileUtils {

    extern void openFile(const std::string& path);
    extern std::string readFile(std::ifstream file);

    extern std::string DownloadFile(const std::string& url);

}

#endif //WPMSENDER_FILEMANAGER_H
