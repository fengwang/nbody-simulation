all:
	g++ -Wall -I./include -O2 -c src/nbody_show.cc -std=c++0x 
	g++ -L/usr/X11R6/lib -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm -lpthread -o nbody nbody_show.o 

