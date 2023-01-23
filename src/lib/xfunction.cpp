#include "xfunction.h"

/*
#include <array>
using AB = std::array<bool, 10>;
#include <deque>
using QN = std::deque<int>;
using QS = std::deque<string>;
#include <unordered_map>
#include <forward_list>

#include <string>
using std::string;

#include <algorithm>
#include <utility>

#include <cassert>
#include <stdexcept>
using std::out_of_range;

#include <ostream>
*/

#include <vector>
using std::vector;
#include <string>
using std::string;

#include <iostream>
using std::cout;

#include "macros.h"

template <typename T>
std::ostream& operator << ( std::ostream& stream, const vector<T>& vc )
{
    stream << "{ ";
    for ( std::size_t nIndex = 0; nIndex < vc.size(); ++nIndex ) {
        if ( nIndex != 0 ) {
            stream << ", ";
        }
        stream << vc.at( nIndex );
        stream << "(";
        stream << static_cast<const void*>(vc.at( nIndex ).data());
        stream << ")";
    }
    stream << " }";
    return stream;
}

void printVVS( string sName, const vector<vector<string>>& vvs) {
    cout << sName << " = ";
    cout << vvs << "\n";
}

void xfunction_simple() {
    vector<vector<string>>     vvs;

    vvs.push_back( vector<string>{ string{"a1"}, string{"a2"}, string{"a3"} } );
    vvs.push_back( vector<string>{ "b1", "b3" } );
    vvs.push_back( vector<string>{ "d1", "d2", "d3", "d4" } );

    printVVS( "vvs", vvs );

    auto    itVS = vvs.at( 1 ).cbegin();
    itVS++;
    vvs.at( 1 ).insert( itVS, "b2" );

    printVVS( "vvs", vvs );

    auto    itVVS = vvs.cbegin();
    itVVS++;
    itVVS++;
    vvs.insert( itVVS, { "c1", "c2", "c3" } );

    printVVS( "vvs", vvs );
}

SECTION(xfunction) {
    SUB_SECTION( xfunction_simple );
    END_SECTION
}
