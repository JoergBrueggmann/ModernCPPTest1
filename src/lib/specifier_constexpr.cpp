#include "specifier_constexpr.h"

#include "macros.h"

#include <iostream>
#include <ostream>

using std::cout;
using std::ostream;

class A {
    friend constexpr A operator + ( const A& a1, const A& a2 );
    friend ostream& operator<< ( ostream& stream, const A& a );
public:
    int     mnA;
    constexpr A( const A& a ) noexcept : mnA{ a.mnA }  {
    }
    constexpr A( int nA = 0 ) noexcept : mnA{ nA }  {
    }
    // virtual ~A() { } // ...cannot have a destructor when an object of type A is created that also is specified as constexpr.
    constexpr int GetValue() const noexcept {
        return mnA;
    }
};

constexpr A operator + ( const A& a1, const A& a2 ) {
    return A{ a1.mnA + a2.mnA };
}

ostream& operator<< ( ostream& stream, const A& a )
{
    stream << a.mnA;
    return stream;
}

void specifier_constexpr_simple() {

    constexpr int n{ 5 + 7 + 11 };  // will be computed during compile time

    cout << "n = " << n << '\n';
}

void specifier_constexpr_class_constructor() {

    constexpr A     a1{ 5 };        // will be computed during compile time
    constexpr A     a2{ 7 };        // will be computed during compile time

    cout << "a1  = " << a1 << '\n';
    cout << "a2  = " << a2 << '\n';
}

void specifier_constexpr_friend_function() {

    constexpr A     a1{ 5 };        // will be computed during compile time
    constexpr A     a2{ 7 };        // will be computed during compile time
    constexpr A     a3{ a1 + a2 };  // will be computed during compile time

    cout << a1 << " + " << a2 << " = " << a3 << '\n';
}

SECTION(specifier_constexpr) {
    SUB_SECTION( specifier_constexpr_simple );
    SUB_SECTION( specifier_constexpr_class_constructor );
    SUB_SECTION( specifier_constexpr_friend_function );
    END_SECTION
}
