#ifndef Project3_llist_jahenkor_203_H
#define Project3_llist_jahenkor_203_H

typedef struct _passengerInfo
{

  int uniqueID;
  char *firstName;
  char *lastName;
  double balance;
  char location;

} passengerInfo;


typedef struct passengerList
{

  passengerInfo *passengerNode;
  struct passengerList *next;

} passengerlist;

void insertNodeSorted (passengerlist * head, passengerlist * node);
//passengerlist* createNode();
passengerlist *deleteNode (passengerlist * head, int uniqueID);
int returnID (passengerlist * node);
void printList (passengerlist * head);
passengerlist *searchList (passengerlist * head, int uniqueID);
void deleteList (passengerlist * head);
void printNode (passengerlist * node, int passengerID);

#endif
