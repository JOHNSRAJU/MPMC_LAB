#include<stdio.h>
void print(int);
void fcfs(int);
void sjf(int);
void priority(int);
void roundrobin(int);
struct cpuScheduling{
	int no;
	int burst;
	int burstCopy;
	int priority;
	int turnAround;
	int waiting;
};struct cpuScheduling p[10],temp;
int main(){
	int i,j,n,option;
	printf("Enter no. of process :- ");
	scanf("%d",&n);
	printf("Enter the burst Time\n");
	for(i=0;i<n;i++){
		printf("p[%d] :- ",i);
		scanf("%d",&p[i].burst);
		p[i].burstCopy=p[i].burst;
		p[i].no=i;
	}
	do{
		for(i=0;i<n;i++){
			for(j=0;j<n-1-i;j++){
				if(p[j].no>p[j+1].no){
					temp = p[j];
					p[j] = p[j+1];
					p[j+1] = temp;
				}
			}
		}
		printf("___________________________________");
		printf("\nPlease choose your option\n");
		printf("1.FCFS\n2.SJF\n3.PRIORITY\n4.RoundRobin\n5.Exit\n");
		scanf("%d",&option);
		switch(option){
			case 1:
				fcfs(n);
				break;
			case 2:
				sjf(n);
				break;
			case 3:
				priority(n);
				break;
			case 4:
				roundrobin(n);
				break;
			case 5:
				break;
			default:
				printf("Enter a valid option");
		}
	}while(option!=5);
	
	return 0;
}
void fcfs(int n){
	int i,com;
	float totalTurn=0,totalWait=0,avgT,avgW;
	
	
	com=0;
	for(i=0;i<n;i++){
		com=com+p[i].burst;
		p[i].turnAround=com;
		p[i].waiting=com-p[i].burst;
	}
	printf("\nGatt Chart\n");
	printf("0");
	for(i=0;i<n;i++){
		printf("[%d]  %d  ",p[i].no,p[i].turnAround);
	}
	printf("\n");
	print(n);
	for(i=0;i<n;i++){
		totalTurn+=p[i].turnAround;
		totalWait+=p[i].waiting;
	}
	avgT=totalTurn/n;
	avgW=totalWait/n;
	printf("Average Turnaround Time = %.2f \n",avgT);
	printf("Average Waiting Time = %.2f \n",avgW);
}
void sjf(int n){
	int i,j,com;
	float totalTurn=0,totalWait=0,avgT,avgW;
	
	for(i=0;i<n;i++){
		for(j=0;j<n-1-i;j++){
			if(p[j].burst>p[j+1].burst){
				temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
		}
	}
	com=0;
	for(i=0;i<n;i++){
		com=com+p[i].burst;
		p[i].turnAround=com;
		p[i].waiting=com-p[i].burst;
	}
	printf("\nGatt Chart\n");
	printf("0");
	for(i=0;i<n;i++){
		printf("[%d]  %d  ",p[i].no,p[i].turnAround);
	}
	printf("\n");
	print(n);
	for(i=0;i<n;i++){
		totalTurn+=p[i].turnAround;
		totalWait+=p[i].waiting;
	}
	avgT=totalTurn/n;
	avgW=totalWait/n;
	printf("Average Turnaround Time = %.2f \n",avgT);
	printf("Average Waiting Time = %.2f \n",avgW);
}
void priority(int n){
	int i,j,com;
	float totalTurn=0,totalWait=0,avgT,avgW;
	printf("Enter the Priority\n");
	for(i=0;i<n;i++){
		printf("p[%d] :- ",i);
		scanf("%d",&p[i].priority);
	}
	for(i=0;i<n;i++){
		for(j=0;j<n-1-i;j++){
			if(p[j].priority>p[j+1].priority){
				temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
		}
	}
	com=0;
	for(i=0;i<n;i++){
		com=com+p[i].burst;
		p[i].turnAround=com;
		p[i].waiting=com-p[i].burst;
	}
	printf("\nGatt Chart\n");
	printf("0");
	for(i=0;i<n;i++){
		printf("p[%d]  %d  ",p[i].no,p[i].turnAround);
	}
	printf("\n");
	print(n);
	for(i=0;i<n;i++){
		totalTurn+=p[i].turnAround;
		totalWait+=p[i].waiting;
	}
	avgT=totalTurn/n;
	avgW=totalWait/n;
	printf("Average Turnaround Time = %.2f \n",avgT);
	printf("Average Waiting Time = %.2f \n",avgW);
}
void roundrobin(int n){
	int i,quanta,totalBurst=0,com;
	float totalTurn=0,totalWait=0,avgT,avgW;
	printf("Enter the Time Quanta :- ");
	scanf("%d",&quanta);
	com=0;
	for(i=0;i<n;i++){
		totalBurst+=p[i].burst;
	}
	printf("Gatt chart :- \n 0   ");
	while(com<totalBurst){
		for(i=0;i<n;i++){
			if(p[i].burstCopy>0){
				if(p[i].burstCopy<=quanta){
					com+=p[i].burstCopy;
					p[i].burstCopy=0;
					p[i].turnAround=com;
					p[i].waiting=com-p[i].burst;
				}
				else{
					com+=quanta;
					p[i].burstCopy-=quanta;
				}
				printf("p[%d]  %d   ",i,com);
			}
		}
	}
	print(n);
	for(i=0;i<n;i++){
		totalTurn+=p[i].turnAround;
		totalWait+=p[i].waiting;
	}
	avgT=totalTurn/n;
	avgW=totalWait/n;
	printf("Average Turnaround Time = %.2f \n",avgT);
	printf("Average Waiting Time = %.2f \n",avgW);
}
void print(int n){
	int i;
	printf("\nProc\tbur\tturn\twait\n");
	for(i=0;i<n;i++){
		printf("p[%d]\t%d\t%d\t%d\n",p[i].no,p[i].burst,p[i].turnAround,p[i].waiting);
	}
}
