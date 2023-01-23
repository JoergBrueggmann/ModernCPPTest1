#include "container_unordered_map.h"

#include "container_helper.h"
#include "macros.h"

#include <unordered_map>
#include <string>
#include <iostream>
#include <stdexcept>

using std::string;
using UMSI = std::unordered_map<string,int>;
using std::out_of_range;
using std::cout;

static void unordered_map_simple_construction() {
    UMSI    umsiTemp 
        {
            { "People's Republic of China", 1412600000 }, 
            { "Republic of India", 1375586000 }, 
            { "United States of America", 333291537 }, 
            { "Republic of Indonesia", 275773800 }, 
            { "Islamic Republic of Pakistan", 229489000 }
        };
    container_print( umsiTemp );
}

static void unordered_map_out_of_range() {
    UMSI    umsiTemp 
        {
            { "People's Republic of China", 1412600000 }, 
            { "Republic of India", 1375586000 }, 
            { "United States of America", 333291537 }, 
            { "Republic of Indonesia", 275773800 }, 
            { "Islamic Republic of Pakistan", 229489000 }
        };
    container_print( umsiTemp );
    try {
        umsiTemp.at( "Federal Republic of Nigeria") = 216747000;
        container_print( umsiTemp );
    } catch ( out_of_range const& exc ) {
        cout << "   error: out of range" << '\n';
        cout << "   exception: " << exc.what() << '\n';
        container_print( umsiTemp );
    }
}

SECTION(container_unordered_map) {
    SUB_SECTION( unordered_map_simple_construction );
    SUB_SECTION( unordered_map_out_of_range );
    END_SECTION
}
