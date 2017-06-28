/*
* Assignment: Final Project
* Description: This project will assess static code
* Date: 12-6-2016
* Name of Programmer: Jeremy Brachle
* Student Number: 46659942
* Course Number: 2341-802
* Lab Section: N11
*/

//Blanks.cpp
//Metric 1: Calculate Blanks

#include "Blanks.h"

//begin class imlpementation

//constructor
Blanks::Blanks()
{
    //create a Blanks object

    //set the message to initially say what metric this is:
    String start = "\n\nMetric 1: Evaluate Blank Lines:\n";
    concatMessage(start);
}

//destructor
Blanks::~Blanks()
{
    //destroy objects
}

//overridden calculate function
double Blanks::calculate(const Vector<String> &files)
{
    //double for the total score for this metric
    double totalScore = 0.0;

    //double for inidividual score
    double individual = 0.0;

    //ifstream object for reading the file
    ifstream reader;

    //character buffer
    char buffer;

    //individual string for feedback
    String feedback = "";

    //loop through the files
    for (int i = 0; i < files.size(); i ++)
    {
        //for each file, read through and look for occurrences of when a programmer uses two \n in a row
        //divide this count by the number of \n in the program

        //make a counter for incorrect usages
        int incorrect = 0;

        //open the file
        reader.open(files[i].c_str());

        //count for total
        double totalBlank = 0.0;
        //count for correct
        double correct = 0.0;
        //bool for if previous was new line
        bool prev = false;
        //counter for number of lines of code
        int lines = 0;

        //loop through the file while EOF (which is '\0') has not been reached
        //reader.get(buffer);
        while (reader.get(buffer))
        {
            //check for when an entire line is blank and the previous line was not blank
            if (buffer == '\n' && prev == false)
            {
                //increment the number of blanks
                totalBlank += 1.0;
                //increment the number of correct usages
                correct += 1.0;
                //set previous to be true
                prev = true;
                //increment number of lines of code
                lines++;
            }
            //if a blank line is encountered and the previous line was also blank
            else if (buffer == '\n' && prev == true)
            {
                //increment the number of blanks
                totalBlank += 1.0;
                //do NOT increment the number of correct
                //keep previous boolean still true
                //increment number of lines of code
                lines++;

                //increment the incorrect
                incorrect++;

                //signify that a transgression has occurred:
                //String feedback = "";
                //getOffense(lines, feedback);


                //signify that a transgression has occurred:
                //make a stringstream object
                stringstream convert;
                //read the line into the stringstream
                convert<<lines;
                //convert to a const char*
                const char* lineNum = convert.str().c_str();
                //make a new string stream object
                stringstream convertIncorrect;
                //read the incorrect usages into the stringstream
                convertIncorrect<<incorrect;
                //convert to a const char*
                const char* incorrectUsage = convertIncorrect.str().c_str();
                //convert to a string
                String offense = lineNum;
                //make an output message
                //feedback = feedback + "\n\tIn file: ";
                //feedback = feedback + files[i].c_str();
                feedback = feedback + "\n\t" + incorrectUsage + ") An extra blank line was added on line: ";
                feedback = feedback + offense + "\n\tFIX -> Delete line " + offense + ".\n";
                //concatMessage(feedback);


            }
            //if it is not a blank
            else
            {
                //make the previous false
                prev = false;

                //loop through while \n is not reached
                while (buffer != '\n')
                {
                    //get the next character
                    reader.get(buffer);
                }
                //increment number of lines of code
                lines++;
            }

        }

        //close the file
        reader.close();

        //calculate the score for each file:

        //make sure no divide by zero error
        if (totalBlank != 0)
        {
            //calculate the individual score:
            individual = correct / totalBlank;
        }
        //if zero blank lines
        else
        {
            //award full credit
            individual = 1.0;
        }


        //make a stringstream object for incorrect
        stringstream ssIncorrect;
        //read value in
        double totalIncorrect = totalBlank - correct;
        ssIncorrect<<totalIncorrect;
        //convert to char*
        const char* ccIncorrect = ssIncorrect.str().c_str();
        //make a string
        String strIncorrect = ccIncorrect;

        //make a stringstream object for total
        stringstream ssTotal;
        //read value in
        ssTotal<<totalBlank;
        //convert to char*
        const char* ccTotal = ssTotal.str().c_str();
        //make a string
        String strTotal = ccTotal;


        //make a stringstream object for message
        stringstream indivScore;
        //read the double into the string stream object
        indivScore<<(100 - individual*100);
        //convert to char*
        const char* temp = indivScore.str().c_str();
        //convert to string
        String messageScore = temp;
        //make a message that will number the files in order
        String indivMessage = "\nFile ";
        indivMessage = indivMessage + (i + 1) + ": ";
        //concat the message
        //determine if plural or singular
        if (totalIncorrect == 1)
        {
            //now check the total correct
            if (totalBlank == 1)
            {
                indivMessage = indivMessage + files[i] + "\nScore for file = " + messageScore + "% good code, based on 1 incorrect usage of blank lines out of 1 total instance of blank lines.\n";
            }
            else
            {
                indivMessage = indivMessage + files[i] + "\nScore for file = " + messageScore + "% good code, based on 1 incorrect usage of blank lines out of " + strTotal + " total instances of blank lines.\n";
            }

        }
        else
        {
            indivMessage = indivMessage + files[i] + "\nScore for file = " + messageScore + "% good code, based on " + strIncorrect + " incorrect usages of blank lines out of " + strTotal + " total instances of blank lines.\n";
        }
        //check if incorrect blanks
        if (correct != totalBlank)
        {
            //check for 1
            if (totalBlank - correct == 1)
            {
                indivMessage = indivMessage + "------->Break down for the incorrect usage of blank lines:\n" + feedback;
            }
            //more than 1
            else
            {
                indivMessage = indivMessage + "------->Break down for the incorrect usages of blank lines:\n" + feedback;
            }

        }
        //let the user know they named everything correctly
        else
        {
            indivMessage = indivMessage + "\tAll blank lines in this file were used correctly.\n";
        }

        //concatenate the message for the individual feedback
        concatMessage(indivMessage);

        //add to the total score
        //divide the inidividual score by the number of files
        individual /= (double) files.size();
        //now increment the total score
        totalScore += individual;
        //reset the individual score
        individual = 0.0;

        //reset the feedback
        feedback = "";

    }

    //increment the final score of this metric
    incrementScore(totalScore);

    //output message for the total score for this metric
    String finalMessage = "_______________________________________________________________________________________________________________________________________\n\t->Total Metric Score: ";
    finalMessage = finalMessage + (100 - totalScore*100) + "% good code.\n";
    concatMessage(finalMessage);

    //return the score
    return getScore();
}
