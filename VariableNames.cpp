/*
* Assignment: Final Project
* Description: This project will assess static code
* Date: 12-6-2016
* Name of Programmer: Jeremy Brachle
* Student Number: 46659942
* Course Number: 2341-802
* Lab Section: N11
*/

//VariableNames.cpp
//Metric 2: Calculate Variable Lengths

/*types to be checked:
 1) int
 2) char
 3) double
 4) bool
 5) String
 6) void
*/


#include "VariableNames.h"

//constructor
VariableNames::VariableNames()
{
    //create a VariableLength object

    //set the message to initially say what metric this is:
    String start = "\n\nMetric 2: Evaluate Variable and Function Naming conventions:\n";
    concatMessage(start);
}

//destructor
VariableNames::~VariableNames()
{
    //destorys objects
}

//calculate
double VariableNames::calculate(const Vector<String> &files)
{
    //double for the total score for this metric
    double totalScore = 0.0;

    //double for inidividual score
    double individual = 0.0;

    //ifstream object for reading the file
    ifstream reader;

    //character buffer
    char buffer;

    //string for feedback
    String feedback = "";

    //loop through the files
    for (int i = 0; i < files.size(); i ++)
    {
        //for each file, read through and look at the variable name lengths
        //divide this count by the number of variables in the program (maybe a sample?)

        //vector of strings for holding all the variables/functions
        Vector<String> members;

        //open the file
        reader.open(files[i].c_str());
        //count for total
        double totalVariables = 0.0;
        //count for correct
        double correct = 0.0;

        //reader.get(buffer);


        //loop through the file while EOF (which is '\0') has not been reached
        while (reader.get(buffer))
        {
            //read through character by character
            //ignore commented code
            /*if (buffer == '/')
            {
                //check if next is the next /
                if (reader.peek() == '/')
                {
                    //loop until the next line
                    while (reader.peek() != '\n')
                    {
                        //loop and get the characters off
                        reader.get(buffer);
                    }
                    //get the newline character
                    reader.get(buffer);
                }
                //check if next is the *
                else if (reader.peek() == '*')
                {
                    reader.get(buffer);

                    //loop until the end of the comment paragraph
                    while (reader.peek() != '/')
                    {
                        //get the characters off
                        reader.get(buffer);
                    }
                }
            }*/

            //ignore comments
            if (buffer == '/')
            {
                //check for next /
                if (reader.peek() == '/')
                {
                    //get /
                    reader.get(buffer);

                    //loop through while \n is not reached
                    while (reader.peek() != '\n' && reader.peek() != '\0')
                    {
                        //get the next character
                        reader.get(buffer);
                    }
                    if (reader.peek() != '\0')
                    {
                        //get the new line character
                        reader.get(buffer);
                    }
                    else
                    {
                        break;
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

                    } while ((buffer == '*' && reader.peek() != '/') || (buffer != '*' && reader.peek() != '/') || (buffer != '*' && reader.peek() == '/'));

                    //read off the /
                    reader.get(buffer);

                }
            }
            //ignore "code" commented code within double quotes... also check for \"
            else if (buffer == '"')
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
            //now that commented code is accounted for, look for integers
            else if (buffer == 'i')
            {
                //check to see if n is next
                if (reader.peek() == 'n')
                {
                    //get n
                    reader.get(buffer);
                    //check to see if t is next
                    if (reader.peek() == 't')
                    {
                        //get t
                        reader.get(buffer);
                        //check to see if a space or pointer is next
                        if (reader.peek() == ' ' || reader.peek() == '*')
                        {
                            //loop until no spaces or pointers
                            while (reader.peek() == ' ' || reader.peek() =='*')
                            {
                                //get the spaces/asterisks off
                                reader.get(buffer);
                            }

                            //check for const variables
                            char checkConst[7];
                            String evalConst = "const ";
                            //get next 6 characters
                            for (int j = 0; j < 6; j++)
                            {
                                reader.get(buffer);
                                checkConst[j] = buffer;
                            }
                            checkConst[6] = '\0';
                            //check if it is named const
                            if (evalConst != checkConst)
                            {
                                //unget the characters
                                for (int j = 0; j < 6; j ++)
                                {
                                    reader.unget();
                                }
                            }

                            //ignore ampersand
                            if (reader.peek() == '&')
                            {
                                //ignore because pass by reference signifier
                                reader.get(buffer);
                            }

                            //loop through and get until end of variable name (255 because the max size for a variable name
                            char temp [255];

                            //get next
                            reader.get(buffer);

                            //loop through size of the buffer and break when an edge case has been reached
                            for (int j = 0; j < 255; j ++)
                            {
                                //if not numeric, alphabetic or underscore
                                if ((buffer >= 97 && buffer <= 122) || (buffer >= 65 && buffer<= 90) || (buffer>= 48 && buffer<=57) || buffer == '_')
                                {
                                    temp[j] = buffer;
                                    reader.get(buffer);
                                }
                                //check for edge cases
                                else
                                {
                                    //check for ::
                                    if (buffer == ':' && reader.peek() ==':')
                                    {
                                        //get the next 2 :'s
                                        reader.get(buffer);
                                        reader.get(buffer);


                                        //loop through and get the rest
                                        for (int k=0; k < 255; k ++)
                                        {
                                            //if not numeric, alphabetic or underscore
                                            if ((buffer >= 97 && buffer <= 122) || (buffer >= 65 && buffer<= 90) || (buffer>= 48 && buffer<=57) || buffer == '_')
                                            {
                                                //will restart since the thing that came before it is a class member type
                                                temp[k] = buffer;
                                                reader.get(buffer);
                                            }
                                            else
                                            {
                                                //add null-terminator
                                                temp[k] = '\0';
                                                //make a string
                                                String h = temp;
                                                //add to vector
                                                //make sure no "" and actually named variables
                                                if (h != "")
                                                {
                                                   members.add(h);
                                                }
                                                //break out of for loop
                                                break;
                                            }
                                        }
                                        //now break out of outer for loop
                                        break;

                                    }
                                    else
                                    {
                                        //null-terminator
                                        temp[j] = '\0';
                                        //stirng object
                                        String h = temp;
                                        //add to vector
                                        //make sure no "" and actually named variables
                                        if (h != "")
                                        {
                                           members.add(h);
                                        }
                                        //break out of loop
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }

            }
            //check for char
            else if (buffer == 'c')
            {
                //check to see if h is next
                if (reader.peek() == 'h')
                {
                    //get h
                    reader.get(buffer);
                    //check to see if a is next
                    if (reader.peek() == 'a')
                    {
                        //get a
                        reader.get(buffer);
                        //check to see if r is next
                        if (reader.peek() == 'r')
                        {
                            //get r
                            reader.get(buffer);
                            //check to see if a space or pointer is next
                            if (reader.peek() == ' ' || reader.peek() == '*')
                            {
                                //loop until no spaces or pointers
                                while (reader.peek() == ' ' || reader.peek() =='*')
                                {
                                    //get the spaces/asterisks off
                                    reader.get(buffer);
                                }

                                //check for const variables
                                char checkConst[7];
                                String evalConst = "const ";
                                //get next 6 characters
                                for (int j = 0; j < 6; j++)
                                {
                                    reader.get(buffer);
                                    checkConst[j] = buffer;
                                }
                                checkConst[6] = '\0';
                                //check if it is named const
                                if (evalConst != checkConst)
                                {
                                    //unget the characters
                                    for (int j = 0; j < 6; j ++)
                                    {
                                        reader.unget();
                                    }
                                }

                                //ignore ampersand
                                if (reader.peek() == '&')
                                {
                                    //ignore because pass by reference signifier
                                    reader.get(buffer);
                                }



                                //loop through and get until end of variable name (255 because max size for a variable name)
                                char temp [255];

                                //get next
                                reader.get(buffer);

                                //loop through size of the buffer and break when an edge case has been reached
                                for (int k = 0; k < 255; k ++)
                                {
                                    //if not numeric, alphabetic or underscore
                                    if ((buffer >= 97 && buffer <= 122) || (buffer >= 65 && buffer<= 90) || (buffer>= 48 && buffer<=57) || buffer == '_')
                                    {
                                        temp[k] = buffer;
                                        reader.get(buffer);
                                    }
                                    //check for edge cases
                                    else
                                    {
                                        //check for ::
                                        if (buffer == ':' && reader.peek() ==':')
                                        {
                                            //get the next 2 :'s
                                            reader.get(buffer);
                                            reader.get(buffer);


                                            //loop through and get the rest
                                            for (int p=0; p < 255; p ++)
                                            {
                                                //if not numeric, alphabetic or underscore
                                                if ((buffer >= 97 && buffer <= 122) || (buffer >= 65 && buffer<= 90) || (buffer>= 48 && buffer<=57) || buffer == '_')
                                                {
                                                    //will restart since the thing that came before it is a class member type
                                                    temp[p] = buffer;
                                                    reader.get(buffer);
                                                }
                                                else
                                                {
                                                    //add null-terminator
                                                    temp[p] = '\0';
                                                    //make a string
                                                    String h = temp;
                                                    //add to vector
                                                    //make sure no "" and actually named variables
                                                    if (h != "")
                                                    {
                                                       members.add(h);
                                                    }
                                                    //break out of for loop
                                                    break;
                                                }
                                            }
                                            //now break out of outer for loop
                                            break;

                                        }
                                        else
                                        {
                                            //null-terminator
                                            temp[k] = '\0';
                                            //stirng object
                                            String h = temp;
                                            //add to vector
                                            //make sure no "" and actually named variables
                                            if (h != "")
                                            {
                                               members.add(h);
                                            }
                                            //break out of loop
                                            break;
                                        }
                                    }
                                }
                            }

                        }

                    }

                }

            }


            //check for double
            else if (buffer == 'd')
            {
                //check to see if o is next
                if (reader.peek() == 'o')
                {
                    //get o
                    reader.get(buffer);
                    //check to see if u is next
                    if (reader.peek() == 'u')
                    {
                        //get u
                        reader.get(buffer);
                        //check to see if b is next
                        if (reader.peek() == 'b')
                        {
                            //get b
                            reader.get(buffer);
                            //check to see if l is next
                            if (reader.peek() == 'l')
                            {
                                //get l
                                reader.get(buffer);
                                //check to see if e is next
                                if (reader.peek() == 'e')
                                {
                                    //get e
                                    reader.get(buffer);

                                    //check to see if a space or pointer is next
                                    if (reader.peek() == ' ' || reader.peek() == '*')
                                    {
                                        //loop until no spaces or pointers
                                        while (reader.peek() == ' ' || reader.peek() =='*')
                                        {
                                            //get the spaces/asterisks off
                                            reader.get(buffer);
                                        }

                                        //check for const variables
                                        char checkConst[7];
                                        String evalConst = "const ";
                                        //get next 6 characters
                                        for (int j = 0; j < 6; j++)
                                        {
                                            reader.get(buffer);
                                            checkConst[j] = buffer;
                                        }
                                        checkConst[6] = '\0';
                                        //check if it is named const
                                        if (evalConst != checkConst)
                                        {
                                            //unget the characters
                                            for (int j = 0; j < 6; j ++)
                                            {
                                                reader.unget();
                                            }
                                        }

                                        //ignore ampersand
                                        if (reader.peek() == '&')
                                        {
                                            //ignore because pass by reference signifier
                                            reader.get(buffer);
                                        }



                                        //loop through and get until end of variable name (255 because max size for a variable name)
                                        char temp [255];

                                        //get next
                                        reader.get(buffer);

                                        //loop through size of the buffer and break when an edge case has been reached
                                        for (int k = 0; k < 255; k ++)
                                        {
                                            //if not numeric, alphabetic or underscore
                                            if ((buffer >= 97 && buffer <= 122) || (buffer >= 65 && buffer<= 90) || (buffer>= 48 && buffer<=57) || buffer == '_')
                                            {
                                                temp[k] = buffer;
                                                reader.get(buffer);
                                            }
                                            //check for edge cases
                                            else
                                            {
                                                //check for ::
                                                if (buffer == ':' && reader.peek() ==':')
                                                {
                                                    //get the next 2 :'s
                                                    reader.get(buffer);
                                                    reader.get(buffer);


                                                    //loop through and get the rest
                                                    for (int p=0; p < 255; p ++)
                                                    {
                                                        //if not numeric, alphabetic or underscore
                                                        if ((buffer >= 97 && buffer <= 122) || (buffer >= 65 && buffer<= 90) || (buffer>= 48 && buffer<=57) || buffer == '_')
                                                        {
                                                            //will restart since the thing that came before it is a class member type
                                                            temp[p] = buffer;
                                                            reader.get(buffer);
                                                        }
                                                        else
                                                        {
                                                            //add null-terminator
                                                            temp[p] = '\0';
                                                            //make a string
                                                            String h = temp;
                                                            //add to vector
                                                            //make sure no "" and actually named variables
                                                            if (h != "")
                                                            {
                                                               members.add(h);
                                                            }
                                                            //break out of for loop
                                                            break;
                                                        }
                                                    }
                                                    //now break out of outer for loop
                                                    break;

                                                }
                                                else
                                                {
                                                    //null-terminator
                                                    temp[k] = '\0';
                                                    //stirng object
                                                    String h = temp;
                                                    //add to vector
                                                    //make sure no "" and actually named variables
                                                    if (h != "")
                                                    {
                                                       members.add(h);
                                                    }
                                                    //break out of loop
                                                    break;
                                                }
                                            }
                                        }
                                    }


                                }
                            }



                        }

                    }

                }

            }

            //check for String
            else if (buffer == 'S')
            {
                //check to see if t is next
                if (reader.peek() == 't')
                {
                    //get t
                    reader.get(buffer);
                    //check to see if r is next
                    if (reader.peek() == 'r')
                    {
                        //get r
                        reader.get(buffer);
                        //check to see if i is next
                        if (reader.peek() == 'i')
                        {
                            //get i
                            reader.get(buffer);
                            //check to see if n is next
                            if (reader.peek() == 'n')
                            {
                                //get n
                                reader.get(buffer);
                                //check to see if g is next
                                if (reader.peek() == 'g')
                                {
                                    //get g
                                    reader.get(buffer);

                                    //check to see if a space or pointer is next
                                    if (reader.peek() == ' ' || reader.peek() == '*')
                                    {
                                        //loop until no spaces or pointers
                                        while (reader.peek() == ' ' || reader.peek() =='*')
                                        {
                                            //get the spaces/asterisks off
                                            reader.get(buffer);
                                        }

                                        //check for const variables
                                        char checkConst[7];
                                        String evalConst = "const ";
                                        //get next 6 characters
                                        for (int j = 0; j < 6; j++)
                                        {
                                            reader.get(buffer);
                                            checkConst[j] = buffer;
                                        }
                                        checkConst[6] = '\0';
                                        //check if it is named const
                                        if (evalConst != checkConst)
                                        {
                                            //unget the characters
                                            for (int j = 0; j < 6; j ++)
                                            {
                                                reader.unget();
                                            }
                                        }

                                        //ignore ampersand
                                        if (reader.peek() == '&')
                                        {
                                            //ignore because pass by reference signifier
                                            reader.get(buffer);
                                        }



                                        //loop through and get until end of variable name (255 because max size for a variable name)
                                        char temp [255];

                                        //get next
                                        reader.get(buffer);

                                        //loop through size of the buffer and break when an edge case has been reached
                                        for (int k = 0; k < 255; k ++)
                                        {
                                            //if not numeric, alphabetic or underscore
                                            if ((buffer >= 97 && buffer <= 122) || (buffer >= 65 && buffer<= 90) || (buffer>= 48 && buffer<=57) || buffer == '_')
                                            {
                                                temp[k] = buffer;
                                                reader.get(buffer);
                                            }
                                            //check for edge cases
                                            else
                                            {
                                                //check for ::
                                                if (buffer == ':' && reader.peek() ==':')
                                                {
                                                    //get the next 2 :'s
                                                    reader.get(buffer);
                                                    reader.get(buffer);


                                                    //loop through and get the rest
                                                    for (int p=0; p < 255; p ++)
                                                    {
                                                        //if not numeric, alphabetic or underscore
                                                        if ((buffer >= 97 && buffer <= 122) || (buffer >= 65 && buffer<= 90) || (buffer>= 48 && buffer<=57) || buffer == '_')
                                                        {
                                                            //will restart since the thing that came before it is a class member type
                                                            temp[p] = buffer;
                                                            reader.get(buffer);
                                                        }
                                                        else
                                                        {
                                                            //add null-terminator
                                                            temp[p] = '\0';
                                                            //make a string
                                                            String h = temp;
                                                            //add to vector
                                                            //make sure no "" and actually named variables
                                                            if (h != "")
                                                            {
                                                               members.add(h);
                                                            }
                                                            //break out of for loop
                                                            break;
                                                        }
                                                    }
                                                    //now break out of outer for loop
                                                    break;

                                                }
                                                else
                                                {
                                                    //null-terminator
                                                    temp[k] = '\0';
                                                    //stirng object
                                                    String h = temp;
                                                    //add to vector
                                                    //make sure no "" and actually named variables
                                                    if (h != "")
                                                    {
                                                       members.add(h);
                                                    }
                                                    //break out of loop
                                                    break;
                                                }
                                            }
                                        }
                                    }


                                }
                            }



                        }

                    }

                }

            }

            //check for bool
            else if (buffer == 'b')
            {
                //check to see if o is next
                if (reader.peek() == 'o')
                {
                    //get o
                    reader.get(buffer);
                    //check to see if o is next
                    if (reader.peek() == 'o')
                    {
                        //geto
                        reader.get(buffer);
                        //check to see if l is next
                        if (reader.peek() == 'l')
                        {
                            //get l
                            reader.get(buffer);
                            //check to see if a space or pointer is next
                            if (reader.peek() == ' ' || reader.peek() == '*')
                            {
                                //loop until no spaces or pointers
                                while (reader.peek() == ' ' || reader.peek() =='*')
                                {
                                    //get the spaces/asterisks off
                                    reader.get(buffer);
                                }

                                //check for const variables
                                char checkConst[7];
                                String evalConst = "const ";
                                //get next 6 characters
                                for (int j = 0; j < 6; j++)
                                {
                                    reader.get(buffer);
                                    checkConst[j] = buffer;
                                }
                                checkConst[6] = '\0';
                                //check if it is named const
                                if (evalConst != checkConst)
                                {
                                    //unget the characters
                                    for (int j = 0; j < 6; j ++)
                                    {
                                        reader.unget();
                                    }
                                }

                                //ignore ampersand
                                if (reader.peek() == '&')
                                {
                                    //ignore because pass by reference signifier
                                    reader.get(buffer);
                                }



                                //loop through and get until end of variable name (255 because max size for a variable name)
                                char temp [255];

                                //get next
                                reader.get(buffer);

                                //loop through size of the buffer and break when an edge case has been reached
                                for (int k = 0; k < 255; k ++)
                                {
                                    //if not numeric, alphabetic or underscore
                                    if ((buffer >= 97 && buffer <= 122) || (buffer >= 65 && buffer<= 90) || (buffer>= 48 && buffer<=57) || buffer == '_')
                                    {
                                        temp[k] = buffer;
                                        reader.get(buffer);
                                    }
                                    //check for edge cases
                                    else
                                    {
                                        //check for ::
                                        if (buffer == ':' && reader.peek() ==':')
                                        {
                                            //get the next 2 :'s
                                            reader.get(buffer);
                                            reader.get(buffer);


                                            //loop through and get the rest
                                            for (int p=0; p < 255; p ++)
                                            {
                                                //if not numeric, alphabetic or underscore
                                                if ((buffer >= 97 && buffer <= 122) || (buffer >= 65 && buffer<= 90) || (buffer>= 48 && buffer<=57) || buffer == '_')
                                                {
                                                    //will restart since the thing that came before it is a class member type
                                                    temp[p] = buffer;
                                                    reader.get(buffer);
                                                }
                                                else
                                                {
                                                    //add null-terminator
                                                    temp[p] = '\0';
                                                    //make a string
                                                    String h = temp;
                                                    //add to vector
                                                    //make sure no "" and actually named variables
                                                    if (h != "")
                                                    {
                                                       members.add(h);
                                                    }
                                                    //break out of for loop
                                                    break;
                                                }
                                            }
                                            //now break out of outer for loop
                                            break;

                                        }
                                        else
                                        {
                                            //null-terminator
                                            temp[k] = '\0';
                                            //stirng object
                                            String h = temp;
                                            //add to vector
                                            //make sure no "" and actually named variables
                                            if (h != "")
                                            {
                                               members.add(h);
                                            }
                                            //break out of loop
                                            break;
                                        }
                                    }
                                }
                            }

                        }

                    }

                }

            }


            //check for void
            else if (buffer == 'v')
            {
                //check to see if o is next
                if (reader.peek() == 'o')
                {
                    //get o
                    reader.get(buffer);
                    //check to see if i is next
                    if (reader.peek() == 'i')
                    {
                        //get i
                        reader.get(buffer);
                        //check to see if d is next
                        if (reader.peek() == 'd')
                        {
                            //get d
                            reader.get(buffer);
                            //check to see if a space or pointer is next
                            if (reader.peek() == ' ' || reader.peek() == '*')
                            {
                                //loop until no spaces or pointers
                                while (reader.peek() == ' ' || reader.peek() =='*')
                                {
                                    //get the spaces/asterisks off
                                    reader.get(buffer);
                                }

                                //check for const variables
                                char checkConst[7];
                                String evalConst = "const ";
                                //get next 6 characters
                                for (int j = 0; j < 6; j++)
                                {
                                    reader.get(buffer);
                                    checkConst[j] = buffer;
                                }
                                checkConst[6] = '\0';
                                //check if it is named const
                                if (evalConst != checkConst)
                                {
                                    //unget the characters
                                    for (int j = 0; j < 6; j ++)
                                    {
                                        reader.unget();
                                    }
                                }

                                //ignore ampersand
                                if (reader.peek() == '&')
                                {
                                    //ignore because pass by reference signifier
                                    reader.get(buffer);
                                }



                                //loop through and get until end of variable name (255 because max size for a variable name)
                                char temp [255];

                                //get next
                                reader.get(buffer);

                                //loop through size of the buffer and break when an edge case has been reached
                                for (int k = 0; k < 255; k ++)
                                {
                                    //if not numeric, alphabetic or underscore
                                    if ((buffer >= 97 && buffer <= 122) || (buffer >= 65 && buffer<= 90) || (buffer>= 48 && buffer<=57) || buffer == '_')
                                    {
                                        temp[k] = buffer;
                                        reader.get(buffer);
                                    }
                                    //check for edge cases
                                    else
                                    {
                                        //check for ::
                                        if (buffer == ':' && reader.peek() ==':')
                                        {
                                            //get the next 2 :'s
                                            reader.get(buffer);
                                            reader.get(buffer);


                                            //loop through and get the rest
                                            for (int p=0; p < 255; p ++)
                                            {
                                                //if not numeric, alphabetic or underscore
                                                if ((buffer >= 97 && buffer <= 122) || (buffer >= 65 && buffer<= 90) || (buffer>= 48 && buffer<=57) || buffer == '_')
                                                {
                                                    //will restart since the thing that came before it is a class member type
                                                    temp[p] = buffer;
                                                    reader.get(buffer);
                                                }
                                                else
                                                {
                                                    //add null-terminator
                                                    temp[p] = '\0';
                                                    //make a string
                                                    String h = temp;
                                                    //add to vector
                                                    //make sure no "" and actually named variables
                                                    if (h != "")
                                                    {
                                                       members.add(h);
                                                    }
                                                    //break out of for loop
                                                    break;
                                                }
                                            }
                                            //now break out of outer for loop
                                            break;

                                        }
                                        else
                                        {
                                            //null-terminator
                                            temp[k] = '\0';
                                            //stirng object
                                            String h = temp;
                                            //add to vector
                                            //make sure no "" and actually named variables
                                            if (h != "")
                                            {
                                               members.add(h);
                                            }
                                            //break out of loop
                                            break;
                                        }
                                    }
                                }
                            }

                        }

                    }

                }

            }

        }

        //close the file
        reader.close();

        //now determine whether the members are "good" names
        //good: they do not end in numbers, are no longer than 30 characters, first character is lower case or _
        //loop through members vector
        for (int j = 0; j < members.size(); j ++)
        {
            //check for if the first character is "good"

            //if the first character is lower case
            if (members[j][0] >= 97 && members[j][0] <= 122)
            {
                //check for if the size is less than 30 and not a loop variable
                if (members[j].size() < 30 && members[j].size() > 1)
                {

                    //check for last character not being a number
                    if (members[j][members[j].size()-1] < 48 || members[j][members[j].size()-1] > 57)
                    {
                        //increment the correct variables
                        correct++;
                    }
                    else
                    {
                        //tell the user not to use numbers as the last character
                        feedback = feedback + "\tIn file: ";
                        feedback = feedback + files[i].c_str();
                        feedback = feedback + ", member data: " + members[j] + ", contains a digit at the end... Change this name in order to eliminate the need for a digit.\n";
                        //concatMessage(feedback);
                    }

                }
                //variable is too long
                else if (members[j].size() >= 30)
                {
                    //tell the user that their variable is too long
                    feedback = feedback + "\tIn file: ";
                    feedback = feedback + files[i].c_str();
                    feedback = feedback + ", member data: " + members[j] + ", exceeds 30 characters... Shorten this variable name.\n";
                    //concatMessage(feedback);

                }
                //variable is too short and not a for loop integer counter (i,j, or k)
                else if (members[j].size() == 1)
                {
                    if (members[j] == "i" || members[j] == "j" || members[j] == "k")
                    {
                        correct++;
                    }
                    //if not a loop integer
                    else
                    {
                        //tell the user that their variable is too short
                        feedback = feedback + "\tIn file: ";
                        feedback = feedback + files[i].c_str();
                        feedback = feedback + ", member data: " + members[j] + ", is only one character... Elaborate this variable name.\n";
                        //concatMessage(feedback);
                    }


                }

            }
            else
            {
                if (members[j][0] != 95)
                {
                    //tell the user that their variable is not camel case
                    feedback = feedback + "\tIn file: ";
                    //feedback = feedback + files[i].c_str();
                    feedback = feedback + files[i];
                    char offense[5];
                    offense[0] = members[j][0];
                    //cout<<members[j]<<endl;
                    offense[1] = '\0';
                    String letter = offense;
                    feedback = feedback + ", member data: " + members[j] + ", begins with an uppercase character... Make: '" + letter + "' lowercase.\n";
                    //concatMessage(feedback);
                }

            }
        }

        //if there exist variables in this file
        if (members.size() != 0)
        {

            //calculate the score for each file:

            //make totalVariables equal to the number of members in the vector
            totalVariables = members.size();

            //calculate the individual score:
            individual = correct / totalVariables;

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
            ssTotal<<totalVariables;
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
            indivMessage = indivMessage + files[i] + " = " + messageScore + "% good code, based on " + strCorrect + " correct variable naming conventions out of " + strTotal + " total variables.\n";
            //check if incorrect variables
            if (correct != totalVariables)
            {
                //check for 1
                if (totalVariables - correct == 1)
                {
                    indivMessage = indivMessage + "\tBreak down for the incorrect variable name:\n" + feedback;
                }
                //more than 1
                else
                {
                    indivMessage = indivMessage + "\tBreak down for the incorrect names of variables:\n" + feedback;
                }
            }
            //let the user know they named everything correctly
            else
            {
                indivMessage = indivMessage + "\tAll variables in this file were named correctly.\n";
            }
            //add this message string to the running total
            concatMessage(indivMessage);

            //add to the total score
            //divide the inidividual score by the number of files
            individual /= (double) files.size();
            //now increment the total score
            totalScore += individual;
            //reset the individual score
            individual = 0.0;

            //reset the analysis
            feedback = "";

        }
        //if there are no variables used in this file, give 100%
        else
        {
            //output message to the user to let them know they did not use variables
            String indivMessage = "\nScore for file: ";
            indivMessage = indivMessage + files[i];
            indivMessage = indivMessage + " = 0% bad code. \n\tNo variables used.\n";
            concatMessage(indivMessage);

            //set individual as 1
            individual = 1.0;
            //divide by all the files
            individual /= (double) files.size();
            //now increment the total score
            totalScore += individual;
            //reset the individual score
            individual = 0.0;
        }



    }

    //calculate total score to 2 decimal places:
    totalScore = ceil(totalScore * 10000.0 - 0.49) / (10000.0);

    //increment the final score of this metric
    incrementScore(totalScore);

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
