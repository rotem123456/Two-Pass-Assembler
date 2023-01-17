#ifndef COMMAND_VALIDATOR_H
#define COMMAND_VALIDATOR_H
#include "inputProcessing.h"
#include "constants.h"
/*----------------------------------------------*/
/*@function that checks if opperands 0 to 4 are valid*/
/*@returns TRUE if yes and ERROR if no*/
int zero_to_four_check(int first_param_type, int second_param_type,int func_check);
/*----------------------------------------------*/
/*@function that checks if opperands 5 to 13 are valid*/
/*@returns TRUE if yes and ERROR if no*/
int five_to_thirteen_check(int first_param_type, int second_param_type,int func_check);
/*----------------------------------------------*/
/*----------------------------------------------*/
/*----------------------------------------------*/
int code_encode_checker(char buffer[]);
#endif
