/* 
 * File:   Horticultural.c
 * Author: Robert
 *
 * Created on 11 November 2015, 21:30
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv) {
    menu();



    return (EXIT_SUCCESS);
}

void menu() {

    int choice;

    print_menu();


    do {

        printf("\nPlease enter a choice");
        scan_int(choice);
        printf("CHOICE = %d \n",choice);
        switch (choice) {

            case 1:
                printf("1.");
                break;
            case 2:
                printf("2.");
                break;
            case 3:
                printf("3.");
                break;
            default:
                printf("Invalid option");

        }
    } while (choice != 'Q');
    return;
}

void print_menu() {
    printf("print menu");
    return;
}

void read_in_user() {




}

int scan_int(int num) {
    //from http://stackoverflow.com/questions/4072190/check-if-input-is-integer-type-in-c
    
    char term;
    int valid = 0;
    do {
        if (scanf("%d%c", &num, &term) != 2 || term != '\n'){
            printf("failure\n");
            
        
        } else {
            printf("valid integer followed by enter key\n");
            valid = 1;
        }
    }while (!valid);
    return num;

}