#include "second_pass.h"

void second_pass(FILE *file,label_node **label_head,data_image **data_head,code_img **code_head)
{
	/*char buffer[MAX_ROW_SIZE];*/
	code_img *curr = *code_head;
	update_label_list(*label_head);
	while(curr!=NULL)
	{
		if(curr -> second_pass_line != NULL)
		{	
			char *sentence = curr -> second_pass_line;
			
			
			char *token = strtok(sentence, "\t\n ");
			char *cmd, *src, *dest;
			int  j;
			if(token==NULL)
			{
				curr = curr -> next;
				continue;
			}
			else
			{
				j = label_check(token);
				if(j!= FALSE && j!= ERROR)
				{
					token = strtok(NULL,"\t\n ");
				}
				cmd = token;
				src = strtok(NULL,",\n\t ");
				dest = strtok(NULL,"\n\t ");
			}
			
			encode_second(curr,*label_head , cmd, src,dest);

		}
		
		curr = curr -> next;
	}
	
}


void entry_print(label_node *head,char *name)
{
	label_node *curr = head;
	char *name_cpy = (char*)calloc(MAX_ROW_SIZE,sizeof(char));
	char g[] = ".ent";
	FILE* entry_file;
	strcpy(name_cpy,name);
	strncat(name_cpy,g,4);
	entry_file = fopen(name_cpy, "w");
	while(curr)
	{
		if(curr -> data_type == entry)
		{
			char *name = curr -> name;
 			 
			if(search_name_entry(curr,name)!=NULL)
			{
				char *address = base32(search_name_entry(curr,name)->address);
				fprintf(entry_file,"%s\t%s\n",name,address);
				free(address);
			}
		}
		curr = curr -> next;
	}
	free(name_cpy);
}
void extern_print(extern_node *head,char *name)
{
	extern_node *curr =  head;
	char *name_cpy = (char*)calloc(MAX_LABEL_SIZE,sizeof(char));
	char g[] = ".ext";
	FILE* extern_file;
	strcpy(name_cpy,name);
	strncat(name_cpy,g,4);
	extern_file = fopen(name_cpy,"w");
	while(curr)
	{
		char *name = curr -> name;
		char *address =  base32(curr->address);
		fprintf(extern_file,"%s\t%s\n",name,address);
		free(name);
		free(address);
		curr = curr -> next;
	}
	free(name_cpy);
}









