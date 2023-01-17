#ifndef SECOND_PASS_H
#define SECOND_PASS_H
#include "constants.h"
#include "data_image.h"
#include "machine_word.h"
#include "label.h"
#include "label_list.h"
#include "command_validator.h"
#include "inputProcessing.h"
#include "base_32.h"
#include "extern.h"

void second_pass(FILE *file,label_node **label_head,data_image **data_head,code_img **code_head);

void entry_print(label_node *head,char *name);


void extern_print(extern_node *head,char *name);
#endif
