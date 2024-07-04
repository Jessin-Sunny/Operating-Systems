#include <stdio.h>
#include <stdlib.h>

#define size 25

int nop,nob;
int blocks[size],process[size];

void FirstFit()
{
    int i,j,temp;
    int fragments[size],block_index[size],block_allocated[size],process_allocated[size];
    int allocated_process_size;//display part
    //block_index[i]=j --> jth index of the block allocated to a particular process i
    //block_allocated[j] --> to indicate whether jth block is allocated (1) or not(0)
    for(i=0;i<nob;i++)
    {
        block_allocated[i]=0;
        fragments[i]=blocks[i];
    }
    for(i=0;i<nop;i++)
    {
        process_allocated[i]=0;
    }
    for(i=0;i<nop;i++)
    {
        temp=-1;
        for(j=0;j<nob;j++)
        {
            if(block_allocated[j] == 0)
            {
                temp=blocks[j]-process[i];
                if(temp >= 0)
                {
                    block_allocated[j]=1;
                    process_allocated[i]=1;
                    block_index[i]=j;
                    fragments[j]=temp;
                    break;
                }
            }
        }
        if(temp < 0)
        {
            block_index[i]=-1;
        }
    }
    printf("Block No\t|Block Size\t|Process No\t|Process Size\t|Fragmentation\t|\n");
    for(j=0;j<nob;j++)
    {
        allocated_process_size=-1;
        for(i=0;i<nop;i++)//finding which process i is allocated to the block j
        {
            if(block_index[i] == j)
            {
                allocated_process_size=process[i];
                break;
            }
        }
        if(allocated_process_size!=-1)
        {
            printf("%d\t\t|%d\t\t|%d\t\t|%d\t\t|%d\t\t|\n",j+1,blocks[j],i+1,allocated_process_size,fragments[j]);
        }
        else
        {
            printf("%d\t\t|%d\t\t|-\t\t|-\t\t|%d\t\t|\n",j+1,blocks[j],fragments[j]);
        }
    }
    for(i=0;i<nop;i++)
    {
        if(process_allocated[i]==0)
        {
            printf("Process %d with size %d is not allocated\n",i+1,process[i]);
        }
    }
}

void BestFit()
{
    int fragments[size],blocks_allocated[size],process_allocated[size],block_index[size];
    int i,j,temp;
    int bestfit_index,minfragment;
    int allocation_process_size;
    for(i=0;i<nob;i++)
    {
        blocks_allocated[i]=0;
        fragments[i]=blocks[i];
    }
    for(i=0;i<nop;i++)
    {
        process_allocated[i]=0;
    }
    for(i=0;i<nop;i++)
    {
        bestfit_index=-1;
        minfragment=10000;
        for(j=0;j<nob;j++)
        {
            if(blocks_allocated[j] == 0)
            {
                temp=blocks[j]-process[i];
                if(temp >= 0 && temp < minfragment)
                {
                    bestfit_index=j;
                    minfragment=temp;
                }
            }
        }
        if(bestfit_index != -1)
        {
             blocks_allocated[bestfit_index]=1;
             process_allocated[i]=1;
             block_index[i]=bestfit_index;
             fragments[bestfit_index]=minfragment;
        }
        else
        {
            block_index[i]=-1;
        }
    }
    printf("Block No\t|Block Size\t|Process No\t|Process Size\t|Fragmentation\t|\n");
    for(j=0;j<nob;j++)
    {
        allocation_process_size=-1;
        for(i=0;i<nop;i++)
        {
            if(block_index[i] == j)
            {
                allocation_process_size=process[i];
                break;
            }
        }
        if(allocation_process_size!=-1)
        {
            printf("%d\t\t|%d\t\t|%d\t\t|%d\t\t|%d\t\t|\n",j+1,blocks[j],i+1,allocation_process_size,fragments[j]);
        }
        else
        {
            printf("%d\t\t|%d\t\t|-\t\t|-\t\t|%d\t\t|\n",j+1,blocks[j],fragments[j]);
        }
    }
    for(i=0;i<nop;i++)
    {
        if(process_allocated[i] == 0)
        {
            printf("Process %d with size %d is not allocated\n",i+1,process[i]);
        }
    }
}

void WorstFit()
{
    int fragments[size],blocks_allocated[size],process_allocated[size],block_index[size];
    int i,j,temp;
    int worstfit_index,maxfragment;
    int allocation_process_size;
    for(i=0;i<nob;i++)
    {
        blocks_allocated[i]=0;
        fragments[i]=blocks[i];
    }
    for(i=0;i<nop;i++)
    {
        process_allocated[i]=0;
    }
    for(i=0;i<nop;i++)
    {
        worstfit_index=-1;
        maxfragment=-10000;
        for(j=0;j<nob;j++)
        {
            if(blocks_allocated[j] == 0)
            {
                temp=blocks[j]-process[i];
                if(temp >= 0 && temp > maxfragment)
                {
                    worstfit_index=j;
                    maxfragment=temp;
                }
            }
        }
        if(worstfit_index != -1)
        {
             blocks_allocated[worstfit_index]=1;
             process_allocated[i]=1;
             block_index[i]=worstfit_index;
             fragments[worstfit_index]=maxfragment;
        }
        else
        {
            block_index[i]=-1;
        }
    }
    printf("Block No\t|Block Size\t|Process No\t|Process Size\t|Fragmentation\t|\n");
    for(j=0;j<nob;j++)
    {
        allocation_process_size=-1;
        for(i=0;i<nop;i++)
        {
            if(block_index[i] == j)
            {
                allocation_process_size=process[i];
                break;
            }
        }
        if(allocation_process_size!=-1)
        {
            printf("%d\t\t|%d\t\t|%d\t\t|%d\t\t|%d\t\t|\n",j+1,blocks[j],i+1,allocation_process_size,fragments[j]);
        }
        else
        {
            printf("%d\t\t|%d\t\t|-\t\t|-\t\t|%d\t\t|\n",j+1,blocks[j],fragments[j]);
        }
    }
    for(i=0;i<nop;i++)
    {
        if(process_allocated[i] == 0)
        {
            printf("Process %d with size %d is not allocated\n",i+1,process[i]);
        }
    }
}

void main()
{
    int i;
    printf("How many blocks ? : ");
    scanf("%d",&nob);
    for(i=0;i<nob;i++)
    {
        printf("Enter the size of Block %d : ",i+1);
        scanf("%d",&blocks[i]);
    }
    printf("How many processes ? : ");
    scanf("%d",&nop);
    for(i=0;i<nop;i++)
    {
        printf("Enter the size of Process %d : ",i+1);
        scanf("%d",&process[i]);
    }
    printf("\nFIRST FIT MEMORY ALLOCATION\n");
    FirstFit();
    printf("\nBEST FIT MEMORY ALLOCATION\n");
    BestFit();
    printf("\nWORST FIT MEMORY ALLOCATION\n");
    WorstFit();
}
