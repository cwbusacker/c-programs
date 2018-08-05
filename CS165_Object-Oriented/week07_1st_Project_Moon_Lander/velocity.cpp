#include "velocity.h"
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
* Purpose: set the x by taking the ddx float parameter
* and adding it to dx.
************************************************/
void Velocity::setDx(float ddx)
{
   dx += ddx;
}

/***********************************************
* Function: setDy()
* Purpose: set the y by taking the ddy float parameter
* and adding it to dy.
************************************************/
void Velocity::setDy(float ddy)
{
   dy += ddy;
}