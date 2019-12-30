#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int main()
{
    int i,j,p,q;
    int found;
    int foundfault=0;
    int entries[100000];
    int timeLastUsed[100000];
    for(i=0; i<100000; i++)
    {
        entries[i]=-1;
    }
    for(i=0; i<100000; i++)
    {
        timeLastUsed[i]=INT_MAX-1;
    }
    int numberOfEntries=0;
    int numberOfPages;
    int numberOfPageFaults=0;
    int pageReference=-2;
    scanf("%d",&numberOfPages);
    int Pages[numberOfPages];
    int nextReferenced[numberOfPages];
    for(i=0; i<numberOfPages; i++)
    {
        nextReferenced[i]=INT_MAX;

    }
    for(i=0; i<numberOfPages; i++)
    {
        Pages[i]=-1;
    }

    char algorithm [10];
    scanf("%s",algorithm);
    if(strcmp(algorithm,"OPTIMAL")==0)
    {
        int pointer=0;
        int elementFoundNext=0;
        int z,u;
        int stepsTillNext=0;
        int maxStep;
        int maxStepIndex;
        while (pageReference!=-1)
        {
            scanf("%d",&pageReference);

            if(pageReference!=-1)
            {
                entries[numberOfEntries]=pageReference;
                numberOfEntries++;
            }
        }

        printf("Replacement Policy = OPTIMAL\n");
        printf("-------------------------------------\n");
        printf("Page   Content of Frames\n");
        printf("----   -----------------\n");
        for(i=0; i<numberOfEntries; i++)
        {

            for(u=0; u<numberOfPages; u++)
            {
                nextReferenced[u]=INT_MAX;

            }



            for(j=0; j<numberOfPages; j++)
            {
                if(entries[i]==Pages[j])
                    found=1;
            }
            if(!found)
            {
                if(pointer<numberOfPages)
                {
                    Pages[pointer]=entries[i];
                    pointer++;
                }
                else
                {
                    //Selects the page for which the time to the next reference is the longest
                    //Loop through the pages and write down the steps till next reference or infinity if not found
                    numberOfPageFaults++;
                    foundfault=1;
                    for(q=0; q<numberOfPages; q++)
                    {
                    stepsTillNext=0;
                        for(z=i+1; z<numberOfEntries; z++)
                        {
                            stepsTillNext++;
                            if(Pages[q]==entries[z])
                            {
                                elementFoundNext=1;
                                nextReferenced[q]=stepsTillNext;
                                break;
                            }

                        }
                        if(!elementFoundNext)
                        {
                            nextReferenced[q]=INT_MAX;
                            elementFoundNext=0;

                        }

                    }

                    //Find max value and its index in the nextReferenced array in order for replacement to take place
                    maxStep=nextReferenced[0];
                    maxStepIndex=0;
                    for(q=0; q<numberOfPages; q++)
                    {
                        if(nextReferenced[q]>maxStep)
                        {
                            maxStep=nextReferenced[q];
                            maxStepIndex=q;

                        }

                    }
                    //Replace

                    Pages[maxStepIndex]=entries[i];







                }

            }
            if(foundfault==0)
                printf("%02d     ",entries[i]);
            else
            {
                printf("%02d F   ",entries[i]);
            }
            for(p=0; p<numberOfPages; p++)
            {
                if(Pages[p]!=-1)
                {
                    printf("%02d ",Pages[p]);
                }
            }
            printf("\n");
            found=0;
            foundfault=0;
        }
        printf("-------------------------------------\n");
        printf("Number of page faults = %d\n",numberOfPageFaults);




    }
    else if(strcmp(algorithm,"FIFO")==0)
    {
        int pointer=0;
        while (pageReference!=-1)
        {
            scanf("%d",&pageReference);

            if(pageReference!=-1)
            {
                entries[numberOfEntries]=pageReference;
                numberOfEntries++;
            }
        }

        printf("Replacement Policy = FIFO\n");
        printf("-------------------------------------\n");
        printf("Page   Content of Frames\n");
        printf("----   -----------------\n");

        for(i=0; i<numberOfEntries; i++)
        {
            for(j=0; j<numberOfPages; j++)
            {
                if(entries[i]==Pages[j])
                    found=1;
            }
            if(!found)
            {
                if(Pages[pointer]!=-1)
                {
                    numberOfPageFaults++;
                    foundfault=1;

                }
                Pages[pointer]=entries[i];
                pointer=(pointer+1)%numberOfPages;
            }
            if(foundfault==0)
                printf("%02d     ",entries[i]);
            else
            {
                printf("%02d F   ",entries[i]);
            }
            for(p=0; p<numberOfPages; p++)
            {
                if(Pages[p]!=-1)
                {
                    printf("%02d ",Pages[p]);
                }
            }
            printf("\n");
            found=0;
            foundfault=0;

        }
        printf("-------------------------------------\n");
        printf("Number of page faults = %d\n",numberOfPageFaults);



    }
    else if(strcmp(algorithm,"LRU")==0)
    {
        int pointer=0;
        int timer=0;
        while (pageReference!=-1)
        {
            scanf("%d",&pageReference);

            if(pageReference!=-1)
            {
                entries[numberOfEntries]=pageReference;
                numberOfEntries++;
            }
        }
        printf("Replacement Policy = LRU\n");
        printf("-------------------------------------\n");
        printf("Page   Content of Frames\n");
        printf("----   -----------------\n");
        for(i=0; i<numberOfEntries; i++)
        {
            timer++;
            timeLastUsed[entries[i]]=timer;
            for(j=0; j<numberOfPages; j++)
            {
                if(entries[i]==Pages[j])
                    found=1;
            }
            if(!found)
            {
                if(pointer<numberOfPages)
                {
                    Pages[pointer]=entries[i];
                    pointer++;
                }
                else
                {
                    //Search for the least recentely used page and get its index then replace the new entry with it but we must find the index of the page in the page array
                    numberOfPageFaults++;
                    foundfault=1;
                    int  minTimeAvailable=INT_MAX;
                    int    minTimeIndex=-1;
                    for(p=0; p<numberOfPages; p++)
                    {
                        if(timeLastUsed[Pages[p]]<minTimeAvailable)
                        {
                            minTimeAvailable=timeLastUsed[Pages[p]];
                            minTimeIndex=p;
                        }
                    }
                    Pages[minTimeIndex]=entries[i];



                }




            }


            if(foundfault==0)
                printf("%02d     ",entries[i]);
            else
            {
                printf("%02d F   ",entries[i]);
            }
            for(p=0; p<numberOfPages; p++)
            {
                if(Pages[p]!=-1)
                {
                    printf("%02d ",Pages[p]);
                }
            }
            printf("\n");
            found=0;
            foundfault=0;



        }
        printf("-------------------------------------\n");
        printf("Number of page faults = %d\n",numberOfPageFaults);

    }
    else if (strcmp(algorithm,"CLOCK")==0)
    {

        int pointer=0;
        int additionalBit[numberOfPages];
        for(i=0;i<numberOfPages;i++)
        {
        additionalBit[i]=0;
        }

        while (pageReference!=-1)
        {
            scanf("%d",&pageReference);

            if(pageReference!=-1)
            {
                entries[numberOfEntries]=pageReference;
                numberOfEntries++;
            }
        }

        printf("Replacement Policy = CLOCK\n");
        printf("-------------------------------------\n");
        printf("Page   Content of Frames\n");
        printf("----   -----------------\n");

        for(i=0; i<numberOfEntries; i++)
        {
            for(j=0; j<numberOfPages; j++)
            {
                if(entries[i]==Pages[j]){
                    found=1;
                    additionalBit[j]=1;


                    }
            }
            if(!found)
            {
                if(Pages[pointer]!=-1)
                {
                    numberOfPageFaults++;
                    foundfault=1;

                }
                if(additionalBit[pointer]==0){
                Pages[pointer]=entries[i];
                additionalBit[pointer]=1;
                pointer=(pointer+1)%numberOfPages;
                }
                else
                {

                while(additionalBit[pointer]!=0)
                {
                additionalBit[pointer]=0;
                pointer=(pointer+1)%numberOfPages;
                }
                Pages[pointer]=entries[i];
                additionalBit[pointer]=1;
                pointer=(pointer+1)%numberOfPages;
                }

            }
            if(foundfault==0)
                printf("%02d     ",entries[i]);
            else
            {
                printf("%02d F   ",entries[i]);
            }
            for(p=0; p<numberOfPages; p++)
            {
                if(Pages[p]!=-1)
                {
                    printf("%02d ",Pages[p]);
                }
            }
            printf("\n");
            found=0;
            foundfault=0;

        }
        printf("-------------------------------------\n");
        printf("Number of page faults = %d\n",numberOfPageFaults);







    }


    return 0;
}
