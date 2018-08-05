#include "ship.h"
#define M_PI       3.14159265358979323846
#define deg2rad(value) ((M_PI / 180) * (value))

/********************************************
* Function: Ship Constructor
* Purpose: when the Ship is created, it's point will
* be at 0,0 and it's angle will be written at 0.
*********************************************/
Ship::Ship()
{
   setPoint(0, 0);
   angle = 0;
}

/********************************************
* Function: advance
* Purpose: set the Velocity of the ship to the
* current velocity + the Thrust in the direction
* the ship is facing.
*********************************************/
void Ship::advance()
{
   setVelocity(velocity.getDx() + THRUST_AMOUNT * cos(deg2rad(angle+90)),
      velocity.getDy() + THRUST_AMOUNT * sin(deg2rad(angle+90)));
}

/********************************************
* Function: draw
* Purpose: draw the ship after adding the current
* velocity to the x and y directions. Then,
* draw the ship in the new location.
*********************************************/
void Ship::draw()
{
   location.addX(velocity.getDx());
   location.addY(velocity.getDy());
   drawShip(location, angle, isThrusting);
}

/********************************************
* Function: SetThrust
* Purpose: set the thrust to the parameter.
* This determines if the thrust will be drawn
* or not.
*********************************************/
void Ship::setThrust(bool isThrusting)
{
   this ->isThrusting = isThrusting;
}

/********************************************
* Function: rotateRight
* Purpose: rotate the ship to the right.
*********************************************/
void Ship::rotateRight()
{
   this->angle -= ROTATE_AMOUNT;
}

/********************************************
* Function: rotateLeft
* Purpose: rotate the ship to the left.
*********************************************/
void Ship::rotateLeft()
{
   this->angle += ROTATE_AMOUNT;
}

/********************************************
* Function: getAngle
* Purpose: return the angle of the ship.
*********************************************/
int Ship::getAngle() const
{
   return angle;
}

/********************************************
* Function: setAngle
* Purpose: set the Angle of the ship to the angle
* parameter.
*********************************************/
void Ship::setAngle(int angle)
{
   this->angle = angle;
}

/********************************************
* Function: drawLives
* Purpose: draw the Lives the same way the ship
* is drawn starting at x location -195 + 10 pixels
* for every life. Draw until there are no lives left.
*********************************************/
void Ship::drawLives(int lives)
{
   int offset = 5;
   while (lives > 0)
   {
      Point lifedrawlocation(-195 + offset, 170);
      drawShip(lifedrawlocation, 0, false);
      offset += 10;
      lives--;
   }
}

/********************************************
* Function: Debris Constructor
* Purpose: take the paramters and set the variables
* for each debris item.
*********************************************/
Debris::Debris(int number, Point shipPoint, int angle)
{
   setPoint(shipPoint.getX(), shipPoint.getY());
   this->angle = angle;
   this->number = number;
   switch (number)
   {
   case 0:
      driftangle = angle - 90;
      break;
   case 1:
      driftangle = angle - 90 + 122;
      break;
   case 2:
      driftangle = angle - 90 - 122;
      break;
      
   }
   setVelocity(0.8*cos(deg2rad(driftangle)), 0.8*sin(deg2rad(driftangle)));
}

/********************************************
* Function: advance
* Purpose: advance the debris in the direction
* of the Velocity.
*********************************************/
void Debris::advance()
{
   location.addX(velocity.getDx());
   location.addY(velocity.getDy());
}

/********************************************
* Function: draw
* Purpose: draw the Ship debris based on the location,
* angle, and number.
*********************************************/
void Debris::draw()
{
   drawShipDebris(location, angle, number);
}
