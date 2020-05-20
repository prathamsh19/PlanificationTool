#include<stdio.h>
#include<stdlib.h>
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort(int* a,int* p,int n)
{
for(int i=0;i<(n);i++)
 {
     for(int j=i+1;j<n;j++)
     {
       if(a[i]>a[j])
       {
        int t=a[i];
        a[i]=a[j];
        a[j]=t;
        swap(&p[i],&p[j]);
       }
     }
 }
}

void fcfs(int n1,int n,int* burst,int* p)
{
    int *wait=(int*)malloc(sizeof(int)*n);
    int *tat=(int*)malloc(sizeof(int)*n);
    int tot_w=0,tot_tat=0;
    if(n1==1)
    {
    printf("Enter the arrival time of processes\n");
    int *arrival=(int *)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++)
        scanf("%d",&arrival[i]);
     sort(arrival,p,n);
    }
     for(int i=0;i<n;i++)
     {
     if(i==0)
      wait[p[i]]=0;
     else
     wait[p[i]]=wait[p[i-1]]+burst[p[i-1]];
     tat[p[i]]=wait[p[i]]+burst[p[i]];
     tot_w+=wait[p[i]];
     tot_tat+=tat[p[i]];
     }
     printf("Processes   Burst time   Waiting time   Turn around time\n");
     for (int i=0; i<n; i++)
    {
        printf("  P%d\t\t%d\t    %d\t\t     %d\t\t\n",p[i]+1,burst[p[i]], wait[p[i]], tat[p[i]]);
    }
    printf("Average waiting time = %f",(float)tot_w/(float)n);
    printf("\nAverage turn around time = %f",(float)tot_tat/(float)n);
}

void sjf(int n1,int n,int* burst,int* p)
{

  int *wait=(int*)malloc(sizeof(int)*n);
  int *tat=(int*)malloc(sizeof(int)*n);
  int tot_w=0,tot_tat=0;
  if(n1==2)
  {
    sort(burst,p,n);
    for(int i=0;i<n;i++)
     {
     if(i==0)
      wait[p[i]]=0;
     else
     wait[p[i]]=wait[p[i-1]]+burst[p[i-1]];
     tat[p[i]]=wait[p[i]]+burst[p[i]];
     tot_w+=wait[p[i]];
     tot_tat+=tat[p[i]];
     }
     printf("Processes   Burst time   Waiting time   Turn around time\n");
     for (int i=0; i<n; i++)
     {
        printf("  P%d\t\t%d\t    %d\t\t     %d\t\t\n",p[i]+1,burst[p[i]], wait[p[i]], tat[p[i]]);
     }
  }
  else
  {
    printf("Enter the arrival time of processes\n");
    int *arrival=(int *)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++)
        scanf("%d",&arrival[i]);
    sort(arrival,p,n);
    int temp=0,val=0,i=0;
    int *ct=(int*)malloc(sizeof(int)*n);
    ct[p[i]]=arrival[p[i]]+burst[p[i]]; //4
    tat[p[i]]=ct[p[i]]-arrival[p[i]];//4
    wait[p[i]]=tat[p[i]]-burst[p[i]]; //0

	for(int i=1; i<n; i++)
	{
		temp = ct[p[i-1]]; //4
		int low = burst[p[i]]; //3
		val=i;
		for(int j=i; j<n; j++)
		{
			if(temp>= arrival[p[j]] && low >= burst[p[j]])
			{
				low = burst[p[j]];
				val = j;
			}
		}
        ct[p[val]]=temp+burst[p[val]];
        tat[p[val]]=ct[p[val]]-arrival[p[val]];
        wait[p[val]]=tat[p[val]]-burst[p[val]];
        tot_w+=wait[p[val]];
        tot_tat+=tat[p[val]];
        swap(&p[val],&p[i]);
    }
         printf("Processes   Burst time   Waiting time   Turn around time\n");
        for (i=0; i<n; i++)
        {
           printf("  P%d\t\t%d\t    %d\t\t     %d\t\t\n",p[i]+1,burst[p[i]], wait[p[i]], tat[p[i]]);
        }
  }
    printf("Average waiting time = %f",(float)tot_w/(float)n);
    printf("\nAverage turn around time = %f",(float)tot_tat/(float)n);
}

void rr(int n1,int n,int* burst,int* p)
{
   int *wait=(int*)malloc(sizeof(int)*n);
   int *tat=(int*)malloc(sizeof(int)*n);
   int tot_w=0,tot_tat=0,quantum=0;
   int *rem_bt=(int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++)
        rem_bt[i]=burst[i];
    int t =0;
    if(n1==1)
    {
    printf("Enter the arrival time of processes\n");
    int *arrival=(int *)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++)
        scanf("%d",&arrival[i]);
    sort(arrival,p,n);
    printf("Enter the quantum\n");
    scanf("%d",&quantum);
    while (1)
     {
        int done = 1;
        for (int i = 0 ; i < n; i++)
        {
            if (rem_bt[p[i]] > 0)
            {
                done = 0;

                if (rem_bt[p[i]] > quantum)
                {
                    t += quantum;
                    rem_bt[p[i]] -= quantum;
                }
                else
                {
                    t = t + rem_bt[p[i]];
                    wait[p[i]] = t - burst[p[i]]-arrival[p[i]];
                    tat[p[i]] = burst[p[i]] + wait[p[i]];
                    tot_w+=wait[p[i]];
                    tot_tat+=tat[p[i]];
                    rem_bt[i] = 0;
                }
            }
        }
        if (done)
          break;
     }
    }
    else
    {
     printf("Enter the quantum\n");
     scanf("%d",&quantum);
     while (1)
     {
        int done = 1;
        for (int i = 0 ; i < n; i++)
        {
            if (rem_bt[i] > 0)
            {
                done = 0;

                if (rem_bt[i] > quantum)
                {
                    t += quantum;
                    rem_bt[i] -= quantum;
                }
                else
                {
                    t = t + rem_bt[i];
                    wait[i] = t - burst[i];
                    tat[i] = burst[i] + wait[i];
                    tot_w+=wait[i];
                    tot_tat+=tat[i];
                    rem_bt[i] = 0;
                }
            }
        }
        if (done)
          break;
     }
    }
     printf("Processes   Burst time   Waiting time   Turn around time\n");
     for (int i=0; i<n; i++)
           printf("  P%d\t\t%d\t    %d\t\t     %d\t\t\n",p[i]+1,burst[p[i]], wait[p[i]], tat[p[i]]);
    printf("Average waiting time = %f",(float)tot_w/(float)n);
    printf("\nAverage turn around time = %f",(float)tot_tat/(float)n);
}

void priority(int n1,int n,int* burst,int* p)
{
  int *wait=(int*)malloc(sizeof(int)*n);
  int *tat=(int*)malloc(sizeof(int)*n);
  int *prio=(int*)malloc(sizeof(int)*n);
  int tot_w=0,tot_tat=0;
  printf("Enter the priorities of processes\n");
  for(int i=0;i<n;i++)
        scanf("%d",&prio[i]);
  if(n1==1)
  {
   printf("Enter the arrival time of processes\n");
   int *arrival=(int *)malloc(sizeof(int)*n);
   int *service=(int *)malloc(sizeof(int)*n);
   for(int i=0;i<n;i++)
     scanf("%d",&arrival[i]);
   sort(arrival,p,n);
   for(int i=0;i<n;i++)
   {
     for(int j=0;j<n-1;j++)
     {
         if(arrival[p[j]]==arrival[p[j+1]])
         {
             if(prio[p[j]]>prio[p[j+1]])
                swap(&p[j],&p[j+1]);
         }
     }
   }
   service[p[0]]=0;
   wait[p[0]]=0;
   tat[p[0]]=burst[p[0]]+wait[p[0]];
   tot_tat+=tat[p[0]];
   for(int i=1;i<n;i++)
   {
       service[p[i]]=burst[p[i-1]]+ service[p[i-1]];
       printf("%d ",service[p[i]]);
       wait[p[i]]= service[p[i]]-arrival[p[i]]+1;
       if(wait[p[i]]<0)
        wait[p[i]]=0;
       tat[p[i]]=burst[p[i]]+wait[p[i]];
       tot_w+=wait[p[i]];
       tot_tat+=tat[p[i]];
   }
  }
  else
 {
  sort(prio,p,n);
  for(int i=0;i<n;i++)
     {
     if(i==0)
      wait[p[i]]=0;
     else
     wait[p[i]]=wait[p[i-1]]+burst[p[i-1]];
     tat[p[i]]=wait[p[i]]+burst[p[i]];
     tot_w+=wait[p[i]];
     tot_tat+=tat[p[i]];
     }
 }
     printf("Processes   Burst time   Waiting time   Turn around time\n");
     for (int i=0; i<n; i++)
    {
        printf("  P%d\t\t%d\t    %d\t\t     %d\t\t\n",p[i]+1,burst[p[i]], wait[p[i]], tat[p[i]]);
    }
    printf("Average waiting time = %f",(float)tot_w/(float)n);
    printf("\nAverage turn around time = %f",(float)tot_tat/(float)n);
}


int main()
{
    printf("Please select the algorithm and enter the required number\n");
    printf("1.FCFS(First Come First Serve)                  2.SJF(Shortest Job First)\n");
    printf("3.SRTF(Shortest Remaining Time First)           4.RR(Round-Robin)\n");
    printf("5.Priority Based Scheduling\n");
    int n1,n2=0,n=0,i=0;
    scanf("%d",&n1);
    printf("Enter 1 for with arrival time \nEnter 2 for without arrival time\n");
    scanf("%d",&n2);
    printf("Enter number of processes\n");
    scanf("%d",&n);
    int *burst=(int*)malloc(sizeof(int)*n);
    int *p=(int*)malloc(sizeof(int)*n);
    printf("Enter burst time of processes\n");
    for(i=0;i<n;i++)
    {
        scanf("%d",&burst[i]);
        p[i]=i;
    }

    if(n2==1||n2==2)
    {
    switch(n1)
    {
        case 1:
        fcfs(n2,n,burst,p);
        break;

        case 2:
        sjf(n2,n,burst,p);
        break;

        /*case 3:
        srtf(n2);
        break;8*/

        case 4:
        rr(n2,n,burst,p);
        break;

        case 5:
        priority(n2,n,burst,p);
        break;

        default:
        printf("Wrong Input!!!\n Select number between 1 to 5\n");
        break;
    }
   }
   else
     printf("Wrong Input!!!\n Enter number 1 or 2\n");
   return 0;
}
