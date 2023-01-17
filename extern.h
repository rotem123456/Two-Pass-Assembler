#ifndef EXTERN_H
#define EXTERN_H
#define MAX_ROW_SIZE 85
#define MAX_LABEL_SIZE 30
#define TRUE 1
#define FALSE 0
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "constants.h"

typedef struct extern_node
{
	char name[MAX_LABEL_SIZE];
	unsigned int address;
	struct extern_node *next;
}extern_node;

/*-----------------------------------*/
/*-----------------------------------*/
/*@function that inserts an extern node to the linked list*/
void insert_label_extern(extern_node **head,char name[], unsigned int address);
/*-----------------------------------*/
/*@function that creates an extern node */
extern_node *init_extern();
/*-----------------------------------*/
/*@function that prints the extern node linked list*/
void print_node_extern(extern_node *head);
/*-----------------------------------*/
/*@function that checks the the extern node linked list and checks if the @parameter name is inside*/
/*@returns pointer to the pointer if the name is there and NULL if the name is not here*/
extern_node *search_name_extern(extern_node *head,char name[]);
/*-----------------------------------*/
/*-----------------------------------*/
extern extern_node *extern_head;

#endif
