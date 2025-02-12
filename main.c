#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "parser.h"

int main(int argc, char* argv[]){
    FILE* asm_file;
    int current_line; // unnecessary?
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

    // open the file for the generated binary code

//---------- Parse ---------------//

//---------- Translate ----------//

    fclose(asm_file);
}
