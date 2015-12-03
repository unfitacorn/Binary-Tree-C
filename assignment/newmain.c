/* 
 * File:   newmain.c
 * Author: Robert
 *
 * Created on 28 November 2015, 15:19
 */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "newfile.h"

/*
 * 
 */
int main(int argc, char** argv) {
    char file[60];
    get_file(file);

    read_in(file);
    return (EXIT_SUCCESS);
}

void get_file(char *file) {
    DIR * current_directory_ptr;
    current_directory_ptr;
    struct dirent * next_entry_ptr;
    char to_open[60];

    current_directory_ptr = opendir(direct);

    printf("These are the files available:");
    while (next_entry_ptr != NULL) {

        printf("\n -- %s", next_entry_ptr->d_name);
        next_entry_ptr = readdir(current_directory_ptr);
    }
    strcpy(file, direct);
    printf("What file do you want?");
    scanf(" %s", to_open);


    strcat(file, to_open);

}

void read_in(char *file) {
    int ID_count = 1;
    char tempformat[60];
    float tempfloat = 0;
    FILE * fileloc = file;
    if (fopen(fileloc, "r") != NULL) {

        fileloc = fopen(fileloc, "r");
        

        fgets(location, 60, fileloc);
        fgets(date, 60, fileloc);
        int i;

        int set = 0;
        while (!set) {
            //http://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
            struct competitor* temps = malloc(sizeof (struct competitor));
            
             if (fgets(temps->name, 60, fileloc) == NULL){
                 break;
             }
            temps->name[strcspn(temps->name, "\r\n")] = 0;
            temps->ID = ID_count;
            ID_count++;

            fgets(temps->address, 60, fileloc);
            temps->address[strcspn(temps->address, "\r\n")] = 0;
            fgets(temps->phone, 60, fileloc);
            temps->phone[strcspn(temps->phone, "\r\n")] = 0;

            fgets(tempformat, 60, fileloc);
            convert_to_inches(tempformat);
            tempfloat = atof(tempformat);
            temps->cucumber = tempfloat;

            fgets(tempformat, 60, fileloc);
            convert_to_inches(tempformat);
            tempfloat = atof(tempformat);
            temps->carrot = tempfloat;

            fgets(tempformat, 60, fileloc);
            convert_to_inches(tempformat);
            tempfloat = atof(tempformat);
            temps->runner = tempfloat;


            //need to hold pointer to current.
            current = root;
            holdpointer = &current;

            insert(temps,&current);
            if (rootset == 1) {
                root = *holdpointer;
            }
            rootset = 1;
        }


    fclose(fileloc);
} else {
    printf("File  \"%s\" does not exist \n\n PROGRAM TERMINATING", fileloc);
}
}

void convert_to_inches(char *tempformat) {
    char split1[5];
    char split2[5];
    float splitfloat1 = 0;
    float splitfloat2 = 0;

    int i;

    split1[0] = tempformat[0];

    split2[0] = tempformat[2];
    for (i = 1; i < 4; i++) {
        if (tempformat[i + 2] != NULL && tempformat[i + 2] != '\r') {

            split2[i] = tempformat[i + 2];

        }
    }

    splitfloat1 = atof(split1);

    splitfloat2 = atof(split2);

    splitfloat1 = (splitfloat1 * feet_to_inches) + splitfloat2;

    sprintf(tempformat, "%f", splitfloat1);


}

void insert(struct competitor *node, struct competitor *cur) {
    if (root.ID == NULL) {
        new(node);
        root = *node;

    } else if ((node->carrot + node->cucumber + node->runner) < (cur->carrot + cur->cucumber + cur->runner)) {
        if (cur->left == NULL) {
            new(node);
            cur->left = node;
        } else {
//            cur = cur.left;
            insert(node, (cur->left));
        }

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

struct competitor new(struct competitor * node) {

    struct competitor *newnode = (struct competitor *) malloc(sizeof (struct competitor));
    newnode = node;
    newnode->left = newnode->right = NULL;
    return *newnode;
}