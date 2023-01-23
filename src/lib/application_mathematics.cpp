#include "application_mathematics.h"

#include "macros.h"

#include <algorithm>
#include <utility>
#include <cassert>

#include <iostream>
using std::cout;

template <class T>
class vector {
    template <class T_>
    friend std::ostream& operator << ( std::ostream& stream, const vector<T_>& mx );

protected:
    std::size_t     mnCountOfElements;
    T*              mpaValue;

public:
    constexpr vector( std::size_t nSize, T xInitial ) noexcept;
    constexpr vector( const std::initializer_list<T> l ) noexcept;
    constexpr vector( const vector<T>& vc ) noexcept;
    virtual ~vector() noexcept;
    constexpr vector& operator = ( const vector<T>& vc ) noexcept;
    constexpr bool operator == ( const vector<T>& vc ) const noexcept;
    virtual std::size_t count_of_elements() const noexcept;
    virtual T& at( std::size_t posIndex );
    virtual const T& at( std::size_t posIndex ) const;
    virtual std::size_t get_index( std::size_t posIndex ) const;
protected:
    virtual void new_array( std::size_t nCountOfElements ) noexcept;
    virtual void delete_array() noexcept;
    virtual void copy_values( const vector<T>& vc ) noexcept;
};

template <class T>
constexpr vector<T>::vector( std::size_t nSize, T xInitial ) noexcept {
std::cout << "vector<T>::vector( std::size_t nSize, T xInitial )\n";
    // -> create new "mpaValue" according to parameter "nSize"
    new_array( nSize );
    // -> initialise all to xInitial
    if ( mpaValue != nullptr ) {
        for ( std::size_t nIndex = 0; nIndex < mnCountOfElements; ++nIndex ) {
            mpaValue[ nIndex ] = xInitial;
        }
    }
}

template <class T>
constexpr vector<T>::vector( const std::initializer_list<T> l ) noexcept {
std::cout << "vector<T>::vector( const std::initializer_list<T> l )\n";
    // -> create new "mpaValue" according to dimension from initialiser list
    new_array( l.size() );
    // -> initialise from initialiser list
    if ( mpaValue != nullptr ) {
        int     nIndex = 0;
        for ( auto xCell : l ) {
            mpaValue[ nIndex ] = xCell;
            nIndex++;
        }
    }
}

template <class T>
vector<T>::~vector() noexcept {
std::cout << "vector<T>::~vector()\n";
    delete_array();
}

template <class T>
constexpr vector<T>::vector( const vector<T>& vc ) noexcept {
std::cout << "vector<T>::vector( const vector<T>& vc )\n";
    // -> create new "mpaValue" according to parameter "vc"
    new_array( vc.count_of_elements() );
    // copy values; do nothing if mpaValue is nullptr
    copy_values( vc );
}

template <class T>
constexpr vector<T>& vector<T>::operator = ( const vector<T>& vc ) noexcept {
std::cout << "vector<T>& vector<T>::operator = ( const vector<T>& vc )\n";
    // check whether the dimensions to be changed
    if ( mnCountOfElements != vc.count_of_elements() ) {
        // re-allocate memory from
        delete_array();
        new_array( vc.count_of_elements() );
    }
    // copy values; do nothing if mpaValue is nullptr
    copy_values( vc );
    return *this;
}

template <class T>
constexpr bool vector<T>::operator == ( const vector<T>& vc ) const noexcept {
    bool    bIsEqual = ( mnCountOfElements == vc.count_of_elements() );
    for ( std::size_t nIndex = 0; bIsEqual && ( nIndex < mnCountOfElements ); ++nIndex ) {
        bIsEqual &= vc.at( nIndex ) == at( nIndex );
    }
    return bIsEqual;
}

template <class T>
std::size_t vector<T>::count_of_elements() const noexcept {
    return mnCountOfElements;
}

template <class T>
T& vector<T>::at( std::size_t posIndex ) {
    return mpaValue[ get_index( posIndex ) ];
}

template <class T>
const T& vector<T>::at( std::size_t posIndex ) const {
    return mpaValue[ get_index( posIndex ) ];
}

template <class T>
std::size_t vector<T>::get_index( std::size_t posIndex ) const {
    if ( mpaValue != nullptr ) {
        if ( posIndex >= mnCountOfElements ) {
            throw std::out_of_range( "In method \"at\", row index of vector is out of range." );
        }
    } else {
        throw std::out_of_range( "In method \"at\", vector is not initialised." );
    }
    return posIndex;
}

template <class T>
void vector<T>::new_array( std::size_t nCountOfElements ) noexcept {
    mpaValue = new (std::nothrow) T[ nCountOfElements ];
    mnCountOfElements = nCountOfElements;
}

template <class T>
void vector<T>::delete_array() noexcept {
    if ( mpaValue != nullptr ) {
        try {
            delete [] mpaValue;
        } catch ( ... ) {
            assert( false );
        }
        mpaValue = nullptr;
    }
    mnCountOfElements = 0;
}

template <class T>
void vector<T>::copy_values( const vector<T>& vc ) noexcept {
    if ( mpaValue != nullptr ) {
        for ( std::size_t nIndex = 0; nIndex < mnCountOfElements; ++nIndex ) {
            mpaValue[ nIndex ] = vc.at( nIndex );
        }
    }
}

template <typename T>
std::ostream& operator << ( std::ostream& stream, const vector<T>& vc )
{
    stream << "{ ";
    for ( std::size_t nIndex = 0; nIndex < vc.mnCountOfElements; ++nIndex ) {
        if ( nIndex != 0 ) {
            stream << ", ";
        }
        stream << vc.at( nIndex );
    }
    stream << " }";
    return stream;
}

template <class T>
class matrix {
    template <typename T_>
    friend std::ostream& operator << ( std::ostream& stream, const matrix<T_>& mx );

protected:
    std::size_t     mnCountOfRows;
    std::size_t     mnCountOfColumns;
    T*              mpaValue;

public:
    constexpr matrix( std::initializer_list<std::initializer_list<T>> l ) noexcept;
    virtual ~matrix() noexcept;
    virtual std::size_t count_of_rows() const noexcept;
    virtual std::size_t count_of_columns() const noexcept;
    virtual T& at( std::size_t posRow, std::size_t posCol );
    virtual const T& at( std::size_t posRow, std::size_t posCol ) const;
    virtual std::size_t get_index( std::size_t posRow, std::size_t posCol ) const;
};

template <typename T>
constexpr matrix<T>::matrix( std::initializer_list<std::initializer_list<T>> l ) noexcept {
    // compute dimension from initialiser list
    mnCountOfRows = l.size();
    mnCountOfColumns = 0;
    for ( auto xRow : l ) {
        mnCountOfColumns = std::max( xRow.size(), mnCountOfColumns );
    }
    // allocate memory from
    mpaValue = new (std::nothrow) T[ mnCountOfRows * mnCountOfColumns ];
    // initialise cells
    if ( mpaValue != nullptr ) {
        std::size_t nRowIndex = 0;
        for ( auto xRow : l ) {
            std::size_t nColIndex = 0;
            for ( auto xCell : xRow ) {
                mpaValue[ ( nRowIndex * mnCountOfColumns ) + nColIndex ] = xCell;
                nColIndex++;
            }
            for ( /*nColIndex = nColIndex */; nColIndex < mnCountOfColumns; nColIndex++ ) {
                mpaValue[ ( nRowIndex * mnCountOfColumns ) + nColIndex ] = 0;
            }
            nRowIndex++;
        }
    }
}

template <typename T>
matrix<T>::~matrix() noexcept {
    if ( mpaValue != nullptr ) {
        try {
            delete [] mpaValue;
        } catch ( ... ) {
            assert( false );
        }
        mpaValue = nullptr;
    }
}

template <typename T>
std::size_t matrix<T>::count_of_rows() const noexcept {
    return mnCountOfRows;
}

template <typename T>
std::size_t matrix<T>::count_of_columns() const noexcept {
    return mnCountOfColumns;
}

template <typename T>
T& matrix<T>::at( std::size_t posRow, std::size_t posCol ) {
    return mpaValue[ get_index( posRow, posCol ) ];
}

template <typename T>
const T& matrix<T>::at( std::size_t posRow, std::size_t posCol ) const {
    return mpaValue[ get_index( posRow, posCol ) ];
}

template <typename T>
std::size_t matrix<T>::get_index( std::size_t posRow, std::size_t posCol ) const {
    if ( mpaValue != nullptr ) {
        if (  posRow >= mnCountOfRows ) {
            throw std::out_of_range( "In method \"at\", row index of matrix is out of range." );
        }
        if ( posCol >= mnCountOfColumns ) {
            throw std::out_of_range( "In method \"at\", column index of matrix is out of range." );
        }
        // std::size_t nIndex = ( posRow * mnCountOfColumns ) + posCol; // for debbugging purposes
        return ( posRow * mnCountOfColumns ) + posCol;
    } else {
        throw std::out_of_range( "In method \"at\", matrix is not initialised." );
    }
}

template <typename T>
std::ostream& operator << ( std::ostream& stream, const matrix<T>& mx )
{
    stream << "\n   {\n      { ";
    for ( std::size_t nRow = 0; nRow < mx.mnCountOfRows; ++nRow ) {
        if ( nRow != 0 ) {
            stream << ",\n      { ";
        }
        for ( std::size_t nCol = 0; nCol < mx.mnCountOfColumns; ++nCol ) {
            if ( nCol != 0 ) {
                stream << ", ";
            }
            stream << mx.at( nRow, nCol );
        }
        stream << " }";
    }
    stream << "\n   }";
    return stream;
}

template <typename T>
vector<T> operator * ( const matrix<T>& mx, const vector<T>& vc ) {     // works with rvalues and lvalues
    vector<T>   vcResult( 3, 0 );
    if ( mx.count_of_rows() == vc.count_of_elements() ) {
        for ( std::size_t nRow = 0; nRow < mx.count_of_rows(); ++nRow ) {
            for ( std::size_t nCol = 0; nCol < mx.count_of_columns(); ++nCol ) {
                vcResult.at( nRow ) += mx.at( nRow, nCol ) * vc.at( nRow );
            }
        }
        return vcResult;
    } else {
        throw std::runtime_error( "In multiplication of matrix by vector, the matrix's count of rows is not equal to vector elements." );
    }
}

void application_mathematics_simple() {
    matrix<double>  mxA { { 2, 4.3, 3 }, { 4, 0, 8 }, { 1, 3, 0 } };    // using the initialiser list constructor
    vector<double>  vcB{ 2, 4, 5 };                                     // using the initialiser list constructor
    vector<double>  vcB2 = vcB;                                         // forcing to use the copy constructor
    vcB2.at( 1 ) = 3;
    vcB = vcB2;                                                         // forcing to use the copy operator
    mxA.at( 0, 1 ) = 5.3;
    cout << "mxA = " << mxA << '\n';
    cout << "vcB = \n   " << vcB << '\n';
    cout << "vcB2 = \n   " << vcB2 << '\n';
    vector<double> vcResult1 = mxA                                                       * vcB;     // operator * creates result vector using this initialising constructor ("vector<T>::vector( std::size_t nSize, T xInitial )")
    cout << "vcResult1 = \n   " << vcResult1 << '\n';
    vector<double> vcResult2 = matrix<double>{ { 2, 5.3, 3 }, { 4, 0, 8 }, { 1, 3, 0 } } * vcB;     // operator * creates ... as above, and in all 4 cases
    cout << "vcResult2 = \n   " << vcResult2 << '\n';
    vector<double> vcResult3 = matrix<double>{ { 2, 5.3, 3 }, { 4, 0, 8 }, { 1, 3, 0 } } * vector<double>{ 2, 3, 5 };   // ...and in all cases return value optimisation ("RVO ")...
    cout << "vcResult3 = \n   " << vcResult3 << '\n';
    vector<double> vcResult4 = mxA                                                       * vector<double>{ 2, 3, 5 };   // ...reuses the ressources
    cout << "vcResult4 = \n   " << vcResult4 << '\n';
    assert( vcResult1 == vcResult2 );
    assert( vcResult2 == vcResult3 );
    assert( vcResult3 == vcResult4 );
    assert( vcResult4 == vcResult1 );
}

SECTION(application_mathematics) {
    SUB_SECTION( application_mathematics_simple );
    END_SECTION
}
