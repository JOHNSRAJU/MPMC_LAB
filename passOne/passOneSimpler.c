#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
    FILE *input,*intermediate,*symtab;
    char label[20],opcode[20],operand[20];
    int LOCCTR,op;
    input=fopen("input.txt","r");
    intermediate=fopen("intermediate.txt","w");
    symtab=fopen("symtab.txt","w");
    fscanf(input,"%s%s%d",label,opcode,&op);
    if(strcmp(opcode,"START")==0){
        LOCCTR=op;
        fprintf(intermediate,"\t%s\t\t%s\t\t%d\n",label,opcode,op);
    }
    else{
        LOCCTR=0;
    }
    while(strcmp(opcode,"END")!=0){
        fscanf(input,"%s%s%s",label,opcode,operand);
        fprintf(intermediate,"%d\t\t%s\t\t%s\t\t%s\n",LOCCTR,label,opcode,operand);
        if(strcmp(label,"**")!=0){
            fprintf(symtab,"%s %d\n",label,LOCCTR);
        }
        if(strcmp(opcode,"WORD")==0){
            LOCCTR+=3;
        }
        else if(strcmp(opcode,"RESW")==0){
            op=atoi(operand);
            LOCCTR=LOCCTR+(3*op);
        }
        else if(strcmp(opcode,"RESB")==0){
            op=atoi(operand);
            LOCCTR=LOCCTR+op;
        }
        else if(strcmp(opcode,"BYTE")==0){
            LOCCTR=LOCCTR+(strlen(operand)-3);
        }
        else{
            LOCCTR+=3;
        }
        
    }
    fclose(input);
    fclose(intermediate);
    fclose(symtab);
    return 0;
}
