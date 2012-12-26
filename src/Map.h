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
    void drawMapLayer( char *layerName, ViewPort &cam );

    // Get/Set map's id
    int getId();
    void setId( int id );

    // Get/Set map's width
    int getWidth();
    void setWidth( int width );

    // Get/Set map's height
    int getHeight();
    void setHeight( int height );

private:
    int m_mapId;

    std::vector <CTile> m_tileset;

    ALLEGRO_MAP *m_map;

    int m_width;

    int m_height;

    int m_numLayers;
};

#endif // MAP_H
