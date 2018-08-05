#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5

#include <vector>
#include "flyingObject.h"
using namespace std;

class Ship :public flyingObjects
{
private:
   bool isThrusting;
   int angle;
   int lives;
public:
   Ship();
   void advance();
   void draw();
   void setThrust(bool isThrusting);
   void rotateRight();
   void rotateLeft();
   int getAngle() const;
   void setAngle(int angle);
   void drawLives(int lives);
   
};

class Debris : public flyingObjects
{
public:
   Debris(int number, Point shipPoint, int angle);
   void draw();
   void advance();

private:
   int angle;
   int driftangle;
   int number;
};

#endif /* ship_h */
