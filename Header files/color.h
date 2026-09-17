#pragma once
#include <iostream>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace Color {
    inline void setAttribute(WORD attr) {
        static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, attr);
    }

    inline std::ostream& reset(std::ostream& os) {
        os.flush();
        setAttribute(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        return os;
    }

    inline std::ostream& red(std::ostream& os) {
        os.flush();
        setAttribute(FOREGROUND_RED | FOREGROUND_INTENSITY);
        return os;
    }

    inline std::ostream& green(std::ostream& os) {
        os.flush();
        setAttribute(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        return os;
    }

    inline std::ostream& yellow(std::ostream& os) {
        os.flush();
        setAttribute(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        return os;
    }

    inline std::ostream& blue(std::ostream& os) {
        os.flush();
        setAttribute(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        return os;
    }

    inline std::ostream& cyan(std::ostream& os) {
        os.flush();
        setAttribute(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        return os;
    }
}