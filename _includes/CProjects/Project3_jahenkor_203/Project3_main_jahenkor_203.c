//Julius Ahenkora G00835346
//CS 262, Lab Section: 203 
//Project 3 Main Source File

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Project3_llist_jahenkor_203.h"
#define BUFFERSIZE 100
#define FIRSTNAMELEN 25
#define LASTNAMELEN 35
#define MAXPASSENGERS 1000

//Function Prototypes
void MainMenu ();
void PassengerInformationMenu ();
void PrintMenu ();
void EmbarkAll (passengerlist * offShipHead, passengerlist * onShipHead);
void DebarkAll (passengerlist * offShipHead, passengerlist * onShipHead);
int PassengerOffBoardPurchase (passengerlist * offShipHead,
			       passengerlist * onShipHead);
void SynchronizePassengerList (passengerlist * offShipHead,
			       passengerlist * onShipHead);
void ReadPassengerManifest ();
int DebarkPassenger (passengerlist * offShipHead, passengerlist * onShipHead);
int EmbarkPassenger (passengerlist * offShipHead, passengerlist * onShipHead);
int PassengerOnBoardPurchase (passengerlist * offShipHead,
			      passengerlist * onShipHead);
void SynchronizeList (passengerlist * offShipHead,
		      passengerlist * onShipHead);

void Quit ();


int
main ()
{

//Allocate head for onship list
  passengerlist *onShipHead = malloc (sizeof (passengerlist));

//Malloc Error Check
  if (onShipHead == NULL)
    {
      printf ("Error Allocating!\n");
      exit (1);
    }
  onShipHead->next = NULL;

//Allocate head for offship list
  passengerlist *offShipHead = malloc (sizeof (passengerlist));

//Malloc Error Check
  if (offShipHead == NULL)
    {
      printf ("Error Allocating!\n");
      exit (1);
    }
  offShipHead->next = NULL;


//Main Menu Functionality
  while (1)
    {
      char menuChoice = '0';
      char buffer[BUFFERSIZE] = "";
      char passengerMenuChoice = '0';
      char printMenuChoice = '0';
      int valHolder = 0;
      passengerlist *iterant;

      MainMenu ();
      fgets (buffer, sizeof (buffer), stdin);
      sscanf (buffer, "%c", &menuChoice);

      switch (menuChoice)
	{

	case ('P'):
	case ('p'):
	PassengerMenu:
	  PassengerInformationMenu ();
	  fgets (buffer, sizeof (buffer), stdin);
	  sscanf (buffer, "%c", &passengerMenuChoice);


	  switch (passengerMenuChoice)
	    {
	    case ('E'):
	    case ('e'):
	      valHolder = 0;
	      valHolder = EmbarkPassenger (offShipHead, onShipHead);
	      if (valHolder == 0)
		{
		  goto PassengerMenu;
		}
	      break;
	    case ('D'):
	    case ('d'):
	      valHolder = 0;
	      valHolder = DebarkPassenger (offShipHead, onShipHead);
	      if (valHolder == 0)
		{
		  goto PassengerMenu;
		}
	      break;
	    case ('O'):
	    case ('o'):
	      PassengerOffBoardPurchase (offShipHead, onShipHead);
	      break;
	    case ('P'):
	    case ('p'):
	      valHolder = 0;
	      valHolder = PassengerOnBoardPurchase (offShipHead, onShipHead);
	      if (valHolder == 0)
		{
		  goto PassengerMenu;
		}
	      break;
	    case ('S'):
	    case ('s'):
	      SynchronizeList (offShipHead, onShipHead);
	      break;
	    case ('M'):
	    case ('m'):
	      break;

	    default:
	      printf ("Please select valid choice!\n");
	      break;



	    }
	  break;
	case ('E'):
	case ('e'):
	  //Embark All Passengers
	  EmbarkAll (offShipHead, onShipHead);
	  SynchronizeList (offShipHead, onShipHead);
	  break;
	case ('D'):
	case ('d'):
	  //Debarks All Passengers
	  DebarkAll (offShipHead, onShipHead);
	  SynchronizeList (offShipHead, onShipHead);
	  break;
	case ('A'):
	case ('a'):
	  //Delete both lists before reading manifest
	  deleteList (onShipHead);
	  deleteList (offShipHead);
	  offShipHead->next = NULL;
	  onShipHead->next = NULL;
	  ReadPassengerManifest (offShipHead);
	  break;
	case ('R'):
	case ('r'):

	PrintMenu:
	  PrintMenu ();
	  fgets (buffer, sizeof (buffer), stdin);
	  sscanf (buffer, "%c", &printMenuChoice);

	  switch (printMenuChoice)
	    {

	    case ('S'):
	    case ('s'):

	      //Prompt user for Passenger ID
	      printf ("Please Enter Passenger ID\n");
	      fgets (buffer, sizeof (buffer), stdin);
	      sscanf (buffer, "%d", &valHolder);
	      //Search onship and offship for passenger,if not found returns to Print Menu
	      if (searchList (onShipHead, valHolder) != NULL)
		{
		  iterant = searchList (onShipHead, valHolder);
		  printNode (iterant, valHolder);
		}

	      else if (searchList (offShipHead, valHolder) != NULL)
		{
		  iterant = searchList (offShipHead, valHolder);
		  printNode (iterant, valHolder);

		}
	      else
		{
		  printf
		    ("Couldn't find customer ID....returning to Print Menu\n");
		  goto PrintMenu;
		}
	      //Print info for passenger
	      //If not found, write a message saying so and return to print menu, (use goto)
	      break;
	    case ('P'):
	    case ('p'):
	      printf ("Off Ship List: \n");
	      printList (offShipHead);
	      printf ("On Ship List: \n");
	      printList (onShipHead);
	    case ('F'):
	    case ('f'):
	      printf ("Off Ship List: \n");
	      printList (offShipHead);
	      break;
	    case ('O'):
	    case ('o'):
	      printf ("On Ship List: \n");
	      printList (onShipHead);
	      break;
	    case ('M'):
	    case ('m'):
	      break;
	    default:
	      printf ("Choose valid menu choice!");
	      break;
	    }

	  break;
	case ('Q'):
	case ('q'):
//Deletes both lists and quits program
	  deleteList (onShipHead);
	  deleteList (offShipHead);
	  free (onShipHead);
	  free (offShipHead);
	  onShipHead = NULL;
	  offShipHead = NULL;

	  Quit ();
	  break;
	default:
	  printf ("Please select valid choice!\n");
	  break;

	}
    }

}

//Main Menu Dialog
void
MainMenu ()
{


  printf ("Choose a Menu Choice:\n");
  printf ("(P)assengerInformation\n");
  printf ("Re(A)d Passenger Manifest\n");
  printf ("P(R)int Menu\n");
  printf ("(E)mbark All Passengers\n");
  printf ("(D)ebark All Passengers\n");
  printf ("(Q)uit\n");
  printf
    ("\n\n***Note: Input single bracketed character from choices above***\n");
  printf ("***Values are not case sensitive***\n");




}


//Passenger Information Dialog
void
PassengerInformationMenu ()
{

  printf ("(E)mbark Passenger\n");
  printf ("(D)ebark Passenger\n");
  printf ("(P)assenger OnBoard Purchase\n");
  printf ("Passenger (O)ffBoard Purchase\n");
  printf ("(S)ynchronize Passenger Lists\n");
  printf ("(M)ain Menu\n");
}

//PrintMenu Dialog
void
PrintMenu ()
{
  printf ("Print Menu: \n");
  printf ("Print Account for (S)ingle Passenger\n");
  printf ("Print All (P)assenger Accounts\n");
  printf ("Print Accounts for (O)nship Passengers\n");
  printf ("Print Accounts for O(F)Fship Passengers\n");
  printf ("Return to main (M)enu\n");
}

/*
 * Function: Embark All
 * @param offShipHead, onShipHead
 *
 * Embarks all the passengers
 *
 */
void
EmbarkAll (passengerlist * offShipHead, passengerlist * onShipHead)
{
  printf ("Embark All\n");

  passengerlist *itr = offShipHead;
  int i = 0;

//Sets all passengers to be on ship 
  for (; itr != NULL; itr = itr->next)
    {
      if (i > 0)
	{
	  itr->passengerNode->location = '1';
	}
      i += 1;
    }
}


/*
* Function: Debark All
* @param offShipHead, onShipHead
*
* Debarks all the passengers
*
*/
void
DebarkAll (passengerlist * offShipHead, passengerlist * onShipHead)
{
  printf ("Debark All\n");
  double totalSpent = 0.0;

  passengerlist *itr = onShipHead;
  int i = 0;

//Sets all passengers to be off the ship
  for (; itr != NULL; itr = itr->next)

    {
      if (i > 0)
	{
	  totalSpent += itr->passengerNode->balance;
	  itr->passengerNode->location = '0';
	}
      i += 1;

    }
  printf ("Average Spent Per Customer: %.2lf\n", ((double) totalSpent / i));
  printf ("Total Spent: %.2lf\n", totalSpent);



}

/*
 * Function ReadPassengerManifest
 * @param offShipHead
 *
 * Function reads from a file the passengers name, and ID.
 * Sets balance and location to be 0 and offship respectively.
 */
void
ReadPassengerManifest (passengerlist * offShipHead)
{

  char firstname[MAXPASSENGERS][FIRSTNAMELEN];
  char lastname[MAXPASSENGERS][LASTNAMELEN];
  int passengerID = 0;
  char filename[BUFFERSIZE] = "";
  char buffer[BUFFERSIZE] = "";
  FILE *fp;
  int i = 0;

  printf ("Enter Filename to Read: \n");

  fgets (buffer, sizeof (buffer), stdin);
  sscanf (buffer, "%s", filename);


  fp = fopen (filename, "r");


//Valid file check
  if (fp == NULL)
    {
      printf ("File cannot be open for read operations\n");
      printf ("Returning to Main Menu....Please wait....\n");
    }

  if (fp != NULL)
    {
      while (!feof (fp))
	{

	  passengerInfo *newNode = malloc (sizeof (passengerInfo));
	  passengerlist *newPassNode = malloc (sizeof (passengerlist));

	  if (!feof (fp))
	    {


//Malloc Check
	      if (newNode == NULL)
		{
		  printf ("Error! Cannot allocate memory to node!\n");
		  exit (1);
		}
	      if (newPassNode == NULL)
		{
		  printf ("Error! Cannot allocate memory to nod!\n");
		  exit (1);
		}


	      fgets (buffer, sizeof (buffer), fp);
	      sscanf (buffer, "%d", &passengerID);
	      if (feof (fp))
		{
		  break;
		}
	      newNode->uniqueID = passengerID;

	      fgets (buffer, sizeof (buffer), fp);
	      sscanf (buffer, "%s", *(firstname + i));
	      newNode->firstName = *(firstname + i);

	      fgets (buffer, sizeof (buffer), fp);
	      sscanf (buffer, "%s", *(lastname + i));
	      newNode->lastName = *(lastname + i);
	      newNode->location = '0';
	      newNode->balance = 0.00;

	      newPassNode->passengerNode = newNode;
	      newPassNode->next = NULL;

//Puts new node into list
	      insertNodeSorted (offShipHead, newPassNode);
	      i += 1;
	    }

	}
    }


}

/*
 * Function: Embark Passenger
 * @param offShipHead, onShipHead
 * 
 * Embarks individual passenger onto ship, if found onship, 
 * prompts user that individual is onship, else returns incorrect ID and
 * returns to print menu
 */
int
EmbarkPassenger (passengerlist * offShipHead, passengerlist * onShipHead)
{

  int passengerID = 0;
  char buffer[BUFFERSIZE] = "";
  int i = 0;
  int passengerFound = 0;


  passengerlist *itrOffHead = offShipHead;
  passengerlist *itrOnHead = onShipHead;

  printf ("Enter passenger ID: ");

  fgets (buffer, sizeof (buffer), stdin);
  sscanf (buffer, "%d", &passengerID);

//Searches for passenger in offShip list
  for (; itrOffHead != NULL; itrOffHead = itrOffHead->next)
    {

      if (i > 0 && passengerFound == 0)
	{
	  if (itrOffHead->passengerNode->uniqueID == passengerID)
	    {
	      itrOffHead->passengerNode->location = '1';
	      deleteNode (offShipHead, passengerID);

	      insertNodeSorted (onShipHead, itrOffHead);
	      passengerFound = 1;
	    }
	}
      i += 1;

    }

//If passenger not found in offship list, checks onShipList
  if (passengerFound == 0)
    {
      i = 0;
      for (; itrOnHead != NULL; itrOnHead = itrOnHead->next)
	{

	  if (i > 0)
	    {
	      if (itrOnHead->passengerNode->uniqueID == passengerID)
		{
		  printf ("Passenger is on the OnShip list!\n");
		  passengerFound = 1;
		}
	    }
	  i += 1;
	}

    }

//If not found returns message
  if (passengerFound == 0)
    {

      printf ("Incorrect ID!");
      return 0;

    }


  return 1;
}

/*
 * Function: Debark Passenger
 * @param offShipHead, onShipHead
 * 
 * Debarks individual passenger onto ship, if found onship, 
 * prompts user that individual is onship, else returns incorrect ID and
 * returns to print menu

 */
int
DebarkPassenger (passengerlist * offShipHead, passengerlist * onShipHead)
{

  int passengerID = 0;
  char buffer[BUFFERSIZE] = "";
  int i = 0;
  int passengerFound = 0;


  passengerlist *itrOffHead = offShipHead;
  passengerlist *itrOnHead = onShipHead;

  printf ("Enter passenger ID: ");

  fgets (buffer, sizeof (buffer), stdin);
  sscanf (buffer, "%d", &passengerID);

//Checks onship list for passenger
  for (; itrOnHead != NULL; itrOnHead = itrOnHead->next)
    {

      if (i > 0 && passengerFound == 0)
	{
	  if (itrOnHead->passengerNode->uniqueID == passengerID)
	    {
	      itrOnHead->passengerNode->location = '0';
	      deleteNode (onShipHead, passengerID);

	      insertNodeSorted (offShipHead, itrOnHead);
	      passengerFound = 1;
	    }
	}
      i += 1;

    }

//If not found onship , checks offship list
  if (passengerFound == 0)
    {
      i = 0;
      for (; itrOffHead != NULL; itrOffHead = itrOffHead->next)
	{

	  if (i > 0)
	    {
	      if (itrOffHead->passengerNode->uniqueID == passengerID)
		{
		  printf ("Passenger is on the OffShip list!\n");
		  passengerFound = 1;
		}
	    }
	  i += 1;
	}

    }

//If not found in either list output message
  if (passengerFound == 0)
    {

      printf ("Incorrect ID!");
      return 0;

    }


  return 1;



}

/*
 * Function: PassengerOnBoardPurchase
 * @param offShipHead, onShipHead
 *
 * Prompts user for passenger ID and purchase amount, if found offship, user is prompted and returned
 * to Main Menu, else outputs incorrect ID and returns to print meu
 */
int
PassengerOnBoardPurchase (passengerlist * offShipHead,
			  passengerlist * onShipHead)
{

  int passengerID = 0;
  double purchaseAmount = 0.0;
  char buffer[BUFFERSIZE] = "";
  passengerlist *found = NULL;

  printf ("Enter passenger ID: ");

  fgets (buffer, sizeof (buffer), stdin);
  sscanf (buffer, "%d", &passengerID);

  printf ("Enter Purchase Amount");

  fgets (buffer, sizeof (buffer), stdin);
  sscanf (buffer, "%lf", &purchaseAmount);

  found = searchList (onShipHead, passengerID);
  if (found == NULL)
    {
      found = searchList (offShipHead, passengerID);
      if (found != NULL)
	{
	  printf ("Passenger is on OffShip List, Returning to Main Menu\n");
	  return 1;
	}
      else
	{
	  printf
	    ("Incorrect ID entered, returning to Passenger Information Menu\n");
	  return 0;
	}
    }
  else if (found != NULL)
    {
      found->passengerNode->location = '1';
      found->passengerNode->balance = purchaseAmount;
      return 1;
    }

  return 1;
}

/*
 * Function: PassengerOffBoardPurchase
 * @param offShipHead, onShipHead
 *
 * Prompts user for passenger ID and purchase amount, if found onship, user is prompted and returned
 * to Main Menu, else outputs incorrect ID and returns to print meu
 */

int
PassengerOffBoardPurchase (passengerlist * offShipHead,
			   passengerlist * onShipHead)
{

  int passengerID = 0;
  double purchaseAmount = 0.0;
  char buffer[BUFFERSIZE] = "";
  passengerlist *found = NULL;

  printf ("Enter passenger ID: ");

  fgets (buffer, sizeof (buffer), stdin);
  sscanf (buffer, "%d", &passengerID);

  printf ("Enter Purchase Amount");

  fgets (buffer, sizeof (buffer), stdin);
  sscanf (buffer, "%lf", &purchaseAmount);

  found = searchList (offShipHead, passengerID);
  if (found == NULL)
    {
      found = searchList (onShipHead, passengerID);
      if (found != NULL)
	{
	  printf ("Passenger is on OnShip List, Returning to Main Menu\n");
	  return 1;
	}
      else
	{
	  printf
	    ("Incorrect ID entered, returning to Passenger Information Menu\n");
	  return 0;
	}
    }
  else if (found != NULL)
    {
      found->passengerNode->location = '0';
      found->passengerNode->balance = purchaseAmount;
      return 1;
    }

  return 1;

}

/*
 * Function: SynchronizeList 
 * @param offShipHead, onShipHead
 *
 * Synchronizes offShip and OnShip lists based on passenger location
 *
 */
void
SynchronizeList (passengerlist * offShipHead, passengerlist * onShipHead)
{

//Traverse both lists
//Put nodes in proper location based on location, and delete nodes from list if necessary.
  passengerlist *itrOnHead = onShipHead;
  passengerlist *itrOffHead = offShipHead;
  passengerlist *temp = offShipHead;
  int i = 0;

//Puts nodes with location of '0' into offShip list
  for (; itrOnHead != NULL; itrOnHead = itrOnHead->next)
    {
      if (i > 0)
	{
	  if (itrOnHead->passengerNode->location == '0')
	    {
	      temp =
		deleteNode (onShipHead, itrOnHead->passengerNode->uniqueID);
	      insertNodeSorted (offShipHead, temp);
	      itrOnHead = onShipHead;
	    }
	}

      i += 1;
    }

  i = 0;

//Puts all nodes with locaiton '1' into onship list
  for (; itrOffHead != NULL; itrOffHead = itrOffHead->next)
    {
      if (i > 0)
	{
	  if (itrOffHead->passengerNode->location == '1')
	    {
	      temp =
		deleteNode (offShipHead, itrOffHead->passengerNode->uniqueID);
	      insertNodeSorted (onShipHead, temp);
	      itrOffHead = offShipHead;
	    }

	}
      i += 1;
    }



}

// Quit
void
Quit ()
{
  printf ("Exiting......\n");
  exit (0);
}
