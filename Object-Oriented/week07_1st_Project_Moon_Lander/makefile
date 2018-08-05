###############################################################
# Program:
#     Project 07, Moon Lander
#     Brother Alvey, CS165
# Author:
#     Chase Busacker
# Summary:
#     This program is similar to atari's MoonLander game.
#     MoonLander Generates the ground and a platform,
#     draws the lander in a random location(on the top half
#     of the display), and allows the user to manipulate 
#     where the lander moves on the screen. As the lander is
#     moved using the thrusts the program subtracts the fuel and stops
#     thrusting when out of fuel. If the user lands the lander on the 
#     platform at the right speed, MoonLander program will display 
#     "You have landed. If the lander hits the surface of the 
#     moon or the edge of the display, the program will display
#     "You have crashed" 
# Above and Beyond:
#     1. I created a new display function in the uiDraw file
#        that displays a multi-color explosion when the lander crashes
#     2. I displayed instructions to the user so they know how to
#        play
#     3. I displayed "You are out of fuel!" when the fuel runs
#        out.
#     4. I shifted all words upward so that they won't collide
#        with the ground causing them to not be readable.
###############################################################


LFLAGS = -lglut -lGLU -lGL

###############################################################
# Build the main Moon Lander game
###############################################################
a.out: driver.o ground.o game.o uiInteract.o uiDraw.o point.o velocity.o lander.o
	g++ driver.o ground.o game.o uiInteract.o uiDraw.o point.o velocity.o lander.o $(LFLAGS)
	tar -j -cf moonLander.tar makefile *.h *.cpp

###############################################################
# Individual files
#    uiDraw.o      Draw polygons on the screen and do all OpenGL graphics
#    uiInteract.o  Handles input events
#    point.o       The position on the screen
#    ground.o      Handles the ground / world
#    game.o        Handles the game interaction
#    lander.o      Handles the lander position and drawing.
#    velocity.o    Handles the velocity of the lander.
###############################################################
uiDraw.o: uiDraw.cpp uiDraw.h
	g++ -c uiDraw.cpp

uiInteract.o: uiInteract.cpp uiInteract.h
	g++ -c uiInteract.cpp

point.o: point.cpp point.h
	g++ -c point.cpp

ground.o: ground.cpp ground.h
	g++ -c ground.cpp

game.o: game.h game.cpp uiDraw.h uiInteract.h point.h ground.h lander.h
	g++ -c game.cpp

driver.o: driver.cpp game.h uiInteract.h
	g++ -c driver.cpp

lander.o: lander.cpp lander.h velocity.h point.h
	g++ -c lander.cpp

velocity.o: velocity.cpp velocity.h
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
	rm a.out *.o *.tar
