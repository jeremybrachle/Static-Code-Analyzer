
/*
* Assignment: Final Project
* Description: This project will assess static code
* Date: 12-6-2016
* Name of Programmer: Jeremy Brachle
* Student Number: 46659942
* Course Number: 2341-802
* Lab Section: N11
*/

//FunctionSize.h
//Metric 3: Assess the average lenth of functions

#ifndef FUNCTIONSIZE
#define FUNCTIONSIZE

#include "Metrics.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;

//begin class declaration
class FunctionSize : public Metrics
{
    //public data
public:
    //constructor
    FunctionSize();
    //destructor
    ~FunctionSize();

    //function that will calculate the score
    //this overrides the virtual function in Metrics.h
    virtual double calculate(const Vector<String>&) override;

};


#endif
