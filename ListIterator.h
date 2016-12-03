#pragma once

#include "arduino.h"
#include "Node.h"

template<class T> class ListIterator {
public:
  ListIterator(){}
  ListIterator(Node<T>* begin):current(begin){}
  virtual ~ListIterator(){}
  //
  bool hasNext(){
    return current->next == 0? false : true;
  }
  //
  void set_begin(Node<T>* begin){
    current = begin;
  }
  //
  T next(){
    Node<T>* temp = new Node<T>;
    temp = current->next;
    current = temp;
    return current->data;
  }
  
  Node<T>* next_node(){
    Node<T>* temp = new Node<T>;
    temp = current->next;
    current = temp;
    return current;
  }

protected:
  Node<T>* current;
};
