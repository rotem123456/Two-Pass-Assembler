#include "first_pass.h"
/*First Pass
Param:
We receive the file from the PreProcessor -> file
label_head -> the head of the label linked list
data_head -> the head of the data head linked list
code_head -> the head of the code head linked list

The first pass itirates over the file and:
1.Encodes the machine word
2.Encodes the data segment of the given assembly code
3.updates the lable list
4.labels that have not been defined are stored in the machie word linked list and forwarded to the second pass where they wil be handled


type 1 line -> Line format that looks like this : lable: oppcode paramters
type 2 line -> Line format that looks like this : oppcode parameters
*/
void first_pass(FILE *file, label_node **label_head, data_image **data_head, code_img **code_head)
{
	char buffer[MAX_ROW_SIZE];
	char *label_z;
	char *label;
	char ch;
	while(fgets(buffer,MAX_ROW_SIZE,file))
	{	
		
		char *token = first_word_getter(buffer); 
		line_counter++;
		if(strlen(buffer)>LINE_LENGTH)
		{
			printf("line %d: exceeding max line length(80)\n",line_counter);
			first_pass_counter++;
		}
		if(token == NULL)
		    continue;
		if(entry_extern(token) != ERROR) /*Checking if the first word of the buffer is an entry or extern type - phase 8 of algorithm*/
		{
				if(entry_extern(token) == extrn) /*if it is an extern declartion*/
				{
					int space = 0;
					extern_counter++;
					label_z = param_getter_for_type_2(buffer);
					label = first_word_getter(label_z); /*obtaining the label*/
					
					ch =':';
					
					strncat(label,&ch,1);
					if(space_finder(label_z) == ERROR)
					{
						space++;
					}
					if(isalpha(label[0])>0 && third_word_getter(buffer)==NULL && space == 0)               /*Checking if the label is valid*/
					{
						insert_label(label_head,label,0,extrn); /*Inserting the label (entry or extern) to the linked label list*/
					}
					else
					{
						printf("line: %d: Invalid Label Declartion: %s\n",line_counter,label_z);  /*If we have an invalid label declartion */
						first_pass_counter ++;
						
					}
					
				}
				if(entry_extern(first_word_getter(buffer)) == entry)  /*if we have an entry declaration*/
				{
					int space = 0;
					entry_counter++;
					label_z = param_getter_for_type_2(buffer);
					if(space_finder(label_z) == ERROR)
					{
						space++;
					}
					label = first_word_getter(label_z);
					if(isalpha(label[0])>0 && third_word_getter(buffer) == NULL && space == 0)
					{
						ch =':';
					    strncat(label,&ch,1);
					    insert_label(label_head,label,0,entry); /*Inserting the label (entry or extern) to the linked label list*/
					}
					else
					{
						printf("line: %d: Invalid Label Declartion: %s\n",line_counter,label_z);  /*If we have an invalid label declartion */
						first_pass_counter ++;
						
					}
				}
				}
						
				if((data_type_checker(token)==data_types || data_type_checker(token)==string_type || data_type_checker(token)==struct_type)  && 						second_word_getter(buffer)!=NULL)
				{
					first_word_data_type(token,buffer,data_head);
					continue;
					
				}
				
		
		if(token[0] == ';')
		{

			continue;
		}
		if(line_type(buffer) == ERROR && entry_extern(first_word_getter(buffer))==ERROR)
		{
			printf("line %d: function |%s| undefined\n",line_counter,token);
		}
		else if(line_type(buffer) == type_1) /*Checking the line type*/
		{
			type_1_line_data(buffer,label_head,data_head,code_head); /*function description in head file*/ 
		}
		
		else if(line_type(buffer) == type_2) 
		{	
			int oppcodez = function_check(ops,token,NUM_OF_OPS);
			
			type_2_handler(oppcodez,buffer,code_head,label_head);
			
		}
		
		if(regr_error!=0)
		{
			printf("warning in line  %d: REGISTER OUT OF BOUNDS\n",regr_error);
			regr_error = 0;
		}
	}

}

/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/		

/*encapsulated function that handles data and code encoding*/

void type_1_line_data(char buffer[],label_node **label_head,data_image **data_head,code_img **image_head)
{
	
	char* label = first_word_getter(buffer); /*since we know its type one we know that the first word is a label*/
	
	char* second_word = second_word_getter(buffer); /*here we recieve the second word of the sentance*/
	
	
	if(data_type_checker(second_word) != command_line) 
	{	
			char* third_word = third_word_getter(buffer);
			
			inserting_data(label ,  second_word, third_word,  label_head, data_head); /*data encoder*/
	}	
	else if(function_check(ops,second_word,NUM_OF_OPS)!=ERROR) /*Command line from type LABEL oppcode source,dest:*/
	{
			code_enocde_with_lable(buffer,image_head,label_head); /*code encoder*/
	}
	else if(function_check(ops,second_word,NUM_OF_OPS)==ERROR)
	{
		printf("line %d: command |%s| is not defined\n",line_counter,second_word);
	}

}
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
void inserting_data(char *label,char *second_word,char *third_word,label_node **label_head,data_image **data_head) /*function that encodes data*/
{
	int data_type = data_type_checker(second_word); /*checking the type (immediate-0,direct-1,access to list-2,register-3)*/
	
 	char* is_valid_number =  num_checker(third_word); /*here we check if the .data syntax is correct*/
	int *numbers;
	int len;
	char *string;
	if(second_word_getter(third_word)!=NULL)
	{
		printf("line %d: Extraneous text after command\n",line_counter);
	}
	if(DC==0){DC++;}
	switch(data_type)
	{
		case data_types:
			{
			char *new_string = removeSpacesFromStr(third_word);
			int i;
			for(i=0;i<strlen(third_word);i++)
				{
					if(isalpha(third_word[i])!=0)
					{
						printf("line %d; a char was found in a .data declartion(FATAL ERROR)\n",line_counter);
						exit(1);
					}
				}
			if(is_valid_number != NULL && isdigit(new_string[strlen(new_string)-1])!=0 ) 
				{
					insert_label(label_head,label,DC,data_type); /*inserting the label with the Data Counter*/
					
					DC =  DC + comma_counter(is_valid_number) + 1; /*we update the Data COunter with the number of numbers in the given data type*/
					
					numbers = num_getter(third_word); /*we revieve a dynamically allocated list of numbers*/
					
					len = comma_counter(third_word) + 1; 
					
					encode_data(data_head,numbers,len); /*data encoder*/
				}
			else
				{
					printf("line %d: Invalid number syntax: %s\n",line_counter,is_valid_number);
				}
	    	break;
	    	}
		
		case string_type:
			{
				char *new_string = removeSpacesFromStr(third_word);
				if(new_string[strlen(new_string)-1]!='"')
				{
					printf("line %d: Invalid string syntax: %s\n",line_counter,third_word);
					first_pass_counter++;
				}
				/*check if valid*/
				if(string_check(third_word) != NULL && second_word_getter(third_word)==NULL) /*checking if .string type*/
				{
					insert_label(label_head,label,DC,data_type); /*inserting the label with the Data Counter*/
					
					DC = DC + strlen(third_word); /*we updated the Data Counter with the number of chars in the .string type*/

					encode_string(data_head,third_word+1); /*string encoder*/
				}
			}

			break;

		case struct_type: /*struct type*/
		{
			int commas =  comma_counter(third_word);
			char *new_string =  removeSpacesFromStr(third_word);
			if(isdigit(first_param_getter(third_word)) != TRUE && string_check(second_param_getter(third_word)) != NULL)
			{
				insert_label(label_head,label,DC,data_type);  /*inserting the label with the Data Counter*/
				
				DC = DC + strlen(second_param_getter(third_word)) + 1; /*updating the Data Counter*/
				
				numbers = num_getter(first_param_getter(third_word)); /*getting the number part of the struct*/
				
				string = string_check(second_param_getter(third_word)); /*checking if valid string*/
				
				encode_struct(data_head,numbers,string,1);
			}
			if(commas > 1 || new_string[strlen(new_string)-1]!='"')
			{
				printf("line %d: Invalid struct structure %s\n",line_counter,third_word);
				first_pass_counter++;
			}
			break;
	}
	}

}
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
void code_enocde_with_lable(char buffer[],code_img **image_head,label_node **label_head)
{
	char *first_word = first_word_getter(buffer);
	
	char *second_word = second_word_getter(buffer);
	
	int oppcode = function_check(ops,second_word,NUM_OF_OPS);
	
	int src,dest;
	
	
	if(label_check(first_word) == TRUE)
		{
		if(oppcode != ERROR)
		{
			if(code_encode_checker(buffer) == TRUE && third_word_getter(buffer)!=NULL && ((oppcode>=first_bound && oppcode<second_bound) 
			|| oppcode == third_bound )) /*checking the oppcode number*/ 
			{
				
				char* first_param = first_param_getter(third_word_getter(buffer));
				
				char* second_param = second_param_getter(third_word_getter(buffer)); /*if oppcode num beetwen 5 and 13*/
				
				if(first_param!= NULL && second_param!= NULL && comma_counter(second_param) == 0) 
				{
					src = param_type_getter(first_param);/*receiving the src type*/
				
					dest = param_type_getter(second_param);/*receiving the src type*/
				}
				else if(first_param == NULL || second_param == NULL || comma_counter(second_param)>0)
				{
					printf("line %d: Invalid amount of opperands\n",line_counter);
					first_pass_counter++;
				}
				
				encode_all_code(image_head,*label_head,second_word,first_param,second_param,buffer);/*function that encodes all the codes*/
				
				insert_label(label_head,first_word,IC,-1); /*inserting the label*/
			
				IC++;
				switch(src)
				{
					case regr || immediate || direct:
						IC = IC + 2; /*updating the Insturction Counter*/
						break;
					case access_to_listed:
						IC = IC + 3;
						break;
				}
				switch(dest)
				{
					case regr || immediate || direct:
						IC = IC + 2;
						break;
					case access_to_listed:
						IC = IC + 3;
						break;
				}	

				
			}
			else if(third_word_getter(buffer)!=NULL && (oppcode>=fourth_bound && oppcode<=fifth_bound))
			{
				char *param = third_word_getter(buffer); /*getting the third word of line*/
				
				int dest = param_type_getter(param); /*getting the opperand type of the dest opperand*/
				
				insert_label(label_head,first_word,IC,-1); /*inserting the first word as label,with the Instruction Counter, and -1 as the address*/
				
				encode_all_code(image_head,*label_head,second_word,NULL,param,buffer); /*encoding the given code*/
				
				IC++; /*Instruction Counter Updater*/
				
				switch(dest)
				{
					case regr || immediate || direct: /*Updating the Instruction Counter based on the given opperand type*/
						IC = IC + 2;
						break;
					case access_to_listed:
						IC = IC + 3;
						break;
				}	

			}
			else if(third_word_getter(buffer) == NULL && (function_check(ops,second_word,NUM_OF_OPS)== seventh_bound 
			|| function_check(ops,second_word,NUM_OF_OPS)== eigth_bound))
				{
					insert_label(label_head,first_word,IC,-1); /*inserting the first word as label,with the Instruction Counter, and -1 as the address*/
					
					encode_all_code(image_head,*label_head,second_word,NULL,NULL,buffer); /*encoding the given code*/
					
					IC = IC + 1; /*Instruction Counter Updater*/
				}
				
		}
		else if(oppcode == ERROR)
		{
			printf("line %d: oppcode |%s| not defined\n",line_counter,second_word);
		}
		
		
	}

}
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/
void type_2_handler(int oppcodez,char buffer[],code_img **code_head,label_node **label_head)
{
			
	char *oppcode;
	char *first_param;
	char *second_param;
	char* param;
	int first_param_type,second_param_type;
	char *token = first_word_getter(buffer); 
	if(oppcodez==ERROR)
	{
		printf("line %d: function |%s| not defined\n",line_counter,token);
	}
	if((oppcodez<second_bound && oppcodez>=first_bound) 
	|| 
	oppcodez==third_bound) /*checking the oppcode number of the given command */
	{
		oppcode =  token; 
		
		param = removeSpacesFromStr(param_getter_for_type_2(buffer)); /*opperands*/
		first_param = first_param_getter(param); /*first opperand*/
		
		second_param = second_param_getter(param); /*second opperand*/


		if(second_param==NULL || comma_counter(second_param)>0 || second_word_getter(param)!=NULL)
		{
			
			printf("line %d: Extraneous text after command\n",line_counter); 
		}
		
		first_param_type = param_type_getter(first_param); /*checking the type (immediate-0,direct-1,access to list-2,register-3)*/

		second_param_type = param_type_getter(second_param); /*checking the type (immediate-0,direct-1,access to list-2,register-3)*/

		if(code_encode_checker(buffer) == TRUE) /*code encode checker checks if the given buffer line is valid*/
		{

			encode_all_code(code_head, *label_head , oppcode , first_param , second_param , buffer );/*function that encodes*/
			IC++;
			switch(first_param_type) /*checking the first type of the parameters-immediate,direct,access to list,register*/
			{
				case direct || immediate || regr:
					IC = IC + 1; /*here we update the Instruction Counter (according to the "MION" type which we recieved*/
					break;
				case access_to_listed:
					IC = IC + 2;
					break;
			}
			switch(second_param_type)
			{
				case direct || immediate || regr:
					IC = IC + 1;
					break;
				case access_to_listed:
					IC = IC + 2;
					break;
			}
		}
	
		
	}

	else if(function_check(ops,first_word_getter(buffer),NUM_OF_OPS) <= fifth_bound  /*the oppcode beetwen 5 and 13 receive only one paramter(dest opperand)*/
	    && 
	    
	   function_check(ops,first_word_getter(buffer),NUM_OF_OPS) >= fourth_bound)
	{
		oppcode =  first_word_getter(buffer); /*checked if its type 2 line, so first word is oppcode*/
		
		param = param_getter_for_type_2(buffer); /*getting the parameter*/
		
		if(code_encode_checker(buffer) == TRUE) /*validating that the line is valid*/
		{
			
			int param_type = param_type_getter(first_word_getter(param)); /*checking the type (immediate-0,direct-1,access to list-2,register-3)*/

			encode_all_code(code_head,*label_head,oppcode,NULL,first_word_getter(param),buffer); /*encoding*/
			
			IC++;
			switch(param_type) 
			{
				case direct || immediate || regr:
					IC = IC + 1; /*here we update the Instruction Counter (according to the "mion" type which we recieved*/
					break;
				case access_to_listed:
					IC = IC + 2;
					break;
					
			}
		}

	}
	else if(function_check(ops,first_word_getter(buffer),NUM_OF_OPS) >= seventh_bound 
	&&
	function_check(ops,first_word_getter(buffer),NUM_OF_OPS) <= eigth_bound)
	{
		if(second_word_getter(buffer)!=NULL)
		{
			printf("line %d: extraneous ammount of parameters for oppde : %s\n",line_counter,first_word_getter(buffer));
			first_pass_counter++;
		}
		else
		{
			encode_all_code(code_head,*label_head,first_word_getter(buffer),NULL,NULL,buffer);
		}
	}	
	

}


void first_word_data_type(char *token,char buffer[],data_image **data_head)
{
	int type = data_type_checker(token);
		char *second_word = second_word_getter(buffer);
		switch(type)
		{
			case data_types:
				{
					char *new_string = removeSpacesFromStr(second_word);
					char* is_valid_number =  num_checker(new_string);
					int len;
					int *numbers;
					if(is_valid_number != NULL && isdigit(new_string[strlen(new_string)-1])!=0 && comma_validator(new_string)==0)
					{
						DC =  DC + comma_counter(is_valid_number) + 1; 
						numbers = num_getter(second_word); 
						len = comma_counter(second_word) + 1; 
						encode_data(data_head,numbers,len);
					}
					else
						{
							printf("line %d;Invalid Data synxtax,RECOMMENDATION: insert label before\n",line_counter);
							first_pass_counter++;
						}

					break;
				}
			case string_type:
				{
					char *new_string = removeSpacesFromStr(second_word);
					if(second_word[strlen(new_string)-1]!='"' )
					{
						printf("line %d: Invalid string syntax,RECOMMENDATION: insert label before\n",line_counter);
						first_pass_counter++;
					}
					if(string_check(second_word) != NULL && second_word_getter(second_word)==NULL)
						{
		
							DC = DC + strlen(second_word);

							encode_string(data_head,second_word+1);
						}
				break;
				}
			case struct_type:
			{
				int commas =  comma_counter(second_word);
				char *new_string =  removeSpacesFromStr(second_word);
				int *numbers;
				char *string;
				if(isdigit(first_param_getter(second_word)) != TRUE && string_check(second_param_getter(second_word)) != NULL)
				{
	
					DC = DC + strlen(second_param_getter(second_word)) + 1; 
	
					numbers = num_getter(first_param_getter(second_word)); 
	
					string = string_check(second_param_getter(second_word)); 
	
					encode_struct(data_head,numbers,string,1);
				}
				if(commas > 1 || new_string[strlen(new_string)-1]!='"')
				{
					printf("line %d: Invalid struct structure,RECOMMENDATION: insert label before\n",line_counter);
					first_pass_counter++;
				}
				break;
			}
				
		}	
}
















