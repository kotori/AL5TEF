/**
 * \file Character.h
 * \author Kotori
 *
 * The character class provides a container for our character's many attributes.
 *  This class keeps track of animation steps, collisions, visibility, and much
 *  more for a single character to an array of characters.
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include "Util.h"
#include "Collidable.h"

/**
 * \class CCharacter
 * \details The base structure for building a full character.
 */
class CCharacter : public CCollidable
{
public:
	CCharacter( void );     /**< Default class constructor. */
	~CCharacter( void );    /**< Default class destructor. */

	/**
     * \fn void draw( ALLEGRO_DISPLAY *disp )
     * \warning This method is reserved for drawing a non-animated image.
	 * \details draw's the character to the passed display
	 * \param [in] disp ALLEGRO_DISPLAY object pointer.
     */
	void draw( ALLEGRO_DISPLAY *disp );

	/**
     * \fn void draw( ALLEGRO_DISPLAY *disp, int indexValue )
	 * \details draw's the character to the passed display and at the indexValue passed.
	 * \param [in] disp ALLEGRO_DISPLAY object pointer.
	 * \param [in] indexValue Index in the animation sequence.
     */
	void draw( ALLEGRO_DISPLAY *disp, int indexValue );

	/**
     * \fn void draw( ALLEGRO_DISPLAY *disp, int sX, int sY )
	 * \details draw's the character to the passed display and from the passed locations
	 *  from the character's image tilesheet.
	 * \param [in] disp ALLEGRO_DISPLAY object pointer.
	 * \param [in] sX Source X-axis position to draw from the tilesheet.
	 * \param [in] sY Source Y-axis position to draw from the tilesheet.
     */
	void draw( ALLEGRO_DISPLAY *disp, int sX, int sY );

	void move( int directions );

	void moving( bool isMoving );
	bool getMoving();

	int setPalette( ALLEGRO_BITMAP *bmp );
	ALLEGRO_BITMAP* getPalette();

    /**
     * \fn bool checkCollision( CCollidable *c )
	 * \details Detects if there is a collision between this object and the passed object.
	 * \param [in] c Collision object.
	 * \returns True if a collision will occur.
     */
	bool checkCollision( CCollidable *c );

	bool getIsVisible();
	void setIsVisible( bool vis );

	CharacterType getType();
	void setType( CharacterType charType );

	int getDirection( );
    void setDirection( int dir );

    int getPrevDirection();
    void setPrevDirection( int dir );

    //ALLEGRO_BITMAP *m_bmpPlayerWalk[12];
    ALLEGRO_BITMAP* getImage( int index );
    void setImage( int index, ALLEGRO_BITMAP *img );

    int getIndex();
    void setIndex(int index );

    /**
     * \fn int getAttribute( int attrId )
     * \details Retrieve the attribute value matching the passed \b attrId
     * \param [in] attrId Integer value representing a member of ATTRIBUTE_LIST.
     * \returns Integer representing this attributes current value.
     *
     * Example Usage:
     * \code
     * CCharacter *myPlayer = new CCharacter(); // Create new player object.
     * int player_health = myPlayer->getAttribute( ATTRIBUTE_LIST::ATTR_HEALTH ); // Get the player's health.
     * \endcode
     * \see ATTRIBUTE_LIST
     */
    int getAttribute( int attrId );

    /**
     * \fn void setAttribute( int attrId, int attrVal )
     * \details Set the attribute value for the matching attrID to attrVal.
     * \param [in] attrId Integer value representing a member of ATTRIBUTE_LIST.
     * \param [in] attrVal Integer value to set this attribute to.
     *
     * Example Usage:
     * \code
     * CCharacter *myPlayer = new CCharacter(); // Create new player object.
     * myPlayer->setAttribute( ATTRIBUTE_LIST::ATTR_HEALTH, 10 ); // Set player's health to 10.
     * \endcode
     * \see ATTRIBUTE_LIST
     */
    void setAttribute( int attrId, int attrVal );

protected:
    int m_direction; /**< Character's current direction. */
    int m_prevDirection; /**< Character's previous direction. */
    int m_index; /**< Current position in the animation index. */

	std::vector <ALLEGRO_BITMAP*> m_bmpImage; /**< Contains the animation images for movement. */

    bool m_inMotion; /**< Movement flag. True equals in-motion. */
	bool m_isVisible; /**< Visibility flag. True equals visible. */
	CharacterType m_type; /**< Character's type. \see CharacterType */
	Point m_previousPos; /**< Player's previous x,y position. \see Point */
	int m_indexTileSheetX; /**< \warning MAY REMOVE. */
	int m_indexTileSheetY; /**< \warning MAY REMOVE. */

	// Various other attributes
	/**
	 * \var std::vector <int> m_attributes
	 * \details Vector containing all numerical attributes of this character.
	 */
	std::vector <int> m_attributes;
};

#endif	// CHARACTER_H
