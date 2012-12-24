#include "Collidable.h"


CCollidable::CCollidable(void)
{
    m_prevContainer.x = 0;
    m_prevContainer.y = 0;
    m_prevContainer.w = 0;
    m_prevContainer.h = 0;
    m_container.x = 0;
    m_container.y = 0;
    m_container.w = 0;
    m_container.h = 0;
}

CCollidable::~CCollidable(void)
{
    // Empty destructor.
}

Point CCollidable::getPos()
{
	Point pos;
	pos.x = m_container.x;
	pos.y = m_container.y;

	return pos;
}

float CCollidable::getPrevX()
{
    return m_prevContainer.x;
}

float CCollidable::getPrevY()
{
    return m_prevContainer.y;
}

Rect CCollidable::getContainer()
{
	return m_container;
}

void CCollidable::setPos( Point pos )
{
    m_prevContainer = m_container;
	m_container.x = pos.x;
	m_container.y = pos.y;

}

void CCollidable::setPos( int x, int y )
{
    m_prevContainer = m_container;
	m_container.x = x;
	m_container.y = y;
}

void CCollidable::setContainer( Rect container )
{
    m_prevContainer = m_container;
	m_container = container;
}

void CCollidable::setContainer( Point pos, int w, int h )
{
    m_prevContainer = m_container;
	setContainer( pos.x, pos.y, w, h );
}

void CCollidable::setContainer( int x, int y, int w, int h )
{
    m_prevContainer = m_container;
	m_container.x = x;
	m_container.y = y;
	m_container.w = w;
	m_container.h = h;
}

float CCollidable::getX()
{
    return m_container.x;
}

float CCollidable::getY()
{
    return m_container.y;
}

void CCollidable::setX( int pos )
{
    m_prevContainer = m_container;
    m_container.x = pos;
}

void CCollidable::setY( int pos )
{
    m_prevContainer = m_container;
    m_container.y = pos;
}

bool CCollidable::isColliding( CCollidable *c )
{
	return isColliding( c->getContainer() );
}

bool CCollidable::isColliding( Rect r )
{
	if(m_container.y + m_container.h < r.y)
		return false;
	if(m_container.y > r.y + r.h)
		return false;
	if(m_container.x + m_container.w < r.x)
		return false;
	if(m_container.x > r.x + r.w)
		return false;

	return true;
}
