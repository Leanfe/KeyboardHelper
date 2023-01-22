//
// Created by lkapi on 22.01.2023.
//

#include <codecvt>
#include <locale>
#include <shlobj.h>
#include "FileManager.hpp"

namespace FileUtils {

    std::string DownloadFile(const std::string& url) {
        // Get the user's home directory
        char szPath[MAX_PATH];
        if (SUCCEEDED(SHGetFolderPathA(nullptr, CSIDL_PROFILE, nullptr, 0, szPath))) {
            std::string homeDirectory(szPath);
            std::string filePath = homeDirectory + "\\";
            // Open the URL
            HINTERNET hInternet = InternetOpenA("PNG downloader", INTERNET_OPEN_TYPE_PRECONFIG, nullptr, nullptr, 0);
            if (!hInternet) {
                std::cerr << "Failed to open internet session" << std::endl;
                return "";
            }
            HINTERNET hUrl = InternetOpenUrlA(hInternet, url.c_str(), nullptr, 0, INTERNET_FLAG_RELOAD, 0);
            if (!hUrl) {
                std::cerr << "Failed to open URL" << std::endl;
                InternetCloseHandle(hInternet);
                return "";
            }

            // Get the file name
            char szFile[MAX_PATH] = { 0 };
            DWORD dwSize = sizeof(szFile);
            if (!HttpQueryInfoA(hUrl, HTTP_QUERY_CONTENT_DISPOSITION, szFile, &dwSize, nullptr)) {
                std::cerr << "Failed to get file name" << std::endl;
                InternetCloseHandle(hUrl);
                InternetCloseHandle(hInternet);
                return "";
            }

            // Save the file
            DWORD dwBytesRead;
            char buffer[4096] = { 0 };
            filePath += std::string(szFile);
            HANDLE hFile = CreateFileA(filePath.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
            if (hFile == INVALID_HANDLE_VALUE) {
                std::cerr << "Failed to create file" << std::endl;
                InternetCloseHandle(hUrl);
                InternetCloseHandle(hInternet);
                return "";
            }
            while (InternetReadFile(hUrl, buffer, sizeof(buffer), &dwBytesRead) && dwBytesRead) {
                DWORD dwBytesWritten;
                WriteFile(hFile, buffer, dwBytesRead, &dwBytesWritten, nullptr);
            }

            // Clean up
            CloseHandle(hFile);
            InternetCloseHandle(hUrl);
            InternetCloseHandle(hInternet);

            return filePath;
        } else {
            std::cerr << "Failed to get user's home directory" << std::endl;
            return "";
        }
    }

    void openFile(const std::string& path) {

        std::cout << "Open file with keycodes!";

        std::ifstream file(path);

        if (file.is_open()) {

        } else {
            std::cerr << "Unable to open file!";
            exit(EXIT_FAILURE);
        }
    }

    std::string readFile(std::ifstream file) {
        std::string line;
        std::string file_contents;

        while (getline(file, line)) {
            file_contents += line;
        }

        file.close();
        std::cout << "File was read and closed!";

        return file_contents;
    }
}
