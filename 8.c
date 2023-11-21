// Implement the C program for Deadlock Avoidance Algorithm: Bankers Algorithm.	 


#include <stdio.h>

int main() {
	int np,nr;
	printf("Enter number of processes: ");
	scanf("%d", &np);
	printf("Enter number of resources: ");
	scanf("%d", &nr);
	
	int max[np][nr];
	int alloc[np][nr];
	int avail[nr];
	int need[np][nr];
	printf("Enter max. resources for each process: \n");
	for(int i=0;i<np;i++) {
		for(int j=0;j<nr;j++) {
			scanf("%d", &max[i][j]);
		}
	}
	printf("Enter allocated resources for each process: \n");
	for(int i=0;i<np;i++) {
		for(int j=0;j<nr;j++) {
			scanf("%d", &alloc[i][j]);
			need[i][j] = max[i][j] - alloc[i][j];
		}
	}
	printf("Enter max. resources for each process: \n");
	for(int i=0;i<nr;i++) {
		scanf("%d", &avail[i]);
	}
	
	int work[nr];
	int finish[np];
	for(int i=0;i<nr;i++) {
		work[i] = avail[i];
	}
	for(int i=0;i<np;i++) {
		finish[i] = 0;
	}
	
	int safe[np];
	int count=0;
	while(count < np) 
	{
		int found=0;
		for(int i=0;i<np;i++) //for each process
		{
			if(finish[i] == 0) //if any process is not executed
			{
				int j;
				for(j=0;j<nr;j++) //check for each resource
				{
					if(need[i][j] > work[j])
					{
						break;
					}
				}
				
				if(j == nr) //if satisfied till last resource
				{
					for(int k=0;k<nr;k++)
					{
						work[k] += alloc[i][k]; //append in respective resource
					}
					
					safe[count++] = i;
					finish[i] = 1;
					found = 1;
				}
			}
		}
		if(found == 0)
		{
			printf("System is not in a safe state.\n");
            return 0;
		}
	}
	
	printf("System is in a safe state.\n");
    printf("Safe Sequence: ");
    for (int i = 0; i < np; i++) {
        printf("%d ", safe[i]);
    }
    printf("\n");

    return 0;
}