#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "proj4.h"


int main (int argc, char **argv)
{

 char *input;
 int ch;
 int debugMode = 0;
 Queue* waitingForFood;
 waitingForFood = init(waitingForFood);
 

 printf ("Starting Fast Food Order Management Program\n\n");
 printf ("Enter command: ");

 while ((ch = getNextNWSChar ()) != EOF)
   {
    /* check for the various commands */
    if ('q' == ch)
      {
       printf ("Quitting Program\n");
       return (0);
      }
    else if('D' == ch){
      if(debugMode == 0){
        debugMode = 1;
        printf("Debug mode is active\n");
      }else if(debugMode == 1){
        debugMode = 0;
        printf("Debug mode is not active\n");
      }
      continue;
    }  
    else if ('?' == ch)
      {
       printCommands();
      }
    else if('a' == ch)
      {
       doAdd(&waitingForFood, debugMode);
      } 
    else if('c' == ch)
      {
       doCallAhead(&waitingForFood, debugMode);
      } 
    else if('w' == ch)
      {
       doWaiting(&waitingForFood, debugMode);
      } 
    else if('r' == ch)
      {
       doRetrieve(&waitingForFood, debugMode);
      } 
    else if('l' == ch)
      {
       doList(waitingForFood, debugMode);
      } 
    else if('d' == ch)
      {
       doDisplay(waitingForFood);
      } 

    else if('t' == ch)
      {
      	doEstimateTime(waitingForFood, debugMode);
      }	
      
    else if('\n' == ch )
      {
       /* nothing entered on input line     *
        * do nothing, but don't give error  */
      } 
    else
      {
       printf ("%c - in not a valid command\n", ch);
       printf ("For a list of valid commands, type ?\n");
       clearToEoln();
      }

    printf ("\nEnter command: ");
   }

 printf ("Quiting Program - EOF reached\n");
 return 1;
}