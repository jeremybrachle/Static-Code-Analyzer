/*
* Assignment: Final Project
* Description: This project will assess static code
* Date: 12-6-2016
* Name of Programmer: Jeremy Brachle
* Student Number: 46659942
* Course Number: 2341-802
* Lab Section: N11
*/


//functionsize.cpp
//Metric 3: Evaluate the average length of the functions in a file

#include "FunctionSize.h"

//begin class implementation

//constructor
FunctionSize::FunctionSize()
{
    //create  the object

    //set up the message:
    //set the message to initially say what metric this is:
    String start = "\n\nMetric 3: Evaluate the Average Function Length in a file:\n";
    concatMessage(start);
}

//destructor
FunctionSize::~FunctionSize()
{
    //destroys objects
}

//overloaded calculate function:
//calculate
double FunctionSize::calculate(const Vector<String> &files)
{
    //loop through the files and calculate the average function length

    //double for the total score for this metric
    double totalScore = 0.0;

    //double for inidividual score
    double individual = 0.0;

    //ifstream object for reading the file
    ifstream reader;

    //character buffer
    char buffer;

    //counter for left brace
    int leftBrace = 0;

    //counter for lines
    int lines = 0;

    //counter for ignoring right braces
    int ignore = 0;

    //number of functions
    int functions = 0;

    //total number of function lines in a file:
    int totalLines = 0;

    //average function length
    double averageLength = 0;

    //current line
    int currentLine = 0;

    //string for feedback
    String feedback = "";

    //counter for the number of correct usages
    double correct = 0.0;

    //loop through files
    for(int i = 0; i < files.size(); i ++)
    {

        //open the file
        reader.open(files[i].c_str());
        //cout<<files[i]<<endl;

        //look for the first '{' character and count the number of lines until its matching pair

        //loop until end of file
        while (reader.get(buffer))
        {
            //check for {

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
            //ignore comments
            else if (buffer == '/')
            {
                //check for next /
                if (reader.peek() == '/')
                {
                    //loop through while \n is not reached
                    while (reader.peek() != '\n')
                    {
                        //get the next character
                        reader.get(buffer);
                    }
                    //get the new line character
                    reader.get(buffer);
                    //increment the current line
                    currentLine++;
                    //increment lines too if applicable
                    if (leftBrace == 1)
                    {
                        lines++;
                    }
                }
                //check for *
                else if (reader.peek() == '*')
                {
                    //read until another * followed by /
                    //get the current *
                    reader.get(buffer);
                    do
                    {
                        //read off the character
                        reader.get(buffer);

                        //check for new line
                        if (buffer == '\n')
                        {
                            currentLine++;
                        }
                        else if (buffer == '\n' && leftBrace == 1)
                        {
                            currentLine++;
                            lines++;
                        }


                    } while ((buffer == '*' && reader.peek() != '/') || (buffer != '*' && reader.peek() != '/') || (buffer != '*' && reader.peek() == '/'));

                    //read off the /
                    reader.get(buffer);

                }
            }
            //first occurrence of {
            else if (buffer == '{' && leftBrace == 0)
            {
                //start the count
                leftBrace = 1;
                //increment the number of functions
                functions++;
                //reset lines
                lines = 0;
            }
            //any other occurrence within the first {
            else if (buffer == '{'&& leftBrace == 1)
            {
                //increment ignore
                ignore ++;
            }
            //first occurrence of } when nested inside
            else if (buffer == '}' && ignore != 0)
            {
                //decrement ignore
                ignore --;
            }
            //final occurrence of } (nesting has been found)
            else if (buffer == '}' && ignore == 0)
            {
                //reset left brace
                leftBrace = 0;

                //determine which output
                //if there is more than one line for the function
                if (lines != 0)
                {
                    //decrement lines
                    lines--;
                    //increment total number of lines:
                    totalLines += lines;

                    //make an integer for the starting line
                    int startLine = currentLine - lines;

                    //make a string stream object for the start line
                    stringstream ssStartLine;
                    //read value in
                    ssStartLine<<startLine;
                    //convert to char*
                    const char* ccStartLine = ssStartLine.str().c_str();
                    //make a string
                    String strStartLine = ccStartLine;

                    //make a string stream object for the number of lines
                    stringstream ssNumLines;
                    //read value in
                    ssNumLines<<lines;
                    //convert to char*
                    const char* ccNumLines = ssNumLines.str().c_str();
                    //make a string
                    String strNumLines = ccNumLines;

                    //set the feedback
                    if (lines == 1)
                    {
                        //set feedback
                        feedback = feedback + "\tFunction beginning on line " + strStartLine + ", contains: "+ strNumLines + " line of code... This is acceptable.\n";
                        //increment correct
                        correct ++;
                    }
                    else
                    {
                        //check if more than 50
                        //less than 50
                        if (lines <= 50)
                        {
                            //set feedback
                            feedback = feedback + "\tFunction beginning on line " + strStartLine + ", contains: "+ strNumLines + " lines of code... This is acceptable.\n";
                            //increment correct
                            correct ++;
                        }
                        //greater than 50
                        else
                        {
                            //set feedback and tell user to fix this function.. also, do not increment correct
                            feedback = feedback + "\tFunction beginning on line " + strStartLine + ", contains: "+ strNumLines + " lines of code... Shorten this function or split the task into several smaller functions.\n";
                        }
                    }


                    //cout<<"Function beginning on line: "<<(currentLine - lines)<<" contains "<<lines<<" line(s)"<<endl;
                }
                //if only one line for a function
                else if (lines == 0)
                {
                    //make an integer for the starting line (plus 1 to make up for the fact that this function is only on one line)
                    int startLine = currentLine - lines + 1;

                    //make a string stream object for the start line
                    stringstream ssStartLine;
                    //read value in
                    ssStartLine<<startLine;
                    //convert to char*
                    const char* ccStartLine = ssStartLine.str().c_str();
                    //make a string
                    String strStartLine = ccStartLine;

                    //set the feedback
                    feedback = feedback + "\tFunction beginning on line " + strStartLine + ", contains: zero lines of code... This is acceptable.\n";

                    //increment correct
                    correct ++;

                    //cout<<"Function beginning on line "<<(currentLine - lines + 1)<<", contains "<<lines<<" line(s)"<<endl;
                }

                //check to see how many functions have been read so far
                if (functions > 20)
                {
                    //only read 30 functions
                    //break out;
                    break;
                }

            }
            //check for new line character if buffer is inside a left brace
            else if (buffer == '\n' && leftBrace == 1)
            {
                //increment line count
                lines++;
                //increment current line
                currentLine ++;
            }
            //if just normal new line
            else if (buffer == '\n' && leftBrace != 1)
            {
               //increment current line
                currentLine ++;
            }

        }

        //close the file reader:
        reader.close();



        //cout<<"Number of functions: "<<functions<<endl;
        //cout<<"Average Function Length: "<<averageLength<<" lines"<<endl;



        //calculate the score for each file:

        //first calculate the average function length
        //averageLength = totalLines / (double)functions;

        //make sure no divide by zero error
        if (functions != 0)
        {
            //calculate the individual score:
            averageLength = totalLines / (double)functions;
        }
        //if zero blank lines
        else
        {
            //award full credit
            averageLength = 1.0;
        }

        //make a string stream object for average function length
        stringstream ssAverage;
        //read value in
        ssAverage<<averageLength;
        //convert to char*
        const char* ccAverage = ssAverage.str().c_str();
        //make a string
        String strAverage = ccAverage;

        //make a string stream object for total number of functions
        stringstream ssNumFunctions;
        //read value in
        ssNumFunctions<<functions;
        //convert to char*
        const char* ccNumFunctions = ssNumFunctions.str().c_str();
        //make a string
        String strNumFunctions = ccNumFunctions;

        //make a string for average message
        String avgMessage = "";
        //provide a message for the average function length
        avgMessage = "average function length: ";
        //check the number of functions
        //if only 1
        if (functions == 1)
        {
            avgMessage = avgMessage + strAverage + " lines of code for every 1 function.\n\tBreak down for the single function:\n";
        }
        //if more than 1
        else if (functions != 0)
        {
            avgMessage = avgMessage + strAverage + " lines of code for every "+ strNumFunctions + " functions.\n\tBreak down for the functions (both correct and incorrect):\n";
        }
        else if (functions == 0)
        {
            avgMessage = avgMessage + strAverage + " lines of code for every "+ strNumFunctions + " functions.\n";
        }



        //calculate the individual score:
        //if it is less than or equal to 50, automatically award full points
        if (averageLength <= 50.0)
        {
            //set individual equal to 1.0 (this is the full score)
            individual = 1.0;
        }
        //if it is greater than 50
        else
        {
            //make sure no divide by zero error
            if (functions != 0)
            {
                //calculate the individual score:
                individual = correct / (double)functions;
            }
            //if zero blank lines
            else
            {
                //award full credit
                individual = 1.0;
            }

            //set individual score to be the number of correct usages (functions less than or equal to 50 lines) divided by  the total functions
            //individual = correct / (double)functions;
        }




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
        if (functions != 0)
        {
            indivMessage = indivMessage + files[i] + " = " + messageScore + "% good code, based on "+ avgMessage + feedback;
        }
        else if (functions == 0)
        {
            indivMessage = indivMessage + files[i] + " = " + messageScore + "% good code.\n\tNote: no functions in this file.\n";
        }

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
        //reset the counter for the number of lines
        lines = 0;
        //reset the counter for the number of functions
        functions = 0;
        //reset total lines
        totalLines = 0;
        //reset the average length
        averageLength = 0;
        //reset current line
        currentLine = 0;
        //reset correct
        correct = 0.0;
        //reset left brace
        leftBrace = 0;

    }

    //calculate total score to 2 decimal places:
    totalScore = ceil(totalScore * 10000.0 - 0.49) / (10000.0);

    //increment the final score of this metric
    incrementScore(totalScore);

    //output message for the total score for this metric
    //make string stream
    stringstream mScore;
    //read the double into this
    mScore<<(100 - ((totalScore)*100));
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
