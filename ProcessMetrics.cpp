/*
* Assignment: Final Project
* Description: This project will assess static code
* Date: 12-6-2016
* Name of Programmer: Jeremy Brachle
* Student Number: 46659942
* Course Number: 2341-802
* Lab Section: N11
*/

//ProcessMetrics.cpp
//contains the implementation of processmetrics.h

#include "ProcessMetrics.h"
//#include "DSString.h"
//#include "vector.h"
//will include the metrics files
//#include "Blanks.h"
//#include "VariableLength.h"

//constructor
ProcessMetrics::ProcessMetrics()
{
    //create a processmetric object
}

//destructor

ProcessMetrics::~ProcessMetrics()
{
    //delete the object
}


//get the score from the individual metrics classes
String ProcessMetrics::getScore(const Vector<String> &files, const String &request, String &output, double &totalScore)
{
    //temporary double for holding inidivual scores
    double temp = 0.0;

    //weights for each metric
    //for now they are all equal (20%) but can be subject to change if desired)
    double m1WeightBlanks = 20.0;
    double m2WeightVarName = 20.0;
    double m3WeightFuncSize = 20.0;
    double m4WeightComments = 20.0;
    double m5WeightLineLen = 20.0;
    
    //individual weight
    double indivWeight = 0.0;

    //make an int for the number of metrics being processed
    int numMetrics = 5;
    
    //make objects for the different metrics
    Blanks m1; //blanks
    VariableNames m2; //variable names
    FunctionSize m3; //function size
    CommentUsage m4; //comment usage
    LineLength m5; //line length
    
    //make a general metrics pointer that will be reset every time
    Metrics* processMetrics = NULL;
    
    //check for brief or verbose request
    //if just the score
    if (request == "-b")
    {
        //tell the user what type of output was requested
        output = "Brief Output Requested.\n";

        //loop through the metrics
        for (int i = 1; i <= numMetrics; i ++)
        {
            //for each iteration, set the metrics pointer equal to a different metric
            switch(i)
            {
                case 1: processMetrics = &m1; indivWeight = m1WeightBlanks; break;
                case 2: processMetrics = &m2; indivWeight = m2WeightVarName; break;
                case 3: processMetrics = &m3; indivWeight = m3WeightFuncSize; break;
                case 4: processMetrics = &m4; indivWeight = m4WeightComments; break;
                case 5: processMetrics = &m5; indivWeight = m5WeightLineLen; break;
            }
            
            //call the process metrics function
            processMetrics->calculate(files);
            
            //get the temporary score
            temp = processMetrics->getScore();
            
            //now divide the temp score by the individual weight
            temp /= (100 / indivWeight);
            
            //add the temp score to the total
            totalScore += temp;
            
        }

    }
    
    //if the user wants feedback
    else if (request == "-v")
    {
        //tell the user what type of output was requested
        output = "Verbose Output Requested.\n";

        //calculate metrics and retrieve verbose output score

        //tell the user how many files will be examined
        output = output + "\nNumber of files to be examined: " + files.size();

        //loop through the metrics
        for (int i = 1; i <= numMetrics; i ++)
        {
            //for each iteration, set the metrics pointer equal to a different metric
            switch(i)
            {
                case 1: processMetrics = &m1; indivWeight = m1WeightBlanks; break;
                case 2: processMetrics = &m2; indivWeight = m2WeightVarName; break;
                case 3: processMetrics = &m3; indivWeight = m3WeightFuncSize; break;
                case 4: processMetrics = &m4; indivWeight = m4WeightComments; break;
                case 5: processMetrics = &m5; indivWeight = m5WeightLineLen; break;
            }
            
            //call the process metrics function
            processMetrics->calculate(files);
            
            //get the output
            output+= processMetrics->getMessage();
            
            //get the temporary score
            temp = processMetrics->getScore();
            
            //now divide the temp score by the individual weight
            temp /= (100 / indivWeight);
            
            //add the temp score to the total
            totalScore += temp;
            
        }
        
    }

    return output;
}
