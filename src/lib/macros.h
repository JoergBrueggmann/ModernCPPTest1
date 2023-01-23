#ifndef macros_h
#define macros_h

#include <iostream>

#define SUB_SECTION(_name)      \
    std::cout << "---" << '\n';      \
    std::cout << "> " << #_name << '\n';    \
    _name();

#define SECTION(_name)                                                      \
void _name() {                                                              \
    std::cout << '\n';                                                           \
    std::cout << "--------------------------------------------------" << '\n';   \
    std::cout << ">> " << #_name << '\n';

#define END_SECTION     \
    }

#endif // macros_h
