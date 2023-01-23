#include "rvo_or_copy_elision.h"

#include <iostream>
using std::cout;

#include <initializer_list>
using std::initializer_list;

class Fruit {
public:
    int     man[5];
    Fruit( std::initializer_list<int> ln ) {
        cout << "         construct Fruit - #1\n";
        int nIndex = 0;
        cout << "         construct Fruit - #2\n";
        for ( auto n : ln ) {
            cout << "         construct Fruit - #3\n";
            man[nIndex] = n;
            nIndex++;
        }
        cout << "         construct Fruit - #4\n";
    }
    virtual ~Fruit() {
        cout << "         destruct Fruit\n";
    }
};

class Durian : public Fruit {
public:
    double  msmell;
    Durian( std::initializer_list<int> ln, double smell ) : Fruit{ ln }, msmell { smell } {
        cout << "         construct Durian\n";
    }
    virtual ~Durian() {
        cout << "         destruct Durian\n";
    }
};

Fruit slapChop() {
    cout << "      slapChop - #1\n";
    Durian  d{ { 1, 2, 3, 4, 5 }, 5.3 };
    cout << "      slapChop - #2\n";
    return d;
}

class RVOTestClass
{
public:
    int     mn;
 
    explicit RVOTestClass( int n ) : mn { n } {
        // mn = n; // alternative way to contruct
        cout << "construct RVOTestClass( " << n << " )\n";
    }

    RVOTestClass( const RVOTestClass& rvoToCopy ) : mn { rvoToCopy.mn } {
        // mn = rvoToCopy.mn; // alternative way to copy
        cout << "copy RVOTestClass( " << rvoToCopy.mn << " )\n";
    }
};

RVOTestClass    makeRVOObject( int n ) {
    return RVOTestClass( n );
}

RVOTestClass    makeRVOObjectWithDoubledValue( int n ) {
    RVOTestClass    rvo = makeRVOObject( n );
    rvo.mn = 2 * n;
    return rvo;
}

void rvo_or_copy_elision() {
    cout << "########################\n";
    RVOTestClass    rvo = makeRVOObjectWithDoubledValue( 21 );
    cout << "__cpp_guaranteed_copy_elision = " << __cpp_guaranteed_copy_elision << '\n';
    cout << "rvo.mn = " << rvo.mn << '\n';
    cout << "########################\n";
    cout << "   rvo_or_copy_elision - #1\n";
    Fruit   f = slapChop();
    cout << "   rvo_or_copy_elision - #2\n";
    for ( int i = 0; i < 5; ++i ) {
        cout << "   f.man[" << i << "] = " << f.man[i] << '\n';
    }
    cout << "   rvo_or_copy_elision - #3\n";
}
