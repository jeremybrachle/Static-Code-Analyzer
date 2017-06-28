/*
* Assignment: Final Project
* Description: This project will assess static code
* Date: 12-6-2016
* Name of Programmer: Jeremy Brachle
* Student Number: 46659942
* Course Number: 2341-802
* Lab Section: N11
*/

//CommentUsage.h
//metric 4: evaluate comment usage and take off points if they occur to the side of code

#ifndef COMMENTUSAGE
#define COMMENTUSAGE

#include "Metrics.h"
#include <fstream>
#include <iostream>
#include <sstream>
//#include <cmath>
using namespace std;

//begin class declaration
class CommentUsage : public Metrics
{
    //public data
public:
    //constructor
    CommentUsage();
    //destructor
    ~CommentUsage();

    //function that will calculate the score
    //this overrides the virtual function in Metrics.h
    virtual double calculate(const Vector<String>&) override;
};


#endif
