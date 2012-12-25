
#include "Util.h"
#include "Map.h"

CMap::CMap()
{
    m_mapId = 0;
    m_width = 0;
    m_height = 0;
}

CMap::CMap( int id )
{
    m_mapId = id;
    m_width = 0;
    m_height = 0;
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
    m_map = al_open_map( "Maps", filename );
    if( !m_map )
    {
        std::cerr << "Failed loading mapfile: " << filename << std::endl;
        return -1;
    }

    // Now that we've loaded our map, we can grab some basic values.

    // Set the map's total width.
    m_width = al_get_map_width( m_map ) * al_get_tile_width( m_map );

    // Set the map's total height.
    m_height = al_get_map_height( m_map ) * al_get_tile_height( m_map );

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

// Get/Set map's id
int CMap::getId()
{
    return m_mapId;
}

void CMap::setId( int id )
{
    m_mapId = id;
}

// Get/Set map's width
int CMap::getWidth()
{
    return m_width;
}

void CMap::setWidth( int width )
{
    m_width = width;
}

// Get/Set map's height
int CMap::getHeight()
{
    return m_height;
}

void CMap::setHeight( int height )
{
    m_height = height;
}
