
#include "Util.h"
#include "Tile.h"

CTile::CTile( void )
{
    m_id = 0;
    m_isTrigger = false;
    m_isWall = false;
    m_isAnimated = false;
    m_animationIndex = 0;
}

CTile::~CTile( void )
{
    //
}

// Set this tile's ID.
void CTile::setId( int id )
{
    m_id = id;
}

// Get this tile's ID.
int CTile::getId()
{
    return m_id;
}

// Set if this tile acts as a trigger.
void CTile::setTrigger( bool trigger )
{
    m_isTrigger = trigger;
}

// Get if this tile is a trigger.
bool CTile::getTrigger()
{
    return m_isTrigger;
}

// Set if this tile acts as a block, no passage.
void CTile::setWall( bool wall )
{
    m_isWall = wall;
}

// Get if this tile acts as a block.
bool CTile::getWall()
{
    return m_isWall;
}

// Set if this tile is animated.
void CTile::setAnimated( bool animated )
{
    m_isAnimated = animated;
}

// Get if this tile i saniamted.
bool CTile::getAnimated()
{
    return m_isAnimated;
}

// Set this tile's animation index value.
void CTile::setAnimIndex( int index )
{
    m_animationIndex = index;
}

// Get this tile's animation index value.
int CTile::getAnimIndex()
{
    return m_animationIndex;
}
