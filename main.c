#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "parser.h"

int main(int argc, char* argv[]){
    FILE* asm_file;
    bool more_commands;
    char type;
    char* dest_mnemonic[3];
    char* comp_mnemonic[10];
    char* jump_mnemonic[3];
    char* current_symbol[20];
    long internal_fileptr;
    int buffer_size = 250;
    char* buffer[buffer_size];
    char* reduced_buffer[3];
    FILE* hack_file;
//-- Initialize files and variables --//
    if(argc>0){
        argv++;
    }else{
        printf("Please provide Assembly Code!");
        exit();
    }

    more_commands = true;

    // open the file for the generated binary code

//---------- Parse ---------------//
    while(more_commands==true){
        initializer(argv);
        type = commandType();
        if(type=='C'){
            dest_mnemonic = dest();
            comp_mnemonic = comp();
            jump_mnemonic = jump();
        }else{
            current_symbol = symbol();
        }
        more_commands = hasMoreCommands();
    }


//---------- Translate ----------//

    fclose(asm_file);
    fclose(hack_file);
}
