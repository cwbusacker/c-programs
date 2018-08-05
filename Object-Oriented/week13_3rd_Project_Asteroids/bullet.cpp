#include "bullet.h"

/********************************************
* Function: fire
* Purpose: create the bullet as soon as it is fired.
* start the drawcount at 0. Put the point of the bullet
* in the same location as the point parameter which came
* from game.cpp. Set the Velocity of the bullet to the
* BULLET_SPEED in the direction of the ship's angle plus the
* Ship's velocity.
*********************************************/
void Bullets::fire(Point point, float angle, Velocity shipVelocity)
{
   drawcount = 0;
   location = point;
   setVelocity(BULLET_SPEED * cos(angle* 3.1415 / 180)+shipVelocity.getDx(), 
      BULLET_SPEED * sin(angle* 3.1415 / 180)+shipVelocity.getDy());
}

/********************************************
* Function: advance
* Purpose: advance the bullet to the new location
* for the next frame. Add the x velocity to the x
* location and the y velocity to the y location.
*********************************************/
void Bullets::advance()
{
   location.addX(velocity.getDx());
   location.addY(velocity.getDy());
}

/********************************************
* Function: draw
* Purpose: draw the bullet if it has not been
* drawn forty times. Otherwise, kill the bullet.
*********************************************/
void Bullets::draw()
{
   if (drawcount <= BULLET_LIFE)
   {
      drawDot(location);
      drawcount++;
   }
   else
   {
      kill();
   }
}
