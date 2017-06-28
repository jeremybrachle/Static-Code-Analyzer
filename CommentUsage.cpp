/*
* Assignment: Final Project
* Description: This project will assess static code
* Date: 12-6-2016
* Name of Programmer: Jeremy Brachle
* Student Number: 46659942
* Course Number: 2341-802
* Lab Section: N11
*/

//CommentUsage.cpp
//metric 4: evaluate comment usage and take off points if they occur to the side of code

#include "CommentUsage.h"

//begin class implementation

//constructor
CommentUsage::CommentUsage()
{
    //create a CommentUsage object

    //set the message to initially say what metric this is:
    String start = "\n\nMetric 4: Evaluate Comment Usage:\n";
    concatMessage(start);
}

//destructor
CommentUsage::~CommentUsage()
{
    //destroy objects
}

//overridden calculate function
double CommentUsage::calculate(const Vector<String> &files)
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

    //total comments
    int totalComments = 0;

    //total correct usgaes
    int correct = 0;

    //string for the feedback
    feedback = "";

    //counter for the line number:
    int lineCount = 0;

    //loop through the files
    for (int i = 0; i < files.size(); i ++)
    {
        //open the file
        reader.open(files[i].c_str());
        //cout<<files[i]<<endl;

        //loop until EOF
        while (reader.get(buffer))
        {

            //ignore "code" commented code within double quotes... also check for \"
            if (buffer == '"')
            {
                //loop until the next one
                while (reader.peek() != '"')
                {
                    //check if \ next
                    if (reader.peek() == '\\')
                    {
                        //get the \ character
                        reader.get(buffer);
                        //get whatever is next
                        reader.get(buffer);
                    }
                    else
                    {
                       reader.get(buffer);
                    }
                }
                //get "
                reader.get(buffer);
            }
            //ignore 'code' (which is '\'') commented code... also, check for '\''
            else if (buffer == '\'')
            {
                    //until the next one
                    while (reader.peek() != '\'')
                    {
                        //check if \ next
                        if (reader.peek() == '\\')
                        {
                            //get the \ character
                            reader.get(buffer);
                            //get whatever is next
                            reader.get(buffer);
                        }
                        else
                        {
                           reader.get(buffer);
                        }

                    }
                    //get '
                    reader.get(buffer);
            }
            //look for // or /*
            else if (buffer == '/')
            {
                //check for next /
                if (reader.peek() == '/')
                {
                    //increment the total comments and the total correct
                    totalComments++; correct ++;

                    //loop through while \n is not reached
                    while (buffer != '\n' && buffer != '\0')
                    {
                        //get the next character
                        reader.get(buffer);
                    }
                    //increment the line number
                    lineCount++;
                }
                //check for *
                else if (reader.peek() == '*')
                {
                    //increment the total commments and the total correct
                    totalComments++; correct++;

                    //read until another * followed by /
                    //get the current *
                    reader.get(buffer);
                    do
                    {
                        //read off the character
                        reader.get(buffer);
                        //increment the line counter if buffer equals the new line character
                        if (buffer == '\n')
                        {
                            lineCount++;
                        }

                    } while ((buffer == '*' && reader.peek() != '/') || (buffer != '*' && reader.peek() != '/') || (buffer != '*' && reader.peek() == '/'));

                    //read off the /
                    reader.get(buffer);
                }
            }
            //look for ;
            else if (buffer == ';')
            {
                //now look for comments before the next new line
               while (reader.peek() != '\n')
                {
                    reader.get(buffer);
                    //check for comments
                    //look for // or /*
                    if (buffer == '/')
                    {
                        //check for next /
                        if (reader.peek() == '/')
                        {
                            //increment the total comments but not the total correct
                            totalComments++;

                            //set feedback message
                            //make a stringstream object for total
                            stringstream ssCurrLine;
                            //read value in
                            ssCurrLine<<(lineCount + 1);
                            //convert to char*
                            const char* ccCurrLine = ssCurrLine.str().c_str();
                            //make a string
                            String strCurrLine = ccCurrLine;
                            feedback = feedback + "\tOn line " + strCurrLine + ", there was a comment placed after a semi-colon... Place this comment somewhere else.\n";

                            //loop through while \n is not reached
                            while (buffer != '\n')
                            {
                                //get the next character
                                reader.get(buffer);
                            }
                            //increment the line count
                            lineCount++;
                        }
                        //check for *
                        else if (reader.peek() == '*')
                        {
                            //increment the total commments but not the total correct
                            totalComments++;

                            //set feedback message
                            //make a stringstream object for total
                            stringstream ssCurrLine;
                            //read value in
                            ssCurrLine<<(lineCount + 1);
                            //convert to char*
                            const char* ccCurrLine = ssCurrLine.str().c_str();
                            //make a string
                            String strCurrLine = ccCurrLine;
                            feedback = feedback + "\tOn line " + strCurrLine + ", there was a comment placed after a semi-colon... Place this comment somewhere else.\n";

                            //read until another * followed by /
                            //get the current *
                            reader.get(buffer);
                            do
                            {
                                //read off the character
                                reader.get(buffer);
                                //increment the line counter if buffer equals the new line character
                                if (buffer == '\n')
                                {
                                    lineCount++;
                                }

                            } while ((buffer == '*' && reader.peek() != '/') || (buffer != '*' && reader.peek() != '/') || (buffer != '*' && reader.peek() == '/'));

                            //read off the /
                            reader.get(buffer);
                        }
                    }
                }

            }
            else if (buffer == '\n')
            {
                //increment line count
                lineCount++;
            }

        }

        //close the file
        reader.close();

        //calculate the score for each file:

        //calculate the individual score:
        //individual = correct / (double)totalComments;

        //make sure no divide by zero error
        if (totalComments != 0)
        {
            //calculate the individual score:
            individual = correct / (double) totalComments;
        }
        //if zero blank lines
        else
        {
            //award full credit
            individual = 1.0;
        }

        //make a stringstream object for total
        stringstream ssTotal;
        //read value in
        ssTotal<<totalComments;
        //convert to char*
        const char* ccTotal = ssTotal.str().c_str();
        //make a string
        String strTotal = ccTotal;

        //make a stringstream object for correct
        stringstream ssCorrect;
        //read value in
        ssCorrect<<correct;
        //convert to char*
        const char* ccCorrect = ssCorrect.str().c_str();
        //make a string
        String strCorrect = ccCorrect;

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
        indivMessage = indivMessage + files[i] + " = " + messageScore + "% good code, based on " + strCorrect + " correct usages of comments out of " + strTotal + " total instances.\n";
        //check for improper comments
        if (correct != totalComments)
        {
            //check for 1
            if (totalComments - correct == 1)
            {
                indivMessage = indivMessage + "\tBreak down for the incorrect use of comments:\n" + feedback;
            }
            //more than 1
            else
            {
                indivMessage = indivMessage + "\tBreak down for the incorrect uses of comments:\n" + feedback;
            }

        }
        //let the user know they used comments correctly
        else
        {
            indivMessage = indivMessage + "\tAll comments in this file were used correctly.\n";
        }

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
        //reset total comments
        totalComments = 0;
        //reset correct
        correct = 0;
        //reset the feedback
        feedback = "";
        //reset the line count
        lineCount = 0;

    }

    //calculate total score to 2 decimal places:
    totalScore = ceil(totalScore * 10000.0 - 0.49) / (10000.0);

    incrementScore(totalScore);

    //output message for the total score for this metric
    //make string stream
    stringstream mScore;
    //read the double into this
    mScore<<(100 - ((totalScore)*100));
    //mScore<<(100 - (ceil(( ( totalScore * pow( 10,2 ) ) - 0.49 ) / pow( 10,2 ))*100));
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
