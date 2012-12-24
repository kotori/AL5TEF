/**
 * \file GameManager.h
 * \author Kotori
 *
 * This class combines the various other helper classes into a managable game interface. The
 *  CGameManager class handles all the creation and destruction of all of the game's objects.
 */

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Map.h"
#include "Character.h"
#include "Util.h"

/**
 * \class CGameManager
 * \details Provides a wrapper around starting, stopping and running the game engine.
 */
class CGameManager
{
    public:
	/**
	 * \fn CGameManager( const char *gameTitle )
	 * \details Class constructor, takes the game's title as an argument.
	 * \param [in] gameTitle char string representing the game's title.
	 *
	 * Example Usage:
	 * \code
	 * CGameManager myGame("Game Title"); // Create new game object.
	 * OR
	 * CGameManager *newGame = new CGameManager("Game Title"); // Create new game object pointer.
	 * \endcode
	 */
        CGameManager( const char *gameTitle );

	/**
	 * \fn ~CGameManager()
	 * \details Default class destructor.
	 */
        ~CGameManager();

	/**
	 * \fn int Initialize()
	 * \details Initializes the Allegro libraries and loads all required resources.
	 * \returns True if an error occurred, False if everything loaded properly.
	 *
	 * Example Usage:
	 * \code
	 * CGameManager myGame = new CGameManager("Game Title"); // Create new game object.
	 * if( myGame->Initialize() ) // Initialize this new game object.
	 * {
	 *     return -1; // An error has occurred!
	 * }
	 * \endcode
	 */
        int Initialize();

	/**
	 * \fn int RunGameLoop()
	 * \details Runs the game loop until an exit condition is met.
	 *  The exit conditions are: ESC button pressed, or 'X' window button pressed.
	 *
	 * Example Usage:
	 * \code
	 * CGameManager myGame = new CGameManager("Game Title"); // Create new game object.
	 * if( myGame->Initialize() )	// Initialize this new game object.
     * {
	 *     return -1; // An error has occurred!
	 * }
	 * else
	 * {
	 *     if( myGame->RunGameLoop() ) // Run the game loop until an exit condition is met.
	 *     {
	 *         return -1; // An error has occurred!
	 *     }
	 * }
	 * \endcode
	 */
        int RunGameLoop();

	/**
     * \fn void Shutdown()
     * \details Releases our stored resources and destroys any created Allegro objects to free memory.
	 *
	 * Example Usage:
	 * \code
	 * CGameManager myGame = new CGameManager("Game Title"); // Create new game object.
     * if( myGame->Initialize() )    // Initialize this new game object.
     * {
     *     return -1; // An error has occurred!
     * }
     * else
     * {
     *     if( myGame->RunGameLoop() ) // Run the game loop until an exit condition is met.
     *     {
     *         return -1; // An error has occurred!
     *     }
     * }
	 * myGame->Shutdown(); // Cleanup the loaded resources, and destory the Allegro objects.
	 * \endcode
     */
        void Shutdown();

    private:

        void errorPrompt( const char *headerMsg, const char *errorMsg, ... );

        void onKeyDown( int keycode );
        void onKeyUp( int keycode );

        int randomNum( int min, int max );
        int buildEnemyForces( int xFloor, int xCeiling, int yFloor, int yCeiling );

        void fixDirectory();
        bool checkCollisions();
        void cameraUpdate( float *cameraPosition, float x, float y, int width, int height );
        void drawScene( float *cameraPositions, float player_x, float player_y );
        void printer( ALLEGRO_DISPLAY *disp, int x, int y, const char *msg, ... );
        void printer( ALLEGRO_DISPLAY *disp, int fontID, int x, int y, const char *msg, ... );
        void handleKeyboardDirectionChange();

        ALLEGRO_BITMAP      *m_bmp;
        ALLEGRO_DISPLAY     *m_display;
        ALLEGRO_EVENT_QUEUE *m_eventQueue;
        ALLEGRO_TIMER       *m_timer;
        ALLEGRO_TIMER       *m_fpsTimer;
        ALLEGRO_BITMAP      *m_bmpFPSCount;
        ALLEGRO_FONT        *m_fonts[MAX_NUM_FONTS];
        ALLEGRO_SAMPLE      *m_samples[MAX_AUDIO_SAMPLES];
        ALLEGRO_TRANSFORM   m_camera;

        CCharacter *m_player;

        // Draws the entire map to the screen, this will be removed in favor of
        // the function: drawMapLayer( int mapId, int layerId, ALLEGRO_BITMAP *tiles )
        void drawMap( int mapId, ALLEGRO_BITMAP *tiles );
        void drawMapLayer( int mapId, int layerId, ALLEGRO_BITMAP *tiles );

        int loadMap( const char *filename, std::vector< std::vector< std::vector <int> > > &map );

        int sourceX;
        int sourceY;

        int nFrames;

        std::vector <CCharacter*> enemyForce;
        std::vector< std::vector <int> > completeMap;
        ALLEGRO_BITMAP *mapTileSet;

        const char *m_gameTitle;
        bool bRedraw;
        bool bExit;
        bool debugMode;
        bool isActive;
        bool keyboardActive;

        bool bKeys[RIGHT+1];

        // Debugging strings.
        char szFPSText[32];
        char szPlayerPosText[32];
        char szEnemyPosText1[32];
        char szEnemyPosText2[32];
        char szCurrentDirection[32];
        char szIsMoving[32];

        // Camera position array.
        float cameraPosition[2];
        short nMoveDirection;

        int mapLoadState;

        CMap myMap;
};

#endif	// GAME_MANAGER_H
