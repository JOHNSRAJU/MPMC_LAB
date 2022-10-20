#include<stdio.h>
void fcfs(int,int,int[]);
void scan(int,int,int[],int);
void cscan(int,int,int[],int);
int main(){
	int i,r,j,req[20],diskS,pm,headCP,option,sReq[20],temp;
	printf("Enter no. of requests :- ");
	scanf("%d",&r);
	printf("Enter the request sequence :- \n");
	for(i=0;i<r;i++){
		scanf("%d",&req[i]);
		sReq[i]=req[i];
		
	}
	for(i=0;i<r;i++){
		for(j=0;j<r-1-i;j++){
			if(sReq[j]>sReq[j+1]){
				temp=sReq[j];
				sReq[j]=sReq[j+1];
				sReq[j+1]=temp;
			}
		}
	}
	printf("Enter current position of head :- ");
	scanf("%d",&headCP);
	printf("Enter the Disk size :- ");
	scanf("%d",&diskS);
	do{
		printf("\n___________________________________");
		printf("\nPlease choose your option\n");
		printf("1.FCFS\n2.SCAN\n3.C_SCAN\n4.Exit\n");
		scanf("%d",&option);
		switch(option){
			case 1:
				fcfs(r,headCP,req);
				break;
			case 2:
				scan(r,headCP,sReq,diskS);
				break;
			case 3:
				cscan(r,headCP,sReq,diskS);
				break;
			case 4:
				
				break;
			default:
				printf("Enter a valid option");
		}
	}while(option!=4);
	return 0;
}
void fcfs(int r,int headCP,int req[20]){
	int i,point,headM=0;
	point=headCP;
	for(i=0;i<r;i++){
		if(req[i]<point){
			headM+=(point-req[i]);
		}
		else{
			headM+=(req[i]-point);
		}
		point=req[i];
	}
	printf("\nTotal head movement :- %d",headM);
}
void scan(int r,int headCP,int sReq[20],int diskS){
	int i,point,headM0=0,headM1=0;
	point=headCP;
		headM0+=(diskS-point)+(diskS-sReq[0]);
		headM1+=(point+sReq[r-1]);
		printf("\nTotal head movement in left to right direction:- %d",headM0);
		printf("\nTotal head movement in right to left direction:- %d",headM1);
}
void cscan(int r,int headCP,int sReq[20],int diskS){
	int i,point,headM0=0,headM1=0;
	point=0;

	for(i=0;i<r;i++){
		if(headCP>sReq[i]){
			point=i;
		}
	}
		headM0+=(diskS-headCP)+(diskS+sReq[point]);
		headM1+=headCP+diskS+(diskS-sReq[point+1]);
		printf("\nTotal head movement in left to right direction:- %d",headM0);
		printf("\nTotal head movement in right to left direction:- %d",headM1);
}

