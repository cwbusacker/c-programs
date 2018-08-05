/***********************************************************************
* Header File:
*    Velocity: set the Velocity
* Author:
*    Chase Busacker
* Summary:
*    
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
   Velocity();
   float getDx();
   float getDy();
   void setDx(float dx);
   void setDy(float dy);
private:
   float dx;
   float dy;
};

#endif
