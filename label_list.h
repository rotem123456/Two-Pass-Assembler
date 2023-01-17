#ifndef LABEL_LIST_H
#define LABEL_LIST_H
#define MAX_ROW_SIZE 85
#define MAX_LABEL_SIZE 30
#define TRUE 1
#define FALSE 0
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "constants.h"
typedef struct label_node
{
	char name[MAX_LABEL_SIZE];
	unsigned int address;
	unsigned int data_type; /*data or code*/
	/* entry or extern or none*/
	struct label_node *next;
}label_node;

/*-----------------------------------*/
/*@function that inserts label to the label linked list*/
void insert_label(label_node **head,char name[], unsigned int address,unsigned int data_type);
/*-----------------------------------*/
/*creating a label list node*/
label_node *init_label();
/*-----------------------------------*/
/*@functuon for priting the keys of the given linked list*/
void print_node(label_node *head);
/*-----------------------------------*/
/*@function for searching if the given name is inside said linked list*/
/*@returning the label node if found and NULL if not found -O(N)*/
label_node *search_name(label_node *head,char name[]);
/*-----------------------------------*/
void update_label_list(label_node *label_head);
/*-----------------------------------*/
/*function for searching if given node is an entry */
label_node *search_name_entry(label_node *head,char name[]);

void delete_label_list(label_node **head);
#endif


