###############################################################
# Program:
#     Project 13, Asteroids
#     Brother Alvey, CS165
# Author:
#     Chase Busacker
# Summary:
#     Introduced by Atari in 1979, Asteroids was one of the most 
#     successful of the first generation of arcade games and was 
#     highly influential on the video game landscape for the next 
#     decade. The basic premise of the game is that a ship moves 
#     around the screen shooting asteroids while trying not to 
#     get hit by them.
# Above and Beyond
#     *****Multiple Lives drawn in the corner and removed when the
#     ship crashes.
#     *****Clear the game and write "GAME OVER" when the ship crashes
#     and has no lives left.
#     *****Draw Spaceship Debris when the ship crashes and has no lives left.
#     *****HYPERSPACE:When the user presses the letter 'h' relocate the ship
#     in a random location. Also, draw the amount of HYPERSPACE uses in the top
#     middle of the screen.
#     *****Multiple Levels: Start the game with 3 Large Asteroids
#     with 2 more Asteroids in each level and Asteroids speed up slightly
#     every level.
#     *****Score: Big Asteroids are worth 20 points, Medium Asteroids are worth
#     50 points and Small Asteroids are worth 100 points. Right this score in the
#     top left corner of the screen.
#     *****For every 5,000 points earned, give the player an extra life.
#     *****Rocks spin in random directions.
###############################################################


LFLAGS = -lglut -lGLU -lGL

###############################################################
# Build the main game
###############################################################
a.out: driver.o game.o uiInteract.o uiDraw.o point.o velocity.o flyingObject.o ship.o bullet.o rocks.o
	g++ driver.o game.o uiInteract.o uiDraw.o point.o velocity.o flyingObject.o ship.o bullet.o rocks.o $(LFLAGS)

###############################################################
# Individual files
#    uiDraw.o       Draw polygons on the screen and do all OpenGL graphics
#    uiInteract.o   Handles input events
#    point.o        The position on the screen
#    game.o         Handles the game interaction
#    velocity.o     Velocity (speed and direction)
#    flyingObject.o Base class for all flying objects
#    ship.o         The player's ship
#    bullet.o       The bullets fired from the ship
#    rocks.o        Contains all of the Rock classes
###############################################################
uiDraw.o: uiDraw.cpp uiDraw.h
	g++ -c uiDraw.cpp

uiInteract.o: uiInteract.cpp uiInteract.h
	g++ -c uiInteract.cpp

point.o: point.cpp point.h
	g++ -c point.cpp

driver.o: driver.cpp game.h
	g++ -c driver.cpp

game.o: game.cpp game.h uiDraw.h uiInteract.h point.h velocity.h flyingObject.h bullet.h rocks.h ship.h
	g++ -c game.cpp

velocity.o: velocity.cpp velocity.h point.h
	g++ -c velocity.cpp

flyingObject.o: flyingObject.cpp flyingObject.h point.h velocity.h uiDraw.h
	g++ -c flyingObject.cpp

ship.o: ship.cpp ship.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c ship.cpp

bullet.o: bullet.cpp bullet.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c bullet.cpp

rocks.o: rocks.cpp rocks.h flyingObject.h point.h velocity.h uiDraw.h
	g++ -c rocks.cpp


###############################################################
# General rules
###############################################################
clean:
	rm a.out *.o
