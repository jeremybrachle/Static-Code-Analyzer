
/*
* Assignment: Final Project
* Description: This project will assess static code
* Date: 12-6-2016
* Name of Programmer: Jeremy Brachle
* Student Number: 46659942
* Course Number: 2341-802
* Lab Section: N11
*/

#ifndef VECTOR
#define VECTOR

#include <iostream>
#include <cstring>
//#include "DSString.h"

template<class T>
class Vector{

  public:

      //default constructor
      Vector();

      //constructor that sets up a vector to be a specified size
      Vector(int);

      //copy constructor
      Vector(const Vector<T>&);

      //overloaded assignment operator
      Vector<T>& operator=(Vector<T>&);

      //destructor
      ~Vector();

      //add a slot of specified type to the end of a vector
      void add(T);

      //return the length of a vector
      int size() const;

      //return the capacity
      int capacity();

      //sort a vector from least to greatest
      void sort();

      //tell whether an element has already been put into the vector
      bool isAnElement(T);

      //return the item from a vector given a subscript
      T& operator[](int) const;

  private:

      //creates a vector array named data
      T* data;

      //vector length
      int len;

      //vector capacity
      int cap;

      //resize a vector given data and capacity
      void resize(T* &, int &);

};

#endif

//default constructor
template<typename T>
Vector<T>::Vector()
{
   //std::cout<<"Default Constructor\n";
   len = 0; //length is zero
   cap = 10; //capacity is 10 more than length
   data = new T[cap]; //make a blank vector with 10 elements inside (the capacity)
}

//constructor that sets up a blank vector type with given size
template<typename T>
Vector<T>::Vector(int numElements)
{
    //std::cout<<"Constructor given integer size\n";
    len = numElements; //set the length equal to the number of elements given
    cap = len + 10; //make capacity 10 more than the length
    data = new T[cap]; //set up an array of T type with size equal to the given number of elements
}

//copy constructor
template<typename T>
Vector<T>::Vector(const Vector<T> &rhs)
{
    //std::cout<<"Copy Constructor Vector\n";
    if (rhs.len != 0) //rhs is not null
    {
        len = rhs.len; //make the left have the same length as the right
        cap = rhs.cap; //make the left have the same capacity as the right
        data = new T[cap];

        //copy values from the right vector into the left vector
        for (int i = 0; i < len; i ++)
        {
            data[i] = rhs.data[i];
        }
    }
    else if (rhs.len == 0) //if rhs is null, then just make left null too
    {
        len = 0; //length is zero
        cap = 10; //capacity is 10 more than length
        data = new T[cap]; //make a blank vector with 10 elements inside (the capacity)
    }

}

//overloaded assignment operator
template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&rhs)
{
    //std::cout<<"Overloaded Assignment Operator\n";
    if (this != &rhs) //if NOT self assignment
    {
        if (rhs.size() != 0) //if right is NOT null
        {

            if (data != NULL) //if left is NOT null
            {
                delete[] data;
                len = rhs.len;
                cap = rhs.cap;
                data = new T[cap];
                for (int i = 0; i < len; i ++)
                {
                    data[i] = rhs.data[i];
                }
            }
            else //if left IS null
            {
                //create new object
                len = rhs.len; //make the left have the same length as the right
                cap = rhs.cap; //make the left have the same capacity as the right
                data = new T[cap];

                //copy values from the right vector into the left vector
                for (int i = 0; i < len; i ++)
                {
                    data[i] = rhs.data[i];
                }
            }

        }
        else //if right IS null
        {
            if (size() != 0)
            {
                delete[] data;
            }
            //since right is null, just make left null too
            len = 0; //length is zero
            cap = 10; //capacity is 10 more than length
            data = new T[cap]; //make a blank vector with 10 elements inside (the capacity)
        }

    }
    else //if it is self assignment
    {
        return *this;
    }

}

//destructor
template<typename T>
Vector<T>::~Vector()
{
    //std::cout<<"Destructor\n";
    delete [] data;
}

//size or length
template<typename T>
int Vector<T>::size() const
{
    return len;
}

//capacity
template<typename T>
int Vector<T>::capacity()
{
    return cap;
}

//return the item from a vector given a subscript
template<typename T>
T& Vector<T>::operator[](int index) const
{
    //std::cout<<"index subscript\n";
    return data[index];
}

//resize
template<typename T>
void Vector<T>::resize(T* &data, int &capacity)
{
    //make a new vector of type T that has 10 more elements than previous
    T* ptr = new T[capacity + 10];

    //copy old array into new array but stop before getting to the new capacity
    for (int i = 0; i<capacity; i ++)
    {
        ptr[i] = data[i];
    }
    delete [] data; //get rid of old vector
    data = ptr; //replace old vector with larger one
    capacity +=10; //update the capacity
    //delete[] ptr;
}

//add a slot of specified and instantiated type at the end of the vector
template<typename T>
void Vector<T>::add(T rhs)
{
    //std::cout<<"Add Function\n";

    //make sure the length has not reached capacity yet
    if (len != cap)
    {
        data[len] = rhs; //assign the new object to the end of the vector
        len++; //increase the length because you have appended a new item
    }
    else if (len == cap) //if the length has reached capacity
    {
        resize (data, cap); //since the length has reached capacity, the vector must now be resized
        data[len] = rhs; //assign same as before
        len++; //increase length
    }
}

//sort the elements using selection sort
template<typename T>
void Vector<T>::sort()
{
    //std::cout<<"sort function\n";
    //selection sort:
    int minIndex;
    T temp;
    for(int i = 0; i < (this->size() - 1); i ++)
    {
        minIndex = i;
        for(int j = i + 1; j < this->size(); j ++)
        {
            if ( data[j] < data[minIndex])
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            temp = data[i];
            data[i] = data[minIndex];
            data[minIndex] = temp;
        }
    }

}

//check to see if the given value is already in the vector
template<typename T>
bool Vector<T>::isAnElement(T value)
{
    //loop through each element of the vector
    for (int i = 0; i < this->size(); i ++)
    {
        //check to see if this
        if (data[i] == value)
        {
            return true;
        }
    }
    return false;
}
