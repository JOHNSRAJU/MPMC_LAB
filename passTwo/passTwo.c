#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int searchOptab(char opcode[10]){
    FILE *optab;
    char op[10];
    int value;
    optab=fopen("optab.txt","r");
    while(!feof(optab)){
        fscanf(optab,"%s%d",op,&value);
        if(strcmp(op,opcode)==0){
            return value;
        }
    }
    fclose(optab);
    return -1;
}
int searchSymtab(char label[10]){
    FILE *symtab;
    char sym[10];
    int value;
    symtab=fopen("symtab.txt","r");
    while(!feof(symtab)){
        fscanf(symtab,"%s%d",sym,&value);
        if(strcmp(sym,label)==0){
            return value;
        }
    }
    fclose(symtab);
    return -1;
}
int main(){
    FILE *intermediate,*output,*header,*text,*end,*symtab,*optab;
    char label[10],opcode[10],operand[10],obcode[10],obcodeTe[100]="",obcodeCopy[10];
    int LOCCTR,symaddr,opaddr,i,sa,leng,lenObCode=0,flag=0,flag2=0;
    intermediate=fopen("intermediate.txt","r");
    output=fopen("output.txt","w");
    header=fopen("header.txt","w");
    text=fopen("text.txt","w");
    end=fopen("end.txt","w");
    fscanf(intermediate,"%s%s%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0){
        fprintf(header,"H^%06s^%06s",label,operand);
        fprintf(text,"T^%06s",operand);
        fprintf(end,"E^%06s",operand);
        fprintf(output,"\t%s\t%s\t%s\n",label,opcode,operand);
        sa=atoi(operand);
    }
    while(strcmp(opcode,"END")!=0){
        fscanf(intermediate,"%d%s%s%s",&LOCCTR,label,opcode,operand);
        if(strcmp(label,"**")==0){
            opaddr=searchOptab(opcode);
            if(opaddr!=-1){
                symaddr=searchSymtab(operand);
                if(symaddr!=-1){
                    sprintf(obcode,"%02d%d",opaddr,symaddr);
                    lenObCode+=3;
                } 
                sprintf(obcodeTe,"%s^%s",obcodeTe,obcode);
            }
        }
        else if(strcmp(opcode,"BYTE")==0){
            if(flag==0){
                fprintf(text,"^%02d%s",lenObCode,obcodeTe);
                sprintf(obcodeTe,"");
                lenObCode=0;
                flag=1;
                flag2=1;
            }
            sprintf(obcodeCopy,"");
            for(i=2;i<strlen(operand)-1;i++){
                sprintf(obcodeCopy,"%s%c",obcodeCopy,operand[i]);
            }
            lenObCode+=3;
            sprintf(obcode,"%06s",obcodeCopy);
            sprintf(obcodeTe,"%s^%s",obcodeTe,obcode);
        }
        else if(strcmp(opcode,"WORD")==0){
            if(flag==0){
                fprintf(text,"^%02d%s",lenObCode,obcodeTe);
                sprintf(obcodeTe,"");
                lenObCode=0;
                flag=1;
                flag2=1;
            }
            sprintf(obcode,"%06s",operand);
            lenObCode+=3;
            sprintf(obcodeTe,"%s^%s",obcodeTe,obcode);
        }
        else{
            sprintf(obcode,"");
        }
        fprintf(output,"%d\t%s\t\t%s\t\t%s\t\t%s\n",LOCCTR,label,opcode,operand,obcode);
        if(strcmp(obcode,"")!=0){
            if(flag2==1 && (strcmp(obcodeTe,"")!=0)){
                fprintf(text,"\nT^%06d",LOCCTR);
                flag2=0;
            }
            if(lenObCode>17){
                fprintf(text,"^%02d%s",lenObCode,obcodeTe);
                sprintf(obcodeTe,"");
                lenObCode=0;
                flag2=1;
            }
        }
    }
    if(lenObCode>0){
        fprintf(text,"^%02d%s",lenObCode,obcodeTe);
    }
    leng=LOCCTR-sa;
    fprintf(header,"^%06d",leng);
    fclose(intermediate);
    fclose(output);
    fclose(header);
    fclose(text);
    fclose(end);
    printf("Output generated successfully");
    return 0;
}