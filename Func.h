#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <tuple>
using namespace std;
// General functions
namespace func{
    void getFiles(string directory) {
        HANDLE dir;
        WIN32_FIND_DATA file_data;
        string  file_name, full_file_name;
        if ((dir = FindFirstFile((directory + "/*").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
        {
            cout << "Error";
            return;
        }

        while (FindNextFile(dir, &file_data)) {
            file_name = file_data.cFileName;
            string TempDir = directory;
            if (TempDir.back() != char("\\")) {
                TempDir += "\\";
            }
            full_file_name = TempDir + file_name;
            if (strcmp(file_data.cFileName, ".") != 0 && strcmp(file_data.cFileName, "..") != 0)
            {
                cout << full_file_name << endl;
            }
        }
    }

    tuple<bool, size_t> find(string search, string TextFind) {
        int ret = search.find(TextFind);
        if (ret == string::npos) {
            return tuple<bool, size_t>{ false, ret };
        }
        return tuple<bool, size_t>{ true, ret };
    }

    bool contains(string search, string TextFind) {
        tuple<bool, size_t> ValueHold = find(search, TextFind);
        return get<0>(ValueHold);
    }

    string replace(string str, const char replace, const char with) {
        if (str.size() == 0) return "";
        string out = "";
        for (char c : str)
        {
            if (c != replace) out += c;
            c += with;
        }
        return out;
    }
}