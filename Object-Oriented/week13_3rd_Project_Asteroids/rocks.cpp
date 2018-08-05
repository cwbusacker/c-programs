#include "rocks.h"
#include "uiDraw.h"
#include <cmath>

#define M_PI       3.14159265358979323846
#define deg2rad(value) ((M_PI / 180) * (value))

/********************************************
* Function: Rock constructor
* Purpose: set the spin direction top either
* positive 1 or negative 1.
*********************************************/
Rock :: Rock()
{
   spindirection = 0;
   while (spindirection == 0)
   {
      spindirection = random(-1,2);
   }
}

/********************************************
* Function: getRadius
* Purpose: return the radius of the rock.
*********************************************/
int Rock::getRadius()
{
   return radius;
}

/********************************************
* Function: getRockType
* Purpose: Return the Rock Type string.
*********************************************/
string Rock::getRockType()
{
   return rockType;
}

/********************************************
* Function: BigRock Constructor
* Purpose: set the variables of the Big Rock:
* 1. Set the direction the rock will travel to
*    a random angle.
* 2. Set the velocity of the rock to 1.
* 3. Set the location of the BigRock to a 
*    random area on the screen.
* 4. Set the angle that the BigRock starts at
*    to 0.
* 5. Set the radius to 16.
* 6. Set the rockType to "BigRock"
*********************************************/
BigRock::BigRock()
{
   int randomAngle = random(0, 360);
   setVelocity(1 * cos(deg2rad(randomAngle)), 1 * sin(deg2rad(randomAngle)));
   setPoint(random(-200, 200), random(-200, 200));
   angle = 0;
   radius = 16;
   rockType = "BigRock";
   
  
}

/********************************************
* Function: advance
* Purpose: advance the ships x and y location
* using the velocity. Rotate the rock by adding
* the BIG_ROCK_SPIN (times the spindirection) to the angle.
*********************************************/
void BigRock::advance()
{
   location.addX(velocity.getDx());
   location.addY(velocity.getDy());
   angle += (BIG_ROCK_SPIN * spindirection);
}

/********************************************
* Function: hit
* Purpose: when the Bigrock is hit, award 20 points.
*********************************************/
int BigRock::hit()
{
   return 20;
}

/********************************************
* Function: draw
* Purpose: draw the Large Asteroid in the location
* rotated at the angle.
*********************************************/
void BigRock::draw()
{
   drawLargeAsteroid(location, angle);
}

/********************************************
* Function: MediumRock Constructor
* Purpose: set the variables of the Medium Rock:
* 1. Set the starting Point of the Medium Rock to
*    the startlocation parameter.
* 2. Set the velocity of the rock to the x and y 
*    velocity parameters.
* 3. Set the angle that the MediumRock starts at
*    to 0.
* 4. Set the radius to 8.
* 5. Set the rockType to "MediumRock"
*********************************************/
MediumRock::MediumRock(Point startlocation, float xvelocity, float yvelocity)
{
   setVelocity(xvelocity, yvelocity);
   setPoint(startlocation.getX(), startlocation.getY());
   angle = 0;
   radius = 8;
   rockType = "MediumRock";
   
}

/********************************************
* Function: advance
* Purpose: advance the ships x and y location
* using the velocity. Rotate the rock by adding
* the MEDIUM_ROCK_SPIN (times the spindirection) to the angle.
*********************************************/
void MediumRock::advance()
{
   location.addX(velocity.getDx());
   location.addY(velocity.getDy());
   angle += (MEDIUM_ROCK_SPIN * spindirection);
}

/********************************************
* Function: draw
* Purpose: draw the Medium Asteroid in the location
* rotated at the angle.
*********************************************/
void MediumRock::draw()
{
   
   drawMediumAsteroid(location, angle);
}

/********************************************
* Function: hit
* Purpose: when the Mediumrock is hit, award 50 points.
*********************************************/
int MediumRock::hit()
{
   return 50;
}

/********************************************
* Function: SmallRock Constructor
* Purpose: set the variables of the Small Rock:
* 1. Set the starting Point of the Small Rock to
*    the startlocation parameter.
* 2. Set the velocity of the rock to the x and y
*    velocity parameters.
* 3. Set the angle that the MediumRock starts at
*    to 0.
* 4. Set the radius to 4.
* 5. Set the rockType to "SmallRock"
*********************************************/
SmallRock::SmallRock(Point startlocation, float xvelocity, float yvelocity)
{
   //int randomAngle = random(0, 360);
   setVelocity(xvelocity, yvelocity);
   setPoint(startlocation.getX(), startlocation.getY());
   angle = 0;
   radius = 4;
   rockType = "SmallRock";
   
}

/********************************************
* Function: advance
* Purpose: advance the ships x and y location
* using the velocity. Rotate the rock by adding
* the SMALL_ROCK_SPIN (times the spindirection) to the angle.
*********************************************/
void SmallRock::advance()
{
   location.addX(velocity.getDx());
   location.addY(velocity.getDy());
   angle += (SMALL_ROCK_SPIN *spindirection);
}

/********************************************
* Function: draw
* Purpose: draw the Small Asteroid in the location
* rotated at the angle.
*********************************************/
void SmallRock::draw()
{
   
   drawSmallAsteroid(location, angle);
}

/********************************************
* Function: hit
* Purpose: when the Smallrock is hit, award 100 points.
*********************************************/
int SmallRock::hit()
{
   return 100;
}
