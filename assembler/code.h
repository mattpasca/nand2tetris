/* This file contains the code module for
 * the hack assembler of tthe nand2tetris project.
 *
 * TODO handle file opening/closing limited to header scope
 *      skip lines based on length of comp_mnemonic
 *      reset internal fileptr of comp_table to 0
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

FILE* comp_table;
int occurence;
char buffer[50];

// NO comp_table = fopen("comp_table.csv", "r");

char* dest(char* mnemonic){
    char result[3];
    char registers[] = {'A', 'D', 'M'};
    for(int i=0; i<3; ++i){
        occurence = strlen(mnemonic) - strcspn(mnemonic, registers[i]);
        result[i] = (occurence>0) ? 1:0;
    }
    return result;
}

char* comp(char* mnemonic){
    char result[7];
    char comma = ',';
    int string_comparison;
    int line;
    string_comparison = 1;
    switch(strlen(mnemonic)){
        case 1: while(string_comparison!=0){
                    fgets(buffer, 50, comp_table);
                    string_comparison = strncmp(mnemonic, buffer, 1);
                }
                for(int i=0; i<7; ++i){
                    result[i] = buffer[i+2];
                }
                break;

        case 2: line = 7;
                while(line>0){
                    fgets(buffer, 50, comp_table);
                    line += -1;
                }
                 while(string_comparison!=0){
                    fgets(buffer, 50, comp_table);
                    string_comparison = strncmp(mnemonic, buffer, 2);
                }
                for(int i=0; i<7; ++i){
                    result[i] = buffer[i+3];
                }
                break;


        case 3: line = 14;
                while(line>0){
                    fgets(buffer, 50, comp_table);
                    line += -1;
                }
                 while(string_comparison!=0){
                    fgets(buffer, 50, comp_table);
                    string_comparison = strncmp(mnemonic, buffer, 3);
                }
                for(int i=0; i<7; ++i){
                    result[i] = buffer[i+4];
                }
                break;

    }
    fseek(comp_table, 0, SEEK_SET);
    return result;
}

char* jump(char* mnemonic){
    char result[3];
    for(int i=0; i<3; ++i){
        result[i] = (mnemonic[i]==0) ? 0 : 1;
    }
    return result;
}

void open_comp_table(){
        comp_table = fopen("comp_table.csv", "r");
}

void close_comp_table(){
    if(comp_table){
        fclose(comp_table);
    }
}
