/* 
 * File:   header.h
 * Author: Robert
 *
 * Created on 11 November 2015, 21:42
 */

#ifndef HEADER_H
#define	HEADER_H

#ifdef	__cplusplus
extern "C" {
#endif

void print_menu();
void menu();
void read_in_user();    
struct competitor* comp[];
    
struct competitor{
    char name[60];
    char postal[60];
    char phone_number[15];
    int competitorID;
    int cucumber;
    int carrot;
    int runner;
};



#ifdef	__cplusplus
}
#endif

#endif	/* HEADER_H */

