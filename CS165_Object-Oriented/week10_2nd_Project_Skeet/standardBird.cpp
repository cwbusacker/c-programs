#include "standardBird.h"

/********************************************************
* Function: StandardBird
* Purpose: start by drawing the bird at the location
* set by BaseBird.
*********************************************************/
StandardBird::StandardBird()
{
   draw();
}

/********************************************************
* Function: draw
* Purpose: draw the bird at the location using UIdraw.
*********************************************************/
void StandardBird::draw()
{  
   drawCircle(location, 15);
}

/********************************************************
* Function: advance
* Purpose: set the velocity and then draw the bird on
* the screen in the new location based on that velocity.
*********************************************************/
void StandardBird::advance()
{
   velocity.setDx(random(3, 6));
   if (startingy >= 0)
   {
      velocity.setDy(random(-4, 0));
   }
   else if (startingy < 0)
   {
      velocity.setDy(random(0, 4));
   }
   location.addX(velocity.getDx());
   location.addY(velocity.getDy());
   draw();
}

/********************************************************
* Function: hit
* Purpose: set the bird to not alive and return 1 point
* for hitting the standard bird.
*********************************************************/
int StandardBird::hit()
{
   alive = false;
   return 1;
}

