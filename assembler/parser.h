/* This file contains the parser module for the hack assembler
 * of the nand2tetris Project.
 *
 * ISSUES empty spaces in buffer are not handled
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

extern FILE* asm_file;
long internal_fileptr;
extern char buffer[250];
extern char dest_mnemonic[3];
extern char comp_mnemonic[10];
extern char jump_mnemonic[3];
extern char current_symbol[20];
int string_length;
int occurence;
char* last_occurence;
char expression[10];

void initializer(char* filename){
    asm_file = fopen(filename, "r");
}

bool hasMoreCommands(){
    internal_fileptr = feof(asm_file);
    if(internal_fileptr==0){
         return true;
    }else{
        return false;
    }
}

void advance(){
    if(hasMoreCommands()){
        fgets(buffer, 150, asm_file);
    }
}

char commandType(){
    char a_command = '@';
    char l_command = '(';

    char white_space = ' ';
    last_occurence = strrchr(buffer, white_space);
    if(strlen(buffer)>1){
        last_occurence++;
    } else{
        return 'N';
    }
    if(*last_occurence==a_command){
        return 'A';
    }
    if(*last_occurence==l_command){
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
    char equal = '=';
    occurence = strcspn(buffer, &equal);
    string_length = strlen(buffer) - occurence;
    if(string_length==0){
        memset(dest_mnemonic, 0, sizeof(dest_mnemonic));
    }else{
        snprintf(expression, sizeof(expression), "%%%ds", occurence+1);
        sscanf(buffer, expression, &dest_mnemonic);
    }
}

void comp(){
    char equal = '=';
    occurence = strcspn(buffer, &equal);
    string_length = strlen(buffer) - occurence;
    if(string_length>0){
        snprintf(expression, sizeof(expression), "%%%ds", occurence+1);
        sscanf(buffer+string_length, expression, &comp_mnemonic);
    }
}

void jump(){
    char semi_colon = ';';
    occurence = strcspn(buffer, &semi_colon);
    string_length = strlen(buffer) - occurence;
    if(string_length>0){
        sscanf(buffer+string_length, expression, &jump_mnemonic);
    }
}
