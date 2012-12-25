/**
 * \file Util.h
 * \details This header file contains commonly used DEFINES and some global enums.
 * \author Kotori
 */

#ifndef UTIL_H
#define UTIL_H

#include <ctime>
#include <map>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_tiled.h>

/**
 * \def DEBUGGING_MODE
 * \details When set to true, debugging mode will write quite a bit of debugging information
 *  to both the console and the screen. You can press 'p' in-game to turn this OFF.
 */
#define DEBUGGING_MODE      true

/**
 * \def BlockSize
 * \details This define stores the width and height of the to-be-loaded tiles.
 *  Normally this will be set to 16, 32, or 40 pixels.
 */
#define BlockSize           32

/**
 * \def ScreenWidth
 * \details This define holds the width of the screen in pixels. This value is used by
 *  Allegro when creating the initial display.
 */
#define ScreenWidth         1024

/**
 * \def ScreenHeight
 * \details This define holds the height of the screen in pixels. This value is used by
 *  Allegro when creating the initial display.
 */
#define ScreenHeight        768

/**
 * \def FPS
 * \details This define holds the rate at which to flip the display. With a value of 60, the
 *  screen will be refreshed every 60 frames.
 */
#define FPS                 60.0

/**
 * \def MAX_NUM_ENEMIES
 * \warning THIS WILL BE REMOVED IN THE FUTURE.
 * \details This define holds the maximum number of enemies to display on the screen at one time. This
 *  define will be removed in future versions, it currently only exists to debug the enemy creation engine.
 */
#define MAX_NUM_ENEMIES     12

/**
 * \def MAX_AUDIO_SAMPLES
 * \details Limits the number of audio samples to load. This value should match the number of enums in the
 *  \b SAMPLE_LIBRARY enumeration.
 */
#define MAX_AUDIO_SAMPLES   1

/**
 * \def MAX_NUM_FONTS
 * \details Limits the number of ALLEGRO_FONTs to load during initialization. This will load a series of fonts
 *  from the 'resources/Fonts' directory.
 */
#define MAX_NUM_FONTS       3

/**
 * \def START_X_POS
 * \details Specifies the 'x' axis start location of our player.
 */
#define START_X_POS         256

/**
 * \def START_Y_POS
 * \details Specifies the 'y' axis start location of our player.
 */
#define START_Y_POS         256

/**
 * \def PLAYER_IMG_OFFSET
 * \warning THIS WILL BE REMOVED IN THE FUTURE.
 * \details Specifies the offset in pixels of our animations. Normally this should be set
 *  to the size of our individual tiles. This will be removed in favor of dynamic detection of the offset.
 */
#define PLAYER_IMG_OFFSET   32

/**
 * \def PLAYER_IMG_TYPE
 * \details This specifies the type of image animation scheme we will use. If the value
 *  is set to 1, a tilesheet will be used, usually a 3x4 containing 3 steps per direction.
 *  If a value of 2 is used, each individual animation step is loaded as a seperate file.
 * \code
 *  example:
 *  step1(north) hero_0.png, step2(north) hero_1.png, step3(north) hero_2.png
 *   hero_0.png - hero_n.png (n is defined as MAX_ANIM_FRAMES-1)
 * \endcode
 */
#define PLAYER_IMG_TYPE     2

/**
 * \def MAX_ANIM_FRAMES
 * \warning THIS WILL BE REMOVED IN THE FUTURE.
 * \details This specifices the total number of frames to use in animation sequences.
 *  If you have 3 frames per direction (4 directions) you will have a MAX_ANIM_FRAMES value
 *  of 12. If you have 4 frames per direction, this value would be 16.
 */
#define MAX_ANIM_FRAMES     12

/**
 * \def NUM_STEPS_ANIM
 * \warning THIS WILL BE REMOVED IN THE FUTURE.
 * \details Defines the number of steps per direction in an animation sequence.
 *
 *  Example:\n
 *  If each direction has 3 frames in its walk animation, this value would be 3.\n
 *  hero_0.png, hero_1.png, hero_2.png : down\n
 *  hero_3.png, hero_4.png, hero_5.png : left\n
 *  hero_6.png, hero_7.png, hero_8.png : right\n
 *  hero_9.png, hero_10.png, hero_11.png : up
 */
#define NUM_STEPS_ANIM      3

/**
 * \def NUM_MAP_LAYERS
 * \warning THIS WILL BE REMOVED IN THE FUTURE.
 * \details Describes the number of layers our maps contain. This allows for a 3d style
 *  effect, allowing our character's to walk over and under certain tiles.
 */
#define NUM_MAP_LAYERS      3

/**
 * \enum ATTRIBUTE_LIST
 * \details The ATTRIBUTE_LIST provides an easy method for setting and getting
 *  character attribute stats. Instead of set_health() / get_health(), you can simply do:
 * \code
 *  CCharacter *player = new CCharacter(); // Create new character object.
 *  player->setAttribute( ATTR_HEALTH_MAX, 100 ); // Set the player's maximum health to 100.
 *  player->setAttribute( ATTR_HEALTH, 10 ); // Set the player's health to 10.
 *  ...
 *  if( player->getAttribute( ATTR_HEALTH ) < ATTR_HEALTH_MAX / 3 )
 *  {
 *     // Alert the player that his life is three-quarters gone...
 *  }
 * \endcode
 */
enum ATTRIBUTE_LIST
{
    ATTR_BEGIN_LIST,			    /**< Beginning of the character attribute list. */

    ATTR_HEALTH = ATTR_BEGIN_LIST,	/**< Player's health attribute. */
    ATTR_HEALTH_MAX,			    /**< Player's max health attribute. */
    ATTR_LIVES_REMAIN,              /**< Player's number of remaining tries */
    ATTR_MAGIC,				        /**< Player's magic attribute */
    ATTR_MAGIC_MAX,			        /**< Player's max magic attribute. */
    ATTR_LEVEL,				        /**< Player's current level attribute. */
    ATTR_MONEY,				    /**< Player's accumulated funds (money). */
    ATTR_EXPERIENCE,			    /**< Player's accumulated experience points attribute. */
    ATTR_ATTACK_RATING,			    /**< Player's attack rating attribute. */
    ATTR_ATTACK_BONUS,			    /**< Player's attack bonus attribute. */
    ATTR_DEFENSE_RATING,		    /**< Player's defense rating attribute. */
    ATTR_DEFENSE_BONUS,			    /**< Player's defense bonus attribute. */
    ATTR_SPEED,				        /**< Player's movement speed attribute. */
    ATTR_LUCK,				        /**< Player's luck attribute. */

    ATTR_END_LIST			        /**< End of the character attribute list. */
};

/**
 * \enum SAMPLE_LIBRARY
 * \details This provides an easy method for loading ALLEGRO_SAMPLEs via ID number.
 */
enum SAMPLE_LIBRARY
{
    SMP_BUMP = 0,	/**< Audio sample representing a BUMP sound effect. */
    SMP_HIT = 1		/**< Audio sample representing a HIT sound effect. */
};

/**
 * \enum Direction
 * \warning THIS WILL BE REMOVED IN THE FUTURE IN FAVOR OF 'Facing'.
 * \details This enumeration contains the movement offset values for directions.
 *  This provides an easy means for determining which direction your character is facing.
 */
enum Direction
{
    UP = 1,	/**< Represents facing UP (North). */
    DOWN = 2,	/**< Represents facing DOWN (South). */
    LEFT = 4,	/**< Represents facing LEFT (West). */
    RIGHT = 8	/**< Represents facing RIGHT (East). */
};

/**
 * \enum Facing
 * \details This enumeration represents the cardinal directions our character can possibly
 *  be facing in. This also controls the animation sequence. If the animation sequence contains
 *  more than 3 frames per direction, or are arranged in a different order, this will need to be adjusted accordingly.
 * \code
 * Tiles 0-2: Down
 * Tiles 3-5: Left
 * Tiles 6-8: Right
 * Tiles 9-11: Up
 * \endcode
 */
enum Facing
{
    FACING_DOWN = 0,	/**< Represents our character facing DOWN. */
    FACING_LEFT = 3,	/**< Represents our character facing LEFT. */
    FACING_RIGHT = 6,	/**< Represents our character facing RIGHT. */
    FACING_UP = 9	/**< Represents our character facing UP. */
};

/**
 * \enum CharacterType
 * \details Specifies the type of character loaded. This determines if the
 *  if the character is able to get into battle, is a merchant, etc.
 */
enum CharacterType
{
    TYPE_NULL = 0,	/**< Null character type. */
    TYPE_PLAYER,	/**< Player character type. */
    TYPE_ENEMY,		/**< Enemy character type. */
    TYPE_BOSS,		/**< Boss character type. (Special enemy). */
    TYPE_NPC,		/**< Normal NPC character type. */
    TYPE_MERCH		/**< Merchant character type. */
};

/**
 * \enum FontType
 * \details This allows the user to easily print with fonts via its ID instead
 *  of remembering a path, etc. This makes printing to the screen with different fonts
 *  for different occassions much easier.
 */
enum FontType
{
    FONT_DEBUG =    0,	/**< Debugging font. */
    FONT_NORMAL =   1,	/**< Normal print font (default used). */
    FONT_LARGE =    2	/**< Large print font. */
};

extern int charType;

/**
 * \enum LoadState
 * \warning THIS WILL BE REMOVED IN THE FUTURE IN FAVOR OF THE NEW MAP LOADING ENGINE.
 * \details This enumeration lists the possible LoadState's for the map-loading routines.
 */
enum LoadState
{
    NullState,	/**< Null load state. Loads nothing. */
    TileSet,	/**< TileSet load state. Loads the tileset. */
    Layer	/**< Layer load state. Loads the map layers. */
};

/**
 * \struct Point
 * \details Wraps a pair of x and y locations into a single Point.
 */
typedef struct Point
{
	int x;	/**< X axis location. */
	int y;	/**< Y axis location. */
} Point; /**< Forward declaration of the Point object. */

/**
 * \struct Rect
 * \details Wraps a set of x,y,w,h values into a single Rect. This value
 *  can then be used to detect bounding box collisions.
 */
typedef struct Rect
{
	int x;	/**< X axis location. */
	int y;	/**< Y axis location. */
	int w;	/**< Rect's width, in pixels. */
	int h;	/**< Rect's height, in pixels. */
} Rect; /**< Forward declaration of the Rect object. */


/**
 * A vector of vector of ints representing our layered map.
 * \details This vector contains another vector filled with integers.
 *  These integers represent tile IDs on the map. When drawing occurs,
 *  the ID is read, and the corresponding Tile is drawn to the screen.
 */
extern std::vector< std::vector< std::vector <int> > > completeMap;

#endif // UTIL_H
