#include "container_deque.h"

#include "container_helper.h"
#include "macros.h"

#include <iostream>
#include <stdexcept>
#include <deque>
#include <string>
#include <cassert>

using std::out_of_range;
using std::cout;
using std::string;

using QN = std::deque<int>;
using QS = std::deque<string>;

static void deque_simple_construction() {
    QN  qnTemp{ 12, 23, 34, 45 };
    container_print( qnTemp );
}

static void deque_out_of_range() {
    QN  qnTemp{ 12, 23, 34, 45 };
    try {
        qnTemp.at(3) = true;
        qnTemp.at(4) = true;
        qnTemp.at(5) = true;
        container_print( qnTemp );
    } catch ( out_of_range const& exc ) {
        cout << "   error: out of range" << '\n';
        cout << "   exception: " << exc.what() << '\n';
        container_print( qnTemp );
    }
}

static void deque_push_back() {
    QN  qnTemp{ 12, 23 };
    qnTemp.push_back( 34 );
    qnTemp.push_back( std::move( 45 ) );
    container_print( qnTemp );
    QS  qsTemp{ "-12-", "-23-" };
    qsTemp.push_back( "-34*-" );
    qsTemp.push_back( std::move( "-45*-" ) );
    container_print( qsTemp );
}

struct President
{
    std::string name;
    std::string country;
    int year;
 
    President(std::string p_name, std::string p_country, int p_year)
        : name(std::move(p_name)), country(std::move(p_country)), year(p_year)
    {
        std::cout << "I (" << this << ") am being constructed.\n";
    }
    President(President&& other)
        : name(std::move(other.name)), country(std::move(other.country)), year(other.year)
    {
        std::cout << "I (" << this << ") am being moved.\n";
    }
    President& operator = (const President& other) = default;
};

static void deque_emplace_back() {
    std::deque<President> elections;
    std::cout << "emplace_back:\n";
    auto& ref = elections.emplace_back("Nelson Mandela", "South Africa", 1994);
    assert(ref.year == 1994 && "uses a reference to the created object (C++17)");
 
    std::deque<President> reElections;
    std::cout << "push_back:\n";
    reElections.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));
 
    std::cout << "Contents:\n";
    std::cout << "   Elections:\n";
    for (President const& president: elections) {
        std::cout << "      (" << (&president) << ")" << president.name << " was elected president of "
                  << president.country << " in " << president.year << ".\n";
    }
    std::cout << "   Re-elections:\n";
    for (President const& president: reElections) {
        std::cout << "      (" << (&president) << ")" << president.name << " was re-elected president of "
                  << president.country << " in " << president.year << ".\n";
    }
}

SECTION(container_deque) {
    SUB_SECTION( deque_simple_construction );
    SUB_SECTION( deque_out_of_range );
    SUB_SECTION( deque_push_back );
    SUB_SECTION( deque_emplace_back );
    END_SECTION
}
