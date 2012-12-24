#include "Character.h"

// Initialize our new character object.
CCharacter::CCharacter( void )
{
    // Setup our character's initial attribute values.
    m_container.x = 0;
    m_container.y = 0;
    m_isVisible = false;
    m_direction = FACING_DOWN;
    m_indexTileSheetY = m_direction;
    //m_bmpPalette = NULL;
    m_type = TYPE_NULL;
    m_index = 0;

    for( int i=0; i < ATTRIBUTE_LIST::ATTR_END_LIST; i++ )
    {
        m_attributes.push_back( 0 );
    }

    for( int i=0; i < MAX_ANIM_FRAMES; i++ )
    {
        m_bmpImage.push_back( NULL );
    }
}


CCharacter::~CCharacter( void )
{
    // Empty destructor.
}


int CCharacter::getAttribute( int attrId )
{
    return m_attributes[attrId];
}

void CCharacter::setAttribute( int attrId, int attrVal )
{
    m_attributes[attrId] = attrVal;
}

ALLEGRO_BITMAP* CCharacter::getImage( int index )
{
    return m_bmpImage[index];
}

void CCharacter::setImage( int index, ALLEGRO_BITMAP *img )
{
    m_bmpImage[index] = img;
}

// Is the character currently moving?
bool CCharacter::getMoving()
{
    return m_inMotion;
}

// Set if this character is currently moving.
void CCharacter::moving( bool isMoving )
{
    //m_inMotion = isMoving;

    if( isMoving )
    {
        m_index++;
    }
    else
    {
        m_index = m_direction + 1;
    }

    // If the index is equal to order greater than the end of the frame.
    if( m_index >= m_direction + 3 )
    {
        m_index = m_direction;
    }

    if( m_direction != m_prevDirection )
    {
        m_index = m_direction;
    }
}

// Draw this character's static image to the passed ALLEGRO_DISPLAY.
//  The character is drawn to the values of:
//  m_container.x, m_container.y
void CCharacter::draw( ALLEGRO_DISPLAY *disp )
{
    // Set the drawing routine's target bitmap.
    al_set_target_bitmap( al_get_backbuffer( disp ) );
    // Draw the image reprenting this character.
    al_draw_bitmap( m_bmpImage[0], m_container.x, m_container.y, 0 );
}

// Draw this character to the passed ALLEGRO_DISPLAY,
//  This is used to draw character walking animations.
//  The value of indexValue is the location in the animation array.
void CCharacter::draw( ALLEGRO_DISPLAY *disp, int indexValue )
{
    al_set_target_bitmap( al_get_backbuffer( disp ) );
    al_convert_mask_to_alpha( m_bmpImage[indexValue], al_map_rgb( 255, 255, 255 ) );
    al_draw_bitmap(
        m_bmpImage[indexValue],
        m_container.x,
        m_container.y,
        0 );
}

/*
// Draw the static character image to the screen to the passed ALLEGRO_DISPLAY.
//  This function also takes a sourceX, and sourceY value to draw this image to.
void CCharacter::draw( ALLEGRO_DISPLAY *disp, int sX, int sY )
{
    // Set the drawing routine's target bitmap.
    al_set_target_bitmap( al_get_backbuffer( disp ) );
    // Draw the sub-bitmap representing the character's current position.
    al_draw_bitmap_region(
        m_bmpPalette,                                   // ALLEGRO_BITMAP image.
        sX,                                             // Source X.
        sY * al_get_bitmap_height( m_bmpPalette ) / 4,  // Source Y.
        32,                                             // Width of image.
        32,                                             // Height of image.
        m_container.x,                                  // X position to display.
        m_container.y,                                  // Y position to display.
        0 );                                         // Additional flags.
}
*/

CharacterType CCharacter::getType()
{
    return m_type;
}

void CCharacter::setType( CharacterType charType )
{
    m_type = charType;
}

// Build the palaette for this character. Returns 0 on success.
int CCharacter::setPalette( ALLEGRO_BITMAP *bmp )
{
    m_bmpImage[0] = bmp;
    if( !bmp )
    {
        std::cerr << "[ERROR] Failed setting character bitmap!" << std::endl;
        return 1;
    }
    return 0;
}

ALLEGRO_BITMAP* CCharacter::getPalette()
{
    return m_bmpImage[0];
}

void CCharacter::move( int directions )
{
    m_previousPos.x = m_container.x;
    m_previousPos.y = m_container.y;

    if( directions & UP )
    {
        m_container.y -= m_attributes[ATTRIBUTE_LIST::ATTR_SPEED];
        //m_container.y -= m_nSpeed;
        m_direction = FACING_UP;
    }

    if( directions & DOWN )
    {
        m_container.y += m_attributes[ATTRIBUTE_LIST::ATTR_SPEED];
        //m_container.y += m_nSpeed;
        m_direction = FACING_DOWN;
    }

    if( directions & LEFT )
    {
        m_container.x -= m_attributes[ATTRIBUTE_LIST::ATTR_SPEED];
        //m_container.x -= m_nSpeed;
        m_direction = FACING_LEFT;
    }

    if( directions & RIGHT )
    {
        m_container.x += m_attributes[ATTRIBUTE_LIST::ATTR_SPEED];
        //m_container.x += m_nSpeed;
        m_direction = FACING_RIGHT;
    }
}


bool CCharacter::getIsVisible()
{
    return m_isVisible;
}

void CCharacter::setIsVisible( bool vis )
{
    m_isVisible = vis;
}

bool CCharacter::checkCollision( CCollidable *c )
{
    bool bIsColliding = isColliding( c );
    if( bIsColliding )
    {
        m_container.x = m_previousPos.x;
        m_container.y = m_previousPos.y;
    }
    return bIsColliding;
}

int CCharacter::getDirection( )
{
    return m_direction;
}

void CCharacter::setDirection( int dir )
{
    m_direction = dir;
}

int CCharacter::getPrevDirection()
{
    return m_prevDirection;
}

void CCharacter::setPrevDirection( int dir )
{
    m_prevDirection = dir;
}

int CCharacter::getIndex()
{
    return m_index;
}

void CCharacter::setIndex(int index )
{
    m_index = index;
}
