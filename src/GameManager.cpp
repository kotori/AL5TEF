
#include "Util.h"
#include "NLTmxMap.h"
#include "Tile.h"
#include "Character.h"

#include "GameManager.h"



CGameManager::CGameManager( const char *gameTitle )
{
    // Nullify our Allegro objects before working with them.
    m_bmp = NULL;
    m_display = NULL;
    m_eventQueue = NULL;
    m_timer = NULL;
    m_fpsTimer = NULL;
    m_bmpFPSCount = NULL;

    //myMap = NULL;

    // Create new player object.
    m_player = new CCharacter();
    // Number of frames processed.
    nFrames = 0;
    // Camera X position.
    cameraPosition[0] = START_X_POS;
    // Camera Y position.
    cameraPosition[1] = START_Y_POS;
    // Current direction moving in.
    nMoveDirection = 0;
    // Current x position.
    sourceX = 32;
    // Current y position.
    sourceY = 0;
    // String representing the game's title.
    m_gameTitle = gameTitle;
    // Redraw the screen flag. Set this to true, so we can
    //  redraw the screen on the first pass.
    bRedraw = true;
    // Exit the main game loop, obviously false.
    bExit = false;
    // Print the debugging information to the screen.
    //  This can be changed by hitting the 'P' key.
    debugMode = true;
    // Is a keyboard key being pressed right now?
    keyboardActive = false;
    // Current state of the map-loader.
    mapLoadState = LoadState::NullState;
}

CGameManager::~CGameManager()
{
    // empty dtr.
}

void CGameManager::Shutdown()
{
    // Destory our Allegro objects.
    //  Only destroy if the object's exist.
    if( m_timer )
    {
        al_destroy_timer( m_timer );
    }

    if( m_display )
    {
        al_destroy_display( m_display );
    }

    for( int i=0; i<MAX_NUM_FONTS; i++ )
    {
        if( m_fonts[i] )
        {
            al_destroy_font( m_fonts[i] );
        }
    }
    if( m_eventQueue )
    {
        al_destroy_event_queue( m_eventQueue );
    }

    for( int i=0; i<MAX_AUDIO_SAMPLES; i++ )
    {
        if( m_samples[i] )
        {
            al_destroy_sample( m_samples[i] );
        }
    }

}

void CGameManager::LoadMap( std::string mapPath )
{
    //
}

int CGameManager::Initialize()
{
    // Seed the random number generator.
    srand( ( unsigned int )time( NULL ) );

    // Set the keypress values to false. As we are just starting the app
    //  these should not be true.
    bKeys[UP] = false;
    bKeys[DOWN] = false;
    bKeys[LEFT] = false;
    bKeys[RIGHT] = false;

    // Create new player object.
    m_player = new CCharacter();

    // Clear the frame counter.
    int nFrames = 0;

    // Create our initial map.
    // tmMap = CFactory::createTileMap();

    std::cerr << "Starting application engine..." << std::endl;

    // Initialize the allegro library.
    if( !al_init() )
    {
        errorPrompt( "al_init()", "Could not initialize Allegro!" );
        return -1;
    }

    // Initialize the allegro mouse routines.
    if( !al_install_mouse() )
    {
        errorPrompt( "al_install_mouse()", "Could not initialize the allegro mouse handler!" );
        return -1;
    }

    // Initialize the allegro keyboard routines.
    if( !al_install_keyboard() )
    {
        errorPrompt( "al_install_keyboard()", "Could not initialize the allegro keboard handler!" );
        return -1;
    }

    // Initialize the allegro audio library.
    if( !al_install_audio() )
    {
        errorPrompt( "al_install_audio()", "Could not initialize the allegro audio driver!" );
        return -1;
    }

    // Initialize the allegro audio codec library.
    if( !al_init_acodec_addon() )
    {
        errorPrompt( "al_init_acodec_addon()", "Could not initialize the allegro audio codec addon!" );
        return -1;
    }

    // Reserve the appropriate samples for the application.
    if( !al_reserve_samples( MAX_AUDIO_SAMPLES ) )
    {
        errorPrompt( "al_reserve_samples()", "Failed to reserve necessary audio samples!\nSamples: %i", MAX_AUDIO_SAMPLES );
        return -1;
    }

    // Initialize the allegro image addon.
    if( !al_init_image_addon() )
    {
        errorPrompt( "al_init_image_addon()", "Failed to initialize the allegro image addon!" );
        return -1;
    }

    // Initialize the allegro font addon.
    al_init_font_addon();

    // Initialize the allegro TTF addon.
    if( !al_init_ttf_addon() )
    {
        errorPrompt( "al_init_ttf_addon()", "Failed to initialize the allegro TTF addon!" );
        return -1;
    }

    fixDirectory();

    m_timer = al_create_timer( 1.0 / FPS );
    m_fpsTimer = al_create_timer( 1.0 );

    if( !m_timer || !m_fpsTimer )
    {
        errorPrompt( "al_create_timer()", "Failed to create allegro timer!" );
        return -1;
    }

    m_display = al_create_display( ScreenWidth, ScreenHeight );
    if( !m_display )
    {
        errorPrompt( "al_create_display()", "Failed to create display!\nWidth: %i\nHeight: %i", ScreenWidth, ScreenHeight );
        al_destroy_timer( m_timer );
        return -1;
    }
    al_set_window_title( m_display, "PRE-alpha Test" );

    al_set_target_backbuffer( m_display );
    al_set_new_bitmap_flags( ALLEGRO_VIDEO_BITMAP );

    al_get_standard_path( ALLEGRO_EXENAME_PATH );


    const char *str = "Maps/zone_01_01.map";
    if( myMap.loadMap( str, completeMap ) )
    {
        errorPrompt( "loadMap()", "Failed to load map!\nCheck mapfile format: %s", str );
        return -1;
    }

    //
    // Load our fonts.
    //
    for( int i = 0; i < MAX_NUM_FONTS; i++ )
    {
        std::stringstream str;
        str << "Fonts/font_" << i << ".ttf";
        // Increment our font size into the array.
        int fntSize = i*2+16;
        // Load the font file.
        m_fonts[i] = al_load_ttf_font( str.str().c_str(), fntSize, 0 );
        // Ensure we properly loaded the font, if not, throw an error.
        if( !m_fonts[i] )
        {
            errorPrompt( "al_load_ttf_font()", "Failed to load font!\n%s", str.str().c_str() );
            return -1;
        }
    }
    //
    // Load our samples.
    //  sfx_0.wav - sfx_MAX_AUDIO_SAMPLES.wav
    //
    for( int i = 0; i < MAX_AUDIO_SAMPLES; i++ )
    {
        std::stringstream str;
        str << "Sfx/sfx_" << i << ".wav";
        m_samples[i] = al_load_sample( str.str().c_str() );
        // Ensure we properly loaded the sample, if not, throw an error.
        if( !m_samples[i] )
        {
            errorPrompt( "al_load_sample()", "Failed to load audio clip!\nMissing: %s", str.str().c_str() );
            return -1;
        }
    }

    //
    // Setup the player.
    //  hero_0.png - sfx_MAX_ANIM_FRAMES.png
    //
    for( int i = 0; i < MAX_ANIM_FRAMES; i++ )
    {
        std::stringstream str;
        str << "Sprites/Hero/hero_" << i << ".png";
        m_player->setImage( i, al_load_bitmap( str.str().c_str() ) );
        //m_player->m_bmpPlayerWalk[i] = al_load_bitmap( str.str().c_str() );
        // Ensure we properly loaded the image, if not, throw an error.
        //if( !m_player->m_bmpPlayerWalk[i] )
        if( !m_player->getImage( i ) )
        {
            errorPrompt( "al_load_bitmap()", "Failed to player's bitmap image!\nMissing: %s", str.str().c_str() );
            return -1;
        }
    }

    // Now that we have our images loaded into the animation array,
    //  set the width and height values based off of the first image in the array.
    //int plyrWidth = al_get_bitmap_width( m_player->m_bmpPlayerWalk[0] );
    //int plyrHeight = al_get_bitmap_height( m_player->m_bmpPlayerWalk[0] );
    int plyrWidth = al_get_bitmap_width( m_player->getImage( 0 ) );
    int plyrHeight = al_get_bitmap_height( m_player->getImage( 0 ) );

    // Set our player's initial direction.
    m_player->setDirection( FACING_DOWN );
    // We want our player visible of course.
    m_player->setIsVisible( true );
    // Setup our collision container with the player's width and height.
    m_player->setContainer( 0, 0, plyrWidth, plyrHeight );
    // Set our player's start x and y position.
    m_player->setX( START_X_POS );
    m_player->setY( START_Y_POS );
    // Set the player's speed.
    m_player->setAttribute( ATTRIBUTE_LIST::ATTR_SPEED, 2 );

    // Build the opposing forces.
    if( buildEnemyForces( 20, ScreenWidth, 30, ScreenHeight ) )
    {
        errorPrompt( "buildEnemyForces()", "Failed to create enemy force!" );
        return -1;
    }

    // Create the Allegro event queue.
    m_eventQueue = al_create_event_queue();
    if( !m_eventQueue )
    {
        errorPrompt( "al_create_event_queue()", "Failed to create the event queue!" );
        al_destroy_display( m_display );
        al_destroy_timer( m_timer );
        return -1;
    }

    // Register our many event sources.
    al_register_event_source( m_eventQueue, al_get_display_event_source( m_display ) );
    al_register_event_source( m_eventQueue, al_get_timer_event_source( m_timer ) );
    al_register_event_source( m_eventQueue, al_get_timer_event_source( m_fpsTimer ) );
    al_register_event_source( m_eventQueue, al_get_mouse_event_source() );
    al_register_event_source( m_eventQueue, al_get_keyboard_event_source() );

    // Set the backbuffer and initial background color, then make it visible.
    al_set_target_bitmap( al_get_backbuffer( m_display ) );
    al_clear_to_color( al_map_rgb( 255, 255, 255 ) );
    al_flip_display();

    // Start our game timer and FPS timer.
    al_start_timer( m_timer );
    al_start_timer( m_fpsTimer );

    // If the debug mode is enabled, store our initial FPS into the szFPSText variable.
    if(debugMode)
    {
        sprintf( szFPSText, "FPS: %i", nFrames );
    }
    isActive = false;

    std::cerr << "Application succesfully loaded! Starting game loop..." << std::endl;
    // If everything went according to plan, return 0, success.
    return 0;
}

int CGameManager::RunGameLoop()
{
    // As we are now starting our game loop, ensure the keyboardActive toggle is false.
    keyboardActive = false;
    // Ensure our exist condition is set.
    bExit = false;

    // Loop until our exit condition is met.
    while( !bExit )
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event( m_eventQueue, &ev );

        // If 'X' button was pressed on the window
        if( ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE )
        {
            fprintf( stderr, "[EVENT] Display has been closed!\n" );
            bExit = true;
        }
        // Else if the event type is a TIMER tick
        else if( ev.type == ALLEGRO_EVENT_TIMER )
        {
            // If the event type is a timer tick, set the player's
            //  previous direction to its current direction.
            m_player->setPrevDirection( m_player->getDirection() );
            // If the event type is a FPS timer tick.
            if( ev.timer.source == m_fpsTimer )
            {
                // Store the current FPS.
                if( debugMode )
                {
                    sprintf( szFPSText, "FPS: %i", nFrames );
                }

                // If a keyboard button is pressed,
                //  increment the player's position and animation index.
                if( keyboardActive )
                {
                    int newIndex = m_player->getIndex();
                    m_player->setIndex( newIndex++ );
                }
                else
                {
                    // Otherwise, set our animation index to + 1
                    m_player->setIndex( m_player->getDirection() + 1 );
                }
                // If the player's index value is larger than the the player's direction +3,
                //  set the player's index to the first value for this direction.
                if( m_player->getIndex() >= m_player->getDirection() + 3 )
                {
                    m_player->setIndex( m_player->getDirection() );
                }
                // If the player's direction is not equal to his previous direction, set the index
                //  to the player's current direction.
                if( m_player->getDirection() != m_player->getPrevDirection() )
                {
                    m_player->setIndex( m_player->getDirection() );
                }

                // Reset the number of frames.
                nFrames = 0;
                // Set the redraw flag to true so we can see our changes.
                bRedraw = true;
            }

            if( ev.timer.source == m_timer )
            {
                bRedraw = true;
            }

            // If the keyboardActive flag is raised, our character should be in motion.
            if( keyboardActive )
            {
                m_player->moving( true );
            }
            else
            {
                m_player->moving( false );

            }
        }

        else if( ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
        {
            fprintf( stderr, "[EVENT] Mouse UP has been pressed!\n" );
            // Do something maybe?
        }
        else if( ev.type == ALLEGRO_EVENT_KEY_DOWN )
        {
            onKeyDown( ev.keyboard.keycode );
        }
        else if( ev.type == ALLEGRO_EVENT_KEY_UP )
        {
            onKeyUp( ev.keyboard.keycode );
        }

        if( bRedraw && al_is_event_queue_empty( m_eventQueue ) )
        {
            bRedraw = false;

            // If the player's position has changed since the last pass, move the character.
            if( m_player->getX() != m_player->getPrevX() || m_player->getY() != m_player->getPrevY() )
            {
                m_player->move( nMoveDirection );
            }

            // player->move( nMoveDirection );

            // Check collisions
            if( checkCollisions() )
            {
                // Change this to play a particular sound depending upon the
                //  type of enemy encountered.
                al_play_sample( m_samples[SMP_BUMP], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL );
            }

            if( debugMode )
            {
                // Player's position.
                int pX = m_player->getX();
                int pY = m_player->getY();
                int e1X = enemyForce[0]->getX();
                int e1Y = enemyForce[0]->getY();
                int e2X = enemyForce[1]->getX();
                int e2Y = enemyForce[1]->getY();

                sprintf( szPlayerPosText, "Player: %i,%i", pX, pY );
                sprintf( szEnemyPosText1, "Enemy 1: %i,%i", e1X, e1Y );
                sprintf( szEnemyPosText2, "Enemy 2: %i,%i", e2X, e2Y );

                if( m_player->getMoving() )
                {
                    sprintf( szIsMoving, "Moving: True" );
                }
                else
                {
                    sprintf( szIsMoving, "Moving: False" );
                }

                switch( m_player->getDirection() )
                {
                case FACING_DOWN:
                    sprintf( szCurrentDirection, "Direction: Down" );
                    break;
                case FACING_UP:
                    sprintf( szCurrentDirection, "Direction: Up" );
                    break;
                case FACING_LEFT:
                    sprintf( szCurrentDirection, "Direction: Left" );
                    break;
                case FACING_RIGHT:
                    sprintf( szCurrentDirection, "Direction: Right" );
                    break;
                }
            }

            // Draw everything else.
            // We need to ensure that whatever is drawn that is supposed
            //  to be visible on the map is drawn within the CAMERA's focus.
            //drawScene( enemyList, cameraPosition, player->getX(), player->getY() );
            drawScene( cameraPosition, m_player->getX(), m_player->getY() );

            // Flip the display to reveal our changes.
            al_flip_display();
            nFrames++;
        }
    }

    // Cleanup
    Shutdown();

    std::cout << "Application Exiting...\n";
    return 0;
}

// Display an error message on the screen.
//  This function using the al_show_native_message_box for a GUI pop-up box.
void CGameManager::errorPrompt( const char *headerMsg, const char *errorMsg, ... )
{
    char buf[256];
    va_list ap;
    va_start( ap, errorMsg );
    vsprintf( buf, errorMsg, ap );
    va_end( ap );

    al_show_native_message_box(
        al_get_current_display(),   // Display.
        "Fatal Error",              // Title.
        headerMsg,                  // Heading.
        buf,                        // Message.
        NULL,                       // Buttons.
        ALLEGRO_MESSAGEBOX_ERROR ); // Flags.
}

// Triggered when a key is pressed.
void CGameManager::onKeyDown(int nKeycode)
{
    switch( nKeycode )
    {
    case ALLEGRO_KEY_P:
        if( debugMode )
        {
            debugMode = false;
        }
        else
        {
            debugMode = true;
        }
        break;
    case ALLEGRO_KEY_UP:
        m_player->setDirection( FACING_UP );
        bKeys[UP] = true;
        keyboardActive = true;
        nMoveDirection |= UP;
        break;
    case ALLEGRO_KEY_DOWN:
        m_player->setDirection( FACING_DOWN );
        bKeys[DOWN] = true;
        keyboardActive = true;
        nMoveDirection |= DOWN;
        break;
    case ALLEGRO_KEY_LEFT:
        m_player->setDirection( FACING_LEFT );
        bKeys[LEFT] = true;
        keyboardActive = true;
        nMoveDirection |= LEFT;
        break;
    case ALLEGRO_KEY_RIGHT:
        m_player->setDirection( FACING_RIGHT );
        bKeys[RIGHT] = true;
        keyboardActive = true;
        nMoveDirection |= RIGHT;
        break;
    }
}

// Triggered when a key is released.
void CGameManager::onKeyUp( int nKeycode )
{
    switch( nKeycode )
    {
    case ALLEGRO_KEY_ESCAPE:
        bExit = true;
        break;
    case ALLEGRO_KEY_UP:
        bKeys[UP] = false;
        handleKeyboardDirectionChange();
        nMoveDirection ^= UP;
        break;
    case ALLEGRO_KEY_DOWN:
        bKeys[DOWN] = false;
        handleKeyboardDirectionChange();
        nMoveDirection ^= DOWN;
        break;
    case ALLEGRO_KEY_LEFT:
        bKeys[LEFT] = false;
        handleKeyboardDirectionChange();
        nMoveDirection ^= LEFT;
        break;
    case ALLEGRO_KEY_RIGHT:
        bKeys[RIGHT] = false;
        handleKeyboardDirectionChange();
        nMoveDirection ^= RIGHT;
        break;
    }
}

// handleKeyboardDirectionChange()
// This function ensures that if multiple keys are pressed, the
// last key remaining active is the current direction. This prevents
// key releases from messing up the animation routines.
void CGameManager::handleKeyboardDirectionChange()
{
    if( bKeys[UP] || bKeys[DOWN] || bKeys[LEFT] || bKeys[RIGHT] )
    {
        keyboardActive = true;
    }
    else
    {
        keyboardActive = false;
    }
}

// checkCollisions()
// Quite simply this function ensures that the player has not
// come in contact with any of the enemies on the screen. This should
// be revised to make smarter matches for enemies as well as triggers/events.
bool CGameManager::checkCollisions()
{
    for( int i=0; i<MAX_NUM_ENEMIES; i++ )
    {
        // First ensure the tile is even on the screen prior to checking for a collision.
        if( enemyForce[i]->getIsVisible() )
        {
            if( m_player->checkCollision( enemyForce[i] ) )
            {
                return true;
            }
        }
    }
    return false;
}

// randomNum(int, int)
// Generates a random integer between 'min' and 'max'.
int CGameManager::randomNum( int min, int max )
{
    return (int)((max - min) * rand()/(float)RAND_MAX + min);
}

// buildEnemyForces( int, int, int, int )
//  Creates an array of enemies randomly placed on the map. The enemies are placed
//  between xFloor, xCeiling and yFloor, yCeiling.
int CGameManager::buildEnemyForces( int xFloor, int xCeiling, int yFloor, int yCeiling )
{
    int xSize = 30;
    int ySize = 30;

    int enemyId = 0;
    for( int count=0; count< MAX_NUM_ENEMIES; count++ )
    {
        // Create new temp CCharacter object to store into the vector.
        CCharacter *tmpEnemy = new CCharacter();
        int ranX = rand() % (xCeiling - xFloor ) + xFloor;
        int ranY = rand() % (yCeiling - yFloor ) + yFloor;
        //int ranX = randomNum( xFloor, xCeiling );
        //int ranY = randomNum( yFloor, yCeiling );

        // Set the enemy's random position.
        tmpEnemy->setContainer(             // Setup our enemy's container.
            ranX,                           // Random 'x' position between xFloor and xCeiling.
            ranY,                           // Random 'y' position between yFloor and yCeiling.
            xSize,                          // Width of the enemy's image.
            ySize );                        // Height of the enemy's iamge.
        // Make this enemy visible.
        tmpEnemy->setIsVisible( true );
        // Set its character type.
        tmpEnemy->setType( TYPE_ENEMY );
        // Now load the enemy's bitmap image, and store it.

        std::stringstream str;
        str << "Sprites/Enemy/enemy_" << enemyId << "_" << count << ".png";
        tmpEnemy->setPalette( al_load_bitmap( str.str().c_str() ) );
        if( !tmpEnemy->getPalette() )
        {
            errorPrompt( "buildEnemyForces( )", "Failed to load enemy bitmap!\nMissing: %s", str.str().c_str() );
            return -1;
        }
        // Finally, insert the built enemy into the enemyForce vector.
        enemyForce.push_back( tmpEnemy );
    }

    return 0;
}

// fixDirectory()
// Ensures that the current working directory is the stanard allegro path
// In other words make sure we are in our executables directory. (bin)
void CGameManager::fixDirectory()
{
    ALLEGRO_PATH *path = al_get_standard_path( ALLEGRO_RESOURCES_PATH );
    al_append_path_component( path, "resources" );
    al_change_directory( al_path_cstr( path, '/' ) );
    al_destroy_path( path );
}

// cameraUpdate( float, float, float, int, int )
//  Updates the camera position for a smooth scrolling map.
//  This ensures that when we move around, the map scrolls with us.
void CGameManager::cameraUpdate( float *cameraPosition, float x, float y, int width, int height )
{
    cameraPosition[0] = -( ScreenWidth / 2 ) + ( x + width / 2 );
    cameraPosition[1] = -( ScreenHeight / 2 ) + ( y + height / 2 );

    if( cameraPosition[0] < 0 )
        cameraPosition[0] = 0;
    if( cameraPosition[1] < 0 )
        cameraPosition[1] = 0;
}

// printer( ALLEGRO_DISPLAY*, int, int, int, const char*, ... )
//  Prints a message to the screen with a particular font. The message
//  is actually printed twice. The first print is the background color, and the
//  foreground message is printed on top of the first, slighty offset.
void CGameManager::printer( ALLEGRO_DISPLAY *disp, int fontID, int x, int y, const char *msg, ... )
{
    ALLEGRO_COLOR COLOR_WHITE = al_map_rgb( 255, 255, 255 );
    ALLEGRO_COLOR COLOR_BLACK = al_map_rgb( 0, 0, 0);
    char buf[256];
    va_list ap;
    va_start( ap, msg );
    vsprintf( buf, msg, ap );
    va_end( ap );

    // Print the background text shadow first.
    al_draw_text( m_fonts[fontID], COLOR_BLACK, x, y, 0, buf );
    // Now print the foreground text.
    al_draw_text( m_fonts[fontID], COLOR_WHITE, x+2, y+2, 0, buf );
}

// drawScene( float, float, float )
//  Prints everything to the screen. This function is necessary to make our
//  movement changes, etc visible on the screen. The scene is updated with the camera's
//  current position and the player's current position.
void CGameManager::drawScene( float *cameraPositions, float player_x, float player_y )
{
    // Background color first.
    al_clear_to_color( al_map_rgb( 255, 255, 255 ) );

    // Draw our camera offsetted around our player.
    cameraUpdate( cameraPositions, player_x, player_y, 32, 32 );
    al_identity_transform( &m_camera );
    al_translate_transform( &m_camera, -cameraPositions[0], -cameraPositions[1] );
    al_use_transform( &m_camera );

    // TODO:
    // Print map layer 1.
    //myMap.drawMapLayer1();
    // TODO:
    // Print map layer 2.
    //

    // This will need to be changed to display enemies depending upon the loaded map!
    // Each enemy is drawn individually.
    for( int i=0; i<MAX_NUM_ENEMIES; i++ )
    {
        // If the enemy is visible, show it.
        if( enemyForce[i]->getIsVisible() )
        {
            enemyForce[i]->draw( m_display );
        }
    }

    // Now the player if it is visible
    if( m_player->getIsVisible() )
    {
        m_player->draw( m_display, m_player->getIndex() );
        //player->draw( display, sourceX, sourceY );
    }

    // TODO:
    // Finally print map layer 3.
    //

    // Now debugging info.
    // Here, two draw statements are used per stat for shadow purposes.
    if( debugMode )
    {
        // Print offset from the left.
        int offSet = 8;
        // FPS.
        printer( m_display, FONT_DEBUG, cameraPositions[0]+offSet, cameraPositions[1]+8, szFPSText );
        // Player's position
        printer( m_display, FONT_DEBUG, cameraPositions[0]+offSet, cameraPositions[1]+24, szPlayerPosText );
        // Enemy's position 1
        printer( m_display, FONT_DEBUG, cameraPositions[0]+offSet, cameraPositions[1]+40, szEnemyPosText1 );
        // Enemy's position 2
        printer( m_display, FONT_DEBUG, cameraPositions[0]+offSet, cameraPositions[1]+56, szEnemyPosText2 );
        // Player's motion indicator
        printer( m_display, FONT_DEBUG, cameraPositions[0]+offSet, cameraPositions[1]+72, szIsMoving );
        // Current Direction
        printer( m_display, FONT_DEBUG, cameraPositions[0]+offSet, cameraPositions[1]+88, szCurrentDirection );
    }

}
