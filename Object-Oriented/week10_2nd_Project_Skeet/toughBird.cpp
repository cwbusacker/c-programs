#include "toughBird.h"

/********************************************************
* Function: StandardBird
* Purpose: start by drawing the bird at the location
* set by BaseBird. Also, since this bird has a hitsleft
* variable, set it to start at 3.
*********************************************************/
ToughBird::ToughBird()
{
   hitsLeft = 3;
   draw();
}

/********************************************************
* Function: draw
* Purpose: draw the bird at the location using UIdraw.
* include the hitsleft in the center of the bird.
*********************************************************/
void ToughBird::draw()
{
   drawToughBird(location, 15, hitsLeft);
}

/********************************************************
* Function: advance
* Purpose: set the velocity and then draw the bird on
* the screen in the new location based on that velocity.
*********************************************************/
void ToughBird::advance()
{
   velocity.setDx(random(2, 4));
   if (startingy >= 0)
   {
      velocity.setDy(random(-3, 0));
   }
   else if (startingy < 0)
   {
      velocity.setDy(random(0, 3));
   }
   location.addX(velocity.getDx());
   location.addY(velocity.getDy());
   draw();
}

/********************************************************
* Function: hit
* Purpose: subtract one from hits left. If hitsleft is now
* zero, return 3 points for killing the tough bird, otherwise
* only reward 1 point.
*********************************************************/
int ToughBird::hit()
{
   hitsLeft -= 1;
   if (hitsLeft > 0)
      return 1;
   else if (hitsLeft == 0)
   {
      alive = false;
      return 3;
   }
}

