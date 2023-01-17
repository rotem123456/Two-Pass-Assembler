#include "macro_list.h"

void insert_macro(macro_node **head,char* name, char* content)
{
	macro_node *current=*head;
	if(*head==NULL)
	{
		*head = init_macro();
		current = *head;
	}
	else
	{
		while(current->next)
			current = current -> next;
		current->next = init_macro();
		current = current -> next;
	}
	strcpy(current->macro_name,name);
	current->content=content;


}

macro_node *init_macro()
{
	macro_node *new = (macro_node *)(malloc(sizeof(macro_node)));
		if(!(new))
		{
			perror("ERROR");
			exit(1);
		}
	new->next=NULL;
	new->content=NULL;
	memset(new->macro_name,0,MAX_ROW_SIZE);
	return new;
	
}
void print_node_macro(macro_node **head)
{
	macro_node *current=*head;
	if(*head==NULL)
		{
		printf("EMPTY");
		}
	else
		{
			while(current)
			{
				printf("%s\n",current->macro_name);
				current = current -> next;
			}	 
		}

}

macro_node* search_name_macro(macro_node *head,char* name)
{
	macro_node *current = head;
	while(current)
		{
			/*printf("%s\n",current->macro_name);*/
			if(strcmp(current->macro_name,name)==0){
				return current;}
			current = current -> next;
		}
	return NULL;
	
}

void delete_macro_List(macro_node** head)
{  
  macro_node* current = *head;
  macro_node* next;
  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
  *head = NULL;
}





































		
