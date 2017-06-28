/*
* Assignment: Final Project
* Description: This project will assess static code
* Date: 12-6-2016
* Name of Programmer: Jeremy Brachle
* Student Number: 46659942
* Course Number: 2341-802
* Lab Section: N11
*/

//VariableNames.h
//Metric 2: Variable Naming Conventions

#ifndef VARIABLENAMES
#define VARIABLENAMES

#include "Metrics.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

//begin class declaration
class VariableNames : public Metrics
{
    //public functions:
public:
    //constructor
    VariableNames();
    //destructor
    ~VariableNames();

    //function that will calculate the score
    //this overrides the virtual function in Metrics.h
    virtual double calculate(const Vector<String>&) override;

};


#endif
