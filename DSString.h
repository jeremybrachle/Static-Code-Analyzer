
/*
* Assignment: Final Project
* Description: This project will assess static code
* Date: 12-6-2016
* Name of Programmer: Jeremy Brachle
* Student Number: 46659942
* Course Number: 2341-802
* Lab Section: N11
*/


//DSstring.h




#ifndef STRING
#define STRING

#include <iostream>
#include <cstring>
#include <sstream>

class String{

    public:

        //create string:
        String();

        //copy constructor
        String(const String&);

        //copy constructor for char*
        String(const char*);

        //assignment operator for strings:
        String& operator= (const String&);

        //assignment operator for character pointers
        String& operator= (const char*);

        //string addition operator
        String operator+ (const String&);

        //string + int addition operator
        String operator+ (const int&);

        //string + double addition operator
        String operator+ (const double&);

        //string += string operator
        String operator+= (const String&);
    
        //string += char operator
        String operator+= (const char*);

        //boolean equality operator for character pointers
        bool operator== (const char*);

        //boolean operator for string
        friend bool operator== (const String&, const String&);

        //boolean != operator for character pointers
        bool operator!= (const char*);

        //boolean != operator for strings
        bool operator!= (const String&);

        //greater than operator for String
        //bool operator> (const String&);
        friend bool operator > (const String&, const String&);

        //less than operator for String
        friend bool operator< (const String&, const String&);
        //bool operator < (const String&);

        //substring operator for
        char& operator[] (const int);

        //size/length of string
        int size();

        //capacity (2 more than lenth)
        int capacity();

        //substring given start and stop
        String substring(int, int);

        //substring given start
        //String substring(int);

        //to Uppercase
        String toUpper();

        //to Lowercase
        String toLower();

        //reverse the string
        String reverse();

        //remove spaces
        String removeSpaces();

        //count the number of characters given in a string
        int countCharacters(char);

        //character pointer string
        char* c_str();

        //output string
        friend std::ostream& operator<< (std::ostream&, const String&);

        //destructor:
        ~String();




    private:
        char* data; //the character pointer in the string
        int len; //the length not including the null-terminator
        int cap; //two more than the length to account for the null-terminator and one extra blank space


};


#endif
