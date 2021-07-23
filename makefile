main: main.o addHelper.o doFile.o doHelper.o mainFunc.o proj4.h
  gcc -o main main.o addHelper.o doFile.o doHelper.o mainFunc.o proj4.h

userInterface.o: userInterface.c proj4.h
  gcc -c userInterface.c

addHelper.o: addHelper.c proj4.h
  gcc -c addHelper.c

doFile.o: doFile.c proj4.h
  gcc -c doFile.c

doHelper.o: doHelper.c proj4.h
  gcc -c doHelper.c  

mainFunc.o: mainFunc.c proj4.h
  gcc -c mainFunc.c

run:
  ./


