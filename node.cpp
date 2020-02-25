//Binary tree functions 
#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

//Constructor
TNode::TNode() {

}
//Destructor
TNode::~TNode() {

}
//Set the left node
void TNode::setLeft(TNode* inleft) {
  left = inleft;
}
//Get the left node
TNode* TNode::getLeft() {
  return left;
}
//Set the right node
void TNode::setRight(TNode* inright) {
  right = inright;
}
//Get the right node
TNode* TNode::getRight() {
  return right; 
}
//Set data
//void TNode::setData(char indata) {
//  data = indata;
//}
//Get data
//char TNode::getData() {
//  return data;
//}
//Set next
void TNode::setNext(TNode* innext) {
  next = innext;
}
//Get next
TNode* TNode::getNext() {
  return next;
}





