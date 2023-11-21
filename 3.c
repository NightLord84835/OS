// Process control system calls: The demonstration of FORK and WAIT system calls along with zombie and orphan states.

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

void arrayStore(char* c[], int* arr,int len)
{
	for(int i=0;i<len;i++)
	{
		arr[i]=atoi(c[i+1]);
	}
}

void arrayDisplay(int * arr,int n)
{
	for(int i=0;i<n;i++)
	{
		printf("%d\t",arr[i]);
	}
	printf("\n\n");
}
void arraySort(int* arr,int len,int order)
{
	for(int i=0;i<len-1;i++)
	{
		for(int j=0;j<len-i-1;j++)
		{
			if(order == -1)
			{
				if(arr[j]<arr[j+1])
				{
					int temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
				}
			}
			else if(order == 1)
			{
				if(arr[j]>arr[j+1])
				{
					int temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
				}
			}
		}
	}
}

int main(int argc,char* argv[])
{
	int order;
	int arr[argc-1];
	int len = argc-1;
	arrayStore(argv,arr,len);

	pid_t pid, tpid, status;
	pid = fork(); 
		
	if (pid == 0)
	{
		printf("\nChild process with id %d\n",getpid());
		printf("\nChild parent id %d\n",getppid());
		order = -1;
		arraySort(arr,len,order);
		arrayDisplay(arr,len);
	}
	else
	{
		system("ps");
		tpid = wait(&status);
		printf("\nparent process with id %d\n",getpid());
		order = 1;
		arraySort(arr,len,order);
		arrayDisplay(arr,len);
	}
}