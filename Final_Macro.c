#include "Final_Macro.h"
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
char* removestartSpacesFromStr(char *string) {
    int i;
    int non_space_count = 0;
    for (i = 0; string[i] != '\0'; i++) {
        if (string[i] != ' ' && string[i] != '\t') {
            string[non_space_count] = string[i];
            non_space_count++;
        }
        if(isalpha(string[i]))
        {
            return string + i;
        }
    }
    string[non_space_count] = '\0';
	return string;
}
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
int start_macro_test(FILE* file,macro_node **head)
{		
	char buffer[MAX_ROW_SIZE];
	char* token;
	char name[MAX_ROW_SIZE];
	while(fgets(buffer,MAX_ROW_SIZE,file))
	{
		char* content = (char*) calloc(1,sizeof(char));
		token=strtok(buffer," ");
		if(strcmp(token,"macro")==0 )
		{
				strcpy(name,strtok(NULL,"\n"));
				while(fgets(buffer,MAX_ROW_SIZE,file))
				{	
					if(strcmp(buffer,"endmacro\n") == 0)
					{
						insert_macro(head,name,content);
						break;
					}
					else
					{
				
						content = realloc(content,strlen(buffer) + strlen(content));
						strcat(content,buffer);
					}
				}
			}	
	}
	fseek(file,0,SEEK_SET);
	
		return 0;
	}
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
int in_macro(char word[])
{
	char new_word[MAX_ROW_SIZE];
	char *token;
	strcpy(new_word,word);
	token = strtok(new_word," ");
	if(strcmp(token,"macro")==0)
		{ 
			return TRUE;
		}
	return FALSE;
}
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
int out_macro(char word[])
{
	if(strcmp(word,"endmacro\n")==0)
		{
			return TRUE;
		}
	return FALSE;
}
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
FILE *macroless_file(FILE* file)
{
	char buffer[MAX_ROW_SIZE];
	int copy = TRUE;
	FILE* new_file = fopen("no_macro.txt","w+");
	while(fgets(buffer,MAX_ROW_SIZE,file))
	{
		if(in_macro(buffer))
		{
			copy=FALSE;
		}
		if(out_macro(buffer))
		{
			copy = TRUE;
		}
		if(copy == TRUE)
		{
			if(!out_macro(buffer))
			{
				fprintf(new_file,"%s",buffer);
			}
		}

	}
	
	fseek(file,0,SEEK_SET);
	fseek(new_file,0,SEEK_SET);
	return new_file;
	
	
}
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
FILE *FINAL(FILE *file,macro_node *head)
{
	char buffer[MAX_ROW_SIZE];
	char word[MAX_ROW_SIZE];
	macro_node *current = head;
	macro_node *curr;
	FILE* final_file =  fopen("ps.txt","w+");
	while(fgets(buffer,MAX_ROW_SIZE,file))
	{
		strcpy(word,buffer);
		strtok(word," \t\n");
		if((curr = search_name_macro(current,word))!=NULL)
		{	
			fprintf(final_file,"%s",curr -> content);
		}
		else
		{	
			fprintf(final_file,"%s",buffer);
		}
	}
	fseek(file,0,SEEK_SET);
	fseek(final_file,0,SEEK_SET);
	remove("no_macro.txt");
	return final_file;
}







	                            

