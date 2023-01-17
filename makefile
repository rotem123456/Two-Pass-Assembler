CFLAGS = -ansi -Wall -pedantic
EXE_SRC=  label_list.o main.o constants.o data_image.o  label.o machine_word.o command_validator.o inputProcessing.o first_pass.o second_pass.o extern.o base_32.o Final_Macro.o macro_list.o
main : $(EXE_SRC)
	gcc -g $(CFLAGS) $(EXE_SRC) -o $@

%.o : %.c 
	gcc -c $^ $(CFLAGS) -o $@








clean:
	rm -rf *.o
