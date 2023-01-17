#ifndef MACHINE_WORD_H
#define MACHINE_WORD_H

#include "label_list.h"
#include "label.h"
#include "inputProcessing.h"
#include "constants.h"
#include "base_32.h"

/*------------------------------------------------*/
typedef struct machine_word
{
	unsigned int ARE : 2; 
	unsigned int dest : 2; 
	unsigned int src : 2; 
	unsigned int oppcode : 4;
}machine_word;
/*------------------------------------------------*/
typedef struct machine_number
{
	unsigned int ARE : 2;
	unsigned int address : 8;
}machine_number;
/*------------------------------------------------*/
typedef struct regr_field
{
	unsigned int ARE : 2;
	unsigned int r_dest : 4;
	unsigned int r_src : 4;
}regr_field;
/*------------------------------------------------*/
typedef struct code_img
{
	unsigned int address;
	char second_pass_line[MAX_ROW_SIZE];
	struct code_img *next; 
	union
	{
		unsigned int binary:10;
		machine_word  word;      
		machine_number number;
		regr_field reg;
	} bits[5];
} code_img;

/*Function for insreting a new code image node*/
void insert_code_img(code_img **head,code_img *newer);
/*------------------------------------------------*/
/*------------------------------------------------*/
/*@function that encodes all the code (register,direct,immediata and access to listed)*/
/*
@param
code_head -> head of the linked list for the code image
label_head -> head of the linked list for the label list
command -> the oppcode
src -> source opperand
dest-> destination opperand
buffer-> the whole line in the file
*/
void encode_all_code(code_img **code_head , label_node *label_head , char command[], char src[],char dest[] ,char buffer[]);
/*------------------------------------------------*/
/*------------------------------------------------*/
/*@function that encodes the first machine word*/
/*@returns a pointer to the machine word node*/
code_img *encode_machine_word(code_img **head,int oppcode,int src,int dest); 
/*------------------------------------------------*/
/*------------------------------------------------*/
/*@function that encodes the register field */
void encode_regr_field(code_img *current,int left, int right,int src); 
/*------------------------------------------------*/
/*------------------------------------------------*/
/*@function that enocdes the machine address*/
void encode_address(code_img *current,unsigned int address,int number,int ARE, int src,char *label_name); /*if its not a struct number gets -1,if its immediate address gets -1,if external address is 0*/
/*------------------------------------------------*/
/*------------------------------------------------*/
/*@function that gets the place in the unioned bit field*/
/*@returns the place in bits (int)*/
int get_place_in_bits(unsigned int src);
/*------------------------------------------------*/
/*------------------------------------------------*/
/*@Ffunction that creates the Node */
/*@returns a pointer to the creatednode*/
code_img *init_code_img();
/*------------------------------------------------*/
/*------------------------------------------------*/
/*@function that prints the code image to a file*/
/*@returns a pointer to that given file*/
FILE* print_code(code_img *head);
/*------------------------------------------------*/
/*------------------------------------------------*/
/*functon that encodes the code in the second pass*/
void encode_second(code_img *curr_img, label_node *label_head , char command[], char src[],char dest[]);

void encode_direct_src(code_img *curr_img,label_node *label_head,char src[],char buffer[]);

void encode_access_to_list_src(code_img *curr_img,label_node *label_head,char src[],char buffer[]);

void encode_direct_dest(code_img *curr_img,label_node *label_head,char dest[],char buffer[]);

void encode_access_to_list_dest(code_img *curr_img,label_node *label_head,char dest[],char buffer[],char src[]);

void encode_direct_second_src(code_img *curr_img,label_node *label_head,char src[]);

void encode_access_to_list_second_src(code_img *curr_img,label_node *label_head,char src[]);

void encode_direct_second_dest(code_img *curr_img,label_node *label_head,char dest[]);

void encode_access_to_list_second_dest(code_img *curr_img,label_node *label_head,char src[],char dest[]);

void delete_code_List(code_img *head);
#endif








