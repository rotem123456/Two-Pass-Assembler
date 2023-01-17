
#include "command_validator.h"
/*file that contains function to check the validation of said line
the validation process is done by:
1.Checking if the number of opperands fits the given oppcode
2.Cheking if the opperand type matches the given oppcode


type 1 line : lable: oppcode opperands
type 2 line : oppcode opperands




*/
int zero_to_four_check(int first_param_type, int second_param_type,int func_check);
int five_to_thirteen_check(int first_param_type, int second_param_type,int func_check);
int code_encode_checker(char buffer[])
{
	char* first_word=first_word_gettr(buffer);

	char* second_word=second_word_getter(buffer);



	if(line_type(buffer) == type_1)/*checks if line of type: function parameters, example : LABEL: opp_code opperand_1,opperand_2*/
	{
		int oppcode = function_check(ops,second_word,NUM_OF_OPS); /**/
		if(oppcode == ERROR)
		{
			printf("line %d: function %s is not defined\n",line_counter,second_word);
		}
		
		if((oppcode>=first_bound && oppcode<second_bound) || oppcode==third_bound ) /*mov,cmp,add,sub,lea*/
		/*first check is how many parameters*/
		{
			if(third_word_getter(buffer) != NULL /*first check is how many parameters*/
			 && (first_param_getter(third_word_getter(buffer)) != NULL)
			 && second_param_getter(third_word_getter(buffer))!=NULL) 
			{
				/*now we check the opperand type*/
				int first_param_type = param_type_getter(third_word_getter(buffer)); /*here we check the type of the first opperand: 0,1,2,3*/
				
				int second_param_type = param_type_getter(third_word_getter(buffer)); /*here we check the type of the second opperand: 0,1,2,3*/
				
				if(zero_to_four_check(first_param_type,second_param_type,oppcode)==ERROR) /*function checks if opperand type are legal*/
				{
					printf("line %d: Invalid opperand type\n",line_counter);
					return FALSE;
				}
				else
					return TRUE;

			}		
			else
				{
				printf("line %d: Not enough parameters\n",line_counter);
				return FALSE;
				}

		}

		if((oppcode>=fourth_bound && oppcode<=fifth_bound) || oppcode==second_bound) /*clr,"not","dec", "jmp","bne", "get", "prn", "jsr","rts"*/
		{
			int first_param_type = param_type_getter(third_word_getter(buffer)); /*getting the first opperand type :0,1,2,3*/
			
			int second_param_type = param_type_getter(third_word_getter(buffer)); /*getting the second opperand type :0,1,2,3*/
			
			if(second_param_getter(third_word_getter(buffer)) != NULL)
			{
				printf("line %d: To Many parameters for given oppcode: %s\n",line_counter,second_word);
				return FALSE;
			}
			else
				{	
					if(five_to_thirteen_check(first_param_type,second_param_type,oppcode)==ERROR)
					{
						printf("line %d: Invalid opperand type\n",line_counter);
						return FALSE;
					}
					else
						return TRUE;
				}
					

		}
		if(oppcode>=rts && oppcode<=hlt) /*rts,hlt*/
		{
			if(third_word_getter(buffer) != NULL) /*checking number of parameters*/
				{
					printf("line %d: Too Many parameters for rts/hlt command\n",line_counter);
					return FALSE;
				}
			else
				{
					return TRUE;
				}
		}

	}
	if(line_type(buffer) == type_2)
	{
		char* first_parameter;
		char* second_parameter;
		int oppcode = function_check(ops,first_word,NUM_OF_OPS);
		if((oppcode >= first_bound && oppcode < second_bound) || oppcode == third_bound) 
		{
		first_parameter = first_param_getter(param_getter_for_type_2(buffer)); /*getting the first opperand*/
		
		second_parameter = second_param_getter(param_getter_for_type_2(buffer));/*getting the second opperand*/
		
			if(second_parameter != NULL && first_parameter != NULL) /*checking if the number of opperands is correct*/
				{
					int first_param_type  = param_type_getter(first_parameter); /*getting the first opperand type :0,1,2,3*/
					
					int second_param_type = param_type_getter(second_parameter); /*getting the second opperand type: 0,1,2,3*/
					
					if(zero_to_four_check(first_param_type,second_param_type,oppcode) == ERROR )
						{
							printf("line %d: Invalid opperand type for given opperand\n",line_counter);
							return FALSE;							
						}
					else
						return TRUE;
				
				}
				else
					{
						printf("line %d: Not enough parameters\n",line_counter);
						return FALSE;						
					}
		}
		
	if((oppcode >= fourth_bound && oppcode <= fifth_bound) || oppcode == second_bound) /*clr,"not","dec", "jmp","bne", "get", "prn", "jsr","rts"*/
	{
		first_parameter = first_param_getter(param_getter_for_type_2(buffer));/*getting the first opperand*/
		
		second_parameter = second_param_getter(param_getter_for_type_2(buffer));/*getting the second opperand*/
		
		if(second_parameter != NULL)
			{
				printf("line %d:Invalid amount of paramters given oppcode\n",line_counter);
				return FALSE;
			}
		else
			{
				int first_param_type = param_type_getter(first_parameter); /*getting the first opperand type :0,1,2,3*/
				
				int second_param_type = param_type_getter(second_parameter);/*getting the second opperand type :0,1,2,3*/
				
				
				if(five_to_thirteen_check(first_param_type,second_param_type,oppcode)==ERROR)
				{
					printf("line %d: Invalid opperand type\n",line_counter);
					return FALSE;
				}
				else
					return TRUE;
			}
	}
	if(oppcode== rts || oppcode == hlt) /*rts,hlt*/
	{
		if(third_word_getter(buffer)!=NULL) /*checking number of parameters*/
		{
			printf("Too many parameters for function of type hlt/rts");
		}
		else
			return TRUE;
	}


	}
		

return 111;}
/*function description in header filer */
int zero_to_four_check(int first_param_type, int second_param_type,int func_check)
{ 
	if(func_check==mov || func_check==add || func_check==sub) /*mov,add,sub*/
		if(((first_param_type == direct) ||     /*addressing mode direct*/
		  (first_param_type == access_to_listed ) ||  /*addressing access to listed*/
		  (first_param_type == immediate) || /*addressing mode immediate*/
		  (first_param_type == regr)) /*addressing mode REGISTER*/
		  &&
			((second_param_type == direct) || /*addressing mode direct*/
			 (second_param_type == regr) ||  /*addressing mode REGISTER*/
			 (second_param_type == access_to_listed))) /*addressing mode access_to_listed*/
			return TRUE;

	if((func_check==lea)) /*lea*/
			{
			if(((first_param_type == direct) || /*addressing mode direct*/
			 (first_param_type == access_to_listed )) /*addressing mode access_to_listed*/
				&& 
				((second_param_type == direct) || /*addressing mode direct*/
				(second_param_type == regr) || /*addressing mode REGISTER*/
				(second_param_type == access_to_listed))) /*addressing mode access_to_listed*/
				return TRUE;
			}
	if((func_check ==cmp)) /*cmp*/
			{
				if(((first_param_type == direct) || /*addressing mode direct*/
				 (first_param_type == access_to_listed ) || /*addressing mode access_to_listed*/
				 (first_param_type == immediate) || /*addressing mode immediate*/
				 (first_param_type == regr)) /*addressing mode REGISTER*/
				 && 
				((second_param_type == direct) || /*addressing mode direct*/
				 (second_param_type == regr) || /*addressing mode REGISTER*/
				 (second_param_type == access_to_listed) || /*addressing mode access_to_listed*/
				 (second_param_type == immediate)))  /*addressing mode immediate*/
					return TRUE;
			}
	
	
				
	return ERROR;
}


int five_to_thirteen_check(int first_param_type, int second_param_type,int func_check)
{
	if((func_check>=clr && func_check!=prn && func_check<=jsr) || func_check == not) /*not,clr,inc,dec,jump,bne,get,jsr*/
	{
		
		if((first_param_type == direct) || /*addressing mode direct*/
		 (first_param_type == regr)  ||  /*addressing mode REGISTER*/
		 (first_param_type == access_to_listed )) /*addressing mode access_to_listed*/
			return TRUE;
	}
	else if(func_check == prn ) /*prn*/
	{
	
		if((first_param_type == direct) ||  /*addressing mode direct*/
		(first_param_type == regr)  ||  /*addressing mode REGISTER*/
		(first_param_type == access_to_listed ) || /*addressing mode access_to_listed*/
		(first_param_type == immediate)) /*addressing mode immediate*/
			return TRUE;
	}
	return ERROR;
}













