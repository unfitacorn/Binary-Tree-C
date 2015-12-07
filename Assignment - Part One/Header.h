/* 
 * File:   HEADER.h
 * Author: Robert
 *
 * Created on 28 November 2015, 15:19
 */

#ifndef HEADER_H
#define	HEADER_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* HEADER_H */




struct competitor{
    char name[79];
    char address[79];
    char phone[79];
    int ID;
    float cucumber;
    float carrot;
    float runner;
    struct competitor *left;
    struct competitor *right;
    
};

struct competitor root, current;
struct competitor *holdpointer;
int rootset = 0;
int exitset = 0;
char location[60];
char date[60];
struct competitor new(struct competitor *node);

#define direct ".//hortfiles/"
#define feet_to_inches 12