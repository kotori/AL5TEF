/**
 * \file main.cpp
 * \details Entry point for this application. To execute the game's engine,
 *  the following calls must be made:
 * \code
 * 1.) Create new CGameManager object.
 * 2.) Initialize the CGameManager object.
 * 3.) Run the game loop until exit.
 * \endcode
 */

#include "Util.h"
#include "GameManager.h"

/**
 * \fn int main( int argc, char **argv )
 * \details Application's entry point.
 */
int main( int argc, char **argv )
{
    CGameManager MyGame( "Alpha WIP" );

    if( MyGame.Initialize() )
    {
        return -1;
    }
    else
    {
        if( MyGame.RunGameLoop() )
        {
            return -1;
        }
    }

    return 0;
}
