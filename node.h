//Binary tree class
#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>

using namespace std;

class TNode {
 public:
  TNode();
  ~TNode();
  void setLeft(TNode* inleft);
  TNode* getLeft();
  void setRight(TNode* inright);
  TNode* getRight();
  void setData(char indata);
  char getData();
  void setNext(TNode* innext);
  TNode* getNext();
  char data;
  TNode* next = NULL;
 private:
  TNode* left = NULL;
  TNode* right = NULL;
};
#endif
