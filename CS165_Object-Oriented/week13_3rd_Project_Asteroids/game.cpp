/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"

#include <limits>
#include <algorithm>
#include <vector>

#define M_PI       3.14159265358979323846
#define deg2rad(value) ((M_PI / 180) * (value))
using namespace std;

/************************************************************
 * Function: Game Constructor
 * Purpose: Set up the beginning of the game and all the variables
 * that are included.
*************************************************************/
Game::Game(Point tl, Point br): topLeft (tl), bottomRight(br)
{
   
   //All games start with level 1.
   gamelevel = 1;                 

   /* With the addition of levels, I wanted the game to initialize with 3
      rocks and with each level add 2 more. Switch these for loops
      for the game to intialize with 5. (Game will run normally 
      and as written if level 2 is reached)*/
   //for (int i = 0; i < 5; i++)
   for (int i = 0; i < 1 + 2 * gamelevel; i++)
   {
      Rock *newRock;
      newRock = new BigRock;
      rock.push_back(newRock);
   }

   //Current life + 3 lives equals 4 lives. Just like the original game.
      lives = 5;

   //Score starts at 0. No points earned yet.
      score = 0;

   //Hyperspace uses. The amount of times the user can HyperSpace.
      hyperSpaceuses = 5;

   //The Game just started. SO obviously the game isn't over.
   //This will become true if lives goes to zero. Written later in code.
      gameover = false;
      playAgain = false; //initialize to false, will change to true if game ends.

   //lifeawardcount. This is used in awarding lives every 5000 points earned.
      lifeawardcount = 0;
     
}

/************************************************************
 * Function: cleanUpZombies
 * Purpose: Delete Bullets that are no longer being drawn.
*************************************************************/
void Game::cleanUpZombies()
{
   
   vector<Bullets>::iterator iteratorBullet = bullets.begin();
   while (iteratorBullet != bullets.end())
   {
      Bullets bullet = *iteratorBullet;

      if (!bullet.isAlive())
      {
        
          iteratorBullet = bullets.erase(iteratorBullet);
      }
      else
      {
         iteratorBullet++; // advance
      }
   }

}

/************************************************************
 * Function: Advance
 * Purpose: To advance the frame once forward before drawing and
 * take care of anything that occurs in the next frame.
*************************************************************/
void Game::advance()
{

   //wrap an object from one side of the screen to the other.
   //needs to be called for each type of flying object.
   wrapFlyingObjects(ship);
   for (int i = 0; i < rock.size(); i++)
   {
      wrapFlyingObjects(*rock[i]);
   }
   for (int i = 0; i < bullets.size(); i++)
   {
      wrapFlyingObjects(bullets[i]);
   }
   //Bullet to Rock collisions, Rock to Ship collisions.
   handleCollisions();

   //Advance all living Rocks to the next position on the screen.
   advanceRocks();

   //Advance all Bullets
   advanceBullets();

   //Delete Bullets that have lived 40 frames or longer.
   cleanUpZombies();

   //If debris exists, advance it.
   if (debris.size())
   {
      for (int i = 0; i < 3; i++)
      {
         debris[i]->advance();
      }
   }
}

/************************************************************
 * Function: advanceBullets
 * Purpose: Advance all Bullets.
 *************************************************************/
void Game::advanceBullets()
{
   for (int i = 0; i < bullets.size(); i++)
   {
      bullets[i].advance();
   }
}

/************************************************************
 * Function: handleInput
 * Purpose: Inputs include:
 *
 * Right Arrow:         Rotates the ship to the right.
 * Left Arrow:          Rotates the ship to the left.
 * Up Arrow:            Thrusts the ship in the direction it's facing.
 * H char key:          Uses HyperSpace.
 * Spacebar:            Fires Bullets.

 * Handles these inputs when they occur.
*************************************************************/
void Game::handleInput(const Interface & ui)
{
   //Right arrow key.
   if (ui.isRight())
   {
      ship.rotateRight();
   }

   //Left arrow key.
   if (ui.isLeft())
   {
      ship.rotateLeft();
   }

   //Spacebar.
   if (ui.isSpace() && !gameover /*If game ends, stop firing bullets.*/)
   {
      Bullets newBullet;
      newBullet.fire(ship.getPoint(), ship.getAngle()+90, ship.getVelocity());
      bullets.push_back(newBullet);
   }

   //Up arrow.
   if (ui.isUp() && !gameover /*If game ends, no moving the ship*/)
   {
      ship.advance();
      ship.setThrust(true);
   }
   //If arrow stops being pressed, setThrust needs
   //to be set back to false.
   else
   {
      ship.setThrust(false);
   }

   //H key.
   if (ui.isH())
   {
      if (hyperSpaceuses > 0)
      {
         //Randomly place the ship in a new location.
         ship.setPoint(random(-200, 200), random(-200, 200)); 

         //Set Velocity back to 0.
         ship.setVelocity(0, 0);

         //Take a hyperSpace use away.
         hyperSpaceuses -= 1;
      }
   }
 
   if (ui.isY() && pause > 71)
   {
      playAgain = true;
   }
   else if (ui.isN() && pause > 71)
   {
      exit(0);
   }
}
   



/************************************************************
 * Function: draw
 * Purpose: draw anything that appears on the screen. This includes:
 *
 * Rocks:               Big, Medium, or Small.
 * Ship:                The Spaceship that the user controls.
 * Bullets:             Any Bullets that are fired.
 * HyperSpace:          The number of HyperSpace uses left.
 * Score:               The score the player has earned.
 * Level:               The level currently being played.
 * Lives:               Draw the lives left just below the score.
 * Game Over:           "GAME OVER" if no more live are left.
 *************************************************************/
void Game::draw(const Interface & ui)
{
   //Rocks
   for (int i = 0; i < rock.size(); i++)
   {
      rock[i]->draw();
   }

   //Ship
   if (ship.isAlive())
   {
      ship.draw();
   }

   //Bullets
   for (int i = 0; i < bullets.size(); i++)
   {
      bullets[i].draw();
   }

   //create a Point variable that can be used
   //to write items on the screen.
   Point itemLocation;

   //draw the Score.
   itemLocation.setX(topLeft.getX() + 5);
   itemLocation.setY(topLeft.getY() - 5);
   drawNumber(itemLocation, score);

   //draw hyperSpace uses and words.
   
   itemLocation.setX(-62);
   itemLocation.setY(185);
   drawText(itemLocation, "HYPERSPACE(H):");

   itemLocation.setX(48);
   itemLocation.setY(195);
   drawNumber(itemLocation, hyperSpaceuses);

   //draw the level.
   itemLocation.setX((-topLeft.getX()) - 20);
   itemLocation.setY(topLeft.getY() - 5);
   drawNumber(itemLocation, gamelevel);

   itemLocation.setX((-topLeft.getX()) - 65);
   itemLocation.setY(topLeft.getY() - 15);
   drawText(itemLocation, "LEVEL");

   //draw the lives that are left.
   ship.drawLives(lives);

   //If gameover then:
   //1. Draw Ship Debris for 40 frames (count frames using pause)
   //2. Draw "GAME OVER" after 70 frames(also using pause)
   if (gameover)
   {  
      
     
            for (int d = 0; d < 3; d++)
            {
               if(debris.size()==3 && pause < 40)
               {
               debris[d]->draw();
               }
            }
         
      
      
      
      if (pause > 70)
      {
         Point center(-55, 0);
         drawTextLarge(center, "GAME OVER");
         Point belowCenter(-55, -15);
         drawText(belowCenter, "Play again(y/n)?");
         
         int i = 0;
         while (i < debris.size())
         {
            delete debris[i];
            debris.erase(debris.begin());
         }
      }
     
      pause += 1;
   }
}

/************************************************************
 * Function: gameOver
 * Purpose: Clear the screen of all items and set gameover to true.
*************************************************************/
void Game::gameOver()
{

   //Clear the Asteroids.
   for (int i = 0; i < rock.size(); i = 0)
   {

      delete rock[i];
      rock.erase(rock.begin());
   }

   //The game is over now!
   gameover = true;

   Debris *newDebris;
   if (!debris.size())
   {
      for (int i = 0; i < 3; i++)
      {
         //All my debris functions need work before finalized.
         newDebris = new Debris(i, ship.getPoint(), ship.getAngle());
         debris.push_back(newDebris);
      }
      pause = 0; //the frame counter must start at 0
                 //to determine when to draw certain items.
   }

  
   


   //Bullets will be killed after 40 frames and
   //will no longer be fired because the bullet
   //loop checks !gameover.
}

/************************************************************
 * Function: advanceRocks
 * Purpose: Performs up to 3 functions.

 * 1. calls nextLevel() if there are no rocks left.
 * 2. Advances rocks if they are alive.
 * 3. Deletes and Erases Rocks that are killed.
*************************************************************/
void Game::advanceRocks()
{
   //All rocks have been shot or destroyed! 
   if (rock.size()== 0 && !gameover)
   {
      //Time to generate the next level!
      nextLevel();
   }

   //Loop through the rock vector.
   for (int i = 0; i < rock.size(); i++)
   {
      //If the rock is still in play...
      if (rock[i]->isAlive())
      {
         //Advance it!
         rock[i]->advance();
      }
      //If not...
      else
      {
         //Delete the memory and remove it from the vector.
         delete rock[i];
         rock.erase(rock.begin() + i);
      }
   }
   
}

/************************************************************
 * Function: nextLevel
 * Purpose: Updates the screen if the user achieves a level.
 * This includes:

 * 1. Adding 1 to the gamelevel.
 * 2. Giving the user 5 additional HyperSpace uses.
 * 3. Creating new rocks with the amount of rocks that go with that level.
*************************************************************/
void Game::nextLevel()
{
   gamelevel += 1;                       // add a level.
   hyperSpaceuses += 5;                  // more hyperSpace for achieving a level

   for (int i = 0; i < 1 + 2 * gamelevel; i++) // Rocks Start with 3 at beginning of the game 
   {                                           // and increments by two each level.
      Rock *newRock;
      newRock = new BigRock;

      //Initial Speed of BigRocks also increases ever so slightly with each level.
      int randomAngle = random(0, 360);
      //Max speed is 10, though.
      //Max speed will be reached when gamelevel is 17 or above.
      float newspeed = min((float)(1 + .5*(gamelevel - 1)), 10.0f); 
      newRock->setVelocity(newspeed * cos(deg2rad(randomAngle)), newspeed * sin(deg2rad(randomAngle)));
      rock.push_back(newRock);
   }
}
/************************************************************
 * Function: wrapFlyingObjects
 * Purpose: Wraps all objects that fly to the edge of the screen.
*************************************************************/
void Game::wrapFlyingObjects( flyingObjects &object)
{
   //check if it needs to be wrapped on the x axis
   if (abs(object.getPoint().getX()) > 200)
   {
      //since the opposite side of the screen 
      //has the negative point(-200 * -1 = 200 and 200 * -1 = -200, 
      //multiply the x by -1.
      object.setPoint(object.getPoint().getX()*-1, object.getPoint().getY());
   }

   //check if it needs to be wrapped on the y axis.
   if (abs(object.getPoint().getY()) > 200)
   {
      //since the opposite side of the screen 
      //has the negative point, multiply
      //the y by -1.
      object.setPoint(object.getPoint().getX(), object.getPoint().getY()*-1);
   }
}

/************************************************************
Function: handleCollisions
Purpose: handleCollisions between certain flyingObjects.
*************************************************************/
void Game::handleCollisions()
{
   

   
   for (int r = 0; r < rock.size(); r++)
   {
      for (int b = 0; b < bullets.size(); b++)
      {
         //Handling Collisions between Rocks and Bullets.
         //if the bullet is in the radius of the rock and the bullet is alive.
         if (getClosestDistance(*rock[r], bullets[b]) < rock[r]->getRadius()
            && bullets[b].isAlive())
         {
            //Anytime a bullet collides with a Rock,
            //both the Rock and Bullet will be killed
            //and new rocks are made (unless the rock is small).
            bullets[b].kill();
            rock[r]->kill();
            makeRockDebris(*rock[r]);
            
            //Hit returns the value the rock is worth.
            score += rock[r]->hit();
            //Every 5000 points the game gives an extra life.
            lifeawardcount += rock[r]->hit();
            if (lifeawardcount > 5000)
            {
               lives++;
               //can't forget to reset the lifeawardcount variable
               //by subtracting 5000 points from it.
               lifeawardcount -= 5000; 
            }
         }
      }
         //Handling Collisions between Rocks and Ship.
         // if the distance between the ship and the rock is less than their radiuses added together.
         if (getClosestDistance(*rock[r], ship) < SHIP_RADIUS + rock[r]->getRadius())
         {
            //When the ship is hit,
            //the rock is killed.
            //and rock debris is made.
            rock[r]->kill();

            //Just like above, we need to make new rocks for BigRock and MediumRock.
            makeRockDebris(*rock[r]);

            //So we hit a rock with the ship, do we have lives to spare?
            if (lives > 0)
            {
               //We have a life to spare so...
               //Return the ship to it's starting position.
               ship.setPoint(0, 0);
               ship.setAngle(0);
               //Return it's velocity to 0.
               ship.setVelocity(0, 0);
               //and subtract a life.
               lives -= 1;
            }
            else // kill the ship, set it's velocity to 0
               //to allow the ship debris to be displayed properly
               //and call gameOver.
            {
               ship.kill();
               ship.setVelocity(0, 0);
               gameOver();
            }


            
         }
      }
   }
void Game::makeRockDebris(Rock &rock)
{
   Rock *newRock;

   if (rock.getRockType() == "BigRock")
   {

      //2 Medium Rocks and 1 Small with the current rock's point and velocity(plus or minus 1 or 2)
      newRock = new MediumRock(rock.getPoint(), rock.getVelocity().getDx(), rock.getVelocity().getDy() + 1);
      this->rock.push_back(newRock);
      newRock = new MediumRock(rock.getPoint(), rock.getVelocity().getDx(), rock.getVelocity().getDy() - 1);
      this->rock.push_back(newRock);
      newRock = new SmallRock(rock.getPoint(), rock.getVelocity().getDx() + 2, rock.getVelocity().getDy());
      this->rock.push_back(newRock);

   }
   else if (rock.getRockType() == "MediumRock")
   {
      //2 Small Rocks with the current rock's point and velocity(plus or minus 1 or 2)
      newRock = new SmallRock(rock.getPoint(), rock.getVelocity().getDx() + 3, rock.getVelocity().getDy());
      this->rock.push_back(newRock);
      newRock = new SmallRock(rock.getPoint(), rock.getVelocity().getDx() - 3, rock.getVelocity().getDy());
      this->rock.push_back(newRock);

   }
   else if (rock.getRockType() == "SmallRock")
   {
      return;
   }
}


/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 * Author: Instructor
 **********************************************************/

float Game :: getClosestDistance(const flyingObjects &obj1, const flyingObjects &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max(); ///biggest float in the computer.
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}

