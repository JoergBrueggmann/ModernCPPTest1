#include "container_vector.h"

#include "container_helper.h"
#include "macros.h"

#include <vector>
#include <iostream>

using VB = std::vector<bool>;

static int from_vector( VB vbIn ) {
    int     nResult = 0;
    while ( ! vbIn.empty() ) {
        nResult <<= 1;
        nResult += vbIn.back() ? 1 : 0;
        vbIn.pop_back();
    }
    return nResult;
}

static VB from_int( int nIn ) {
    VB    vbResult;
    while ( nIn != 0 ) {
        auto it = vbResult.begin();
        vbResult.insert( it, ( ( nIn % 2 ) != 0) ? true : false );
        nIn >>= 1;
    }
    return vbResult;
}

static void print_vector( VB vbIn ) {
    container_print( vbIn );
    std::cout << "vb = " << from_vector( vbIn ) << '\n';
}

static void vector_simple_construction() {
    VB    vbTemp{ true, false };
    print_vector( vbTemp );
}

static void vector_assignment_and_push_back() {
    VB    vbTemp;
    vbTemp = VB{ true, false, true };
    vbTemp.push_back( false );
    vbTemp.push_back( true );
    print_vector( vbTemp );
}

static void vector_insert() {
    VB    vbTemp;
    vbTemp = from_int( 31 );
    print_vector( vbTemp );
}

static void vector_emplace() {
    struct A {
        std::string s;
        A(std::string str) : s(std::move(str))  { std::cout << " constructed\n"; }
        A(const A& o) : s(o.s) { std::cout << " copy constructed\n"; }
        A(A&& o) : s(std::move(o.s)) { std::cout << " move constructed\n"; }
        A& operator=(const A& other) {
            s = other.s;
            std::cout << " copy assigned\n";
            return *this;
        }
        A& operator=(A&& other) {
            s = std::move(other.s);
            std::cout << " move assigned\n";
            return *this;
        }
    };

    std::vector<A> container;
    // reserve enough place so vector does not have to resize
    container.reserve(10);
    std::cout << "construct 2 times A:\n";
    A two { "two" };
    A three { "three" };
 
    std::cout << "emplace:\n";
    container.emplace(container.end(), "one");
 
    std::cout << "emplace with A&:\n";
    container.emplace(container.end(), two);
 
    std::cout << "emplace with A&&:\n";
    container.emplace(container.end(), std::move(three));

    std::cout << "content:\n";
    for (const auto& obj : container)
        std::cout << ' ' << obj.s;
    std::cout << '\n';
}

SECTION(container_vector) {
    SUB_SECTION( vector_simple_construction );
    SUB_SECTION( vector_assignment_and_push_back );
    SUB_SECTION( vector_insert );
    SUB_SECTION( vector_emplace );
    END_SECTION
}
