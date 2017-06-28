/*
* Assignment: Final Project
* Description: This project will assess static code
* Date: 12-6-2016
* Name of Programmer: Jeremy Brachle
* Student Number: 46659942
* Course Number: 2341-802
* Lab Section: N11
*/

//LineLength.cpp
//Metric 5: Calculate Line Length

#include "LineLength.h"

//begin class imlpementation

//constructor
LineLength::LineLength()
{
    //create a LineLength object

    //set the message to initially say what metric this is:
    String start = "\n\nMetric 5: Evaluate Line Length:\n";
    concatMessage(start);
}

//destructor
LineLength::~LineLength()
{
    //destroy objects
}

//overridden calculate function
double LineLength::calculate(const Vector<String> &files)
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

    //character counter for each line
    int charCount = 0;

    //counter for the current line
    int currentLine = 0;

    //counter for the total counted lines
    double totalLines = 0.0;

    //counter for correct lines
    double correct = 0.0;

    //loop through the files
    for (int i = 0; i < files.size(); i ++)
    {
        //open the file
        reader.open(files[i].c_str());

        //cout<<files[i]<<endl;

        //loop until the end of file
        while (reader.get(buffer))
        {
            //if it is not a new line character, increment the counter for the line size

            //if tab character
            if (buffer == '\t')
            {
                //increment character counter by 4
                charCount += 4;
            }
            //if not new line
            else if (buffer != '\n')
            {
                //increment couner normally
                charCount++;
            }
            //if yes new line
            else if (buffer == '\n')
            {
                //increment current line
                currentLine++;

                //increment correct if the character count is less than or equal to 150 and not 0
                if (charCount <= 150 && charCount != 0)
                {
                    //increment correct
                    correct++;
                    //increment number of lines
                    totalLines++;
                }
                //if it is greater than 150
                else if (charCount > 150)
                {
                    //output a message

                    //increment number of lines, but not correct
                    totalLines++;

                    //make a stringstream object for the total characters
                    stringstream ssNumChar;
                    //read value in
                    ssNumChar<<charCount;
                    //convert to char*
                    const char* ccNumChar = ssNumChar.str().c_str();
                    //make a string
                    String strNumChar = ccNumChar;

                    //make a stringstream object for the current line
                    stringstream ssCurrLine;
                    //read value in
                    ssCurrLine<<currentLine;
                    //convert to char*
                    const char* ccCurrLine = ssCurrLine.str().c_str();
                    //make a string
                    String strCurrLine = ccCurrLine;

                    //make the feedback message
                    feedback = feedback + "\tOn line, " + strCurrLine + ", there are " + strNumChar + " characters... Reduce the number of characters on this line by splitting onto different lines.\n";

                }

                //reset character count for the next line
                charCount = 0;
            }
        }


        //close the file
        reader.close();

        //calculate the individual score:
        individual = correct / totalLines;

        //make a stringstream object for correct
        stringstream ssCorrect;
        //read value in
        ssCorrect<<correct;
        //convert to char*
        const char* ccCorrect = ssCorrect.str().c_str();
        //make a string
        String strCorrect = ccCorrect;

        //make a stringstream object for total
        stringstream ssTotal;
        //read value in
        ssTotal<<totalLines;
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
        //make a message
        String indivMessage = "\nScore for file: ";
        //concat the message
        indivMessage = indivMessage + files[i] + " = " + messageScore + "% good code, based on " + strCorrect + " correct lengths of lines (<= 100) out of " + strTotal + " total countable instances.\n";
        //check if incorrect variables
        if (correct != totalLines)
        {
            //check for 1
            if (totalLines - correct == 1)
            {
                indivMessage = indivMessage + "\tBreak down for the incorrect use of line lengths:\n" + feedback;
            }
            //more than 1
            else
            {
                indivMessage = indivMessage + "\tBreak down for the incorrect uses of line lengths:\n" + feedback;
            }

        }
        //let the user know they named everything correctly
        else
        {
            indivMessage = indivMessage + "\tAll lines in this file are an appropriate length.\n";
        }
        //+ feedback;
        //concatenate the message to the running total
        concatMessage(indivMessage);

        //add to the total score
        //divide the inidividual score by the number of files
        individual /= (double) files.size();
        //now increment the total score
        totalScore += individual;
        //reset the individual score
        individual = 0.0;



        //reset variables

        //reset the feedback
        feedback = "";
        //reset character count
        charCount = 0;
        //reset current line
        currentLine = 0;
        //reset total line
        totalLines = 0.0;
        //reset correct
        correct = 0.0;

    }

    //calculate total score to 2 decimal places:
    totalScore = ceil(totalScore * 10000.0 - 0.49) / (10000.0);

    //increment the final score of this metric
    incrementScore(round(totalScore));

    //output message for the total score for this metric
    //make string stream
    stringstream mScore;
    //read the double into this
    mScore<<(100 - totalScore*100);
    //convert to char*
    const char* charScore = mScore.str().c_str();
    //convert to string
    String strScore = charScore;
    //make a message:
    String finalMessage = "_______________________________________________________________________________________________________________________________________\n\t->Total Metric Score: ";
    finalMessage = finalMessage + strScore + "% good code.\n";
    concatMessage(finalMessage);

    //return the score
    return getScore();

}
