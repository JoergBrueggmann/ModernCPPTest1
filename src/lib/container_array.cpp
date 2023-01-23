#include "container_array.h"

#include "container_helper.h"
#include "macros.h"

#include <array>
#include <iostream>
#include <stdexcept>

using AB = std::array<bool, 10>;
using std::out_of_range;
using std::cout;

static void array_simple_construction() {
    // AB  abTemp{ true, false, true, false, true, false, true, false, true, true, true, true }; // error: too many initializers for 'AB' {aka 'std::array<bool, 10>'}
    AB  abTemp{ false, false, true, false, true, false, true, false, true, true };
    container_print( abTemp );
}

static void array_out_of_range() {
    AB  abTemp{ false, false, true, false, true, false, true, false, false, false };
    try {
        abTemp.at(9) = true;
        abTemp.at(10) = true;
        abTemp.at(11) = true;
        container_print( abTemp );
    } catch ( out_of_range const& exc ) {
        cout << "   error: out of range" << '\n';
        cout << "   exception: " << exc.what() << '\n';
        container_print( abTemp );
    }
}

SECTION(container_array) {
    SUB_SECTION( array_simple_construction );
    SUB_SECTION( array_out_of_range );
    END_SECTION
}
