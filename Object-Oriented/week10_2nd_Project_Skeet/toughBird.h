#ifndef TOUGH_BIRD_H
#define TOUGH_BIRD_H
#include "flyingObjects.h"
#include "baseBird.h"

class ToughBird :public BaseBird
{
private:
   int hitsLeft;
public:
   ToughBird();
   void draw();
   void advance();
   virtual int hit();
};
#endif // !TOUGH_BIRD_H
