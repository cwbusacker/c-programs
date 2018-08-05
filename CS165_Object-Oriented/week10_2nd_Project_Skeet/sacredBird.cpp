#include "sacredBird.h"

/********************************************************
* Function: SacredBird
* Purpose: start by drawing the bird at the location
* set by BaseBird.
*********************************************************/
SacredBird::SacredBird()
{
   draw();
}

/********************************************************
* Function: draw
* Purpose: draw the bird at the location using UIdraw.
*********************************************************/
void SacredBird::draw()
{
   drawSacredBird(location, 15);
}

/********************************************************
* Function: advance
* Purpose: set the velocity and then draw the bird on
* the screen in the new location based on that velocity.
*********************************************************/
void SacredBird::advance()
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
* Purpose: set the bird to not alive and return -10 points
* to penalize for hitting the SacredBird.
*********************************************************/
int SacredBird::hit()
{
   alive = false;
   return -10;
}

