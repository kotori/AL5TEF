/**
 * \file Collidable.h
 * \author Kotori
 *
 * This class creates the base object for collisions. Every character that is loaded is also
 *  a member of this class. The x, y and width, height variables for every character is stored here.
 */

#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "Util.h"

/**
 * \class CCollidable
 * \details Collision class for characters.
 */
class CCollidable
{
public:
	/**
	 * \fn CCollidable( void )
	 * \details class constructor.
	 */
	CCollidable( void );

	/**
	 * \fn ~CCollidable( void )
	 * \details class destructor.
	 */
	~CCollidable( void );

	/**
	 * \fn Point getPos()
	 * \details returns the current x,y position
	 * \returns Point value representing this object's coordinates.
	 */
	Point getPos();

	/**
     * \fn Rect getContainer()
	 * \details returns the current x,y,w,h values for this object. The container object returned is \b m_container.
	 * \returns Rect object representing this object's coordinates and size.
     */
	Rect getContainer();

	/**
	 * \fn void setPos( Point pos )
	 * \details Set the object's current position.
	 * \param [in] pos Point object representing this object's x and y values.
	 * \see getPos()
	 */
	void setPos( Point pos );

	/**
	 * \fn void setPos( int x, int y )
	 * \details Set the object's current position.
	 * \param [in] x X-axis coordinate.
	 * \param [in] y Y-axis coordinate.
	 */
	void setPos( int x, int y );

	/**
	 * \fn void setContainer( Rect container )
	 * \details Set the object's container. This will ensure the x,y,w, and h variables are setup properly.
	 * \param [in] container Rect object representing this objects position and size.
	 * \see setContainer( Point pos, int w, int h )
	 * \see setContainer( int x, int y, int w, int h )
	 */
	void setContainer( Rect container );

	/**
     * \fn void setContainer( Point pos, int w, int h )
     * \details Set the object's container. This will ensure the x,y,w, and h variables are setup properly.
     * \param [in] pos Point object representing this objects position.
	 * \param [in] w Width of this object in pixels.
	 * \param [in] h Height of this object in pixels.
     * \see setContainer( Rect container )
     * \see setContainer( int x, int y, int w, int h )
     */
	void setContainer( Point pos, int w, int h );

	/**
     * \fn void setContainer( int x, int y, int w, int h )
     * \details Set the object's container. This will ensure the x,y,w, and h variables are setup properly.
     * \param [in] x X-axis position.
	 * \param [in] y Y-axis position.
	 * \param [in] w Width of this object in pixels.
	 * \param [in] h Height of this object in pixels.
     * \see setContainer( Rect container )
     * \see setContainer( Point pos, int w, int h )
     */
	void setContainer( int x, int y, int w, int h );

	/**
	 * \fn virtual bool isColliding( CCollidable *c )
	 * \details Determines in this object is colliding with the passed CCollidable object pointer.
	 * \param [in] c CCollidable object pointer.
	 * \returns True if a collision is going to happen, False if no collision detected.
	 */
	virtual bool isColliding( CCollidable *c );

	/**
     * \fn virtual bool isColliding( Rect r )
	 * \details Determines in this object is colliding with the passed CCollidable object pointer.
     * \param [in] r Rect object.
     * \returns True if a collision is going to happen, False if no collision detected.
     */
	virtual bool isColliding( Rect r );

	/**
	 * \fn void getX()
	 * \details Return the X-axis location of this object.
	 * \returns float representing this object's X-axis location. Returns: \b m_container.x
	 */
	float getX();

	/**
         * \fn void getY()
         * \details Return the Y-axis location of this object.
         * \returns float representing this object's Y-axis location. Returns: \b m_container.y
         */
	float getY();

	/**
         * \fn void getPrevX()
         * \details Return the previous X-axis location of this object.
         * \returns float representing this object's previous X-axis location. Returns: \b m_prevContainer.x
         */
	float getPrevX();

	/**
         * \fn void getPrevY()
         * \details Return the previous Y-axis location of this object.
         * \returns float representing this object's previous Y-axis location. Returns: \b m_prevContainer.y
         */
	float getPrevY();

	/**
	 * \fn void setX( int pos )
	 * \details Set's the X-axis location of this object. The will update the following: \b m_container.x
	 * \param [in] pos X-axis location of this object.
	 */
	void setX( int pos );

	/**
         * \fn void setY( int pos )
         * \details Set's the Y-axis location of this object. The will update the following: \b m_container.y
         * \param [in] pos Y-axis location of this object.
         */
	void setY( int pos );

protected:
	Rect m_container;	/**< Rect object representing this object's location and dimensions. */
	Rect m_prevContainer;	/**< Rect object representing this object's previous location and dimensions. */
};

#endif	// COLLIDABLE_H
