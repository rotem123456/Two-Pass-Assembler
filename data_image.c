#include "data_image.h"
/*
this file containts functions that encode the given data 
and store them in a linked list
*/

data_image  *init_data_image()
{
	data_image *new = (data_image *)(malloc(sizeof(data_image))); /*allocating new memory for the new node*/
	if(!(new))
	{
		perror("ERROR");
		exit(1);
	}
	new->next=NULL;
	new -> image=NULL;
	return new;
	
}
void insert_to_data_image(data_image **head, data_image *new)
{
	data_image *current=*head;
    if(*head==NULL)  
	{
		*head = new;
	}
	else
	{
		while(current->next)
			current =  current -> next;
			
		current->next=new;
	}
}
void encode_string(data_image **head, char word[]) /*encodes into the data image*/
{
	int len,i;
	data_image *new;
	new=init_data_image();
	len=strlen(word);
	new -> image = (data_bit*)calloc(len+1,sizeof(data_bit));
	for(i=0;i<=len;i++)
	{
		new->image[i].data=word[i];
	}	
	new ->len = len+1;
	insert_to_data_image(head,new);
}

void encode_data(data_image **head, int *arr,int len)/*to use len we use func num of num getter*/
{
	int i;
	data_image *new;
	new=init_data_image();
	new -> image = (data_bit*)calloc(len+1,sizeof(data_bit));

	for(i=0;i<len;i++)
	{
		
		new->image[i].data=arr[i];
	}
	new ->len = len;
    insert_to_data_image(head,new);
    	

}


void encode_struct(data_image **head,int *data_part_of_struct,char string_part_of_struct[], int len)
{
	encode_data(head,data_part_of_struct,len);
	encode_string(head,string_part_of_struct);

}

FILE *print_data(data_image *head,label_node *l_head)
{
	data_image *curr = head;
	FILE* data_file =  fopen("data.txt","w+");
	int counter = IC + 1;
	while(curr)
	{
		int i = 0;
		int len =  curr -> len;
		while(i<len)
		{
			char *base32counter = base32(counter);
			char *base32binary = base32(curr->image[i].data);
			fprintf(data_file,"%s\t %s\n",base32counter,base32binary);
			counter++;
			i++;
			free(base32counter);
			free(base32binary);
		}
		curr = curr -> next;
	}
	fseek(data_file,0,SEEK_SET);
	return data_file;
}


void delete_machine_List(data_image **head)
{
	 data_image* next;
	 while(*head != NULL)
	 {
	   next = (*head)->next;
	   free(((*head)->image));
	   free(*head);
	   *head = next;
	}
	*head = NULL;
}















