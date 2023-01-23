#ifndef class_template_h
#define class_template_h

#include <string>
#include <vector>
#include <ostream>

using std::string;
using std::vector;
using std::ostream;
using VN = vector<int>;

class A
{
// attributes
public:
    string      msA;

// constructor / destructor / copy
public:
    A();                            // default constructor
    // rule of three
    A( const A& a );                // 1. copy constructor
    virtual ~A();                   // 2. destructor
    A& operator = ( const A& a );   // 3. copy operator

// operation
public:
    virtual void Method1( const A& a );

protected:
// internal operation
    virtual string ProtectedMethod1() const;
    virtual void ProtectedMethod2( string sA );
};

class BA : public A
{
    friend void Function1( const BA& ba, string& rsA, VN& rvnB );
    friend ostream& operator << ( ostream& stream, const BA& ba );

// attributes
public:
    VN     mvn;

// constructor / destructor
public:
    BA();                                       // default constructor
    BA( string sA, int nB0, int nB1, int nB2 ); // constructor
    // rule of five
    BA( const BA& a );                          // 1. copy constructor
    virtual ~BA() override;                     // 2. destructor
    BA& operator = ( const BA& a );             // 3. copy operator
    BA( BA&& a );                               // 4. move constructor (move semantics)
    BA& operator = ( BA&& a );                  // 5. move assignment operator (move semantics)
    // NOTE: The type BA&& is a forwarding reference (universal reference according to steve )

// operation
public:
    virtual void Method1( const BA& b );

protected:
// internal operation
    virtual const VN& ProtectedMethod3() const;
    virtual void ProtectedMethod4( VN&& vnB );
};

void class_template();

#endif // class_template_h
