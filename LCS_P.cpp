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
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>
#include <omp.h>
#include <time.h>

using namespace std;

void create_array(int **array, const int len2, const int i);

//function declaration
//LCS
//takes in a dynamic 2d array, 2 strings received from the text files, and their
//  respective lengths
int LCS(int **array, string s1, string s2, const int len1, const int len2);

void work_row(int **array, string s1, string s2, const int len2, const int i);

//main
int main(int argc, char *argv[]) {
    //invalid amount of arguments
    if(argc != 3) {
        cout << "please supply two text files\n";
        return 0;
    }

    ifstream file;                     //file
    stringstream buffer1, buffer2;     //string buffers
    string s1, s2;                     //strings

    //open the first file, read into the buffer, and then convert to a string
    file.open(argv[1]);
    if(file.is_open()) {
        buffer1 << file.rdbuf();
        s1 = buffer1.str();
        file.close();
    }
    else {  //if file didn't open properly
        cout << "Invalid filename for 1st text file, exiting...";
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
        cout << "Invalid filename for 2nd text file, exiting...";
        return 0;
    }

    const int len1 = s1.length();        //length of string 1
    const int len2 = s2.length();        //length of string 2
    int **array = new int *[(len1 + 1)];      //2D dynamic array of size

    #pragma omp parallel
    {
        #pragma omp single
        for(int i = 0; i < (len1 + 1); i++) {      //  (len1 + 1) * (len2 + 1)
            #pragma omp task
            create_array(array, len2, i);
        }
    }

    double t0 = omp_get_wtime();
    //call and output the length of the LCS
    cout << "Length of LCS is: " << LCS(array, s1, s2, len1, len2) << "\n";
    double t = omp_get_wtime() - t0;
    cout << "Total time: " << t << "\n\n";

    //delete the array
    for(int i = 0; i < (len1 + 1); i++) {
        delete [] array[i];
    }
    delete [] array;

    return 0;
}

void create_array(int **array, const int len2, const int i) {
    array[i] = new int[(len2+1)];
    for(int j = 0; j < (len2 + 1); j++) {
        array[i][j] = -1;
    }
}


//LCS
int LCS(int **array, string s1, string s2, const int len1, const int len2) {
    #pragma omp parallel
    {
        #pragma omp single
        for(int i = 0; i < len1 + 1; i++) {        //two for loops, create this graph by columns
            array[i][0] = 0;
            #pragma omp task
            work_row(array, s1, s2, len2, i);
        }
    }
    
    //the maximum length of the LCS is in the last position of the array so return that
    return array[len1][len2];
}

void work_row(int **array, string s1, string s2, const int len2, const int i) {
    for(int j = 1; j < len2 + 1; j++) {
        if(i != 0) {
            if(array[i-1][j] == -1) {
                j--; //stall
            }
            else {
                if(j == 0) {
                    array[i][j] == 0;
                }
                else if(s1[i-1] == s2[j-1]) {
                    array[i][j] = array[i-1][j-1] + 1;
                }
                else {
                    array[i][j] = max(array[i-1][j], array[i][j-1]);
                }
           }
        }
	else {
	    array[i][j] = 0;
	}
    }
}
