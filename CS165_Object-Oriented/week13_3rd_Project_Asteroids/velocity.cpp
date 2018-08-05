#include "velocity.h"

/***********************************************
* Function: Velocity constructor
* Purpose: set the Velocity to 0.
************************************************/
Velocity::Velocity()
{
   dx = 0;
   dy = 0;
}

/***********************************************
* Function: getDx()
* Purpose: return the change in x (left to right)
* aka the velocity in the x direction.
************************************************/
float Velocity::getDx()
{
   return dx;
}
/***********************************************
* Function: getDy()
* Purpose: return the change in y (top to bottom)
* aka the velocity in the y direction.
************************************************/
float Velocity::getDy()
{
   return dy;
}

/***********************************************
* Function: setDx()
* Purpose: set the dx to the passed in parameter.
***********************************************/
void Velocity::setDx(float dx)
{
   this->dx = dx;
}

/***********************************************
* Function: setDy()
* Purpose: set the dy to the passed in parameter.
************************************************/
void Velocity::setDy(float dy)
{
   this->dy = dy;
}