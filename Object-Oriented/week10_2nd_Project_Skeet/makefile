###############################################################
# Program:
#     Project 09, Skeet
#     Brother Alvey, CS165
# Author:
#     Chase Busacker
# Summary:
#     The skeet game that projects birds across the screen. You can
#     shoot the birds and gain or lose points (depending on the bird type)
# Above and Beyond
#      I didn't have time to go above and beyond on this one.'
###############################################################


LFLAGS = -lglut -lGLU -lGL

###############################################################
# Build the main game
###############################################################
a.out: driver.o game.o uiInteract.o uiDraw.o point.o rifle.o bullets.o flyingObjects.o sacredBird.o standardBird.o toughBird.o velocity.o
	g++ driver.o game.o uiInteract.o uiDraw.o point.o rifle.o bullets.o flyingObjects.o sacredBird.o standardBird.o toughBird.o velocity.o $(LFLAGS)

###############################################################
# Individual files
#    uiDraw.o      Draw polygons on the screen and do all OpenGL graphics
#    uiInteract.o  Handles input events
#    point.o       The position on the screen
#    game.o        Handles the game interaction
#    bullets.o     Handles the bullets moving across the screen
#    flyingObjects.o Handles any flyingObject.
#    sacredBird.o  SacredBird(star) flying across screen.
#    standardBird.o standardBird flying across screen
#    toughBird.o   toughBird flying across the screen.
#    velocity.o    All flyingObjects have velocity. 
###############################################################
uiDraw.o: uiDraw.cpp uiDraw.h point.h
	g++ -c uiDraw.cpp

uiInteract.o: uiInteract.cpp uiInteract.h
	g++ -c uiInteract.cpp

point.o: point.cpp point.h
	g++ -c point.cpp

game.o: game.cpp uiDraw.h uiInteract.h point.h rifle.h bullet.h birds.h
	g++ -c game.cpp

driver.o: game.h uiInteract.h driver.cpp
	g++ -c driver.cpp

rifle.o: rifle.h point.h uiDraw.h rifle.cpp
	g++ -c rifle.cpp

bullets.o: bullets.cpp bullets.h uiDraw.h flyingObjects.h 
	g++ -c bullets.cpp

flyingObjects.o: flyingObjects.cpp flyingObjects.h velocity.h point.h 
	g++ -c flyingObjects.cpp

sacredBird.o: sacredBird.cpp sacredBird.h flyingObjects.h baseBird.h 
	g++ -c sacredBird.cpp

standardBird.o: standardBird.cpp standardBird.h flyingObjects.h baseBird.h
	g++ -c standardBird.cpp

toughBird.o: toughBird.cpp toughBird.h flyingObjects.h baseBird.h
	g++ -c toughBird.cpp

velocity.o: velocity.cpp velocity.h point.h 
	g++ -c velocity.cpp
#######################################################################
# ADD YOUR ADDITIONAL RULES HERE!
#
# Then, don't forget to add them to the dependecy list for a.out above.
#######################################################################


###############################################################
# General rules
###############################################################
clean:
	rm a.out *.o
