
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
int CMap::loadMap( const char *filename, std::vector< std::vector <int> > &map )
{
    int rowCounter = 0;
    int numRows = 0;
    int tileCounter = 0;
    m_loadState = 0;
    int prevState = m_loadState;
    bool firstPass = true;
    CTile *tempTile;

    std::ifstream openfile( filename );
	if( openfile.is_open() )
	{
	    std::string line;
        std::string value;
	    bool layerDone = false;

		while( !openfile.eof() )
		{
			std::getline( openfile, line );

			if( line.find( "[TileSet]") != std::string::npos)
			{
				m_loadState = LoadState::TileSet;
				continue;
			}
			else if ( line.find( "[Layer]") != std::string::npos)
			{
			    prevState = m_loadState;
				m_loadState = LoadState::Layer;
				layerDone = false;
				if( !firstPass )
				{
				    rowCounter++;
				}
				firstPass = false;
				continue;
			}

			switch( m_loadState )
			{
			case LoadState::TileSet:
				if( line.length() > 0 )
				{
                    ALLEGRO_PATH *path = al_get_standard_path( ALLEGRO_RESOURCES_PATH );
                    al_append_path_component( path, "resources/Maps/tiles" );
                    al_set_path_filename( path, line.c_str() );

                    m_tileSet = al_load_bitmap( al_path_cstr( path, '/' ) );
                    al_destroy_path( path );

				    if( !m_tileSet )
				    {
				        std::cerr << "[ERROR] Tileset loading failed, missing: " << line.c_str() << std::endl;
				        return -1;
				    }
				}

				break;
			case LoadState::Layer:
				std::stringstream str( line );
				// CURRENTLY, THIS CODE LOADS MULTIPLE LAYERS,
				//  OVERWRITING THE PREVIOUS, THIS NEEDS TO BE FIXED!
				tempTile = new CTile();
                std::vector<int> tempVector;

				while( !str.eof() )
				{
					std::getline( str, value, ' ' );
					if( value.length() > 0 )
					{
                        // Insert the value from the textfile into the tempVector.
                        int val = atoi( value.c_str() );
                        tempVector.push_back( val );
                        // Set this tile's ID to match the pulled mapfile value.
                        tempTile->setId( val );
                        //m_map[tileCounter].push_back( tempTile );
                        tileCounter++;
					}
				}
				layer1.push_back( tempVector );
				layerDone = true;
				numRows++;
				break;
			}
		}
		if( DEBUGGING_MODE )
		{
		    std::cerr << "Map Loaded!" << std::endl;
		    std::cerr << "Dumping Map..." << std::endl;
            drawMapDebug();
		}
	}
	else
	{
	    std::cerr << "[ERROR] Map loading failure, missing: " << filename << std::endl;
        return -1;
	}



	return 0;
}

void CMap::drawMapLayer1( )
{
    for( unsigned int i = 0; i < layer1.size(); i++ )
    {
        for( unsigned int j = 0; j < layer1[i].size(); j++ )
        {
            al_draw_bitmap_region( m_tileSet , layer1[i][j] * BlockSize, 0,
                BlockSize, 32, j * BlockSize, i * BlockSize, 0 );
        }
    }
}

void CMap::drawMapLayer2( )
{
    for( unsigned int i = 0; i < layer2.size(); i++ )
    {
        for( unsigned int j = 0; j < layer2[i].size(); j++ )
        {
            al_draw_bitmap_region( m_tileSet , layer2[i][j] * BlockSize, 0,
                BlockSize, 32, j * BlockSize, i * BlockSize, 0 );
        }
    }
}

void CMap::drawMapLayer3( )
{
    for( unsigned int i = 0; i < layer3.size(); i++ )
    {
        for( unsigned int j = 0; j < layer3[i].size(); j++ )
        {
            al_draw_bitmap_region( m_tileSet , layer3[i][j] * BlockSize, 0,
                BlockSize, 32, j * BlockSize, i * BlockSize, 0 );
        }
    }
}

void CMap::drawMapDebug()
{
    for( unsigned int i = 0; i < layer1.size(); i++ )
    {
        for( unsigned int j = 0; j < layer1[i].size(); j++ )
        {
            std::cerr << layer1[i][j] << " ";
        }
        std::cerr << std::endl;
    }
}
