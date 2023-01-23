#include "specifier_explicit.h"

#include <iostream>

void specifier_explicit()
{
    struct A
    {
        A(int) { }      // converting constructor
        A(int, int) { } // converting constructor (C++11)
        operator bool() const { return true; }
    };

    struct B
    {
        explicit B(int) { }
        explicit B(int, int) { }
        explicit operator bool() const { return true; }
    };

    std::cout << '\n';
    std::cout << "------------------------------" << '\n';
    std::cout << "specifier_explicit" << '\n';
    A a1 = 1;      // OK: copy-initialization selects A::A(int)
    A a2(2);       // OK: direct-initialization selects A::A(int)
    A a3 {4, 5};   // OK: direct-list-initialization selects A::A(int, int)
    A a4 = {4, 5}; // OK: copy-list-initialization selects A::A(int, int)
    A a5 = (A)1;   // OK: explicit cast performs static_cast
    if (a1) { }    // OK: A::operator bool()
    bool na1 = a1; // OK: copy-initialization selects A::operator bool()
    bool na2 = static_cast<bool>(a1); // OK: static_cast performs direct-initialization

//  B b1 = 1;      // error: conversion from ‘int’ to non-scalar type ‘B’ requested
    B b2(2);       // OK: direct-initialization selects B::B(int)
    B b3 {4, 5};   // OK: direct-list-initialization selects B::B(int, int)
//  B b4 = {4, 5}; // error: converting to ‘B’ from initializer list would use explicit constructor ‘B::B(int, int)’
    B b5 = (B)1;   // OK: explicit cast performs static_cast
    if (b2) { }    // OK: B::operator bool()
//  bool nb1 = b2; // error: cannot convert ‘B’ to ‘bool’ in initialization
    bool nb2 = static_cast<bool>(b2); // OK: static_cast performs direct-initialization

    [a4, a5, na1, na2, b5, nb2] { }; // may suppress "unused variable" warnings
}
