/*
* Assignment: Final Project
* Description: This project will assess static code
* Date: 12-6-2016
* Name of Programmer: Jeremy Brachle
* Student Number: 46659942
* Course Number: 2341-802
* Lab Section: N11
*/

//Blanks.h
//Metric 1: Calculate Blanks

#ifndef BLANKS
#define BLANKS

#include "Metrics.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

//#include "DSString.h"
//#include "vector.h"

//begin class declaration
class Blanks : public Metrics
{
    //public functions
public:
    //constructor
    Blanks();
    //destructor
    ~Blanks();

    //function that will calculate the score
    //this overrides the virtual function in Metrics.h
    virtual double calculate(const Vector<String>&) override;

};

#endif
