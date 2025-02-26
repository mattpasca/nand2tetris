/* TODO pass arguments for the binary functions
 *      as &binary[3] for comp
 *         &binary[11] for dest
 *         &binary[14] for jump
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "parser.h"
#include "code.h"

FILE* asm_file;
FILE* hack_file;
char hack_file_name[20];
bool more_commands;
char type;
char dest_mnemonic[3];
char comp_mnemonic[10];
char jump_mnemonic[3];
char current_symbol[20];
char binary[16];
char buffer[250];

int main(int argc, char* argv[]){

//-- Initialize files --//
    if(argc==0){
         printf("Please provide Assembly Code!");
         exit(EXIT_FAILURE);
    }
    initializer(argv[1]);

    // Open the .hack file for the generated binary code
    strcpy(hack_file_name, argv[1]);
    char* substring_ptr;
    substring_ptr = strstr(hack_file_name, &point);
    memset(substring_ptr, '\0', strlen(substring_ptr));
    strcat(hack_file_name, ".hack")
    hack_file = fopen(hack_file_name, "w");

//---------- Parse and Translate---------------//
    more_commands = true;
    while(more_commands==true){
        advance();
        type = commandType();
        if(type == '\0'){
            more_commands = hasMoreCommands();
            continue;
        }
        if(type=='C'){
            dest_parser();
            comp_parser();
            jump_parser();

        }else{
            symbol();
        }

        more_commands = hasMoreCommands();
    }

    fclose(asm_file);
    fclose(hack_file);
}
