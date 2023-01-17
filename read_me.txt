HI!
This project was written by Rotem Tal(316163054) for course 20465
The project is a two pass assembler in C language.
A Two Pass Assembler As the name suggests two pass assembler does two passes over the source file. In first pass, all it does is looks for label definitions and introduces them in the symbol table (a dynamic table which includes the label name and address for each label in the source program). In the second pass, after the symbol table is complete, it does the actual assembly by translating the operations into machine codes and so on
The given machine code is a 32 bit langauge that the assembly code is encoded to
!,@,#,$,%,^,&,*,<,>,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v

A wrote this project in the span of two and half months while working on it intensively and in the process learned alot about the C langauge and about how to code correctly while using large amount of files.

The main program is the progam which runs the given assembler

first step-> The file goes through the pre assembler, the pre assembler searches for macros and stores them in the macro linked list.
After all of the macros are stored in the macro list, the files is read again and where ever there is a macro decleartion the pre assembler appends the given macro contentns in the file whilst returning a file pointer to the newly apended macroless file

second step->The macroless file goes through the first pass, where all the lables are appened to a linked list symbol table,every declaread address is then encoded, data declarations are also encoded

third step->The macroless file goes through the second pass, where all the addresses are then encoded and a file whith the translated code is then printed

My assembler handles syntax and logical errors (The error example file demonstrates this)

short explanation about what each file does:
base_32------> contains functions that translate the given decimal code to our new base
command_valdator------>contains function that check the logic validation of each line buffer
constants------>contains constants (no magic numbers)
data_image------>contatins functions that encode a data declartion(data is a linked list)
extern.c------> contains functions that handle .extern files
Final_Macro------>contains functions that handle macro(pre assembler phase)
first_pass------>contains functions that handle the first pass(encode and store labels)
label------>contains functions that handle lable
label_list------>linked list for storing labels
machine_word------>contains file that encode machine code
macro_list------>linked list for storing macros
main------>our main file (run progam as ./main text_file_name
second_pass------>contains functions that handle the second pass










