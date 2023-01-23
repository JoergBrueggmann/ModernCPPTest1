#include "algorithm_all.h"

#include <algorithm>

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

static void algorithm_all_any_none_of( UMSI& rumsiTemp) {
    if (
        all_of( 
            rumsiTemp.cbegin(), 
            rumsiTemp.cend(), 
            []( const std::pair<const string,int>& pairValue ){ return pairValue.first.find( "Republic" ) != string::npos; } )
        ) {
        cout << "All are called republics.\n";
    } else if
        (
            any_of( 
                rumsiTemp.cbegin(), 
                rumsiTemp.cend(), 
                []( const std::pair<const string,int>& pairValue ){ return pairValue.first.find( "Republic" ) != string::npos; })
        ) {
        cout << "Some of them are called republics.\n";
    } else if
        (
            none_of( 
                rumsiTemp.cbegin(), 
                rumsiTemp.cend(), 
                []( const std::pair<const string,int>& pairValue ){ return pairValue.first.find( "Republic" ) != string::npos; })
        ) {
        cout << "None of them are called republics.\n";
    } else {
        cout << "Dirk Gentley: \"This is a thing! Not all, not any nor none are called republics.\"";
    }
    container_print( rumsiTemp );
}

static void algorithm_all_of() {
    UMSI    umsiTemp
        {
            { "People's Republic of China", 1412600000 }, 
            { "Republic of India", 1375586000 }, 
            { "Republic of Indonesia", 275773800 }, 
            { "Islamic Republic of Pakistan", 229489000 }
        };
    algorithm_all_any_none_of( umsiTemp );
}

static void algorithm_any_of() {
    UMSI    umsiTemp
        {
            { "People's Republic of China", 1412600000 }, 
            { "Republic of India", 1375586000 }, 
            { "United States of America", 333291537 }, 
            { "Republic of Indonesia", 275773800 }, 
            { "Islamic Republic of Pakistan", 229489000 }
        };
    algorithm_all_any_none_of( umsiTemp );
}

static void algorithm_none_of() {
    UMSI    umsiTemp
        {
            { "United States of America", 333291537 }
        };
    algorithm_all_any_none_of( umsiTemp );
}

SECTION(algorithm_all) {
    SUB_SECTION( algorithm_all_of );
    SUB_SECTION( algorithm_any_of );
    SUB_SECTION( algorithm_none_of );
    END_SECTION
}
