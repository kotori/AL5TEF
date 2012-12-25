#ifndef MAP_H
#define MAP_H

#include "Util.h"
#include "Tile.h"

class CMap
{
public:
    // Class constructor.
    CMap();

    // Class constructor with ID override.
    CMap( int id );

    // Class destructor.
    ~CMap();

    // Build our map from a loaded file.
    int loadMap( const char *filename );

    // Draw the map to the screen.
    void drawMap( int layer );

private:
    int m_mapId;

    std::vector <CTile> m_tileset;

    ALLEGRO_MAP *m_map;

    int m_width;

    int m_height;
};

#endif // MAP_H
