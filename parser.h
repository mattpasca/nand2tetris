/* This file contains the parser module for the hack assembler
 * of the nand2tetris Project.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static  FILE* asm_file;
static int current_line;
long internal_fileptr;
int buffer_size = 250;
static char* buffer[buffer_size];
static char* reduced_buffer[3];

void initializer(char* filename){
    asm_file = fopen(filename, "r");
}

bool hasMoreCommands(){
    internal_fileptr = fgets(asm_file);
    if(internal_fileptr>=0){
         return true;
    }else{
        return false;
    }
}

void advance(){
    if(hasMoreCommands()){
        fgets(buffer, buffer_size, asm_file);
    }
}

char commandType(){
    char a_command = '@';
    char l_command = '(';

    if(buffer, a_command){
        return 'A';
    }
    if(buffer, l_command){
        return 'L';
    }else{
        return 'C';
    }
}

char* symbol(){
    char retrieved_symbol[20];
    for(int i=1; i<20; ++i){
        while(buffer[i]!=')'){
            sscanf(buffer, "%c", &retrieved_symbol[i-1]);
        }
    }
    return retrieved_symbol;
}

char* dest(){
    char dest_result[3];
    for(int i=0; i<3; ++i){
        if(buffer[i]==';'){
            return NULL;
        }
        if(buffer[i]=='='){
            break;
        }
        sscanf(buffer, "%c", &dest_result[i]);
    }
    return dest_result;
}

char* comp(){
    char comp_result[6];
    for(int i=0; i<6; ++i){
        while(buffer[i]!=';'){
            sscanf(buffer, "%c", &comp_result[i]);
        }
        if(buffer[i]==';'){
            reduced_buffer = &buffer[i+1];
        }
    }
    return comp_result;
}

char* jump(){
    char* jump_result[3];
    for(int i=0; i<3; +i){
        sscanf(buffer, "%c", &jump_result);
    }
    return jump_result;
}
