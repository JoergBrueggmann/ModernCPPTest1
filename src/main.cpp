
#include "item6.h"
#include "tile_edges.h"
#include "container_vector.h"
#include "container_array.h"
#include "container_deque.h"
#include "container_forward_list.h"
#include "container_unordered_map.h"
#include "algorithm_all.h"
#include "class_template.h"
#include "specifier_constexpr.h"
#include "specifier_explicit.h"
#include "specifier_decltype.h"
#include "application_mathematics.h"
#include "scoped_enums.h"
#include "xfunction.h"
#include "rvo_or_copy_elision.h"


int main( [[maybe_unused]] int argc, [[maybe_unused]] char *argv[] )
{
    int     nReturn = 0;

    try
    {
        /*item6();
        tile_edges();
        container_vector();
        container_array();
        container_deque();
        container_forward_list();
        container_unordered_map();
        algorithm_all();
        class_template();
        specifier_constexpr();
        specifier_explicit();
        specifier_decltype();
        application_mathematics();
        scoped_enums();
        xfunction();*/
        rvo_or_copy_elision();
    }
    catch ( ... )
    {
        nReturn = -1;
    }
    return nReturn;
}
