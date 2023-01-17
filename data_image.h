#ifndef DATA_IMAGE_H
#define DATA_IMAGE_H 
#include "constants.h"
#include "inputProcessing.h"
#include "base_32.h"

typedef struct data_bit
{
    unsigned int data : 10;
		
}data_bit;

typedef struct data_image
{
	data_bit *image;
	unsigned int len;
	struct data_image *next;
		

}data_image;
 

/*------------------------------------------------*/
/*------------------------------------------------*/
/*@function that encodes the parameters of a given .string statement*/
/*the function first encodes the given string to ASCII */
void encode_string(data_image **head, char word[]);
/*------------------------------------------------*/
/*------------------------------------------------*/
/*@function that creates a data image node*/
data_image  *init_data_image();

/*------------------------------------------------*/
/*------------------------------------------------*/
/*@function that enocdes the given parameters of a given .data statement*/
void encode_data(data_image **head, int *arr,int len);
/*------------------------------------------------*/
/*@function that enocdes the given parameters of a given .struct statement*/
void encode_struct(data_image **head,int *data_part_of_struct,char string_part_of_struct[], int len);
/*------------------------------------------------*/
/*------------------------------------------------*/
/*@functuon that prints the encoded data to a file*/
/*@returns the given function*/
FILE* print_data(data_image *head,label_node *l_head);

void delete_machine_List(data_image **head);

#endif 






