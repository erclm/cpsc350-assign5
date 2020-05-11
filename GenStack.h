#include<iostream>
using namespace std;

template <typename T>
class GenStack {
  public:
    GenStack();
    GenStack(int maxSize);
    ~GenStack();
    void push(T d);
    T pop();
    T peek();
    bool isEmpty();
    bool isFull();
    int getSize();
    void grow();


    T *myArray;
    int top;
    int size;
    int count;
};

template <typename T>
GenStack<T>::GenStack(){//default contstryctor
  myArray = new T[10];
	size = 10;
	top = -1;
  count = 0;
}

template <typename T>
GenStack<T>::GenStack(int maxSize){
  myArray = new T[maxSize];
  top = -1;
  size = maxSize;
  count = 0;
}

template <typename T>
GenStack<T>::~GenStack(){
  //cout<<"Stack deleted\n"<<endl;
  delete myArray;

}

template <typename T>
void GenStack<T>::push(T d){
  myArray[++top]=d;
  count++;
}

template <typename T>
T GenStack<T>::pop(){
  if(!this->isEmpty()){
    count--;
    return myArray[top--];
  }else{
    throw invalid_argument("Empty Stack");
  }
}

template <typename T>
T GenStack<T>::peek(){
  if(!this->isEmpty()){
    return myArray[top];
  }else{
    throw invalid_argument("Empty Stack");
  }
}

template <typename T>
void GenStack<T>::grow()
{
	T* newArray = new T[size+10];
	for (int i = 0; i < size; ++i){
	 	newArray[i] = myArray[i];
	}
	myArray = newArray;
	size+=10;
}

template <typename T>
bool GenStack<T>::isEmpty(){
  return (count == 0);
}

template <typename T>
bool GenStack<T>::isFull(){
  return (count == size);
}

template <typename T>
int GenStack<T>::getSize(){
  return count;
}
