#ifndef DEBUG_H
#define DEBUG_H

#include <cstdlib>
#include <cstring>
#include <iostream>

namespace Debug {
// print debugging information only if the DEBUG environemnt variable is
// set
template <typename... Args>
inline void print(const Args&... args)
{
    if (getenv("DEBUG") && strcmp(getenv("DEBUG"), "1") == 0) {
        auto debugPrintImpl = [](const auto&... values) {
            (std::cout << ... << values) << std::endl;
        };

        debugPrintImpl(args...);
    }
}
}

#endif // DEBUG_H