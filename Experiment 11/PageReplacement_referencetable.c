                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  Page_Replacement.c                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 #include <stdio.h>
#include <stdlib.h>
#define size 25

int rs[size],n,capacity;

void fifo()
{
    int frames[size];
    int pageFault=0;
    int frameIndex=0;
    int i,j,pageExists;
    for(i=0;i<capacity;i++)
    {
        frames[i]=-1;
    }
    for(i=0;i<n;i++)
    {
        pageExists=0;
        for(j=0;j<capacity;j++)
        {
            if(frames[j] == rs[i])
            {
                pageExists=1;
                break;
            }
        }
        if(pageExists == 0)
        {
            frames[frameIndex]=rs[i];
            frameIndex=(frameIndex+1)%capacity;
            pageFault++;
        }
        printf("Frames : ");
        for(j=0;j<capacity;j++)
        {
            if(frames[j] != -1)
            {
                printf("%d ",frames[j]);
            }
            else
            {
                printf("- ");
            }
        }
        printf("\n");
    }
    printf("Number of PageFaults (FIFO) : %d\n",pageFault);
}

void lru()
{
    int frames[size],recent[size];
    int i,j,k,pageExists;
    int pageFaults=0;
    int index,oldest;
    for(i=0;i<capacity;i++)
    {
        frames[i]=-1;
        recent[i]=0;
    }
    //recent[j]=k means frame[i]=p page was used at 'k'th time in system
    //Here time can be represented by value i in the following for loop
    //Logic is those page in the memory will be replaced which has the least time in the recent[]
    for(i=0;i<n;i++)
    {
        pageExists=0;
        for(j=0;j<capacity;j++)
        {
            if(frames[j] == rs[i])
            {
                pageExists=1;
                recent[j]=i;
                break;
            }
        }
        if(pageExists == 0)
        {
            oldest=recent[0];
            index=0;
            for(k=0;k<capacity;k++)
            {
                if(frames[k] == -1)  //in case of free frames
                {
                    index=k;
                    break;
                }
                if(recent[k] < oldest)
                {
                    oldest=recent[k];
                    index=k;
                }
            }
            frames[index]=rs[i];
            recent[index]=i;
            pageFaults++;
        }
        printf("Frames : ");
        for(j=0;j<capacity;j++)
        {
            if(frames[j] != -1)
            {
                printf("%d ",frames[j]);
            }
            else
            {
                printf("- ");
            }
        }
        printf("\n");
    }
    printf("Number of PageFaults (LRU) : %d\n",pageFaults);
}
/*
void lfu()
{
    int frames[size],recent[size],count[size];
    int i,j,k;
    int oldest,index,mincount,pageExists;
    int pageFaults=0;
    for(i=0;i<capacity;i++)
    {
        frames[i]=-1;
        recent[i]=0;
        count[i]=0;
    }
    for(i=0;i<n;i++)
    {
        pageExists=0;
        for(j=0;j<capacity;j++)
        {
            if(frames[j] == rs[i])
            {
                pageExists=1;
                count[j]++;
                recent[j]=i;
                break;
            }
        }
        if(pageExists == 0)
        {
            oldest=recent[0];
            index=0;
            mincount=count[0];
            for(k=1;k<capacity;k++)
            {
                if(count[k] < mincount || count[k]==mincount && recent[k] < oldest)
                {
                    oldest=recent[k];
                    index=k;
                    mincount=count[k];
                }
            }
            frames[index]=rs[i];
            recent[index]=i;
            count[index]=1;
            pageFaults++;
        }
        printf("Frames : ");
        for(j=0;j<capacity;j++)
        {
            if(frames[j] != -1)
            {
                printf("%d ",frames[j]);
            }
            else
            {
                printf("- ");
            }
        }
        printf("\n");
    }
    printf("Number of PageFaults (LFU) : %d\n",pageFaults);
}
*/
void lfu_ref()
{
    int frames[size],recent[size],count[8];
    int i,j,k;
    int oldest,index,mincount,pageExists;
    int pageFaults=0;
    for(i=0;i<capacity;i++)
    {
        frames[i]=-1;
        recent[i]=0;
        count[i]=0;
    }
    //reference table
    //assume there is only pages from 0-7
    count[0]=396;count[1]=385;count[2]=311;count[3]=225;count[4]=128;count[5]=442;count[6]=343;count[7]=514;

    //if reference table is not provided taking count from the reference string initially
    /*
    for(i=0;i<n;i++)
    {
        count[rs[i]]++;
    }
    */
    for(i=0;i<n;i++)
    {
        pageExists=0;
        for(j=0;j<capacity;j++)
        {
            if(frames[j] == rs[i])
            {
                pageExists=1;
                //count[rs[i]]++;
                recent[j]=i;
                break;
            }
        }
        if(pageExists == 0)
        {
            oldest=recent[0];
            index=0;
            mincount=count[frames[0]];
            for(k=0;k<capacity;k++)
            {
                if(frames[k] == -1)  //in case of free frames
                {
                    index=k;
                    break;
                }
                if(count[frames[k]] < mincount)
                {
                    oldest=recent[k];
                    index=k;
                    mincount=count[frames[k]];
                }
            }
            frames[index]=rs[i];
            recent[index]=i;
            //count[frames[index]]++;
            pageFaults++;
        }
        printf("Frames : ");
        for(j=0;j<capacity;j++)
        {
            if(frames[j] != -1)
            {
                printf("%d ",frames[j]);
            }
            else
            {
                printf("- ");
            }
        }
        printf("\n");
    }
    printf("Number of PageFaults (LFU) : %d\n",pageFaults);
}

int main()
{
    int i;
    printf("How many pages in the Reference String ? : ");
    scanf("%d",&n);
    printf("Enter the Reference String : ");
    for(i=0;i<n;i++)
    {
        scanf("%d",&rs[i]);
    }
    printf("Enter the capacity of the memory : ");
    scanf("%d",&capacity);
    fifo();
    lru();
    //lfu();
    lfu_ref();
    return 0;
}
