
#include "label_list.h"
#include "constants.h"
#include "inputProcessing.h"
#define MAX_ROW_SIZE 85
#define MAX_LABEL_SIZE 30


/*here we check if this label is vald*/
int saved_word_checker(const char *arr[] , char *word, int arr_size)
{
	int i;
	for(i=0 ;i<arr_size;i++)
	{
		if(!strcmp(word,arr[i]))
		{
			return TRUE; 
		}
	}
	return FALSE;
}

int label_check(char *word)
{

	char c = word[strlen(word)-1];
	char d = word[0];
	if(c ==':')
	{
		if(isalpha(d)!=0)
			{
				if(!saved_word_checker(ops,word,NUM_OF_OPS)	
					&& !saved_word_checker(regs,word,NUM_OF_REG)
					&& !saved_word_checker(data,word,NUM_OF_DEFS))
						return TRUE;
			}
		else
			{
				return ERROR;
			}
	}
	return FALSE;
}
/*get the first word of a sentance*/

char* first_word_getter(char word[])
	{
		char *cpy_word = (char*)calloc(MAX_LABEL_SIZE,sizeof(char));
		char *token;
		strcpy(cpy_word,word);
		token =  strtok(cpy_word," \n");
		return token;
	
		
	}
char* second_word_gettr(char buffer[]) /*gets the second of the line*/
{
	char *cpy_word = (char*)calloc(MAX_LABEL_SIZE,sizeof(char));
	char *token2;
	strcpy(cpy_word,buffer);
	strtok(cpy_word," \n");
	token2 = strtok(NULL," \n");
	return token2;
}

char* copy_until_last_char(char word[])
{
	char* cpy_word= (char*)calloc(MAX_LABEL_SIZE,sizeof(char));
	int i;
	for(i=0;word[i]!=':';i++)
	{
		cpy_word[i]=word[i];
	}
	return cpy_word;
}
int data_type_checkr(char word[]) /*checks if struct/string/data*/
{
	if(strcmp(word,".data")==0)
		return data_types;
	if(strcmp(word,".string")==0)
		return string_type;
	if(strcmp(word,".struct")==0)
		return struct_type;
	return ERROR;
}
/*In this function we go over the file and insert labels+address into our linked list*/
void label_list_update(FILE* file , label_node **head)
{
	char buffer[MAX_ROW_SIZE];
	unsigned int address_cnt=100;
	int if_data;
	char *label_name;
	char *label_name_final;
	while(fgets(buffer,MAX_ROW_SIZE,file))
	{	
		label_name = first_word_getter(buffer);
		if(label_check(label_name)==TRUE)
			{
				if_data = data_type_checkr(second_word_gettr(buffer));
				label_name_final=copy_until_last_char(label_name);
				insert_label(head ,label_name_final , address_cnt,if_data);
				address_cnt++;
			}
		address_cnt++;
	}
}


























