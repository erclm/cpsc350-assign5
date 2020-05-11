#include <iostream>
#include "ListNode.h"
using namespace std;

template <typename T>
class NaiveList{
public:
  NaiveList();
  ~NaiveList();

  ListNode<T> *front;
  ListNode<T> *back;
  unsigned int size;

  void insertFront(T d);
  void insertBack(T d);
  T removeFront();
  T removeBack();
  ListNode<T>* remove(T d);
  int find(T d);
  bool isEmpty();
  void printList();
  T getFront();
  T getBack();
  unsigned int getSize();
};

template <typename T>
NaiveList<T>::NaiveList(){
  size = 0;
  front = NULL;
  back = NULL;
}

template <typename T>
NaiveList<T>::~NaiveList(){
  ListNode<T>* curr = front;
  ListNode<T>* next = curr;
  while(curr != NULL){
    next = curr->next;
    delete curr;
    curr = next;
  }
  curr = NULL;
}

template <typename T>
unsigned int NaiveList<T>::getSize(){
  return size;
}

template <typename T>
void NaiveList<T>::printList(){
  ListNode<T> *curr = front;
  while(curr !=NULL){
    cout << curr->data << endl;
    curr = curr->next;
  }
}

template <typename T>
void NaiveList<T>::insertFront(T d){
  ListNode<T> *node = new ListNode<T>(d);
  if(size == 0){
    back = node;
  }else{
    front->prev = node;
    node->next = front;
  }
  front = node;
  size++;
}

template <typename T>
void NaiveList<T>::insertBack(T d){
  ListNode<T> *node = new ListNode<T>(d);
  if(size == 0){
    front = node;
  }else{
    back->next = node;
    node->prev = back;
  }
  back = node;
  size++;
}

template <typename T>
T NaiveList<T>::removeFront(){
  if(size==0){
    cout << "Error: List Empty" << endl;
    exit(0);
  }
  ListNode<T> *f = front;
  if(size == 1){
    back = NULL;
  }else{
    front->next->prev = NULL;
  }
  front = front->next;
  T temp = f->data;
  f->next = NULL;
  delete f;
  size--;

  return temp;
}

template <typename T>
T NaiveList<T>::removeBack(){
  if(size==0){
    cout << "Error: List Empty" << endl;
    exit(0);
  }
  ListNode<T> *b = back;
  if(size == 1){
    front = NULL;
  }else{
    back->prev->next = NULL;
  }
  back = back->prev;
  T temp = b->data;
  b->prev = NULL;
  delete b;
  size--;
  return temp;
}

template <typename T>
ListNode<T>* NaiveList<T>::remove(T d){
  ListNode<T> *curr = front;

  while(curr->data != d){
    curr = curr->next;
    if(curr == NULL){
      return NULL;
    }
  }

  if(curr == front){
    front = curr->next;
  }else{
    curr->prev->next = curr->next;
  }
  if(curr == back){
    back = curr->prev;
  }else{
    curr->next->prev = curr->prev;
  }

  curr->next = NULL;
  curr->prev = NULL;
  size--;
  return curr;
}

template <typename T>
int NaiveList<T>::find(T d){
  int i = 0;
  ListNode<T> *curr = front;

  while(curr != NULL){
    if(curr->data == d){
      break;
    }
    i++;
    curr = curr->next;
  }
  if(curr == NULL){
    i = -1;
  }
  return i;
}

template <typename T>
T NaiveList<T>::getFront(){
  if(size==0){
    cout << "Error: List Empty" << endl;
    exit(0);
  }
  T temp = front->data;
  return temp;
}

template <typename T>
T NaiveList<T>::getBack(){
  if(size==0){
    cout << "Error: List Empty" << endl;
    exit(0);
  }
  T temp = back->data;
  return temp;
}
