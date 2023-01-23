#include "class_template.h"

#include "macros.h"

#include <string>
using std::string;

#include <algorithm>
using std::transform;
using std::plus;

#include <iostream>
using std::cout;

using std::move;

A::A()
{
    cout << "A::A()\n";
}

A::A( const A& a )
{
    cout << "A::A( const A& a )\n";
    msA = a.msA;
}

A::~A()
{
    cout << "A::~A()\n";
}

A& A::operator = ( const A& a )
{
    cout << "A& A::operator = ( const A& a )\n";
    msA = a.msA;
    return *this;
}

void A::Method1( const A& a )
{
    cout << "void A::Method1( const A& a )\n";
    ProtectedMethod2( ProtectedMethod1() + a.ProtectedMethod1() );
}

string A::ProtectedMethod1() const
{
    cout << "string A::ProtectedMethod1() const\n";
    return msA;
}

void A::ProtectedMethod2( string sA )
{
    cout << "void A::ProtectedMethod2( string sA )\n";
    msA = sA;
}

BA::BA()
{
    cout << "BA::BA()\n";
}

BA::BA( string sA, int nB0, int nB1, int nB2 )
{
    cout << "BA::BA( string sA, int nB0, int nB1, int nB2 )\n";
    msA = sA;
    mvn = VN{ nB0, nB1, nB2};
}

BA::BA( const BA& b )
    : A( b )        // copy of class A specific part
{
    cout << "BA::BA( const BA& b )\n";
    mvn = b.mvn;    // copy of class BA specific part (without class A specific part)
}

BA::~BA()
{
    cout << "BA::~BA()\n";
}

BA& BA::operator = ( const BA& b )
{
    cout << "BA& BA::operator = ( const BA& b )\n";
    A::operator=( b );  // copy of class A specific part
    mvn = b.mvn;        // copy of class BA specific part (without class A specific part)
    return *this;
}

BA::BA( BA&& b )
    : A( b )            // copy of class A specific part, becouse move semantic is not supported
{
    cout << "BA::BA( BA&& b )\n";
    mvn = move(mvn);    // assignment according to move semantics; move casts mvn to an rvalue
}

BA& BA::operator = ( BA&& b )
{
    cout << "BA& BA::operator = ( BA&& b )\n";
    A::operator=( b );
    mvn = move(mvn);    // assignment according to move semantics; move casts mvn to an rvalue
    return *this;
}

void BA::Method1( const BA& b )
{
    cout << "void BA::Method1( const BA& b )\n";
    A::Method1( b ) ;                                                                                           // apply Method1 for part of call A
    VN vnA = ProtectedMethod3();                                                                                // take a copy of vector mvn
    const VN& vnB = b.ProtectedMethod3();                                                                       // take a reference of vector mvn
    transform ( vnA.begin(), vnA.end(), vnB.begin(), vnA.begin(), plus<int>() );                                // transform copy vnA
    //transform ( vnA.begin(), vnA.end(), vnB.begin(), vnA.begin(), []( auto nA, auto nB ){ return nA + nB; } );    // transform copy vnA, using a lambda function
    ProtectedMethod4( move(vnA) );                                                                              // reassign temporary transformed copy
}

const VN& BA::ProtectedMethod3() const
{
    cout << "int BA::ProtectedMethod3() const\n";
    return mvn;
}

void BA::ProtectedMethod4( VN&& vnB )
{
    cout << "void BA::ProtectedMethod4( int nB )\n";
    mvn = move(vnB);
}

void Function1( const BA& ba, string& rsA, VN& rvnB )
{
    cout << "void Function1( const BA& ba, string& rsA, VN& rvnB )\n";
    rsA = ba.ProtectedMethod1();
    rvnB = ba.ProtectedMethod3();
}

ostream& operator<< ( ostream& stream, const BA& ba )
{
    stream << "{ \"" << ba.msA << "\", { ";
    bool    bFirst = true;
    for ( auto n : ba.mvn ) {
        if ( bFirst ) {
            stream << n;
            bFirst = false;
        } else {
            stream << ", " << n;
        }
    }
    stream << " } }";
    return stream;
}

void class_template_ab()
{
    BA  baJohn{ "John", 7, 11, 13 };
    BA  baJohnKarl{ baJohn };
    BA  baKarl( "Karl", 17, 19, 23 );
    BA  baRob;

    cout << baJohn << '\n';
    cout << baJohnKarl << '\n';
    cout << baKarl << '\n';
    cout << baRob << '\n';
    baJohnKarl.Method1( baKarl );
    baRob = BA{ "Rob", 27, 29, 31 };
    cout << baJohn << '\n';
    cout << baJohnKarl << '\n';
    cout << baKarl << '\n';
    cout << baRob << '\n';
}

SECTION(class_template) {
    SUB_SECTION( class_template_ab );
    END_SECTION
}
