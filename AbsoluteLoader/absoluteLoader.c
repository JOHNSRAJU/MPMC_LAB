#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
    int i,start;
    char str[100],name[10]="",starts[10]="",byte[10];
    FILE *f;
    f=fopen("records.txt","r");
    while(!feof(f)){
        fscanf(f,"%s",str);
        if(str[0]=='H'){
            for(i=2;i<8;i++){
                strncat(name,&str[i],1);
            }
            printf("Program name :- %s\n",name);
        }
        if(str[0]=='T'){
            strcpy(starts,"");
            for(i=2;i<8;i++){
                strncat(starts,&str[i],1);
            }
            start=atoi(starts);
            for(i=12;i<strlen(str)-1;i++){
                strcpy(byte,"");
                if(str[i]!='^'){
                    strncat(byte,&str[i],1);
                    i++;
                    strncat(byte,&str[i],1);
                    printf("%d\t%s\n",start,byte);
                    start++;
                }
            }
        }
    }
}