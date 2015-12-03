/* 
 * File:   newfile.h
 * Author: Robert
 *
 * Created on 28 November 2015, 15:19
 */

#ifndef NEWFILE_H
#define	NEWFILE_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* NEWFILE_H */




struct competitor{
    char name[60];
    char address[60];
    char phone[60];
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
char location[60];
char date[60];
struct competitor new(struct competitor *node);

#define direct ".//hortfiles/"
#define feet_to_inches 12