#include "bullets.h"
#include "uiDraw.h"
#include "rifle.h"
/********************************************************
* Function: Bullet constructor
* Purpose: set the velocity of the bullet to zero when it
* is first drawn.
*********************************************************/
Bullet::Bullet()
{
 
   velocity.setDx(0);
   velocity.setDy(0);
}

/********************************************************
* Function: draw
* Purpose: draw a dot as the bullet in the location of
* the bullet.
*********************************************************/
void Bullet::draw()
{
   drawDot(location);
}

/********************************************************
* Function: fire
* Purpose: give the bullet velocity when fired.
*********************************************************/
void Bullet::fire(Point point, float angle)
{
   location = point;
   setVelocity(-10 * cos(angle* 3.1415 / 180), 10 * sin(angle* 3.1415 / 180));  
}

/********************************************************
* Function: advance
* Purpose: advance the bullet to the next location based
* on the set velocity.
*********************************************************/
void Bullet::advance()
{
   location.addX(velocity.getDx());
   location.addY(velocity.getDy());
}
