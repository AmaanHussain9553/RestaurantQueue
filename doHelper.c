#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "proj4.h"

//
// This function traverses through the list to see if a certain
// name exist in the queue of orders. This function is used in
// doAdd, doRetrieve, etc. so if a person already exists in 
// the queue or not
//
bool doesNameExist(Queue* waitline, char* name){

  Queue* temp = waitline;
  while(temp != NULL){
      /* compares two names */
      if(strcmp(temp->Name, name) == 0){
        return true;
      }
      temp = temp->Next;
  }
  return false;
}


//
// This function traverses through the list to display all 
// orders in detail with name, #burgers and #salads
//
void displayList(Queue* waitLine){

 Queue* head = waitLine;
 /*declaring int to count number of orders in the Queue */
 int numOrder = 1;

  /*Depending on whether the person calledAhead or not the 
  print statements are different */
  while(head != NULL){
      if(head->calledAhead == false){
    printf ("%d. The name is: \"%s\" has NumBurgers: %d and NumSalads: %d and called ahead status is: False \n", numOrder, head->Name, head->Burgers , head->Salads);
      }else{
        printf ("The name is: \"%s\" has NumBurgers: %d and NumSalads: %d and called ahead status is: True \n", head->Name, head->Burgers , head->Salads);
      }

    head = head->Next;
    numOrder++;
  }

}

//
// This function adds a node to the list, the node is in the 
// form of a struct which stores the name, #burgers, #salads,
// and status of the person as in-restaurant as default
//
void addToList(Queue* waitLine, int NumBurgers, int NumSalads, char* name){
  /*if the queue is empty add to the head of the queue */
  if(waitLine->Burgers == 0 && waitLine->Salads == 0){
      waitLine->Burgers = NumBurgers;
      waitLine->Salads = NumSalads;
      waitLine->Name = name;
      waitLine->Next = NULL;
      waitLine->calledAhead = false;
  }
  /* else need to traverse to the end of list, create a new 
  struct and then add it to back of the queue */
  else{
    Queue* newOrder = (Queue*)malloc(sizeof(Queue));
    newOrder->Name = name;
    newOrder->Burgers = NumBurgers;
    newOrder->Salads = NumSalads;
    newOrder->Next = NULL;
    newOrder->calledAhead = false;

    /*traversing to the back of the list */
    Queue* temp = waitLine;
    while(temp->Next != NULL){
      temp = temp->Next;
    }
    temp->Next = newOrder;

  }

}


//
// This function changes the status of someone who has called
// ahead and placed their order to now waiting in the 
// restaurant for their order
//
void updateStatus(Queue* waitLine, char* name){
  Queue* temp = waitLine;
  /*traversing through the list until the name is found */
  while(strcmp(temp->Name, name) != 0){
    temp = temp->Next;
  }
  /* Error message if the person is already waiting in the
  restaurant */
  if(temp->calledAhead == false){
    printf ("Error: This person is already waiting at the restaurant\n");
     return;
  }else{
    temp->calledAhead = false;
  }
}

//
// This function gives customers their orders based on #burgers
// and #salads prepared to fulfill orders of customers who are 
// already waiting in the restaurant
//
Queue* retrieveandRemove(int PreparedSalads, int PreparedBurgers, Queue* waitLine){
  Queue* temp = waitLine;

 //if the first order in line matches with prepared salads and burgers
 if(temp->Burgers <= PreparedBurgers && temp->Salads <= PreparedSalads && temp->calledAhead == false){
   waitLine = waitLine->Next;
   free(temp);
   displayList(waitLine);
   return waitLine;
 }
 
 //iterate through list to find first order that can be removed based on 
 //NumBurgers, NumSalads and callingAhead status
 else{
    while(temp != NULL){

      Queue* previousOrder = temp;
      temp = temp->Next;

      if(temp->Burgers <= PreparedBurgers && temp->Salads <= PreparedSalads && temp->calledAhead == false){
        previousOrder->Next = temp->Next;
        free(temp);
        displayList(waitLine);
        return waitLine;
      }
  }
      /*Error message if unable to serve any order */
      printf ("Unable to remove anyone from list because of the following reasons:\n 1.Either the queue is empty \n 2.Number of PreparedBurgers and PreparedSalads is too less to serve anyone at the moment\n");
}
  return waitLine;
}


//
// This function gives a list of all orders that are ahead of
// the person called. This function is called by user input:
// "l <name>"
//
void countOrderAhead(Queue* waitLine){
  Queue* temp = waitLine;
  /* keeps a counter for number of orders */
  int i = 0;
  
  /*traversing through the list until the name is found */
  while(temp != NULL){
    temp = temp->Next;
    i++;
  }
  printf("There are %d people waiting ahead of you\n", i);
}


//
// This function gives a list of all orders that are ahead of
// the person called. This function is called by user input:
// "l <name>"
//
void displayOrdersAhead(Queue* waitLine, char* name){
  Queue* temp = waitLine;
  /* keeps a counter for number of orders */
  int count = 1;

  /* if the customer is the first person in the queue */
  if(strcmp(temp->Name, name) == 0){
   printf ("%s is the first order in line and will be served as soon as the order is ready", name);
   return;
 }

 /* traverses through queue to find the customer and keeps a 
 counter */
 while(strcmp(temp->Name, name) != 0){
   printf ("%d. %s, NumBurgers: %d, NumSalads: %d\n", count, temp->Name, temp->Burgers, temp->Salads);
   temp = temp->Next;
   count++;
  }
}


//
// This function displays the time that is required to wait
// for a customer to receive their order. THis function is 
// called by user as: "t <name>"
//
void displayWaitingTime(Queue* waitLine, char* name){
  /* int to keep track of time */
  int TotalTime = 0;
  Queue* temp = waitLine;

  /*goes through every order until the customer name to 
  calculate time based on #burgers and #salads */
  while(strcmp(temp->Name, name) != 0){
    TotalTime += (10 * temp->Burgers) + (5 * temp->Salads);
    temp = temp->Next;
  }
  
  /* then adds the #burgers and #salads of the customer itself */
  TotalTime += (10 * temp->Burgers) + (5 * temp->Salads);

  printf("The total time for: %s is %d", name, TotalTime);
}

