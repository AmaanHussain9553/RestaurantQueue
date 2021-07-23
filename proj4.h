#ifndef PROJ_4
#define PROJ_4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;

typedef struct RestaurantLine{
  int Burgers;
  int Salads;
  char* Name;
  bool calledAhead;
  struct RestaurantLine* Next;
}Queue;

/* functions belonging to mainFunc.c file*/
void printCommands();
void clearToEoln();
int getNextNWSChar();
int getPosInt ();
char *getName();

/*functions belonging to addHelper.c file */
Queue* init(Queue* waitLine);
void updateStatus2(Queue* waitLine, char* name);

/* functions belonging to doHelper.c file */
bool doesNameExist(Queue* waitLine, char* name);
void displayList(Queue* waitLine);
void addToList(Queue* waitLine, int NumBurgers, int NumSalads, char* name);
void updateStatus(Queue* waitLine, char* name);
Queue* retrieveandRemove(int PreparedSalads, int PreparedBurgers, Queue* waitLine);
void countOrderAhead(Queue* waitLine);
void displayWaitingTime(Queue* waitLine, char* name);
void displayOrdersAhead(Queue* waitLine, char* name);

/*functions belonging to doFile.c file */
void doAdd (Queue** waitLine, int debugMode);
void doCallAhead (Queue** waitLine, int debugMode);
void doWaiting (Queue** waitLine, int debugMode);
void doRetrieve (Queue** waitLine, int debugMode);
void doList (Queue* waitLine, int debugMode);
void doEstimateTime(Queue* waitLine, int debugMode);
void doDisplay (Queue* waitLine);

#endif
