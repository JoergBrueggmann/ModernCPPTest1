#include "tile_edges.h"

#include <vector>
#include <iostream>

static const int    gnCountTiles = 4;
static const int    gnMaxTiles = gnCountTiles - 1;

void set_edges( std::vector<std::vector<bool>>& tiles )
{
    for ( int x = 0; x < gnCountTiles; x++ )
    {
        for ( int y = 0; y < gnCountTiles; y++ )
        {
            tiles.at(x).at(y) = ( x == 0 ) || ( x == gnMaxTiles ) || ( y == 0 ) || ( y == gnMaxTiles );
        }
    }
}

void tile_edges() {
    std::cout << '\n';
    std::cout << "------------------------------" << '\n';
    std::cout << "tile_edges" << '\n';
    std::vector<std::vector<bool>>  tiles( gnCountTiles, std::vector<bool>( gnCountTiles ));
    set_edges(tiles);
    for ( std::vector<bool> row : tiles )
    {
        for ( bool bValue : row )
        {
            std::cout << bValue;
        }
        std::cout << '\n';
    }
}
