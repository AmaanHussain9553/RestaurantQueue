#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "proj4.h"

//
// This function initalizes the struct that is 
// being created in main 
//
Queue* init(Queue* waitLine) {
    /* creates the struct in heap */
    waitLine = (Queue*)malloc(sizeof(Queue));
    waitLine->Burgers = 0;
    waitLine->Salads = 0;
    /* intializes size of string to be 30 */
    waitLine->Name = (char*)malloc(sizeof(char)* 30);
    waitLine->Next = NULL;
    /* sets the status of person waiting to be false by default*/
    bool calledAhead = false;
    return waitLine;
}

//
// This function sets the waiting status of a person who
// ordered from false to true
//
//
void updateStatus2(Queue* waitLine, char* name){
  Queue* temp = waitLine;
  while(strcmp(temp->Name, name) != 0){
    temp = temp->Next;
  }
    temp->calledAhead = true;
}