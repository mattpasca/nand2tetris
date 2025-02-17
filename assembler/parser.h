/* This file contains the parser module for the hack assembler
 * of the nand2tetris Project.
 *
 * ISSUES empty spaces in buffer are not handled.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

extern FILE* asm_file;
extern long internal_fileptr;
extern int buffer_size;
extern char buffer[buffer_size];
extern char reduced_buffer[3];
extern char dest_mnemonic[3];
extern char comp_mnemonic[10];
extern char jump_mnemonic[3];
extern char current_symbol[20];
int string_length;

void initializer(char* filename){
    asm_file = fopen(filename, "r");
}

bool hasMoreCommands(){
    internal_fileptr = ftell(asm_file);
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

    if(buffer[0]==a_command){
        return 'A';
    }
    if(buffer[0]==l_command){
        return 'L';
    }else{
        return 'C';
    }
}

void symbol(){
    sscanf(buffer+1, "%s", current_symbol);
    if(buffer[0]=='('){
        string_length = strlen(current_symbol);
        current_symbol[string_length-1] = '\0';
    }
}

void dest(){
    equal = '=';
    int equal_position = strcspn(buffer, &equal);
    string_length = strlen(buffer) - equal_position;
    if(string_length==0){
        memset(dest_mnemonic, 0, sizeof(dest_mnemonic));
    }else{
        char expression[10];
        snprintf(expression, sizeof(expression), "%%%ds", equal_position+1);
        sscanf(buffer, expression, dest_mnemonic);
    }
}

void comp(){
    equal = '=';
    string_length = strlen(buffer) - strcspn(buffer, &equal);
    if(string_length>0){
        sscanf(buffer+string_length, comp_mnemonic);
    }
}

void jump(){
    for(int i=0; i<3; +i){
        sscanf(buffer, "%c", jump_mnemonic[i]);
    }
}
