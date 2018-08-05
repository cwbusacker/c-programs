#include "flyingObjects.h"

/********************************************************
* Function: getPoint
* Purpose: return the location of the flying object.
*********************************************************/
Point flyingObjects::getPoint()
{
   return location;
}

/********************************************************
* Function: setPoint
* Purpose: set the location of the flyint object.
*********************************************************/
void flyingObjects::setPoint(float x, float y)
{
   location.setX(x);
   location.setY(y);
}

/********************************************************
* Function: getVelocity
* Purpose: return the Velocity of the flying object.
*********************************************************/
Velocity flyingObjects::getVelocity()
{
   return velocity;
}

/********************************************************
* Function: setVelocity
* Purpose: set the velocity of the flying object.
*********************************************************/
void flyingObjects::setVelocity(float dx, float dy)
{
   velocity.setDx(dx);
   velocity.setDy(dy);
}

/********************************************************
* Function: isAlive
* Purpose: return the true as long as the object is alive.
* The object will be alive until an inherited class sets
* it to false or if kill is called.
*********************************************************/
bool flyingObjects::isAlive()
{
   return alive;
}

/********************************************************
* Function: kill
* Purpose: sets alive to false when called.
*********************************************************/
void flyingObjects::kill()
{
   alive = false;
}
