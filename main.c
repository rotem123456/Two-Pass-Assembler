#include "Final_Macro.h"
#include "macro_list.h"
#include "machine_word.h"
#include "command_validator.h"
#include "inputProcessing.h"
#include "data_image.h"
#include "first_pass.h"
#include "label_list.h"
#include "second_pass.h"
#include "extern.h"
#include "base_32.h"

/*Written By Rotem Tal*/ 
int main(int argc, char* argv[])
{	

	
	int i = 1;
	while(i<argc)
	{
		char *name = (char*)calloc(MAX_LABEL_SIZE,sizeof(char));
		char *name_print = (char*)calloc(MAX_LABEL_SIZE,sizeof(char));
		char c;
		char g[]=".ob";
		char ending[] =".as";
		
		
		code_img   *code_head  = NULL;
		data_image *data_head  = NULL;
		label_node *label_head = NULL;
		macro_node *macro_head = NULL;
	
		FILE* file;
		FILE* step_2_file;
		FILE* code_ptr;
		FILE* data_ptr;
		FILE* fp3;
		/*---------------------------------------------------*/
		strcpy(name,argv[i]);
		strcpy(name_print,argv[i]);
		strncat(name,g,3);
		strncat(argv[i],ending,3);
		/*Handling the file name*/
		/*---------------------------------------------------*/
		fp3 = fopen(name, "w"); 
	
		file = fopen(argv[i],"r");
		if(file==NULL)
		{
			perror("ERROR");
			exit(1);
		}
		else
		{
			/*PRE ASSEMBLER*/
			FILE* no_macro = macroless_file(file); /*returns file with no macro*/
			start_macro_test(file,&macro_head); /*appends all macro contents to a macro linked list*/
			step_2_file = FINAL(no_macro,macro_head); /*returns a pointer to the final version with the macro contents appended*/
			
			first_pass(step_2_file,&label_head,&data_head,&code_head);/*FIRST PASS*/
	
			if(first_pass_counter==0) /*If no errors where found in the first pass the encoding continues*/
			{
				second_pass(step_2_file,&label_head,&data_head,&code_head); /*SECOND PASS*/
				code_ptr = print_code(code_head);
				data_ptr = print_data(data_head,label_head);
				while ((c = fgetc(code_ptr)) != EOF)
				  fputc(c, fp3);
			  

			   while ((c = fgetc(data_ptr)) != EOF)
				  fputc(c, fp3);
	
				fclose(fp3);
				remove("code.txt");
				remove("data.txt");
				if(entry_counter>0) /*entry files files*/
					entry_print(label_head,name_print); 
				if(extern_counter>0) /*extern files*/
					extern_print(extern_head,name_print);
			}
			
	
		    delete_macro_List(&macro_head);
		    i++;
		}
	    free(name);
	    free(name_print);
	    remove("no_macro_txt");
	    remove("ps.txt");
	    
	    delete_label_list(&label_head);
	    delete_machine_List(&data_head);
	    delete_code_List(code_head);
	}
	
	return 0;
}













