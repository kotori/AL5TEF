#ifndef TILE_H
#define TILE_H

#include "Util.h"
#include "Collidable.h"

class CTile : public CCollidable
{
public:
    // Constructor.
	CTile( void );
	// Destructor.
	~CTile( void );

	// Set this tile's ID.
	void setId( int id );
	// Get this tile's ID.
	int getId();

    // Set if this tile acts as a trigger.
    void setTrigger( bool trigger );
    // Get if this tile is a trigger.
    bool getTrigger();

    // Set if this tile acts as a block, no passage.
    void setWall( bool wall );
    // Get if this tile acts as a block.
    bool getWall();

    // Set if this tile is animated.
    void setAnimated( bool animated );
    // Get if this tile i saniamted.
    bool getAnimated();

    // Set this tile's animation index value.
    void setAnimIndex( int index );
    // Get this tile's animation index value.
    int getAnimIndex();

protected:

    // This tile's ID.
    int m_id;

    // Is this tile a trigger?
    bool m_isTrigger;

    // Is this tile a blocking tile?
    bool m_isWall;

    // Is this tile animated?
    bool m_isAnimated;

    // Tile's animated images.
    std::vector<ALLEGRO_BITMAP *> m_animation;

    // Tile's animation index counter.
    int m_animationIndex;
};

#endif	// TILE_H
