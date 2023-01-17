# Two-Pass-Assembler
This project is a two pass assembler written in C.

What is a two pass assembler?
A two-pass assembler is a type of assembler that processes assembly language source code in two passes

What happens in the first pass?
In the first pass, the assembler reads through the source code and generates a symbol table, which maps symbol names (such as labels) to memory locations.

What happens in the second pass?
In the second pass, the assembler uses the symbol table to generate machine code, replacing symbolic addresses with their corresponding memory locations.

Why is this usefull?
This approach allows the assembler to handle forward references, where a symbol is used before it is defined.
