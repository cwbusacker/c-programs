
#include "lander.h"
Lander::Lander()
{
   landerPoint.setX(random(-200, 200));
   landerPoint.setY(random(0, 200));
}
/***********************************************
 * Function: setFuel
 * Purpose: Set the fuel to 500 for the beginning
 * of the game
 *************************************************/
void Lander::setFuel(int fuel)
{
   this ->fuel = fuel;
}

/***********************************************
* Function: setCanThrust
* Purpose: Set canThrust to true.
************************************************/
void Lander::setCanThrust()
{
   canThrust = true;
}

/***********************************************
* Function: getPoint
* Purpose: return the point of the lander.
************************************************/
Point Lander::getPoint() const
{
   return landerPoint;
}

/***********************************************
* Function: getVelocity
* Purpose: return the Velocity of the lander.
************************************************/
Velocity Lander::getVelocity() const
{
   return landerVelocity;
}

/***********************************************
* Function: isAlive
* Purpose: Stub Function.
************************************************/
bool Lander::isAlive()
{
   return alive;
}

/***********************************************
* Function: isLanded
* Purpose: return true or false based on if the
* lander has landed. Currently a stub function only.
************************************************/
bool Lander::isLanded()
{
   return landed;
}

/***********************************************
* Function: applyGravity
* Purpose: send the amount of gravity to the
* Velocity class and give the lander that velocity
* in the downward direction.
************************************************/
void Lander::applyGravity(float gravity)
{
   landerVelocity.setDy(-gravity);
}

/***********************************************
* Function: setAlive
* Purpose: stub.
************************************************/
void Lander::setAlive(bool checkAlive)
{
   alive = checkAlive;
}

/***********************************************
* Function: setLanded
* Purpose: stub
************************************************/
void Lander::setLanded(bool checkLanded)
{
   landed = checkLanded;
}

/***********************************************
* Function: applyThrustBottom
* Purpose: give the lander velocity upward from
* the bottom thrust. Then, take away the amount of
* fuel necessary to have thrust.
************************************************/
void Lander::applyThrustBottom()
{
   if (fuel >= 3)
   {
      setCanThrust();
      landerVelocity.setDy(0.3);
      fuel -= 3;
   }
   else if (fuel < 3 && fuel > 0)
   {
      setCanThrust();
      landerVelocity.setDy(0.3);
      fuel = 0;
   }
}

/***********************************************
* Function: applyThrustLeft
* Purpose: give the lander velocity rightward from
* the left thrust. Then, take away the amount of
* fuel necessary to have thrust.
************************************************/
void Lander::applyThrustLeft()
{
   if (fuel > 0)
   {
      setCanThrust();
      landerVelocity.setDx(0.1);
      fuel -= 1;
   }
}

/***********************************************
* Function: applyThrustRight
* Purpose: give the lander velocity leftward from
* the right thrust. Then, take away the amount of
* fuel necessary to have thrust.
************************************************/
void Lander::applyThrustRight()
{
   if (fuel > 0)
   {
      setCanThrust();
      landerVelocity.setDx(-0.1);
      fuel -= 1;
   }
}

/***********************************************
* Function: draw
* Purpose: draw the lander on the screen at the
* given landerpoint.
************************************************/
void Lander::draw()
{
   if (!landed && alive)
   {
      setLanderPoint();
      drawLander(landerPoint);
   }
   else if (landed)
      drawLander(landerPoint);
   else if (!alive)
   {
      canThrust = false;
      drawLanderCrash(landerPoint);
   }
}

/***********************************************
* Function: setLanderpoint
* Purpose: set the landerpoint using the current
* point and the getDx/Dy from landerVelocity.
************************************************/
void Lander::setLanderPoint()
{
   landerPoint.setX(landerPoint.getX() + landerVelocity.getDx());
   landerPoint.setY(landerPoint.getY() + landerVelocity.getDy());
}

/***********************************************
* Function: getCanThrust
* Purpose: return a boolian. True if there is fuel.
* Not true if fuel is 0.
************************************************/
bool Lander::getCanThrust()
{
   if (fuel == 0 || landed)
      return !canThrust;
   else
      return canThrust;
}

/***********************************************
* Function: getFuel
* Purpose: return the fuel integer when called.
************************************************/
int  Lander::getFuel()
{
   return fuel;
}
/***********************************************
* Function: drawNumber
* Purpose: stub function.
************************************************/
//void Lander::drawNumber(Point fuelLocation, int fuelNumber)
//{
//}