/*
* Assignment: Final Project
* Description: This project will assess static code
* Date: 12-6-2016
* Name of Programmer: Jeremy Brachle
* Student Number: 46659942
* Course Number: 2341-802
* Lab Section: N11
*/

//Metrics.h
//Polymorphic metrics file

#ifndef METRICS
#define METRICS

#include "DSString.h"
#include "vector.h"
#include <cmath>

class Metrics
{
    //public functions
public:
    //empty constructor
    Metrics() {}
    //empty destructor
    ~Metrics() {}

    //getters for private data
    double getScore() {return score;}
    String getMessage() {return message;}

    //increment score
    void incrementScore(const double &val) {score += val;}
    //concat the message
    void concatMessage(const String &feedback) {message = message + feedback;}

    //pure virtual function for calculating the score
    virtual double calculate(const Vector<String>&) = 0;
    //virtual double calculate() =0;

    //private data
private:
    //the score:
    double score = 0.0;
    //a message for verbose output
    String message = "";

};

#endif
