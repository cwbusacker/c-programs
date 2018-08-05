#ifndef rocks_h
#define rocks_h
#include "flyingObject.h"

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10



// Define the following classes here:
class Rock:public flyingObjects
{
public:
   Rock();
   virtual void advance() = 0;
   virtual void draw() = 0;
   virtual int hit() = 0;
   string getRockType();
   int getRadius();
   int radius;
protected:
   int angle;
   string rockType;
   int spindirection;
};
class BigRock:public Rock
{
public:
   BigRock();
   virtual void draw();
   virtual void advance();
   virtual int hit();
   
};

class MediumRock :public Rock
{
public:
   MediumRock(Point startlocation, float xvelocity, float yvelocity);
   virtual void advance();
   virtual void draw();
   virtual int hit();
};

class SmallRock : public Rock
{
public:
   SmallRock(Point startlocation, float xvelocity, float yvelocity);
   virtual void advance();
   virtual void draw();
   virtual int hit();
};
#endif /* rocks_h */
