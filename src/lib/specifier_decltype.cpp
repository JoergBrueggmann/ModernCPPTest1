#include "specifier_decltype.h"

#include "macros.h"

#include <iostream>
#include <ostream>
#include <vector>

using std::cout;
using std::ostream;

using VB = std::vector<bool>;

class A {
public:
    bool    misActive;
    constexpr A( bool isActive ) : misActive(isActive) {
    }
};

[[maybe_unused]]static bool fDecltypeSimple1([[maybe_unused]]const A& a) {
    return false;
}

auto fIsActive() { return true; }

void specifier_decltype_simple() {

    const int i = 0;
    decltype(i) j = 2;  // decltype(i) --->>> const int
    //j = 3;  // error: assignment of read-only variable 'j'
    cout << "j = " << j << '\n';

    const A a1 = A{ true };
    const A& ra1 = a1;
    [[maybe_unused]] decltype(ra1) a2 = a1;  // decltype(ra1) --->>> const A&
    decltype(fDecltypeSimple1)  fDecltypeSimple2;    // can be ceclare but linker will complain
    // cout << "a2 = " << fDecltypeSimple2( a2 ) << '\n';

    if ( fIsActive() ) {} // // decltype(fIsActive) --->>> bool
    cout << "fIsActive() = " << fIsActive() << '\n';

    int     anVector[5] = { 2, 3, 5, 7, 11 };
    decltype(anVector[0])   rnValue2 = anVector[1];
    cout << "rnValue2 = " << rnValue2 << '\n';
}

template<typename Container, typename Index>
decltype(auto)
fCpp14(Container&& c, Index i)
{
    // ...
    return std::forward<Container>(c)[i];
}

template<typename Container, typename Index>
auto
fCpp11(Container&& c, Index i)
    -> decltype(std::forward<Container>(c)[i])
{
    // ...
    return std::forward<Container>(c)[i];
}

void specifier_universal_template_function_universal_reference_cpp14() {
    VB  vb{ true, false, true };
    auto b = fCpp14( vb, 1 );
    cout << "b = " << b << '\n';
}

void specifier_universal_template_function_universal_reference_cpp11() {
    VB  vb{ true, false, true };
    auto b = fCpp11( vb, 2 );
    cout << "b = " << b << '\n';
}

static decltype(auto) f1() {
    int x = 27;
    return x;
}

/* 
static decltype(auto) f2() { // same function as f1 but just with return type in brackets, causing to return a reference to int (type: int&).
    int x = 27;
    return (x); // <<< warning: reference to local variable 'x' returned [-Wreturn-local-addr]
}
*/

void specifier_decltype_auto() {
    cout << "f1() = " << f1() << '\n';
    // cout << "f2() = " << f2() << '\n'; // Don't do this, because of undefined behaviour !!! See declaration and comment of f2 above.
}

SECTION(specifier_decltype) {
    SUB_SECTION( specifier_decltype_simple );
    SUB_SECTION( specifier_universal_template_function_universal_reference_cpp14 );
    SUB_SECTION( specifier_universal_template_function_universal_reference_cpp11 );
    SUB_SECTION( specifier_decltype_auto );
    END_SECTION
}
