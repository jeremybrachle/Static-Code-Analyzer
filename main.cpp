
/*
 * Project: Static Code Analyzer
 * Description:
 *   This project analyzes C and C++ source code to assess the "goodness" of it
 *   based on 5 metric that I have chosen. This was my final project for CSE 2341 at
 *   SMU and I am now expanding it to be more versatile.
 * Initial Start Date: 12-6-2016
 * Name of Programmer: Jeremy Brachle
 */

//include the necessary libraries
#include <iostream>
#include <iomanip>
#include "avltree.h"
#include "linkedlist.h"
#include <dirent.h>
#include <fstream>
#include "ProcessMetrics.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

//recursive function that will find the files
void findFiles(String, Vector<String>&);

int main(int argc, char* const argv[])
{
    
    /*Program Hierarchy:
     
     Step 1: Open the Start Folder
     A. Descend through files recursively and add them to a vector of strings
     Note: to access the files, the strings will be converted to c-strings
     
     Step 2: Send the vector of files to be read through and assessed by the following metrics:
     Metric 1: Blank Space Usage (make sure there are not any unnecessary blank lines)
     Metric 2: Variable/function naming conventions based on sample taken from standard types (int, char, String, etc.)
     Metric 3: Average Function Length (make sure the functions are not too long)
     Metric 4: Comment usage (on the side of code rather than above)
     Metric 5: Line Length (make sure the lines don't go too far to the right, over 100 characters)
     
     Step 3: Output the results based on whether the user wants a verbose or brief output
     */
    
    //get the command line arguments
    //argument 1 (brief (-b) or verbose (-v) request)
    const String request = argv[1];
    //argument 2 file that contains the the name of the full qualified path
    const char* inputFile = argv[2];
    //argument 3 (output file)
    const char* outputFile = argv[3];
    
    //make an ifstream object
    ifstream reader;
    //open the input file
    reader.open(inputFile);
    //make sure the input file was opened
    if (!reader)
    {
        cout<<"Input file not found"<<endl;
        return 1;
    }
    
    
    //make an ofstream object for output
    ofstream outputData;
    //open output file
    outputData.open(outputFile);
    //make sure the output file was opened
    if (!outputData)
    {
        cout<<"Output file not found"<<endl;
        return 1;
    }
    
    //make a character buffer
    char buffer;
    //make a string for the beginning directory
    String beginDirectory = "";
    //make a vector for holding the characters from the input file
    Vector<char> letters;
    
    //read the input file to find the name of the folder that will be assessed for this program
    //loop through while the buffer is not at the end of file
    while (reader.get(buffer))
    {
        //add the character to the letter vector
        letters.add(buffer);
        
        //peek at next
        //check if end of file (-1) or new line (10)
        if (reader.peek() == -1 || reader.peek() == 10)
        {
            //make a new character array with the size of the letters and an extra 5 for padding
            char* startFolder = new char [letters.size() + 5];
            
            //loop through and add to the new character array
            for (int i = 0; i < letters.size(); i++)
            {
                startFolder[i] = letters[i];
            }
            
            //add the null-terminator
            startFolder[letters.size()] = '\0';
            
            //set the string equal to the character array
            beginDirectory = startFolder;
            
            //deallocate the character array
            delete [] startFolder;
            
        }
    }
    
    //make a vector of strings which will hold all the files
    Vector<String> files;
    
    //send the start folder and vector into a recursive function for finding the files
    //this function will return the vector by reference with the file paths
    findFiles(beginDirectory, files);
    
    //create a ProcessMetrics object
    ProcessMetrics p;
    
    //String for holding the score feedback
    String feedback = "";
    
    //double for holding the numerical score
    double finalScore = 0.0;
    
    //get the score from the function in ProcessMetrics Class
    p.getScore(files, request, feedback, finalScore);
    
    //output the feedback followed by a line break
    outputData<<feedback<<endl;
    
    //calculate final score
    finalScore = (100 - 100*finalScore);
    //output the final score to 2 decimal places
    outputData<<"\nFinal Score: "<<fixed<<setprecision(2)<<finalScore<<"% good code"<<endl;
    
    //close the input file
    reader.close();
    
    return 0;
}

//recursive function for finding the files in a directory
void findFiles(String directory, Vector<String> &files)
{
    //create a DIR object for opening current directory
    DIR *open = opendir(directory.c_str());
    
    //create a dirent object for reading the current directory
    struct dirent *read;
    
    //make a stat object for tranlating from unix
    //struct stat s;
    
    //make sure ther are still filess to be read
    if (!(open = opendir(directory.c_str())))
    {
        //end recursion
        return;
    }
    
    //make a string object for the file type
    String fileType = "";
    
    //loop through while there are files to read
    while ((read = readdir(open)) != NULL)
    {
        //create a string of the directory object name
        String directoryObject = read->d_name;
        //cout<<directoryObject<<endl;
        
        if (directoryObject != "." && directoryObject != "..")
        {
            
            //get the full path name
            String pathName = directory + "/" + directoryObject;
            
            //make a struct for the statbuf
            //this is for determining folders on a windows machine
            struct stat statbuf;
            
            //call the stat function on the full path name
            stat(pathName.c_str(), &statbuf);
            
            //if it is a directory...
            if (S_ISDIR(statbuf.st_mode))
            {
                //...make the file type a folder
                //cout<<"is a directory"<<endl;
                fileType = "folder";
            }
            
            //check the type
            //if no periods...
            if (directoryObject.countCharacters('.') == 0 && fileType != "folder")
            {
                //..then no type we need to deal with
                fileType = "none";
            }
            //if the file does include periods
            else
            {
                if (directoryObject != "." && directoryObject != "..")
                {
                    //loop through the file name
                    for (int i = 0; i < directoryObject.size(); i ++)
                    {
                        //look for first occurrence of .
                        if (directoryObject[i] == '.')
                        {
                            //set the file type (goes until the end of the word)
                            fileType = directoryObject.substring(i, directoryObject.size());
                            //cout<<fileType<<endl;
                            break;
                        }
                    }
                }
                
                
            }
            
            
            //make sure no ~ at the end
            if (fileType[fileType.size()-1] == '~')
            {
                //remove this character
                //fileType = fileType.substring(0,fileType.size()-1);
            }
            
            
            //make sure .c, .cpp, .h, or .hpp file type
            if (fileType == ".c" || fileType == ".cpp" || fileType == ".h" || fileType == ".hpp")
            {
                //set the file name
                String fileName = directory + "/" + directoryObject;
                //cout<<fileName<<endl;
                
                files.add(fileName);
                //cout<<fileName<<endl;
            }
            
            if (fileType == "folder" && directoryObject != "." && directoryObject != "..")
            {
                //set the new directory
                String nextDirectory = directory + "/" + directoryObject;
                //perform recursion with this new folder
                findFiles(nextDirectory, files);
            }
            
            
        }
        
    }
    
}
