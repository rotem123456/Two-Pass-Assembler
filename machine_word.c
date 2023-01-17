#include "machine_word.h"
#include "extern.h"
#include "base_32.h"
/*
This c file contains function that encodes the given machine word based on its oppcode,src & dest opperands
and stores them in the code image linked list which is a union of the differant varitations of machine words that 
we can recieve:register,machine word(first word encoder) and machine number
*/
/*---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------*/
void insert_code_img(code_img **head,code_img *newer)
{
	if(*head==NULL)
		*head=newer;
	else
	{
		code_img *curr = *head;
		while(curr->next)
			curr = curr -> next;
		
		curr -> next =  newer;	
	}
}
/*---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------*/
code_img *encode_machine_word(code_img **head,int oppcode,int src,int dest) /*first word*/
{
	code_img *new=init_code_img();
	new->bits[0].word.oppcode = oppcode;
	new->bits[0].word.src =  src;
	new->bits[0].word.dest =  dest;
	if(src == -1)
			new->bits[0].word.src =  0;
	if(dest == -1)
			new->bits[0].word.dest =  0;
	insert_code_img(head,new);
	return new;
}
/*---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------*/
code_img *init_code_img()
{
	code_img *new = (code_img *)calloc(1,sizeof(code_img));
	if(!new)
	{
		perror("No memory");
		exit(1);
	}
	return new;
}
/*---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------*/
void encode_regr_field(code_img *current,int left, int right,int src)
{
	
	int place_in_bits;
	if(src == 1)
		place_in_bits = 1;
	else
		place_in_bits = get_place_in_bits(current->bits[0].word.src);
	
	if(right != -1)
		current -> bits[place_in_bits].reg.r_dest = right;
	
	if(left != -1)
		current -> bits[place_in_bits].reg.r_src = left;
	
	
	
}
/*---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------*/
void encode_address(code_img *current,unsigned int address,int number,int ARE, int src,char *label_name)
{

	int place_in_bits;
	if(src)/*in source, after 0*/
		place_in_bits = 1;
	else
		place_in_bits = get_place_in_bits(current -> bits[0].word.src);
	if(address == 0)
	{
		insert_label_extern(&extern_head,label_name,IC + place_in_bits);
	}
	if(address==-1)
		current -> bits[place_in_bits].number.address = number;
	else if(number==-1)
	{
		current -> bits[place_in_bits].number.address = address;
		current -> bits[place_in_bits].number.ARE = ARE;
	}
	else
	{
		current -> bits[place_in_bits].number.address = address;
		current -> bits[place_in_bits].number.ARE = ARE;

		current -> bits[place_in_bits+1].number.address = number;

	}
	
	
}
/*---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------*/
int get_place_in_bits(unsigned int src)
{
	int place_in_bits;
	/*if(src == address_resolution)
		place_in_bits = 1;*/

	if(src == access_to_listed)
		place_in_bits = 3;

	else
		place_in_bits = 2;

	return place_in_bits;
}
/*---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------*/
void encode_all_code(code_img **code_head , label_node *label_head , char command[], char src[],char dest[] ,char buffer[])
{
	
	int oppcode =  function_check(ops,command,NUM_OF_OPS);
	int src_address_resolution = param_type_getter(src);
	int dest_address_resolution = param_type_getter(dest);
	code_img *curr_img;
	if(!dest)         /*Here we check if the destination is NUll*/
	{
		dest = src;
		src = NULL;
		dest_address_resolution = src_address_resolution;
		src_address_resolution  = ERROR;
	}
	curr_img = encode_machine_word(code_head,oppcode,src_address_resolution,dest_address_resolution);
	/*SOURCE*/
	

	if(src != NULL){	
	if(src_address_resolution != regr && src_address_resolution != ERROR)
	{
		if(src_address_resolution == immediate)
			encode_address(curr_img,-1,atoi(src+1),0,1,src); /*encoding the address of the given number for immediate */
		
		else if(src_address_resolution == direct)
		{	
				encode_direct_src(curr_img,label_head,src,buffer); 
			
		}
		else if(src_address_resolution == access_to_listed)
		{
				encode_access_to_list_src(curr_img,label_head,src,buffer);
		}
	}
	else
		{
			if(dest_address_resolution == regr)
			{
				int reg_1 = atoi((src+1));
				int reg_2 = atoi((dest+1));
				encode_regr_field(curr_img,reg_1,reg_2,TRUE);
				return ;
			}
			else
				{
					int reg_1 = atoi(src+1);
					encode_regr_field(curr_img,reg_1,-1,TRUE);
				}
		}
	}

	if(dest){
	
	if(dest_address_resolution != regr && dest_address_resolution != ERROR)
	{
		if(dest_address_resolution == immediate)
		{
			if(src == NULL)
				encode_address(curr_img,-1,atoi(dest+1),0,TRUE,dest);
			else
				encode_address(curr_img,-1,atoi(dest+1),0,FALSE,dest);
		}
		else if(dest_address_resolution == direct)
		{
			encode_direct_dest(curr_img,label_head,dest,buffer);
		}
		else if(dest_address_resolution == access_to_listed)
		{	
			encode_access_to_list_dest(curr_img,label_head,dest,buffer,src);
		}
	}
	else
	{
		int reg_2 = atoi(dest+1);
		encode_regr_field(curr_img,-1,reg_2,FALSE);
	}
	}
/*---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------*/
}

FILE* print_code(code_img *head)
{
	FILE* code_file =  fopen("code.txt","w+");
	code_img *curr = head;
	int counter = 100;
	while(curr!=NULL)
	{
		int i =0;
		for(i=0;i<5;i++)
		{
			if(curr->bits[i].binary!=0)
			{
				char *base32counter = base32(counter);
				char *base32binary = base32(curr->bits[i].binary);
				fprintf(code_file,"%s\t %s\n",base32counter,base32binary);
				free(base32counter);
				free(base32binary);
				counter++;
			}
			
		}
		curr = curr -> next;
	}
	fseek(code_file,0,SEEK_SET);
	return code_file;
	
}
/*---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------*/
void encode_second(code_img *curr_img, label_node *label_head , char command[], char src[],char dest[])
{
	/*int oppcode =  function_check(ops,command,NUM_OF_OPS);*/
	int src_address_resolution = param_type_getter(src);
	int dest_address_resolution = param_type_getter(dest);
	if(!dest)
	{
		dest = src;
		src = NULL;
		dest_address_resolution = src_address_resolution;
		src_address_resolution  = ERROR;
	}
	if(src != NULL){
	if(src_address_resolution != regr && src_address_resolution != ERROR)
	{
		if(src_address_resolution == immediate)
		{
			encode_address(curr_img,-1,atoi(src+1),0,1,src); 
		}
		else if(src_address_resolution == direct)
		{
			encode_direct_second_src(curr_img,label_head,src);
		}
		else if(src_address_resolution == access_to_listed)
		{
			encode_access_to_list_second_src(curr_img,label_head,src);
		}
	}
	else
		{
			if(dest_address_resolution == regr)
			{
				int reg_1 = atoi((src+1));
				int reg_2 = atoi((dest+1));
				encode_regr_field(curr_img,reg_1,reg_2,TRUE);
				return ;
			}
			else
				{
					int reg_1 = atoi(src+1);
					encode_regr_field(curr_img,reg_1,-1,TRUE);
				}
		}
		}

	if(dest){
	
	if(dest_address_resolution != regr && dest_address_resolution != ERROR)
	{
		if(dest_address_resolution == immediate)
		{
		
			if(src == NULL)
				encode_address(curr_img,-1,atoi(dest+1),0,TRUE,dest);
			else
				encode_address(curr_img,-1,atoi(dest+1),0,FALSE,dest);
		}
		else if(dest_address_resolution == direct)
		{
			encode_direct_second_dest(curr_img,label_head,dest);

		}
		else if(dest_address_resolution == access_to_listed)
		{
			encode_access_to_list_second_dest(curr_img,label_head,src,dest);

		}
	}
	else
	{
		int reg_2 = atoi(dest+1);
		encode_regr_field(curr_img,-1,reg_2,FALSE);
	}
	}
}
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------*/
void encode_direct_src(code_img *curr_img,label_node *label_head,char src[],char buffer[])
{
	int address;
	ARE_type ARE = RELOCATABLE;
	label_node *curr_label = search_name(label_head,src);
	if(!curr_label)
	{
		strcpy(curr_img -> second_pass_line , buffer);
		return ; 
	}
	address = curr_label -> address;
	if(address == 0)
	    ARE = EXTERNAL;
	encode_address(curr_img,address,-1,ARE,TRUE,src);
}

void encode_access_to_list_src(code_img *curr_img,label_node *label_head,char src[],char buffer[])
{
	char *label_name = strtok(src,".");	
	int struct_member = atoi(strtok(NULL," \n\t")); 
	int j =  struct_member;
	int address;
	ARE_type ARE = RELOCATABLE;
	label_node *curr_label;
	if(j<1 || j>2)
	{
		printf("line %d: Struct |%s| out of bounds (ONLY NUMBERS 1 OR 2)\n",line_counter,label_name);
		first_pass_counter++;
	}
	curr_label = search_name(label_head,label_name);
	if(!curr_label)
	{
		strcpy(curr_img -> second_pass_line , buffer);
		return ; 
	}
	address = curr_label -> address;
	if(address == 0)
	    ARE = EXTERNAL;
	encode_address(curr_img,address,struct_member,ARE,TRUE,src);
}

void encode_direct_dest(code_img *curr_img,label_node *label_head,char dest[],char buffer[])
{
	int address;
	ARE_type ARE = RELOCATABLE;
	label_node *curr_label = search_name(label_head,dest);
	if(curr_label == NULL)
	{
		strcpy(curr_img -> second_pass_line,buffer);
		return ; 
	}
	address = curr_label -> address;
	if(address == 0)
	    ARE = EXTERNAL;
	encode_address(curr_img,address,-1,ARE,FALSE,dest);
}


void encode_access_to_list_dest(code_img *curr_img,label_node *label_head,char dest[],char buffer[],char src[])
{
	char *label_name = strtok(src,".");	
	int address;
	ARE_type ARE = RELOCATABLE;
	int struct_member = atoi(strtok(NULL," \n\t"));
	int j= struct_member;
	label_node *curr_label = search_name(label_head,label_name);
	if(j<1 || j>2)
	{
		printf("line %d: Struct |%s| out of bounds (ONLY NUMBERS 1 OR 2)\n",line_counter,label_name);
		first_pass_counter++;
	}
	if(!curr_label)
	{
		strcpy(curr_img -> second_pass_line , buffer);
		return ; 
	}
	address = curr_label -> address;
	if(address == 0)
	    ARE = EXTERNAL;
	encode_address(curr_img,address,struct_member,ARE,FALSE,dest);
	
}

void encode_direct_second_src(code_img *curr_img,label_node *label_head,char src[])
{
	int address;
	ARE_type ARE = RELOCATABLE;
	label_node *curr_label = search_name(label_head,src);
	if(!curr_label)
	{
		printf("line %d:Undefined label |%s|\n",line_counter,src);
		return ; 
	}
	address = curr_label -> address;
	if(address == 0)
	 ARE = EXTERNAL;
	encode_address(curr_img,address,-1,ARE,TRUE,src);
}

void encode_access_to_list_second_src(code_img *curr_img,label_node *label_head,char src[])
{
		char *label_name = strtok(src,".");	
		int struct_member = atoi(strtok(NULL," \n\t")); 
		int address;
		ARE_type ARE = RELOCATABLE;
		label_node *curr_label = search_name(label_head,label_name);
		if(!curr_label)
		{
			printf("line %d: Undefined struct (label: %s) in source opperand \n",line_counter,label_name);
			return ; 
		}
		address = curr_label -> address;
		if(address == 0)
		    ARE = EXTERNAL;
		encode_address(curr_img,address,struct_member,ARE,TRUE,src);
}

void encode_direct_second_dest(code_img *curr_img,label_node *label_head,char dest[])
{
	int address;
	ARE_type ARE = RELOCATABLE;
	label_node *curr_label = search_name(label_head,dest);
	if(curr_label == NULL)
	{
		printf("line %d: Undefined label in dest opperand\n",line_counter);
		return ; 
	}
	address = curr_label -> address;
	if(address == 0)
	    ARE = EXTERNAL;
	encode_address(curr_img,address,-1,ARE,FALSE,dest);
}
void encode_access_to_list_second_dest(code_img *curr_img,label_node *label_head,char src[],char dest[])
{
	char *label_name = strtok(src,".");	
	int address;
	ARE_type ARE = RELOCATABLE;
	int struct_member = atoi(strtok(NULL," \n\t"));
	label_node *curr_label = search_name(label_head,label_name);
	if(!curr_label)
	{
		printf("line %d:Undefined struct (label) in dest opperand\n",line_counter);
		return ; 
	}
	address = curr_label -> address;
	if(address == 0)
	    ARE = EXTERNAL;
	encode_address(curr_img,address,struct_member,ARE,FALSE,dest);
}

void delete_code_List(code_img *head)
{
	 code_img* next;
	 while(head != NULL)
	 {
	   next = head->next;
	   free(head);
	   head = next;
	}
}




