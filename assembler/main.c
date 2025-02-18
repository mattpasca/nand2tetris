// TODO buffer has to be without whitespace

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "parser.h"

FILE* asm_file;
bool more_commands;
char type;
char dest_mnemonic[3];
char comp_mnemonic[10];
char jump_mnemonic[3];
char current_symbol[20];
char buffer[250];
FILE* hack_file;

int main(int argc, char* argv[]){

//-- Initialize files and variables --//
    if(argc==0){
         printf("Please provide Assembly Code!");
         exit(EXIT_FAILURE);
    }
    more_commands = true;

    // open the file for the generated binary code
    initializer(argv[1]);

//---------- Parse ---------------//
    while(more_commands==true){
        advance();
        type = commandType();
        if(type == '\0'){
            more_commands = hasMoreCommands();
            continue;
        }
        if(type=='C'){
            dest();
            comp();
            jump();
        }else{
            symbol();
        }
        more_commands = hasMoreCommands();
    }


//---------- Translate ----------//

    fclose(asm_file);
 // fclose(hack_file);
}
