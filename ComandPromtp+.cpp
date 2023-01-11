#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <tuple>
#include <map>
#include "Func.h"
// my keyboard doesnt have a backslash so its here for me to copy \

float version = 0.1;

using namespace std;
using namespace func;
char my_current_path[1024] = "C:\\";

// Enum as int, allows to use switch to detect which command been ran
enum command {
    close = 1,
    print = 2,
    changeDir = 3,
    dir = 4
};

std::map<std::string, command> commandMap = {
    {"exit", close},
    {"print", print},
    {"cd", changeDir},
    {"dir", dir}
};

// Used to split between command and text for command to use or options
constexpr char commandSplit = ';';

int main()
{
    cout << "Command Prompt - Version "<< version << endl;
    SetCurrentDirectory((string("C:/")).c_str());
    while (true) {
        cout << endl;
        string line; // Intial input
        GetCurrentDirectory(1024, my_current_path);
        cout << my_current_path << ">";
        getline(cin, line);
        cout << endl;
        
        string CommandSearch = ""; // Push to lowercase for finding the command
        string CommandText = ""; // Lower case actual command
        bool FoundCommand = false;
        for (char c : line) {
            CommandSearch += char(tolower(c));
            if (c == commandSplit) FoundCommand = true;
            if (!FoundCommand) CommandText += char(tolower(c));
        }

        if (commandMap.find(CommandText) == commandMap.end()) {
            cout << "Invalid command";
            continue;
        }

        switch (commandMap[CommandText]) {
            case close: {
                return 0;
            }

            case print: {
                tuple<bool, size_t> firstCharHold = find(line, string(1, commandSplit));
                if (get<0>(firstCharHold)) {
                    string printme = line.substr(get<1>(firstCharHold) + 1, line.size() - get<1>(firstCharHold));
                    tuple<bool, size_t> FilePrint = find(printme, string(1, commandSplit));
                    if (get<0>(FilePrint)) { // We are printing to a file
                        // Split for file and text to print
                        string PrintMeToFile = printme.substr(0, get<1>(FilePrint));
                        string FileToPrint = printme.substr(get<1>(FilePrint) + 1, printme.size() - get<1>(FilePrint));
                        ofstream OutputFile; 
                        // Open file, check its open
                        OutputFile.open(FileToPrint, ios::app);
                        if (OutputFile.is_open()) {
                            OutputFile << PrintMeToFile << endl; // Write if its open, and add a newline 
                            OutputFile.close();
                        }
                        else {
                            cout << "Invalid file or permission denied"; // If not opened, file is invalid or we dont have perms
                            OutputFile.close();
                        }
                    }
                    else 
                        cout << printme << endl; // Print to screen
                }
                else 
                    cout << "Invalid Print command" << endl; // Command was invalid
                break;
            }

            case changeDir: {
                tuple<bool, size_t> firstCharHold = find(line, string(1, commandSplit));
                if (get<0>(firstCharHold)) {
                    string changeToMe = line.substr(get<1>(firstCharHold) + 1, line.size() - get<1>(firstCharHold));
                    if (changeToMe.back() != char("/")) {
                        changeToMe += "/";
                    }
                    if (!SetCurrentDirectory(changeToMe.c_str())) {
                        cout << "Failed to change directory";
                    }
                }
                else {
                    cout << "Invalid Print command" << endl;
                }
                break;
            }

            case dir: {
                getFiles(string(my_current_path));
                break;
            }

            default:
                cout << "Code should not be here, please report";
                break;
        }
    }
}
