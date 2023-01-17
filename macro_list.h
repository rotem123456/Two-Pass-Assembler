#ifndef LINKLIST_H
#define LINKLIST_H
#define MAX_ROW_SIZE 85
#define TRUE 1
#define FALSE 0
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
typedef struct macro_node
{
	char macro_name[MAX_ROW_SIZE];
	char* content;
	struct macro_node *next; 
} macro_node;

void insert_macro(macro_node **head,char* name, char* content);

macro_node *init_macro();

void print_node_macro(macro_node **head);

macro_node* search_name_macro(macro_node *head,char* name);

void delete_macro_List(macro_node** head);

#endif


