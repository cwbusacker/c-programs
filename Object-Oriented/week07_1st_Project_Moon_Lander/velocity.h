/***********************************************************************
* Header File:
*    Lander : Draw the Lander on the screen
* Author:
*    Chase Busacker
* Summary:
*    Stub file for the lander class
************************************************************************/


#ifndef VELOCITY_H
#define VELOCITY_H

#include <iostream>
#include "point.h"
#include "velocity.h"

/*********************************************
* VELOCITY
* Stub Functions for Velocity
*********************************************/
class Velocity
{
public:
   float getDx();
   float getDy();
   void setDx(float ddx);
   void setDy(float ddy);
private:
   float dx;
   float dy;
};

#endif
