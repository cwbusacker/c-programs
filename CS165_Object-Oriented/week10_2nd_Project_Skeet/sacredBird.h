#ifndef SACRED_BIRD_H
#define SACRED_BIRD_H
#include "flyingObjects.h"
#include "baseBird.h"

class SacredBird :public BaseBird
{
public:
   SacredBird();
   void draw();
   void advance();
   int hit();
};
#endif // !SACRED_BIRD_H
