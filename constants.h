#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define ERROR -1
#define LINE_LENGTH 80
#define type_1 100
#define type_2 200
#define immediate 0
#define direct 1
#define access_to_listed 2
#define regr 3
#define NUM_OF_OPS 16
#define NUM_OF_REG 8
#define NUM_OF_DEFS 4
#define first_bound 0
#define second_bound 4
#define third_bound 6
#define fourth_bound 5
#define fifth_bound 13
#define seventh_bound 14
#define eigth_bound 15
#define extrn 18
#define entry 19
#define data_types 21
#define string_type 22
#define struct_type 23
#define command_line 24
#define mov 0
#define cmp 1
#define add 2
#define sub 3
#define not 4
#define clr 5
#define lea 6
#define inc 7
#define dec 8
#define jmp 9
#define bne 10
#define get 11
#define prn 12
#define jsr 13
#define rts 14
#define hlt 15
extern const char *ops[NUM_OF_OPS];


extern int DC,IC,first_pass_counter,line_counter,regr_error,extern_counter,entry_counter;


extern const char *regs[NUM_OF_REG];

extern const char *data[NUM_OF_DEFS];

typedef enum ARE {ABSOLUTE  , EXTERNAL , RELOCATABLE} ARE_type; 

#endif


























