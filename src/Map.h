#ifndef MAP_H
#define MAP_H

#include "Util.h"
#include "Tile.h"

class CMap
{
public:
    // Class constructor.
    CMap();
    CMap( int id );
    // Class destructor.
    ~CMap();

    // Build our map from a loaded file.
    int loadMap( const char *filename, std::vector< std::vector <int> > &map );

    // Draw the map to the screen.
    void drawMap();
    void drawMapLayer1();
    void drawMapLayer2();
    void drawMapLayer3();
    void drawMapDebug();
    // Draw the map to the screen starting at x and y.
    //void drawMap( int x, int y );

private:
    int m_mapId;
    std::vector<std::vector <CTile> > m_map;

    std::vector < std::vector <int> > layer1;
    std::vector < std::vector <int> > layer2;
    std::vector < std::vector <int> > layer3;
    std::vector < std::vector <int> > layer4;

    std::vector < std::vector <std::vector <int> > > m_completeMap;

    int m_loadState;
    ALLEGRO_BITMAP *m_tileSet;
};

#endif // MAP_H
