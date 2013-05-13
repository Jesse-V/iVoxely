CC=g++
CPPFLAGS=--std=c++0x -g3 
LDLIBS=-lglut -lGLEW -lGLEW -lGL -lGLU
all: main
main: Shader.o Program.o
clean:
	rm -f *.o main
	rm *~
.PHONY: all clean