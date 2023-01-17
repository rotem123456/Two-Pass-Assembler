#include "inputProcessing.h"

char* removeSpacesFromStr(char *string) { 
    int i;
    int non_space_count = 0;
    for (i = 0; string[i] != '\0'; i++) {
        if (string[i] != ' ' && string[i] != '\t') {
            string[non_space_count] = string[i];
            non_space_count++;
        }
    }
    string[non_space_count] = '\0';
	return string;
}

char* first_word_gettr(char buffer[]) 
	{
		char *cpy_word = (char*)calloc(MAX_LABEL_SIZE,sizeof(char));
		char *token;
		strcpy(cpy_word,buffer);
		token =  strtok(cpy_word," \n");
		return token;
	
		
	}

char* second_word_getter(char buffer[]) 
{
	char *cpy_word = (char*)calloc(MAX_LABEL_SIZE,sizeof(char));
	char *token2;
	strcpy(cpy_word,buffer);
	strtok(cpy_word," \n");
	token2 = strtok(NULL," \n");
	return token2;
}
char* third_word_getter(char buffer[]) 
{
	char *cpy_word = (char*)calloc(MAX_LABEL_SIZE,sizeof(char));
	char *token3;
	char *nospace;
	strcpy(cpy_word,buffer);
	strtok(cpy_word," \n\t");
	strtok(NULL," \n\t");
	token3 = strtok(NULL,"\n\t");
	if(token3!=NULL)
	{
		nospace=removeSpacesFromStr(token3);

		return nospace;
	}
	
	return NULL;
}	
int fourth_word_check(char buffer[])
{
	
	char *cpy_word = (char*)calloc(MAX_LABEL_SIZE,sizeof(char));
	char *token_4;
	strcpy(cpy_word,buffer);
	strtok(cpy_word," \n\t");
	strtok(NULL," \n\t");
	token_4 = strtok(NULL," \n\t,");
	if(token_4 != NULL)
	{
		return ERROR;
	} 
	return TRUE;
}

char* param_getter_for_type_2(char buffer[]) 
{
	char *cpy_word = (char*)calloc(MAX_LABEL_SIZE,sizeof(char));
	char *param;
	strcpy(cpy_word,buffer);
	strtok(cpy_word," ");
	param=strtok(NULL,"\n");
	return param;
}
char* first_param_getter(char word[]) 
{
	char *cpy_word = (char*)calloc(MAX_LABEL_SIZE,sizeof(char));
	char *token4;
	strcpy(cpy_word,word);
	token4 = strtok(cpy_word,",");
	return token4;
}

char* second_param_getter(char word[]) 
{
	char *cpy_word = (char*)calloc(MAX_LABEL_SIZE,sizeof(char));
	char *token5;
	strcpy(cpy_word,word);
	strtok(cpy_word,",");
	token5=strtok(NULL," \n");
	return token5;
}

int function_check(const char *arr[], char *word,int arr_size) 
{
	int i;
	for(i=0 ;i<arr_size;i++)
	{	
		if(strcmp(word,arr[i])==0)
		{
			return i;
		}
	}
	return ERROR;
	
}

int comma_counter(char buffer[]) 
{
	int i;
	int len=strlen(buffer);
	int comma_counter = 0;
	for(i=0;i<len;i++)
		{
			if(buffer[i]==',')
				comma_counter++;
		}
	return comma_counter;
}
int comma_validator(char buffer[])
{
	int i;
	int len = strlen(buffer);
	int comma_counter = 0;
	for(i=1;i<len;i++)
	{
		if(buffer[i-1] ==',' && buffer[i] ==',')
		{
			comma_counter++;
		}
	}
	return comma_counter;
}
int line_type(char buffer[]) 
{
	/*type 1 : first word is label -> guidance sentance
	  type 2 : instruction sentance*/
	if(label_check(first_word_getter(buffer))==TRUE)
		{
			
			return type_1;
		}
	if(function_check(ops,first_word_getter(buffer),NUM_OF_OPS) != ERROR )
		{
			return type_2;
		}
	else
		{
			return ERROR;
		}
}

int data_check(char *arr[],char *word,int arr_size) 
{
	int i;
	for(i=0 ;i<arr_size;i++)
	{
		if(strcmp(word,arr[i]))
		{
			return TRUE; 
		}
	}
	return FALSE;
}

char *num_checker(char word[]) /*checker for immieda*/
{	
	int len=strlen(word);
	int i;
	if(isdigit(word[len-1]))
	{
		for(i=0;i<len;i++)
			{
				if(word[i]==',' && word[i+1]==',')
				{
					return NULL;
				}
			}
		
	}
	
	
	return word;
}

int space_finder(char *word)
{
	int i;
	int len = strlen(word);
	for(i=0;i<len;i++)
	{
		if(word[i]==' ' && i != (len-1))
			{
				return ERROR;
			}
	}
	return TRUE;
}


int *num_getter(char *word) 
{
	int i=0;
	int *arr;
	char *token;
	char *cpy_word = (char*)calloc(MAX_LABEL_SIZE,sizeof(char));
	arr = (int *)malloc(sizeof(int));
	strcpy(cpy_word,word);
	token= strtok(cpy_word,",");
	while(token)
	{
		arr[i] = atoi(token);
		i++;
		arr=(int *)realloc(arr,(1+i)*sizeof(int));
		token=strtok(NULL,",");
	}
	return arr;
}

int num_of_num_getter(char word[]) 
{
	int i=0;
	char cpy_word[MAX_ROW_SIZE];
	char *token;
	strcpy(cpy_word,word);
	token = strtok(cpy_word,",");
	
	while(token)
	{
		i++;
		token=strtok(NULL,",");
	}
	return i;
	
}


int saved_word_checkerz(char *arr[] , char *word, int arr_size) 
{
	int i;
	for(i=0;i<arr_size;i++)
	{
		if(!strcmp(word,arr[i]))
		{
			return TRUE; 
		}
	}
	return FALSE;
}

int reg_checker(char *word) 
{
	int i;
	int counter = 0;
	if(word[0]=='r')
	{
		counter++;
		for(i=0;i<NUM_OF_REG;i++)
		{
			if(strcmp(word,regs[i])==0 && (atoi(word)>=0 && atoi(word)<=7))
			{
				counter++;
				return i;
			}
		}
	
	if(counter == 1)
	{
		regr_error = line_counter;
	}
	
	}
	return ERROR;	
}

int entry_extern(char *word) /*checks if entry or extern*/
{
	if(strcmp(word,".entry")==0)
		return entry;
	if(strcmp(word,".extern")==0)
		return extrn;
	return ERROR;
}

int data_type_checker(char *word) /*checks if struct/string/data, recievs second word*/
{
	if(strcmp(word,".data")==0)
		return data_types;
	if(strcmp(word,".string")==0)
		return string_type;
	if(strcmp(word,".struct")==0)
		return struct_type;
	return command_line;
}


char* string_check(char word[]) /*counts number of charcters in a STRING data base*/
{
	int i,len;
	len = strlen(word);
	if(word[0]=='\"' && word[len-1]=='\"')
	{
		for(i=0;i<len-1;i++)
			if(!isprint(word[i]))
				return NULL;
			
	}
	word[len-1]='\0';
	return word + 1;
}	

int struct_checker(char word[]) /*checks if current struct is valid*/
{
	int i;
	int len=strlen(word);
	int is_there_a_dot=FALSE;
	char *cpy_word;
	char *token;
	char ch = ':';
	cpy_word=(char *)malloc(sizeof(char)*strlen(word));
	strcpy(cpy_word,word);
	for(i=0;i<len;i++)
	{
		if(word[i]=='.')
		{
			is_there_a_dot=TRUE;
		}
	}
	if(is_there_a_dot == FALSE)
	{
		return ERROR;
	}
	if(is_there_a_dot==TRUE && (word[len-1]== '1' || word[len-1]=='2'))
	{
		token=strtok(cpy_word,".");
		strncat(token,&ch,1);
		if(label_check(token)==TRUE)
			{
				return access_to_listed;
			}
	}
	return FALSE;
}

int label_check_in_first_pass(char word[])
{
	char *cpy_word;
	char ch = ':';
	cpy_word=(char *)malloc(sizeof(char)*strlen(word));
	strncat(cpy_word,&ch,1);
	if(isalpha(word[0])==0);
	{
		return ERROR;
	}
	if(label_check(cpy_word)==TRUE)
	{
		return direct;
	}
	return ERROR;
	
}
int contains_a_dot(char word[])
{
	int i;
	int len =  strlen(word);
	for(i=0;i<len;i++)
	{
		if(word[i]=='.')
		{
			return TRUE;
		}
	}
	return FALSE;
}
int immediate_check(char word[])
{
	char *token;
	char *cpy_word;
	int len=strlen(word);
	int i;
	cpy_word=(char *)malloc(sizeof(char)*len);
	strcpy(cpy_word,word);
	if(word[0]=='#')
	{
		token=strtok(cpy_word,"#");
		for(i=0;i<strlen(token);i++)
		{
			if(!isdigit(token[i]) && token[i] != '-' && token[i] != ' ' )
			{
				return ERROR;
			}
		}
	}
	return immediate;	
}

int param_type_getter(char word[])/*recieves the first/second parameter and returns the address resolution*/
{
	if(!word)
		return ERROR;
	if(isalpha(word[0])==0 && word[0]!='#')
	{
		return ERROR;
	}
	if(word[0]=='#')
	{
		if(immediate_check(word)!=ERROR)
	{
		return immediate;
	}
	}
	if(word[0] == 'r' && reg_checker(word)!=ERROR)
	{
		return regr;
	}
	if(struct_checker(word)!=ERROR && contains_a_dot(word)==TRUE && regr_error == 0)
	{
		return access_to_listed;
	}
	if((label_check_in_first_pass(word)!=ERROR || label_check_in_first_pass(word)!=FALSE) && regr_error == 0 )
	{
		return direct;
	}

	return ERROR;
}










































