////Partner Work: Project 2
//Elia Deppe & Tatiana Nikolaeva

//CMSC 441
//Professor Marron

/*
!!!NOTE (Elia)!!!
    This was created while using Codeblocks on a Windows machine. When testing the
    project I used a .exe file and 2 text file inputs on the command line. That is why
    the main uses arguments file.open(argv[1]) and file.open(argv[2]); I was unsure of how to adjust
    this to ensure it to read the correct position for the text file for machines running Linux
    or Mac or if someone wished to output to a specific file using terminal arguments.
    Please adjust it to the correct position if necessary.
!!!END NOTE!!!
*/

//includes
#include <iostream>
#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>


//function declaration
//LCS
//takes in a dynamic 2d array, 2 strings received from the text files, and their
//  respective lengths
long LCS(long **array, std::string s1, std::string s2, const long len1, const long len2);


//main
int main(int argc, char *argv[]) {
    //invalid amount of arguments
    if(argc != 3) {
        std::cout << "please supply two text files\n";
        return 0;
    }

    std::ifstream file;                     //file
    std::stringstream buffer1, buffer2;     //string buffers
    std::string s1, s2;                     //strings

    //open the first file, read into the buffer, and then convert to a string
    file.open(argv[1]);
    if(file.is_open()) {
        buffer1 << file.rdbuf();
        s1 = buffer1.str();
        file.close();
    }
    else {  //if file didn't open properly
        std::cout << "Invalid filename for 1st text file, exiting...";
        return 0;
    }

    //open the second file, read into the buffer, and then convert into a string
    file.open(argv[2]);
    if(file.is_open()) {
        buffer2 << file.rdbuf();
        s2 = buffer2.str();
        file.close();
    }
    else {  //if file didn't open properly
        std::cout << "Invalid filename for 2nd text file, exiting...";
        return 0;
    }

    const long len1 = (long)s1.length();        //length of string 1
    const long len2 = (long)s2.length();        //length of string 2
    long **array = new long *[(len1 + 1)];      //2D dynamic array of size
    for(long i = 0; i < (len1 + 1); i++) {      //  (len1 + 1) * (len2 + 1)
        array[i] = new long[(len2 + 1)];        //the + 1 is for the null row/column
        for(long j = 0; j < (len2 + 1); j++) {
            array[i][j] = -1;
        }
    }

    std::cout << array[20][20] << "\n";

    //call and output the length of the LCS
    std::cout << "Length of LCS is: " << LCS(array, s1, s2, len1, len2) << "\n";

    std::cout << array[4][5] << "\n";

    //delete the array
    for(long i = 0; i < (len1 + 1); i++) {
        delete [] array[i];
    }
    delete [] array;

    return 0;
}


//LCS
long LCS(long **array, std::string s1, std::string s2, const long len1, const long len2) {
    for(long i = 0; i < len1 + 1; i++) {        //two for loops, create this graph by columns
        for(long j = 0; j < len2 + 1; j++) {
            //we are in the null row/column, so set to 0
            if(i == 0 || j == 0) {
                array[i][j] = 0;
            }
            //both s1[i-1] and s2[j-1] match, so we look diagonally up and to the left
            //  for that value, grab it and then add one to it. the offset - 1 for accessing the
            //  strings is taking into account of the null row/column e.g. if i = 1, then we are at
            //  the 1st character in that string, accessing it would be string[0]
            else if(s1[i-1] == s2[j-1]) {
                array[i][j] = array[i-1][j-1] + 1;
            }
            //we find no match so we pull the greatest value from to our left or above us
            else {
                array[i][j] = std::max(array[i-1][j], array[i][j-1]);
            }
        }
    }

    //the maximum length of the LCS is in the last position of the array so return that
    return array[len1][len2];
}
