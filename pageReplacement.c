#include<stdio.h>
void fifo(int[],int,int);
void lru(int[],int,int);
void lfu(int[],int,int);
int main(){
	int i,p[20],n,f,option;
	printf("Enter the no. of pages :- ");
	scanf("%d",&n);
	printf("Enter no. of frames :- ");
	scanf("%d",&f);
	printf("Enter the page references :- \n");
	for(i=0;i<n;i++){
		scanf("%d",&p[i]);
	}
	do{
		printf("\nPlease Select your option :- \n");
		printf("1.FIFO\n2.LRU\n3.LFU\n4.Exit\n");
		scanf("%d",&option);
		switch(option){
			case 1:
				fifo(p,n,f);
				break;
			case 2:
				lru(p,n,f);
				break;
			case 3:
				lfu(p,n,f);
				break;
			case 4:
				printf("\nThank You !\n");
				break;
			default:
				printf("\nEnter a valid option\n");
		}
	}while(option!=4);
	return 0;
}
void fifo(int p[20],int n,int f){
	int i,j,pageFault=0,frames[10],flag,point=0;
	for(i=0;i<f;i++){
		frames[i]=p[i];
		pageFault++;
	}
	printf("\nREF\t  Frames\n");
	for(i=0;i<f;i++){
	printf("%d\t",p[i]);
		for(j=0;j<=i;j++){
			printf("%d   ",frames[j]);
		}
		printf("\n");
	}
	for(i=f;i<n;i++){
		flag=0;
		for(j=0;j<f;j++){
			if(frames[j]==p[i]){
				flag=1;
				printf("%d *\t",p[i]);
				break;
			}
		}
		if(flag==0){
			frames[point]=p[i];
			point=(point+1)%f;
			pageFault++;
			printf("%d\t",p[i]);
		}
		
		
		for(j=0;j<f;j++){
			printf("%d   ",frames[j]);
		}
		printf("\n");
	}
	printf("No. of Page Fault :- %d",pageFault);
}

void lru(int p[20],int n,int f){
	int i,j,pageFault=0,frames[10],flag,point,fla[10],k;
	for(i=0;i<f;i++){
		frames[i]=p[i];
		pageFault++;
	}
	printf("\nREF\t  Frames\n");
	for(i=0;i<f;i++){
	printf("%d\t",p[i]);
		for(j=0;j<=i;j++){
			printf("%d   ",frames[j]);
		}
		printf("\n");
	}
	for(i=f;i<n;i++){
		flag=0;
		for(j=0;j<f;j++){
			if(frames[j]==p[i]){
				flag=1;
				printf("%d *\t",p[i]);
				break;
			}
			fla[j]=0;
		}
		if(flag==0){
			for(j=i;j>i-f;j--){
				for(k=0;k<f;k++){
					if(p[j]==frames[k]){
						fla[k]=1;
					}
				}
			}
			for(j=0;j<f;j++){
				if(fla[j]==0){
					point=j;
					break;
				}
			}
			frames[point]=p[i];
			pageFault++;
			printf("%d\t",p[i]);
		}
		for(j=0;j<f;j++){
			printf("%d   ",frames[j]);
		}
		printf("\n");
	}
	printf("No. of Page Fault :- %d",pageFault);
}
void lfu(int p[20],int n,int f){
	int i,j,k,pageFault=0,frames[10],flag,point=0,freq[10],min;
	for(i=0;i<f;i++){
		frames[i]=p[i];
		freq[i]=1;
		pageFault++;
	}
	printf("\nREF\t  Frames\n");
	for(i=0;i<f;i++){
	printf("%d\t",p[i]);
		for(j=0;j<=i;j++){
			printf("%d   ",frames[j]);
		}
		printf("\n");
	}
	for(i=f;i<n;i++){
		flag=0;
		for(j=0;j<f;j++){
			if(frames[j]==p[i]){
				flag=1;
				printf("%d *\t",p[i]);
				freq[j]++;
				break;
			}
		}
		if(flag==0){
			min=point;
			k=point;
			for(j=0;j<f;j++){
				if(freq[min]>freq[k]){
					min=k;
					point=(point+1)%f;
				}
				k=(k+1)%f;
			}
			frames[min]=p[i];
			point=(point+1)%f;
			pageFault++;
			freq[min]=1;
			printf("%d\t",p[i]);
		}
		
		
		for(j=0;j<f;j++){
			printf("%d   ",frames[j]);
		}
		printf("\n");
	}
	printf("No. of Page Fault :- %d",pageFault);
}
