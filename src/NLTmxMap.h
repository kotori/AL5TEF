/**
 * \file NLTmxMap.h
 * \author Tomas Andrle (Copyright © 2006 - 2012 Tomas Andrle - Catnap Games)
 * \version 0.0.1
 *  Integrate Allegro objects into the map loading classes. (rev. Kotori)
 *
 * The NLTmxMap classes provide an easy way to load and display Tiled TMX maps.
 *  This loading library only supports CSV formats, currently no base64/gzip support.
 */
#pragma once

// Also included for compiler optimization.
#ifndef NLTMX_MAP_H_INC
#define NLTMX_MAP_H_INC

#include <string>
#include <vector>

/**
 * \class NLTmxMapTileset
 * \details Provides a means for arranging map tilesets.
 */
class NLTmxMapTileset
{
public:
    int firstGid;		/**< Tileset's firstgid. */
    std::string name;		/**< Tileset's name. */
    int tileWidth;		/**< Tileset's width in pixels. */
    int tileHeight;		/**< Tileset's height in pixels. */
    std::string filename;	/**< Tileset's name on the filesystem. */
};

/**
 * \class NLTmxMapLayer
 * \details Provides a map layer object for storing individual tiles.
 */
class NLTmxMapLayer
{
public:
    std::string name;		/**< Map layer's name in string format. */
    int width;			/**< Map layer's width in pixels. */
    int height;			/**< Map layer's height in pixels. */
    int* data;			/**< Map layer's datafield, (ints). */

    /**
     * \fn ~NLTmxMapLayer()
     * \details class destructor.
     */
    ~NLTmxMapLayer()
    {
        delete[] data;
    }
};

/**
 * \struct NLTmxMapObjectProperty
 * \details Provides a method for storing map property values.
 */
struct NLTmxMapObjectProperty
{
    std::string name;	/**< Map property name in std::string format. */
    std::string value;	/**< Map property value in std::string format. */
};

/**
 * \class NLTmxMapObject
 * \details Provides a means for creating a map of individual tiles.
 * \see NLTmxMapObjectProperty
 */
class NLTmxMapObject
{
public:
    std::string name;		/**< Map object's name in string format. */
    int gid;			/**< Map object's global identifier string. */
    int x;			/**< Map object's x-coordinate location. */
    int y;			/**< Map object's y-coordinate location. */
    int width;			/**< Map object's width in pixels. */
    int height;			/**< Map object's height in pixels. */

    vector<NLTmxMapObjectProperty*> properties;	/**< Map object's property list. */

public:
    /**
     * \fn ~NLTmxMapObject()
     * \details class destructor.
     */
    ~NLTmxMapObject()
    {
        for ( auto property : properties )
        {
            delete property;
        }
    }
};

/**
 * \class NLTmxMapObjectGroup
 * \details Provides the means for storing individual map objects.
 * \see NLTmxMapObject
 */
class NLTmxMapObjectGroup
{
public:
    std::string name;		/**< Map object group's name in string format. */
    int width;			/**< Map object group's width in pixels. */
    int height;			/**< Map object group's height in pixels. */
    bool visible;		/**< Map object group's visibility flag. */

    std::vector<NLTmxMapObject*> objects;	/**< Vector containing a collection of NLTmxMapObject. */

    /**
     * NLTmxMapObjectGroup class destructor.
     */
    ~NLTmxMapObjectGroup()
    {
        for( auto o : objects )
        {
            delete o;
        }
    }
};

/**
 * \class NLTmxMap
 * \details Provides a map object that is filled with tilesets, layers, and objects.
 * \see NLTmxMapTileset
 * \see NLTmxMapLayer
 * \see NLTmxMapObjectGroup
 */
class NLTmxMap
{
public:

    int width;			/**< Map's width in pixels. */
    int height;			/**< Map's height in pixels. */
    int tileWidth;		/**< Map's individual tile width in pixels. */
    int tileHeight;		/**< Map's individual tile height in pixels. */

    std::vector<NLTmxMapTileset*> tilesets;	/**< Vector containing a collection of tilesets. */
    std::vector<NLTmxMapLayer*> layers;		/**< Vector containing a collection of layers. */
    std::vector<NLTmxMapObjectGroup*> groups;	/**< Vector containing a collection of map objects. */

    /**
     * NLTmxMap class destructor.
     */
     ~NLTmxMap()
     {
        for ( auto g : groups )
        {
            delete g;
        }

        for ( auto l : layers )
        {
            delete l;
        }

        for ( auto ts : tilesets )
        {
            delete ts;
        }
    }
};

/**
 * \fn NLTmxMap* NLLoadTmxMap( char *xml )
 * \details This function provides an easy method for loading Tiled maps.
 * \param [in] xml char string representing the path to the XML file to load.
 * \returns NLTmxMap object pointer.
 */
NLTmxMap* NLLoadTmxMap( char *xml );

#endif // NLTMX_MAP_H_INC

