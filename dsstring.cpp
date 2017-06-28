/*
* Assignment: Final Project
* Description: This project will assess static code
* Date: 12-6-2016
* Name of Programmer: Jeremy Brachle
* Student Number: 46659942
* Course Number: 2341-802
* Lab Section: N11
*/

//DSString.cpp

#include "DSString.h"
#include <cstring>

//-------------------------- BEGIN CONSTRUCTOR / DESTRUCTOR SECTION -------------------------------------

//default constructor
String::String() : data(nullptr), len(0), cap(0){}

//copy constructor string
String::String(const String &rhs)
{
    if (rhs.data != nullptr) //if right is NOT null
    {

        data = new char[(rhs.len + 1)]; //add 1 to account for null terminator
        len = rhs.len; //do NOT add 1 since you do not count the null-terminator
        cap = len + 2; //make capacity 2 more than the length to have an empty slot after the null terminator
        for (int i = 0; i < len; i++)
            {
                data[i] = rhs.data[i]; //propogate values from the right hand side into the left
            }
        data[len] = '\0'; // null terminator
    }

    else //if right IS null
    {
        data = nullptr;
        cap = 0;
        len = 0;
    }
}

//copy constructor char*
String::String(const char* rhs)
{
    if (rhs != nullptr) //if right is NOT null
    {
        data = new char[strlen(rhs) + 1]; // add 1 to account for the null terminator
        len = strlen(rhs); //do NOT add 1, since you do not have to account for a null terminator
        cap = len + 2; //make capacity 2 more than the length to have an empty slot after the null terminator
        for (int i = 0; i < len; i ++)
            {
                data[i] = rhs[i]; //propogate values from right into left
            }
        data[len] = '\0'; //null-terminator
    }

    else //if right IS null
    {
        data = nullptr;
        cap = 0;
        len = 0;
    }
}

//destructor
String::~String()
{
    if(data != nullptr)//make sure the object is not already null
    {
        delete[] data;
    }
}

//-------------------------- END CONSTRUCTOR / DESTRUCTOR SECTION -------------------------------------



//------------------------------ BEGIN ASSIGNMENT OPERATOR SECTION -------------------------------------

//overload assignment operator String
String& String::operator= (const String &rhs)
{
    if (this != &rhs) //check for self-assignment
    {
        if (rhs.data != nullptr) //if right is NOT null
        {
            if (data != nullptr) //if left is NOT null
            {
                //copy right into the left
                delete[] data;
                cap = rhs.cap;
                len = rhs.len;
                data = new char[rhs.len + 1];
                for (int i = 0; i < len; i++)
                {
                    data[i] = rhs.data[i];
                }
                data[len] = '\0'; //null-terminator
            }
            else //if left IS null
            {
                //create new object
                data = new char[rhs.len + 1]; // add 1 to account for the null terminator
                len = rhs.len; //do NOT add 1 (because you do not account for a null terminator)
                cap = len + 2; //make capacity 2 more than the length to have an empty slot after the null terminator
                for (int i = 0; i < len; i ++)
                    {
                        data[i] = rhs.data[i]; //propogate right into left
                    }
                data[len] = '\0'; //null-terminator
            }
        }
        else //if right IS null
        {
            //since right is null, make the left null too
            //check to see if left is NULL
            //if left is not null
            if (data != nullptr)
            {
                delete[] data;
                data = nullptr;
                cap = 0;
                len = 0;
            }
            //if left is null
            else
            {
                data = nullptr;
                cap = 0;
                len = 0;
            }

        }
    }
    else // if self assignment
    {
        return *this;
    }
    
    //return this if all else fails
    return *this;
    
}

//overload assignment operator const *
String& String::operator= (const char* rhs)
{
        if (rhs != nullptr) //if right is NOT null
        {
            if (data != nullptr)
            {
                delete[] data;
            }
            data = new char[strlen(rhs) + 1]; // add 1 to account for the null terminator
            len = strlen(rhs); //do NOT add 1 (because you do not account for a null terminator)
            cap = len + 2; //make capacity 2 more than the length to have an empty slot after the null terminator
            for (int i = 0; i < len; i ++)
                {
                    data[i] = rhs[i];
                }
            data[len] = '\0'; //null-terminator
        }
        else //if right IS null
        {
            data = nullptr;
            cap = 0;
            len = 0;
        }

    //return this if all else fails
    return *this;
    
}

//------------------------------ END ASSIGNMENT OPERATOR SECTION ----------------------------------------



//------------------------------ BEGIN BOOLEAN OPERATOR SECTION -------------------------------------

//equality operator for when
//lhs is a String and rhs is a char*
bool String::operator==(const char *rhs)
{
    if (this->size() != strlen(rhs)) //compare the size
    {
        return false; //automatically return false if the sizes are not even the same
    }
        //check to see if the data inside is equal
        for (int i = 0; i < this->size(); i ++)
        {
            if (this->data[i] != rhs[i])
            {
                return false; //return false as soon as a character is not the same
            }
        }
        return true; //return true if both the size is the same and al the characters inside both are the same
}

//equality NOT operator for when
//lhs is a String and rhs is a char*
bool String::operator !=(const char* rhs)
{
    String left = this->data;
    String right = rhs;

    //return the opposite of ==

    //if the same
    if (left == right)
    {
        //return the opposite
        return false;
    }
    //if not the same
    else
    {
        //return true
        return true;
    }
}

//equality NOT operator for when
//lhs is a String and rhs is a string
bool String::operator !=(const String& rhs)
{
    String left = this->data;
    String right = rhs;

    //return the opposite of ==

    //if the same
    if (left == right)
    {
        //return the opposite
        return false;
    }
    //if not the same
    else
    {
        //return true
        return true;
    }
}

//equality operator for when
//lhs is a String and rhs is a String
bool operator == (const String &lhs, const String &rhs)
{
    if (lhs.len != rhs.len)
    {
        return false;
    }

    //check data in strings
    for (int i = 0; i < lhs.len; i ++)
    {
        if (lhs.data[i] != rhs.data[i])
        {
            return false;
        }
    }
    return true;
}


//greater than
bool operator > (const String &lhs, const String &rhs)
{
    //for iterating index
    int index = 0;

    //make copies of left and right for boolean comparison
    String left = lhs.data;
    String right = rhs.data;

    //make sure strings are NOT the same
    if (left!=right)
    {
        //while values of both strinngs are the same
        while (lhs.data[index] == rhs.data[index])
        {
            //increment index
            index++;
        }

        //check for the first occurence when the characters are NOT the same
        if (lhs.data[index] != rhs.data[index])
        {
            //if left is bigger
            if (lhs.data[index] > rhs.data[index])
            {
                return true;
            }
            //if right is bigger
            else if (rhs.data[index] > lhs.data[index])
            {
                return false;
            }
        }
    }
    //if they are the same
    else
    {
        return false;
    }
    
    //return false if all else fails
    return false;
    
}

//less than
bool operator < (const String & lhs, const String & rhs)
{
    //for iterating index
    int index = 0;

    //make copies of left and right for boolean comparison
    String left = lhs.data;
    String right = rhs.data;

    //make sure strings are NOT the same
    if (left!=right)
    {

        //while characters of both strinngs are the same
        while (lhs.data[index] == rhs.data[index])
        {
            //increment index
            index++;
        }

        //check for the first occurence when the characters are NOT the same
        if (lhs.data[index] != rhs.data[index])
        {
            //if left is smaller
            if (lhs.data[index] < rhs.data[index])
            {
                return true;
            }

            //if right is smaller
            else if (rhs.data[index] < lhs.data[index])
            {
                return false;
            }
        }
    }
    //if they ARE the same
    else
        return false;
    
    //return false if all else fails
    return false;
    
}



//------------------------------ END BOOLEAN OPERATOR SECTION -------------------------------------



//---------------------------- BEGIN MISCELLANEOUS FUNCTION SECTION -------------------------------------

//output to console
std::ostream& operator <<(std::ostream& out, const String& line)
{
    out<<line.data;
    return out; //enables cascading
}

//return the size/length
int String::size()
{
    return this->len; //returns the variable for length
}

//return the capcity (2 more than length)
int String::capacity()
{
    return this->cap;
}

//return the String this but in all uppercase
String String::toUpper()
{
    String temp = *this; //create a modifiable copy of the string

    for (int i = 0; i < this->size(); i++) //iterate through the string
    {
        if (temp.data[i] >= 97 && temp.data[i] <= 122) //check to see if lower case
        {
            temp.data[i] -= 32; //subtract ascii value to get to uppercase
        }
    }
    return temp; //return string in all uppercase
}

//return the String this but in all lowercase
String String::toLower()
{
    String temp = *this; //create a modifiable copy of the string

    for (int i = 0; i < this->size(); i ++) //iterator through the string
    {
        if (temp.data[i] >= 65 && temp.data[i] <= 90) //check to see if upper case
        {
            temp.data[i] += 32; //add ascii value to get lowercase
        }
    }
    return temp; //return string in all lowercase
}

//subscript operator with wrapper
char& String::operator[] (const int sub)
{
    if (sub == 0) //if the index IS zero
    {
        return data[sub];
    }
    else if (sub >= 0 && sub < this->size()) //positive and within bounds
    {
        return data[sub];
    }
    else if (sub >= 0 && sub >= this->size()) //positive but out of bounds
    {
        return data[(sub % (this->size()))];
    }
    else if (sub < 0 && (sub * -1) < this->size()) //negative and within bounds
    {
        return data[(sub + (this->size()))];
    }
    else if (sub < 0 && (sub * -1) >= this->size()) //negative and out of bounds
    {
        if ((sub % (this->size())) == 0) //if it wraps around to just be the starting position
        {
            return data[(sub % (this->size()))];
        }
        else //if it wraps around to be anything other than starting
        {
            return data[(sub % (this->size())) + (this->size())];
        }
    }
    else{
        return *this->c_str();
        
    }
    
}

//string concatenation
String String::operator+(const String& rhs)
{
    //make a temp string
    String temp;
    int tempIndex = 0;
    //update the length, capacity, and data
    temp.len = this->len + rhs.len;
    temp.cap = temp.len + 2; //one more than null-terminator
    temp.data = new char[temp.len + 1];

    for (int i = 0; i < this->len; i ++)
    {
        temp.data[i] = this->data[i];
    }

    for (int j = this->len; j < temp.len; j ++)
    {
        temp.data[j] = rhs.data[tempIndex];
        tempIndex += 1;
    }

    temp.data[temp.len] = '\0'; //null terminator

    return temp; //enables cascading
}

//string + int concatenation
String String::operator+(const int& rhs)
{
    //make a temp string
    String finalString;
    //int finalIndex = 0;

    //make a string stream object
    std::stringstream number;

    //read into the string stream object
    number<<rhs;

    //make a string for just the number
    String temp = number.str().c_str();

    //call the string + string function
    finalString = *this + temp;

    //enable cascading
    return finalString;

}

//string + double concatenation
String String::operator+(const double& rhs)
{
    //make a temp string
    String finalString;
    //int finalIndex = 0;

    //make a string stream object
    std::stringstream number;

    //read into the string stream object
    number<<rhs;

    //make a string for just the number
    String temp = number.str().c_str();

    //call the string + string function
    finalString = *this + temp;

    //enable cascading
    return finalString;

}

//string += string operator
String String::operator +=(const String& rhs)
{
    //update this to be the addition of lhs and rhs
    *this = *this + rhs;

    //return this
    return *this;
}

//string += char operator
String String::operator +=(const char* rhs)
{
    //make string for the char argument
    String temp = rhs;
    
    //update this to be the addition of lhs and rhs
    *this = *this + temp;
    
    //return this
    return *this;
}


//c_string
char* String::c_str()
{
/*
    //create a new char*
    char* temp = new char[this->size() + 1];

    for (int i = 0; i < (this->size()); i++)
        {
            temp[i] = this->data[i]; //propogate the new char* with the characters from the given String
        }

    temp[this->size()] = '\0'; // null terminator

    return temp; //return the new char*
*/
    return this->data;
}

//substring given start and stop
String String::substring(int start, int end)
{
    /*
    For my substring functionality, I will not be using negative bounds and I will not wrap around if
    bounds that exceed the length are given. Also, the lower bounds cannot be greater than or equal to
    the upper bounds. If any of these are passed into the substring function as arguments, I will
    simply return a blank string.
    */

    String temp; //create a blank temporary string for creating the new substring



    int length = this->size(); //create a variable for the given string's size

    int counter = 0; //create a counter for finding the substring's size

    //now check to see what starting and ending positions were given:
    if (start < 0 || end < 0) //if negative bounds are given
    {
        temp = "";
        return temp; //return empty string
    }
    else if (start == end) // if the upper bound is the same as the lower bound
    {
        temp = "";
        return temp; //return empty string
    }
    else if (start >= length || end > length) //if the bounds exceed the length of the given string
    {
        temp = "";
        return temp; //return empty string
    }
    else if (start > end) // if the lower bounds is greater than the upper bounds
    {
        temp = "";
        return temp; //return empty string
    }
    else if (start < end) //if the lower bounds is less than the upper bounds
    {

        //add one to account for null-terminator
        temp.data = new char[(end-start) + 1];
        //set length to not account for null-terminator
        temp.len = (end - start);
        //set capacity to be 2 more than the length
        temp.cap = len + 2;

        //loop through and copy data
        for (int i = start; i < end; i ++)
        {
            //set each character
            temp.data[counter] = this->data[i];


            //temp[counter] = this->data[i];
            counter++;
        }
        temp.data[counter] = '\0';
        //temp.len = counter;
        //temp.cap = temp.len + 2;

        return temp; //return the substring
    }
    
    //return fthis if all else fails
    return *this;
    
}

//reverse the contents of a string
String String::reverse()
{
    String temp = ""; //empty string that will hold the given string in reverse order
    int index = (this->size() - 1); // create a variable that will hold the upper bound index

    for (int i = 0 ; i < this->size(); i ++)
    {
        temp.data[i] = this->data[index]; //assign the rightmost index to the start of the new string
        index--; //decrement the index
    }

    temp.data[this->size()] = '\0'; //assign null-terminator to the end of the new string

    temp.len = this->size(); //set the length equal to the original string
    temp.cap = temp.len + 2; //set the capacity to 2 more than the length

    return temp;
}

//remove spaces in a string
String String::removeSpaces()
{
    String temp = ""; //empty string that will hold the given string but without spaces
    int index = 0; //index for adding the non-spaces to the new string

    for (int i = 0; i < this->size(); i ++)
    {
        if (this->data[i] != 32)
        {
            temp.data[index] = this->data[i];
            index++;
        }
    }

    temp.data[index] = '\0'; //assign final character to null-terminator

    temp.len = index; //length does NOT include the null-terminator
    temp.cap = temp.len + 2; //capacity is 2 more than the length

    return temp;
}

//count the characters occurring in this string
int String::countCharacters(char letter)
{
    int count = 0;
    for (int i = 0; i < this->size(); i++)
    {
        if (this->data[i] == letter)
        {
            count++;
        }
    }
    return count;
}






//---------------------------- END MISCELLANEOUS FUNCTION SECTION -------------------------------------

//--------------------------------- END STRING CLASS --------------------------------------------------
