#include "container_helper.h"

#include <iostream>

using std::cout;
using std::string;

void container_print_prologue() {
    cout << "vb = { ";
}

void container_print_seperator() {
    cout << ", ";
}

void container_print_epilogue() {
    cout << " };\n";
}

template <> void container_print_value<int>( const int& nValue) {
    cout << nValue;
}

template <> void container_print_value<string>( const string& nValue) {
    cout << "\"" << nValue << "\"";
}

template <> void container_print_value<bool>( const bool& bValue) {
    cout << (bValue ? "true" : "false");
}

template <> void container_print_value<std::pair<const string,int>>( const std::pair<const string,int>& pairValue ) {
    cout << "\n         { ";
    container_print_value( pairValue.first );
    cout << ", ";
    container_print_value( pairValue.second );
    cout << " }";
}
