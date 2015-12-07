/* 
 * File:   hort.c
 * VERSION : NETBEANS IDE 8.0.2
 * WRITTEN ON : WINDOWS 10
 * Created on 28 November 2015, 15:19
 */


#include <stdio.h>
#include <stdlib.h>
//use dirent.h to look in the directory when displaying what is in the directory
#include <dirent.h>
//use string.h to edit char arrays with functions such as strcat and strcpy
#include <string.h>
//use the header file that holds global variables and defined constants
#include "Header.h"

/*
 * main function that calls all the major functions one by one.
 */
int main(int argc, char** argv) {
    //declare variable to save the file name in
    char file[60];
    //call the function to get the file name from the user. ALL HORT FILES ARE TO BE SAVED IN THE HORTFILES PROJECT FOLDER
    get_file(file);
    //read in the data into a structured binary tree
    read_in(file);

    //if the file location is not there then terminate the program and skip the printing.
    if (!exitset) {
        //print all data
        printf("Competition : %10s\t Date: %10s", location, date);
        printf("        NAME        Competitor Number       Cucumber                Carrot              Runner Bean                Total");
        printf("\n==============================================================================================================================");
        print(&root);
    }
    //exit program
    return (EXIT_SUCCESS);
}

//function to print the contents of the file location and ask the user which file they want to use.
void get_file(char *file) {
   //set up variables needed to open the directory
    DIR * cur_dir;
    cur_dir;
    struct dirent * next;
    char to_open[60];
    //open the directory to look at
    cur_dir = opendir(direct);
    //list all the files available in the directory 
    printf("These are the files available:");
    while (next != NULL) {

        printf("\n -- %s", next->d_name);
        next = readdir(cur_dir);
    }
    //copy the correct directory into 'file' 
    strcpy(file, direct);
    printf("\nWhat file do you want?");
    scanf(" %s", to_open);

    //then concatenate the correct file onto the directory ready to be read.
    strcat(file, to_open);
    //close the directory
    closedir(cur_dir);

}
//function that will read in the data into structures
void read_in(char *file) {
    //count that will keep the ID number for each competitor
    int ID_count = 1;
    //tempformat holds the char array for each measurement and is then later converted to floats
    char tempformat[60];
    //tempfloat holds the float that has been converted before being saved into the structure
    float tempfloat = 0;
    //location of the file to be opened is declared
    FILE * fileloc = file;

    // if the file is not there the program will terminate otherwise it will carry on with the function
    if (fopen(fileloc, "r") != NULL) {
        //open the file for ready only
        fileloc = fopen(fileloc, "r");

        //use fgets to read in the location and date
        fgets(location, 60, fileloc);
        //fgets reads in the return and new line characters so these are removed.
        //USED THIS LINK TO REMOVE THE CHARACTERS : http://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
        date[strcspn(date, "\r\n")] = 0;

        fgets(date, 60, fileloc);
        location[strcspn(location, "\r\n")] = 0;
        
        
   
        //used to continuously loop through the file reading in data
        int set = 0;

        //reads in the file
        while (!set) {
            //memory allocate for temps
            struct competitor* temps = malloc(sizeof (struct competitor));
            //if the next line is empty then break the while loop and read in the name
            if (fgets(temps->name, 60, fileloc) == NULL) {
                break;
            }
            
            //remove the return and newline from the name and set the ID
            //ID is then increased for next competitor
            temps->name[strcspn(temps->name, "\r\n")] = 0;
            temps->ID = ID_count;
            ID_count++;
            
            //read in the address and phone and remove the return and new line characters
            fgets(temps->address, 60, fileloc);
            temps->address[strcspn(temps->address, "\r\n")] = 0;
            fgets(temps->phone, 60, fileloc);
            temps->phone[strcspn(temps->phone, "\r\n")] = 0;

            //read in measurement
            fgets(tempformat, 60, fileloc);
            //convert the measurement just to inches
            convert_to_inches(tempformat);
            //convert the char into a float
            tempfloat = atof(tempformat);
            //save into the struct 
            temps->cucumber = tempfloat;

            //repeat the above process three times 
            fgets(tempformat, 60, fileloc);
            convert_to_inches(tempformat);
            tempfloat = atof(tempformat);
            temps->carrot = tempfloat;

            fgets(tempformat, 60, fileloc);
            convert_to_inches(tempformat);
            tempfloat = atof(tempformat);
            temps->runner = tempfloat;


            //set current to the root so you can transverse down the tree from the top
            current = root;
            //hold the location of the root
            holdpointer = &current;
            //insert the new node into the tree starting from the top of the tree
            insert(temps, &current);
            //if the root has been set the set the root to the original position
            if (rootset == 1) {
                root = *holdpointer;
            }
            rootset = 1;
        }
        //close the file
        fclose(fileloc);
        //if file is not found then terminate
    } else {
        printf("File  \"%s\" does not exist \n\n PROGRAM TERMINATING", fileloc);
        exitset = 1;
    }
}
//convert the char measurements into floats to be stored in the structures
void convert_to_inches(char *tempformat) {
    //temp variables to store data
    char split1[5];
    char split2[5];
    float splitfloat1 = 0;
    float splitfloat2 = 0;

    int i;
    //save the first number into the temp variable. A vegetable or fruit is very unlikely to be over 9ft
    split1[0] = tempformat[0];

    //save the first inches into the char
    split2[0] = tempformat[2];
    //read in the rest if its not NULL or a /r character
    for (i = 1; i < 4; i++) {
        if (tempformat[i + 2] != NULL && tempformat[i + 2] != '\r') {

            split2[i] = tempformat[i + 2];

        }
    }
    //save both as floats
    splitfloat1 = atof(split1);

    splitfloat2 = atof(split2);
    //convert to inches and save 
    splitfloat1 = (splitfloat1 * feet_to_inches) + splitfloat2;
     //set temoforamt to splitfloat1
    sprintf(tempformat, "%f", splitfloat1);


}
//insert the node into the tree
void insert(struct competitor *node, struct competitor *cur) {
    //if the root of the tree is empty then set the root
    if (root.ID == NULL) {
        new(node);
        root = *node;
        //if the new node is less than the current node then go left or set the next node as the new node
    } else if ((node->carrot + node->cucumber + node->runner) < (cur->carrot + cur->cucumber + cur->runner)) {
        if (cur->left == NULL) {
            new(node);
            cur->left = node;
        } else {
            insert(node, (cur->left));
        }
    //if the new node is greater than or equal to the current node then go right or set the next node as the new node
    } else if ((node->carrot + node->cucumber + node->runner) >= (cur->carrot + cur->cucumber + cur->runner)) {
        if (cur->right == NULL) {
            new(node);
            cur->right = node;
        } else {
            //             current = current.right;
            insert(node, (cur->right));
        }
    }
}
//function to create the new node
struct competitor new(struct competitor * node) {
    //allocate memory for the new node
    struct competitor *newnode = (struct competitor *) malloc(sizeof (struct competitor));
    newnode = node;
    //set the left and right children to NULL
    newnode->left = newnode->right = NULL;
    return *newnode;
}
//print all the competitors 
//based off the print function from the case study produced by Dave Price
void print(struct competitor * node) {

    
    //go way left 
    if (node->left != NULL) {

        print(node->left);
    }
    //print the competitors using padding
    printf("\n %15s", node ->name);
    printf("%15d", node ->ID);
    //convert the inches to feet and inches including the total
    convert2format(&node->cucumber);
    convert2format(&node->carrot);
    convert2format(&node->runner);
    float total = node->cucumber + node->carrot + node->runner;
    convert2format(&total);


//go right
    if (node->right != NULL) {
        print(node->right);
    }
}

//convert just inches to inches and feet
void convert2format(float *length) {
    //temps to store the measurements
    int temp;
    float temp2;
    //calculate all the measurements
    temp = *length / 12;
    temp2 = *length - (temp * 12);
    //print measurements using padding
    printf("  %11dft  %4.1fin", temp, temp2);



}