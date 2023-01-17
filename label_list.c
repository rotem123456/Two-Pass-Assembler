#include "label_list.h"

void insert_label(label_node **head,char name[], unsigned int address,unsigned int data_type)
{
	label_node *current=*head;
	name[strlen(name)-1] = 0;
	if(*head==NULL)
	{
		*head = init_label();
		current = *head;
	}
	else
	{
		
		while(current->next)
			current = current -> next;
		current->next = init_label();
		current = current -> next;
	}
	strcpy(current->name,name);
	current -> address = address;
	current -> data_type = data_type;

}

label_node *init_label()
{
	label_node *new = (label_node *)(malloc(sizeof(label_node)));
		if(!(new))
		{
			perror("ERROR");
			exit(1);
		}
	new->next=NULL;
	new->address=0;
	new->data_type=0;
	memset(new->name,0,MAX_LABEL_SIZE);
	return new;
	
}
void print_node(label_node *head)
{
	label_node *current = head;
	if(head==NULL)
		{
		printf("EMPTY");
		}
	else
		{
			while(current)
			{
				printf("%s,%d\n",current -> name,current -> data_type);
				current = current -> next;
			}	 
		}

}

label_node *search_name(label_node *head,char name[])
{
	label_node *current = head;
	if(head==NULL)
	{
		return NULL;
	}
	while(current)
		{
			if(strcmp(current->name,name)==0){
				return current;}
			current = current -> next;
		}

	return NULL;
	
}

void update_label_list(label_node *label_head)
{
	
	while(label_head)
	{
		if(label_head->data_type >= 21 && 
			label_head->data_type <= 23) 
		{
			label_head->address = label_head->address + IC;
		}
		label_head = label_head -> next;
	}
}



label_node *search_name_entry(label_node *head,char name[])
{
	label_node *current = head;
	if(head==NULL)
	{
		return NULL;
	}
	while(current)
		{
			if(strcmp(current->name,name)==0 && (current-> address != 0)){
				return current;}

			current = current -> next;
		}

	return NULL;
	
}



void delete_label_list(label_node **head)
{
    label_node* next;
    while(*head != NULL)
    {
        next = (*head)->next;
        free(*head);
        *head = next;
    }
    *head = NULL;
}















