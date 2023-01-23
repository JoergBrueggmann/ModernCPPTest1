#ifndef container_helper_h
#define container_helper_h

#include <string>
#include <utility>

void container_print_prologue();
void container_print_seperator();
void container_print_epilogue();

template<class TValue>
void container_print_value( const TValue& value );

template <> void container_print_value<int>( const int& nValue);
template <> void container_print_value<bool>( const bool& nValue);
template <> void container_print_value<std::string>( const std::string& nValue);
template <> void container_print_value<std::pair<const std::string,int>>( const std::pair<const std::string,int>& nValue);

template<class TContainer>
void container_print( const TContainer& c ) {
    bool    bNotFirst = false;
    container_print_prologue();
    for (auto value : c )
    {
        if ( bNotFirst ) {
            container_print_seperator();
        }
        container_print_value( value );
        bNotFirst = true;
    }
    container_print_epilogue();
}

#endif // container_helper_h
