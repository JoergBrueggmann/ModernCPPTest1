
#include "item6.h"

#include <string>
#include <vector>
#include <iostream>

using boolvector = std::vector<bool>;
using std::string;
using std::cout;

static boolvector f1( int n ) noexcept {
    boolvector  vbResult;
    switch ( n ) {
    case 1:
        vbResult = boolvector{ true, false, false };
        break;
    case 2:
        vbResult = boolvector{ false, true, false };
        break;
    default:
        vbResult = boolvector{ false, false, true };
    }
    return vbResult;
}

void item6() {
    std::cout << '\n';
    std::cout << "------------------------------" << '\n';
    std::cout << "item6" << '\n';
    auto highPriority = static_cast<bool>(f1( 1 )[0]);  // Item6: Use the explicit typed inititializer idiom when auto deduces undsesired types.
    //                  ^^^^^^^^^^^^^^^^^ explicit typed inititializer idiom
    //auto highPriority = f1( 1 )[0];   // ...may lead to wrong result because the operator [] of teplate class "vector" returns a proxy class!
    cout << "highPriority = " << highPriority << '\n';
}
