
#include "constants.h"



                                   
const char *ops[NUM_OF_OPS] = {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec", "jmp","bne", "get", "prn", "jsr","rts", "hlt"};

const char *regs[NUM_OF_REG] ={"r0","r1","r2","r3","r4","r5","r6","r7"};

const char *data[NUM_OF_DEFS] = {".data", ".string", ".entry", ".extern"};

int extern_counter=0;

int entry_counter=0;

int DC=0,IC=100;

int regr_error=0;

int first_pass_counter=0;

int line_counter = 0;
