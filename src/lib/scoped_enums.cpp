#include "scoped_enums.h"

#include "macros.h"

#include <iostream>
#include <ostream>

using std::cout;
using std::ostream;

enum class ColorIndex;                                      // forward declaration of a scoped enum
ostream& operator<< ( ostream& stream, ColorIndex ci );     // ...used in a forward declaration

enum class ColorIndex {
    red, 
    green, 
    blue
};

enum class Direction {
    up, 
    down, 
    left, 
    right
};

ostream& operator<< ( ostream& stream, ColorIndex ci )
{
    switch ( ci ) {
    case ColorIndex::red:
        stream << "ColorIndex::red";
        break;
    case ColorIndex::green:
        stream << "ColorIndex::green";
        break;
    case ColorIndex::blue:
        stream << "ColorIndex::blue";
        break;
    default:
        stream << "- unknown ColorIndex -";
    }
    return stream;
}

void scoped_enums_simple() {
    // ColorIndex  ciTemp2 = Direction::up;     // error: cannot convert 'Direction' to 'ColorIndex' in initialization
    ColorIndex  ciTemp = ColorIndex::red;
    bool    red;                                // does not conflict with ColorIndex::red
    red = ciTemp == ColorIndex::red;
    if ( red ) {
        cout << "ciTemp is \"red\".\n";
    }
    cout << "ciTemp = " << ciTemp << '\n';
}

SECTION(scoped_enums) {
    SUB_SECTION( scoped_enums_simple );
    END_SECTION
}
