#ifndef INPUTPROCESSING_H
#define INPUTPROCESSING_H
#include "label.h"
/*--------------------------------------------------------------------*/
/*Param-Recieves string*/
/*Returns-string without spaces*/
char* removeSpacesFromStr(char *string);
/*--------------------------------------------------------------------*/
/*Param-Recieves line*/
/*Returns-the first word of line*/
char* first_word_gettr(char buffer[]); /*gets the first of the line*/
/*--------------------------------------------------------------------*/
/*Param-Recieves line*/
/*Returns-second word of line*/
char* second_word_getter(char buffer[]); /*gets the second of the line*/
/*--------------------------------------------------------------------*/
/*Param-Recieves line*/
/*Returns-third word of that line*/
char* third_word_getter(char buffer[]);/*gets the third of the line*/
/*--------------------------------------------------------------------*/
/*Param-Recieves line with out a label in the start*/
/*Returns-the parameters of that line*/
char* param_getter_for_type_2(char buffer[]);
/*--------------------------------------------------------------------*/
/*Param-Recieves 2 parameters*/
/*Returns-the first parameter*/
char* first_param_getter(char word[]); /*gets the first param of the parameter*/
/*--------------------------------------------------------------------*/
/*Param-Recieves 2 parameters*/
/*Returns-the second parameter*/
char* second_param_getter(char word[]); /*gets the second param of the parameter*/
/*--------------------------------------------------------------------*/
/*Param-Recieves arr of functions(ops),recieves function to be checkd,NUM_OF_OPS*/
/*Returns-i->place of said function in the arr or ERROR if its not defined*/
int function_check(const char *arr[], char *word,int arr_size); /*checks if function is defined*/
/*--------------------------------------------------------------------*/
/*Param-line*/
/*Returns-counts number of commas*/
int comma_counter(char buffer[]); /*counts the number of commas)**not so relevant*/
/*--------------------------------------------------------------------*/
/*Param-Recieves line*/
/*Returns-returns what type of line */
int line_type(char buffer[]); /*returns the line type*/
/*--------------------------------------------------------------------*/
/*Param-Recieves data arr(.data,.string,.struct),word to be checked,and size of said array*/
/*Returns-what type of data, and if its not data retrns ERROR*/
int data_check(char *arr[],char *word,int arr_size); /*checks if .data/.string/.struct*/
/*--------------------------------------------------------------------*/
/*Param-Recieves string*/
/*Returns-checks if numbers are valid and returns the number list without the #*/
char *num_checker(char word[]);/*recieves #1,2,3,checks if valid*/
/*--------------------------------------------------------------------*/
/*Param-Recieves of numbers with commas*/
/*Returns-dynamically allocated list of numbers*/
int *num_getter(char *word); 
/*--------------------------------------------------------------------*/
/*Param-Recieves list of numbers*/
/*Returns-the number of numbers in said list of numbers*/
int num_of_num_getter(char word[]);  /*returns the number of numbers in .data*/
/*--------------------------------------------------------------------*/
/*Param-Recieves string,checks if saved*/
/*Returns-TRUE if word is saved, and False if not*/
int saved_word_checkerz(char *arr[] , char *word, int arr_size); /*checks if saved word*/
/*--------------------------------------------------------------------*/
/*Param-Recieves string*/
/*Returns-checks if said string is a register*/
int reg_checker(char *word); /*checks if current register is valid*/
/*--------------------------------------------------------------------*/
/*Param-Recieves string*/
/*Returns-checks if said word is a entry or extern*/
int entry_extern(char *word); /*checks if entry or extern*/
/*--------------------------------------------------------------------*/
/*Param-Recieves string*/
/*Returns-returns what type of data type */
int data_type_checker(char *word); 
/*--------------------------------------------------------------------*/
/*Param-Recieves string*/
/*Returns-checks if string is valid and returns string witout the " "*/
char* string_check(char word[]); 
/*--------------------------------------------------------------------*/
/*Param-Recieves struct*/
/*Returns-checks if mion gisha le reshuma and if yes returns valid struct*/
int struct_checker(char word[]); /*checks if current struct is valid*/
/*--------------------------------------------------------------------*/
/*Param-Recieves word*/
/*Returns-checks if mion yashir or not and if yes returns DIRECT*/
int label_check_in_first_pass(char word[]);
/*--------------------------------------------------------------------*/
/*Param-Recieves word*/
/*Returns-checks if mion meyadi and returns immediate if yes*/
int immediate_check(char word[]);
/*--------------------------------------------------------------------*/
/*Param-Recieves word*/
/*Returns-returns what type of mion it is: mion meyadi:0, mion yasir:01,mion gisha lereshuma:10,mion register:11*/
int param_type_getter(char word[]);/*recieves the first/second parameter and returns the address resolution*/
/*--------------------------------------------------------------------*/
/*Param-Recieves word*/
/*Returns-returns true if the 4th word is NULL and false if the fourth word is not null*/
int fourth_word_check(char buffer[]);
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*Param_Recieves a word*/
/*Checks if the wor contains a dot*/
int contains_a_dot(char word[]);
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*Checks if has comma after comma*/
int comma_validator(char buffer[]);
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*Checks if string contains a space*/
int space_finder(char *word);
#endif 









































