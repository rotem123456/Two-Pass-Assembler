#ifndef FIRST_PASS_H
#define FIRST_PASS_H
#include "constants.h"
#include "data_image.h"
#include "machine_word.h"
#include "label.h"
#include "label_list.h"
#include "command_validator.h"
/*---------------------------------------------*/
/*FIRST PASS*/
void first_pass(FILE *file,label_node **label_head,data_image **data_head,code_img **code_head);
/*---------------------------------------------*/
/*Encapsulated function
which inserts the data type for a type 1 line*/
void type_1_line_data(char buffer[],label_node **label_head,data_image **data_head,code_img **code_head);
/*---------------------------------------------*/
/*---------------------------------------------*/
void type_2_handler(int oppcode,char buffer[],code_img **code_head,label_node **label_head);
/*---------------------------------------------*/
/*---------------------------------------------*/
/*Inserts Label with DC and encodes Data*/
void inserting_data(char *label,char *second_word,char *third_word,label_node **label_head,data_image **data_head);
/*---------------------------------------------*/
/*Inserts Label with DC and encodes Data*/
void code_enocde_with_lable(char buffer[],code_img **image_head,label_node **label_head);

void first_word_data_type(char *token,char buffer[],data_image **data_head);
#endif


