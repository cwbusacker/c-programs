#ifndef BASE_BIRD_H
#define BASE_BIRD_H

#include "point.h"
#include "flyingObjects.h"
#include "uiDraw.h"
#include "uiInteract.h"

class BaseBird: public flyingObjects
{
protected:
   int startingy;
  
public:
   /********************************************************
    * Function: BaseBird
    * Purpose: set the random point where the bird starts and
    * set the bird to alive and set the startingy variable to 
    * allow the y velocity to be determined.
    *********************************************************/
   BaseBird()
   {
      setPoint(-200, random(-200, 200));
      startingy = getPoint().getY();
      alive = true;
   }
   virtual int hit() = 0;
   virtual void draw() = 0;
};

#endif //BASE_BIRD_H