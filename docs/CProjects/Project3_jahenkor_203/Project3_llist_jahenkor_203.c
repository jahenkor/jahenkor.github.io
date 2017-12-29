//Julius Ahenkora G00835346
//CS 262, Lab Section: 203
//Project 3 LinkedList Functions

#include <stdlib.h>
#include <stdio.h>
#include "Project3_llist_jahenkor_203.h"
#define BUFSIZE1 25
#define BUFSIZE2 35

/*
 * Function: returnID
 * @param node
 * 
 * returns ID based on node input
 */
int
returnID (passengerlist * node)
{


  int id = node->passengerNode->uniqueID;

  return id;
}

passengerlist *
searchList (passengerlist * head, int passengerID)
{

  passengerlist *itr = head;
  int i = 0;

//Traverses list looking for input passenger node
  for (; itr != NULL; itr = itr->next)
    {
      if (i > 0)
	{
	  if (itr->passengerNode->uniqueID == passengerID)
	    {

	      return itr;
	    }

	}
      i += 1;
    }

  return NULL;
}

/*
 * Function: InsertNodeSorted
 * @param head, node
 *
 * inserts node in ascending order of head list
 */
void
insertNodeSorted (passengerlist * head, passengerlist * node)
{

  passengerlist *temp = head;
  while ((temp->next != NULL)
	 && (temp->next->passengerNode->uniqueID <
	     node->passengerNode->uniqueID))
    {
      temp = temp->next;
    }
  node->next = temp->next;
  temp->next = node;
}

/*
 *Function: printNode
 *@param head, passengerID
 *
 *Prints individual nodes
 */
void
printNode (passengerlist * head, int passengerID)
{

  passengerlist *temp = head;

  printf
    ("Passenger ID: [%d] Balance: $%.2lf Location: %c First Name: %s, Last Name: %s \n",
     temp->passengerNode->uniqueID, temp->passengerNode->balance,
     temp->passengerNode->location, temp->passengerNode->firstName,
     temp->passengerNode->lastName);

}

passengerlist *
deleteNode (passengerlist * head, int passengerID)
{

  passengerlist *itr = head;
  passengerlist *prev = head;

  int found = 0;

  int i = 0;

//Traverse input list to delete passenger of input ID
  for (; itr != NULL; itr = itr->next)
    {


      if (i > 0)
	{

	  if (i > 1)
	    {
	      prev = prev->next;
	    }
	  if (itr->passengerNode->uniqueID == passengerID)
	    {
	      prev->next = itr->next;
	      found = 1;
	      return itr;
	      break;
	    }

	}

      i += 1;
    }

//If passenger found, output success message
  if (found)
    {
      printf ("Passenger moved Successfully\n");
    }

//If passenger not found, output unsuccessful message
  if (!found)
    {
      printf ("Passenger transfer unsuccessful\n");
    }






  return NULL;
}

//Frees nodes in list
void
deleteList (passengerlist * head)
{

  passengerlist *itr = head;

  while (itr != NULL)
    {

      passengerlist *tmp = itr;
      itr = itr->next;
      if (itr != NULL)
	{
	  tmp = itr;
	  free (tmp->passengerNode);
	  free (tmp);
	  tmp = NULL;
	}
    }



}

/*
 *Function: PrintList 
 *@param head
 * Prints values of all nodes in list
 */
void
printList (passengerlist * head)
{

  int i = 0;

  passengerlist *temp = head;
  for (; temp != NULL; temp = temp->next)
    {

      if (i > 0)
	{
	  printf
	    ("Passenger ID: [%d] Balance: $%.2lf Location: %c First Name: %s, Last Name: %s \n",
	     temp->passengerNode->uniqueID, temp->passengerNode->balance,
	     temp->passengerNode->location, temp->passengerNode->firstName,
	     temp->passengerNode->lastName);

	}
      i += 1;
    }
}
