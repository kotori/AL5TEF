
#include "Util.h"
#include "Map.h"

CMap::CMap()
{
    //
}

CMap::CMap( int id )
{
    m_mapId = id;
}

CMap::~CMap()
{
    //
}

// This is a WIP
//  loadmap( const char*, std::vector< std::vector <int> > )
//  Loads a map and tileset from file, and builds a map from these values.
//  the 'map' object referenced will contain a fully built map.
int CMap::loadMap( const char *filename )
{
    m_map = al_open_map("Maps", "level1.tmx");
    if( !m_map )
    {
        std::cerr << "Failed loading mapfile: " << filename << std::endl;
        return -1;
    }
    return 0;
}

void CMap::drawMap( int layer )
{
    /*
     * Draw the whole layer to the target backbuffer at the given location.
     * Map Object, layer Name, x position, y position, FLAGS
     * void al_draw_tile_layer_for_name( m_map, char *name, float dx, float dy, 0 )
     */
    // al_draw_map_region( m_map, map_x, map_y, screen_width, screen_height, 0, 0, 0 );
}
