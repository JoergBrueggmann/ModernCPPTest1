#include "container_forward_list.h"

#include "container_helper.h"
#include "macros.h"

#include <forward_list>
#include <string>
#include <array>

using std::string;

using FLS = std::forward_list<string>;

static void forward_list_simple_construction() {
    FLS  flsTemp{ "menopl", "jokl", "mniqstufixz", "abcdef" };
    container_print( flsTemp );
}

static void forward_list_sort() {
    FLS  flsTemp{ "menopl", "jokl", "mniqstufixz", "abcdef" };
    flsTemp.sort();
    container_print( flsTemp );
}

static void forward_list_merge() {
    FLS  flsTemp{ "menopl", "jokl", "mniqstufixz", "abcdef" };
    FLS  flsTemp2{ "manuscript", "jabber", "monastery", "apple pie" };
    flsTemp.sort();
    flsTemp2.sort();
    flsTemp.merge(flsTemp2);
    container_print( flsTemp );
    container_print( flsTemp2 );
}

static void forward_list_merge_unsorted() {
    FLS  flsTemp{ "menopl", "jokl", "mniqstufixz", "abcdef" };
    FLS  flsTemp2{ "manuscript", "jabber", "monastery", "apple pie" };
    flsTemp.merge(flsTemp2);
    container_print( flsTemp );
    container_print( flsTemp2 );
}

static void forward_list_remove() {
    FLS  flsTemp{ "abcdef", "apple pie", "jabber", "jokl", "manuscript", "menopl", "mniqstufixz", "monastery" };
    container_print( flsTemp );
    flsTemp.remove( "jabber" );
    container_print( flsTemp );
}

static void forward_list_remove_if() {
    FLS  flsTemp{ "abcdef", "apple pie", "jabber", "jokl", "manuscript", "menopl", "mniqstufixz", "monastery" };
    container_print( flsTemp );
    flsTemp.remove_if( []( string s ){ return s.compare( "jerome" ) > 0; } );
    container_print( flsTemp );
}

static void forward_list_unique() {
    FLS  flsTemp{ "manuscript", "jabber", "menopl", "jokl", "mniqstufixz", "abcdef", "menopl", "monastery", "apple pie" };
    flsTemp.sort();
    container_print( flsTemp );
    flsTemp.unique();
    container_print( flsTemp );
}

static void forward_list_unique_unsorted() {
    FLS  flsTemp{ "manuscript", "jabber", "menopl", "jokl", "mniqstufixz", "abcdef", "menopl", "monastery", "apple pie" };
    container_print( flsTemp );
    flsTemp.unique();
    container_print( flsTemp );
}

static void forward_list_reverse() {
    FLS  flsTemp{ "abcdef", "apple pie", "jabber", "jokl", "manuscript", "menopl", "mniqstufixz", "monastery" };
    container_print( flsTemp );
    flsTemp.reverse();
    container_print( flsTemp );
}

static void forward_list_splice_after() {
    FLS  flsTemp{ "abcdef", "jokl", "menopl", "mniqstufixz" };
    FLS  flsTemp2{ "apple pie", "jabber", "manuscript", "monastery" };
    container_print( flsTemp );
    container_print( flsTemp2 );
    flsTemp.splice_after( flsTemp2.cbegin(), flsTemp, flsTemp.cbegin(), flsTemp.cend() );
    container_print( flsTemp );
    container_print( flsTemp2 );
}

static void forward_list_deduction_guides() {
    using A4S = std::array< string, 4 >;
    A4S     asTemp{ "abcdef", "jokl", "menopl", "mniqstufixz" };
    FLS     flsTemp( asTemp.begin(), asTemp.end() );
    container_print( flsTemp );
}

SECTION(container_forward_list) {
    SUB_SECTION( forward_list_simple_construction );
    SUB_SECTION( forward_list_sort );
    SUB_SECTION( forward_list_merge );
    SUB_SECTION( forward_list_merge_unsorted );
    SUB_SECTION( forward_list_remove );
    SUB_SECTION( forward_list_remove_if );
    SUB_SECTION( forward_list_unique );
    SUB_SECTION( forward_list_unique_unsorted );
    SUB_SECTION( forward_list_reverse );
    SUB_SECTION( forward_list_splice_after );
    SUB_SECTION( forward_list_deduction_guides );
    END_SECTION
}
