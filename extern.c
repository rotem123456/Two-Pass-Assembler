#include "extern.h"
/*
file that contains functions that create and store an extern node 
*/
extern_node *extern_head =  NULL;
void insert_label_extern(extern_node **head,char name[], unsigned int address)
{
	extern_node *current=*head;

	/*printf("%s\n",name);*/
	if(*head==NULL)
	{
		*head = init_extern();
		current = *head;
	}
	else
	{
		while(current->next)
			current = current -> next;
		current->next = init_extern();
		current = current -> next;
	}
	strcpy(current->name,name);

	/*current->address=address;*/
	/*strcpy(current->address,address);*/
	current -> address = address;

}

extern_node *init_extern()
{
	extern_node *new = (extern_node *)(malloc(sizeof(extern_node)));
		if(!(new))
		{
			perror("ERROR");
			exit(1);
		}
	new->next=NULL;
	new->address=0;
	memset(new->name,0,MAX_LABEL_SIZE);
	return new;
	
}
void print_node_extern(extern_node *head)
{
	extern_node *current = head;
	if(head==NULL)
		{
		printf("EMPTY");
		}
	else
		{
			while(current)
			{
				printf("NAME: %s\t ADDRESS: %d\n ",current -> name,current -> address);
				current = current -> next;
			}	 
		}

}

extern_node *search_name_extern(extern_node *head,char name[])
{
	extern_node *current = head;
	if(head==NULL)
	{
		return NULL;
	}
	while(current)
		{
			/*printf("%s\n",current->name);*/
			if(strcmp(current->name,name)==0){
				return current;}
			/*else
				printf("name: %s\t label name;%s\n",name,current -> name);*/
			current = current -> next;
		}

	return NULL;
	
}







