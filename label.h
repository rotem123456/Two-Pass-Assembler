#ifndef LABEL_H
#define LABEL_H
#define TRUE 1
#define FALSE 0
#include "label_list.h"
#define MAX_ROW_SIZE 85
#define MAX_LABEL_SIZE 30


/*@function for checking if the given word is label valid*/
/*@returns TRUE if true*/
int label_check(char word[]);
/*------------------------------------------------*/
/*------------------------------------------------*/
char* first_word_getter(char word[]);
/*------------------------------------------------*/
/*------------------------------------------------*/
/*@function that updates the lable list (adding the last Instruction Counter to the Data Counter)*/
void label_list_update(FILE* file , label_node **head);
/*------------------------------------------------*/
/*------------------------------------------------*/


#endif 
