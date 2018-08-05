/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "rocks.h"
#include "ship.h"
#include "bullet.h"
#include <vector>
using namespace std;

#define SHIP_RADIUS         10


class Game
{
public:
   Game(Point tl, Point br);
   void cleanUpZombies();
   void advance();
   void handleInput(const Interface &ui);
   void draw(const Interface &ui);
   void advanceRocks();
   void advanceBullets();
   void wrapFlyingObjects(flyingObjects &object);
   void handleCollisions();
   float getClosestDistance(const flyingObjects &obj1, const flyingObjects &obj2) const;
   void nextLevel();
   void gameOver();
   void makeRockDebris(Rock &rock);

private:
   vector <Rock*> rock;
   Ship ship;
   vector <Bullets> bullets;
   Point topLeft;
   Point bottomRight;
   int score;
   int lives;
   int hyperSpaceuses;
   int gamelevel;
   bool gameover;
   int lifeawardcount;
   int pause;
   vector <Debris*> debris;
};



#endif /* GAME_H */
