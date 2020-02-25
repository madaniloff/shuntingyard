 //This program implements a shunting yard algorithm to convert an equation in infix to postfix, and then translates
//the postfix equation to either infix, prefix or postfix notation using a binary tree
//Author: Mark Daniloff
//Date: 2/20/2020
#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "node.h"

using namespace std;

//Struct for stack
struct Node {
  char data;
  Node* next;
};

//Struct for queue;
struct QNode {
  char data;
  QNode* next;
};

//Function declarations
bool isoperator(char val);
bool isdigval(char* val);
bool isempty(QNode* &front, QNode* &rear);
bool isemptystack(Node* &head);
int precedence(char token);
int associativity(char token);
void push(Node* &head, char val);
char peek(Node* &head);
void pop(Node* &head);
void enqueue(QNode* &front, QNode* &rear, char val);
void dequeue(QNode* &front, QNode* &rear);
char display(QNode* &front, QNode* &rear);
void printqueue(QNode* &front, QNode* &rear);
void maketree(QNode* &front, QNode* &rear, TNode* &Thead, TNode* &root, char* ptr2);
void Tpush(TNode* &Thead, TNode* &current);
void Tpop(TNode* &Thead);
char Tpeek(TNode* &Thead);
void binarytree(TNode* &Thead, TNode* &root, char* val);
void postfix(TNode* Thead);
void prefix(TNode* Thead);
void infix(TNode* Thead);

int main() {
  //Defining queue, stack, and tree nodes
  Node* head = NULL;
  QNode* front = NULL;
  QNode* rear = NULL;
  TNode* root = NULL;
  TNode* Thead = NULL;
  TNode* current = NULL;
  //Initializing arrays and variables
  char input[100];
  char choiceinput[10];
  char* token[100];
  char* in = new char[3];
  char* ptr2;
  int tencount = 1;
  int count = 0;
  int dignum = 0;
  //Prompt user
  cout << "Enter a mathematical expression in infix notation (only single digits) " << endl;
  cin.get(input, 100);
  cin.ignore();
  int i = 0;
  int j = i + 1;
  while (i < strlen(input) && input[i] != '\0') {
    //Take input char and put it into token char*[]
    if (isdigit(input[i])) {
      //If the next value isn't a number
      if (!isdigit(input[j])) {
	//Single digit
	char* c = &input[i];
	token[i] = c;
	i++;
	j++;
      }
    }
      //Else if the char is anything that's not a number
    else {
      char* c = &input[i];
      token[i] = c;
      i++;
      j++;
      } 
  }
  //Go through the token array and execute the shuntyard algorithm
  //Algorithm is from wikipedia
  //en.wikipedia.org/wiki/Shunting-yard_algorithm
  for (int i = 0; i < strlen(input); i++ ) {
    //If index is digits
    if (isdigit(*token[i])) {
      //Push to queue
      enqueue(front, rear, *token[i]);
    }
    //If index is operator
    else if (isoperator(*token[i]) == true) {
      while (
	     (isoperator(peek(head)) == true) &&
	     //There is an operator at the top of the stack with greater precedence
	     (precedence(peek(head)) > precedence(*token[i])) ||
	     //Or the operator at the top of the stack has equal precendece and token is left associative
	     ((precedence(peek(head)) == precedence(*token[i])) && (associativity(*token[i]) == 1)) &&
	     //And operator at the top of the stack is not (
	     peek(head) != '('
	     ) {
	//Pop operators from stack onto output queue
	enqueue(front, rear, peek(head));
	pop(head);
      }
      //Push operator onto stack
      push(head, *token[i]);
    }
    //If index is left paren
    else if (*token[i] == '(' ) {
      //Push to stack
      push(head, *token[i]);
    }
    //If index is right paren
    else if (*token[i] == ')' ) {
      //While the operator at the top of the stack isn't left paren
      while (peek(head) != '(') {
	//Pop the operator from the operator stack onto the output queue
	enqueue(front, rear, peek(head));
	pop(head);
      }
      //If there is a ) at the top of the operator stack
      if (peek(head) == '(') {
	//Pop the operator from the stack and discard it
	pop(head);
      }
    }
  }
  //While there are still tokens on the stack
  while (isemptystack(head) == false) {
    //Pop operators onto the output queue
    enqueue(front, rear, peek(head));
    pop(head);
  }
  //Display the postfix notation
  cout << "Postfix notation:" << endl;
  printqueue(front, rear);
  cout << "\n";
  //Create binary tree from postfix expression
  maketree(front, rear, Thead, root, ptr2);
  //Ask the user if they want to output postfix, prefix, or infix notation
  cout << "Enter 1 for postfix notation, 2 for prefix, or 3 for infix" << endl;
  cin.get(choiceinput, 10);
  cin.ignore();
  //Postfix
  if (strcmp(choiceinput, "1")==0) {
    postfix(root);
  }
  //Prefix
  if (strcmp(choiceinput, "2")==0) {
    prefix(root);
  }
  //Infix
  if (strcmp(choiceinput, "3")==0) {
    infix(root);
  }
}

//Function to check associativity, a return of 2 means right, and 1 means left
int associativity(char token) {
  //If token is right associative
  if (token == '^') {
    return 2;
  }
  //If token is left associative
  else if (token == 'x' || token == '/' || token == '+' || token == '-') {
    return 1;
  }
}
//Function to check precedence and return the type of value that it is
int precedence(char token) {
  //If token is a power
  if (token == '^') {
    return 3;
  }
  //If token is x or /
  if (token == 'x' || token == '/') {
    return 2;
  }
  //If the token is + or -
  if (token == '+' ||token == '-') {
    return 1;
  }
}

//Function to check whether or not value is an operator
bool isoperator(char val) {
  if (val == 'x' || val == '/' || val == '+' || val == '-' || val == '^') {
    return true;
  }
  else {
    return false;
  }
}
//Function to check whether or not a char is a number
bool isdigval(char* val) {
  if ((int)*val > 47 && (int)*val < 58) {
    return true;
  }
  else {
    return false;
  }
}

//These stack functions are partially from a Youtube video titled
//"Stacks - Linked List implementation of Stack Data Structure - C++" by CodeWhoop
//youtube.com/watch?v=Anq11tezBSM
//Checks if stack is empty
bool isemptystack(Node* &head) {
  if (head == NULL) {
    return true;
  }
  else {
    return false;
  }
}

//Insert new node at the top of the stack
void push(Node* &head, char val) {
  Node *ptr = new Node;
  ptr->data = val;
  ptr->next = head;
  head = ptr;
}
//Returns object at the top of the stack without removing it
char peek(Node* &head) {
  //If stack is empty
  if (isemptystack(head) == false) {
    return head->data;
  }
}
//Remove top element of stack
void pop(Node* &head) {
  Node* ptr = head;
  head = head->next;
  delete ptr;
}
//These queue functions are partially from a Youtube video titled
//"Linked List implementation of Queue Data Structure - C++" by CodeWhoop
//youtube.com/watch!v=TCmkquGrmDQ
//Checks if queue is empty
bool isempty(QNode* &front, QNode* &rear) {
  if (front == NULL && rear == NULL) {
    return true;
  }
  else {
    return false;
  }
}
//Adds an element to queue
void enqueue(QNode* &front, QNode* &rear, char val) {
  //Create a new node to store the address
  QNode *ptr = new QNode();
  ptr->data = val;
  ptr->next = NULL;
  //If the first node is being inserted
  if (front == NULL) {
    front = ptr;
    rear = ptr;
  }
  //If the node being inserted isn't the first node
  else {
    rear->next = ptr;
    rear = ptr;
  }
}
//Removes an element from queue
void dequeue(QNode* &front, QNode* &rear) {
  //Check if the queue is empty
  if(isempty(front, rear) == true) {
    cout << "Queue is empty" << endl;
  }
  else {
    //If there is only one node in the queue
    if (front == rear) {
      delete front;
      front = rear = NULL;
    }
    //If there is more than one node in the queue
    else {
      QNode *ptr = front;
      //Move front pointer to the next QNode
      front = front->next;
      delete ptr;
    }
  }
}
//Displays front element of the queue
char display(QNode* &front, QNode* &rear) {
  //Check if the queue is empty
  if (isempty(front, rear) == true) {
    cout << "Queue is empty" << endl;
  }
  else {
    return front->data; 
  }	
}
//Function to print out the nodes in the queue
void printqueue(QNode* &front, QNode* &rear) {
  QNode* ptr = front;
  //While the queue isn't empty
  while (ptr != NULL) {
    cout << ptr->data << " ";
    ptr = ptr->next;
  }
}
//Binary Tree Functions
//Function to construct binary tree from postfix
void binarytree(TNode* &Thead, TNode* &root, char* val) {
   //If token is an operand
  if (isdigval(val) == true) {
    //Push to stack
    TNode* temp = new TNode;
    temp->data = *val;
    Tpush(Thead, temp);
  }
  //If token is an operator
  else if (isoperator(*val) == true) {
    //Pop first two operands in stack, first is right pointer, second is left pointer
    TNode *ptr = new TNode;
    ptr->data = *val;
    ptr->setRight(Thead);
    Tpop(Thead);
    ptr->setLeft(Thead);
    Tpop(Thead);
    root = ptr;
    //Push the expression tree to stack
    Tpush(Thead, root);
  }
}
//Function to go through postfix expression and push to binary tree
void maketree(QNode* &front, QNode* &rear, TNode* &Thead, TNode* &root, char* ptr2) {
  QNode* ptr = front;
  while (ptr != NULL) {
    ptr2 = &ptr->data;
    //Pass to function to construct binary tree
    binarytree(Thead, root, ptr2);
    ptr = ptr->next;
  }
}
//Binary Tree Functions
//Function to add Node* to binary tree stack
void Tpush(TNode* &Thead, TNode* &current) {
  TNode* temp = new TNode;
  temp = current;
  temp->next = Thead;
  Thead = temp;
}
//Function to pop node from binary stack
void Tpop(TNode* &Thead) {
  //TNode* ptr = Thead;
  Thead = Thead->next;
  //delete ptr;
}
//Function to peek first value from binary stack
char Tpeek(TNode* &Thead) {
  return Thead->data;
}
//Function to go through binary tree and return an expression in postfix notation
void postfix(TNode* Thead) {
  //Print out the left pointer first, then the right pointer, then the data value
  if (Thead != NULL) {
    postfix(Thead->getLeft());
    postfix(Thead->getRight());
    cout << Thead->data << " ";
  }
  
}
//Function go to through binary tree and return an expression in prefix notation
void prefix(TNode* Thead) {
  //Print out the data value, then the left pointer, and then the right
    if (Thead != NULL) {
      cout << Thead->data << " ";
      prefix(Thead->getLeft());
      prefix(Thead->getRight());
    }
}
//Function to go through binary tree and return an expression in infix notation
void infix(TNode* Thead) {
  //Print out the left pointer, then the data value, then the right pointer
  if (Thead != NULL) {
    infix(Thead->getLeft());
    cout << Thead->data << " ";
    infix(Thead->getRight());
  }
}

 
