#ifndef FINAL_MACRO_H
#define FINAL_MACRO_H
#include "macro_list.h"
#define MAX_MACRO_NAME_LENGTH 32
#define ADD_TO_LINE_LENGTH 2
#define MAX_WORDS_IN_MACRO 6
#define MAX_ROW_SIZE 85
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
/*function that removes the starting spaces from a given string*/
char* removestartSpacesFromStr(char *string);
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
/*function that obtains the name of the macro and the content of macro*/
int start_macro_test(FILE* file,macro_node **head);
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
/*function which checks if we are in a macro*/
int in_macro(char word[]);
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
/*function that checks if we are out of the macro*/
int out_macro(char word[]);
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
/*function that returns a pointer to a file without the macro*/
FILE *macroless_file(FILE* file);
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
/*function that returns a pointer to the final file with macros inserted*/
FILE *FINAL(FILE *file,macro_node *head);

#endif
