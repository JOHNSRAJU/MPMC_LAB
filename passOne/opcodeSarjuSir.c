#include<stdio.h>
#include<string.h>
//This function will return 1 if label found else 0
int searchSymtab(char label[10])
{
    char symbol[10];
    FILE *symtab,*inter;
    int value;
    symtab = fopen("symtab.txt","r");
    while(!feof(symtab)){
        fscanf(symtab,"%s%d",symbol,&value);
        if(strcmp(label,symbol)==0){
            return 1; //symbol found
        }
    }
    fclose(symtab);
    return 0; //Symbol Not found

}
int searchOptab(char opcode[10]){
    FILE *optab;
    char op[10],code[10];
    optab = fopen("optab.txt","r");
    while(!feof(optab)){
        fscanf(optab,"%s%s",op,code);
        if(strcmp(op,opcode)==0){
            return 1; //OPCODE Found
        }
    }
    fclose(optab);
    return 0; //OPCODE Not found

}
int main(){
    FILE *in,*symtab,*inter;
    int length;
    char label[20],opcode[20],operand[20];
    int sA, LOCCTR,op;//sA stands for Starting Address
    in=fopen("input.txt","r");
    symtab = fopen("symtab.txt","a");
    inter =fopen("intermediate.txt","a");
    fscanf(in,"%s%s%d",label,opcode,&op);
    if(strcmp(opcode,"START")==0){
        sA=op;
        LOCCTR =op;
        //printf("Starting Address%d Location Counter%d",sA,LOCCTR);
        fprintf(inter,"\t%s\t%s\t%d\n",label,opcode,op);
    }
    else{
        LOCCTR=0;
    }
    while(!feof(in)){
        fscanf(in,"%s%s%s",label,opcode,operand);
//Search SYMTAB for label
        if(strcmp(label,"-")!=0){
                if(searchSymtab(label)==0){
                    fprintf(symtab,"%s %d\n",label,LOCCTR);
                }
        }
        //search OPTAB for OPCODE
        if(searchOptab(opcode)==1){
            LOCCTR+=3;
        }
        else if(strcmp(opcode,"WORD")==0)
        {
            LOCCTR+=3;
        }
        else if(strcmp(opcode,"RESW")==0)
        {
            op = atoi(operand);
            LOCCTR = LOCCTR+(3*op);
        }
        else if(strcmp(opcode,"RESB")==0)
        {
            op =atoi(operand);
            LOCCTR = LOCCTR+op;
        }
        else if(strcmp(opcode,"BYTE")==0)
        {
            length=strlen(operand)-2;
            LOCCTR = LOCCTR + length;
        }
        else{
            printf("ERROR");
        }
        fprintf(inter,"%d\t%s\t%s\t%s\n",LOCCTR,label,opcode,&operand);
    }
    fclose(symtab);
    fclose(in);
    return 0;
}