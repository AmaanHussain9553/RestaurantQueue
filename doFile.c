#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "proj4.h"


//
// This function adds a new order to the linked list for
// a person who is present in the restaurant and ordering.
// This function is called when the user inputs "a <#burgers>
// <#salads> <name>"
//
void doAdd (Queue** waitLine, int debugMode)
{
 /* get number of burgers ordered from input */
 int NumBurgers = getPosInt();
 if (NumBurgers < 0)
   {
    printf ("Error: Add command requires an integer value of at least 0\n");
    printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }

  /* get number of salads ordered from input */
 int NumSalads = getPosInt(); 
 if (NumSalads < 0)
   {
    printf ("Error: Add command requires an integer value of at least 0\n");
    printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }  

 /* get group name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Add command requires a name to be given\n");
    printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }

   /*prints error message if person is already in the queue */
   if(doesNameExist(*waitLine, name) == true){
     printf ("Error: This person already exists in Queue\n");
     return;
   }

  /*calls linked list implementation function to add to Queue */
  addToList(*waitLine, NumBurgers, NumSalads, name);

 printf ("Adding In-restaurant order for \"%s\": %d burgers and %d salads\n", name,NumBurgers ,NumSalads);

 /* debug mode command to display whole queue of ordered items */
 if(debugMode == 1)
 displayList(*waitLine);
  
 
}


//
// This function adds a new order to the linked list for
// a person who is not present in the restaurant and ordering.
// This function is called when the user inputs "c <#burgers>
// <#salads> <name>"
//
void doCallAhead (Queue** waitLine, int debugMode)
{
   /* get number of burgers ordered from input */
 int NumBurgers = getPosInt();
 if (NumBurgers < 0)
   {
    printf ("Error: Call-ahead command requires an integer value of at least 0\n");
    printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }

  /* get number of salads ordered from input */
 int NumSalads = getPosInt(); 
 if (NumSalads < 0)
   {
    printf ("Error: Call-ahead command requires an integer value of at least 0\n");
    printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }  


 /* get group name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Call-ahead command requires a name to be given\n");
    printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }

   /*prints error message if person is already in Queue */
   if(doesNameExist(*waitLine, name) == true){
     printf ("Error: This person already exists in Queue\n");
     return;
   }

   /*linked list implementation function to add to end of Queue */
   addToList(*waitLine, NumBurgers, NumSalads, name);

   /*this updates status of person to not waiting in restaurant */
   updateStatus2(*waitLine, name);

   printf ("Adding Call-ahead order for \"%s\": %d burgers and %d salads\n", name,NumBurgers ,NumSalads);

  /* debug mode command to display whole queue of ordered items */
  if(debugMode == 1)
  displayList(*waitLine);

}


//
// This function changes the status of someone who calledAhead
// to now waiting in the restaurant for their order.
// This function is called by user input: "w <name>"
//
void doWaiting (Queue** waitLine, int debugMode)
{
 /* get order name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Waiting command requires a name to be given\n");
    printf ("Waiting command is of form: w <name>\n");
    printf ("  where: <name> is the name of the group that is now waiting\n");
    return;
   }

   /* prints error message if person already waiting in restaurant */
   if(doesNameExist(*waitLine, name) == false){
     printf ("Error: This person does not exist in Queue\n");
     return;
   }

  /*changes the status of person from calledAhead to waiting in restaurant */
  updateStatus(*waitLine, name);

 printf ("Call-ahead order \"%s\" is now waiting in the restaurant\n", name);

 /* debug mode command to display whole queue of ordered items */
 if(debugMode == 1)
 displayList(*waitLine);

}


//
// This function gives customers their orders based on #burgers
// and #salads prepared to fulfill orders of customers who are 
// already waiting in the restaurant
//
void doRetrieve(Queue** waitLine, int debugMode)
{
 /* get info of prepared food ready on the counter from input */
 int PreparedBurgers = getPosInt();
 if (PreparedBurgers < 0)
   {
    printf ("Error: Retrieve command requires an integer value of at least 0\n");
    printf ("Retrieve command is of form: r <# burgers> <# salads>\n");
    printf ("  where: <# burgers> is the number of burgers waiting on the counter for pick up\n");
    printf ("         <# saladss> is the number of salads waiting on the counter for pick up\n");
    return;
   }

 int PreparedSalads = getPosInt();
 if (PreparedSalads < 0)
   {
    printf ("Error: Retrieve command requires an integer value of at least 0\n");
    printf ("Retrieve command is of form: r <# burgers> <# salads>\n");
    printf ("  where: <# burgers> is the number of burgers waiting on the counter for pick up\n");
    printf ("         <# saladss> is the number of salads waiting on the counter for pick up\n");
    return;
   }   

 clearToEoln();

 printf ("Retrieve (and remove) the first group that can pick up the order of %d burgers and %d salads\n", PreparedBurgers ,PreparedSalads);

 /* this function is the linked list implementation of removing the first person */
 /* whose order is satisfied and are in restaurant */
 *waitLine = retrieveandRemove(PreparedSalads, PreparedBurgers,*waitLine);

 /* debug mode command to display whole queue of ordered items */ 
 if(debugMode == 1)
 displayList(*waitLine);
 }


//
// This function gives a list of all orders that are ahead of
// the person called. This function is called by user input:
// "l <name>"
//
void doList (Queue* waitLine, int debugMode)
{
 /* get order name from input */
 char *name = getName();

 if (NULL == name)
   {
    printf ("Error: List command requires a name to be given\n");
    printf ("List command is of form: l <name>\n");
    printf ("  where: <name> is the name of the order to inquire about\n");
    return;
   }

   /* prints error message if person is not in restaurant */
   if(doesNameExist(waitLine, name) == false){
     printf ("Error: This person does not exist in Queue\n");
     return;
   }
   
   /* this functions displays orders until the person checked upon */
   displayOrdersAhead(waitLine, name);

   /* debug mode command to display whole queue of ordered items */ 
   if(debugMode == 1)
   displayList(waitLine);

}
 

 //
 // This function displays all orders that are present in the 
 // queue and is called by userInput as: "d"
 //
void doDisplay (Queue* waitLine)
{
 clearToEoln();
 printf ("Display information about all orders\n");

 /* this function traverses linked list and displays all orders */
 displayList(waitLine);
}


//
// This function displays the time that is required to wait
// for a customer to receive their order. THis function is 
// called by user as: "t <name>"
//
void doEstimateTime(Queue* waitLine, int debugMode)
{
  /* get order name from input */
 
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: List command requires a name to be given\n");
    printf ("List command is of form: t <name>\n");
    printf ("  where: <name> is the name of the order to inquire about\n");
    return;
   }

  /* this function calculates the time based on #burgers and #salads based on each order 
  until it reaches the person who asked for their waiting time */
  displayWaitingTime(waitLine, name);  

  /* debug mode command to display whole queue of ordered items */
  if(debugMode == 1)
  displayList(waitLine);

}