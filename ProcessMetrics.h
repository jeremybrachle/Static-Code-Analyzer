/*
* Assignment: Final Project
* Description: This project will assess static code
* Date: 12-6-2016
* Name of Programmer: Jeremy Brachle
* Student Number: 46659942
* Course Number: 2341-802
* Lab Section: N11
*/

//ProcessMetrics.h
//file for processing the score from each metric

#ifndef PROCESSMETRICS
#define PROCESSMETRICS

//include string in order to process the vector of strings for files
//#include "Metrics.h"
//#include "Blanks.h"
//#include "DSString.h"
//#include "vector.h"
#include "Blanks.h"
#include "VariableNames.h"
#include "FunctionSize.h"
#include "CommentUsage.h"
#include "LineLength.h"


//begin class declaration
class ProcessMetrics
{
    //publlic functions
public:

    //constructor
    ProcessMetrics();

    //destructor
    ~ProcessMetrics();

    //return the score after processing from the metric classes
    String getScore(const Vector<String>&, const String&, String&, double&);

};


#endif
