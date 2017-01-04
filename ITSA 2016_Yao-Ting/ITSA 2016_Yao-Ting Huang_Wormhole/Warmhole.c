#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define maxLen 200

int sc_function(int table[][maxLen],int sc_table[][maxLen],int i,int j, int dist);
int main()
{
    int num;
    
    // num of test cases
    scanf("%d",&num);
    while(num>0)
    {
        int matters[maxLen];
        int table[maxLen][maxLen]= {0}, sc_table[maxLen][maxLen]= {0};
        
        int dist, energy;
        scanf(" %d", &dist);
        
        int count = 0;
        scanf(" %d", &energy);
        while(energy!=-1)
        {
            matters[count] = energy;
            scanf(" %d", &energy);
            count++;
        }
        
        //initial DP table
        for(int i=0; i<maxLen; i++)
            for(int j=0; j<maxLen; j++)
            {
                if(i==j)
                    table[i][j] = -(0.2*dist);
                else
                    table[i][j] = 0;
            }

        //initial scoring table for each pair of binding letters
        for(int i=0; i<count; i++)
            for(int j=0; j<count; j++)
            {
                if( matters[i] + matters[j] == dist)
                    sc_table[i][j]=dist;
                else
                    sc_table[i][j] = -abs(matters[i] + matters[j] - dist);
            }

        // Bottom-up DP
        for(int k=0; k<count-1; k++)
            for(int i=0, j=k+1; j<count && i<count; i++,j++)
                table[i][j] = sc_function(table, sc_table, i, j, dist);


        /*
        for(int i=0; i<count; i++)
        {
            for(int j=0; j<count; j++)
                printf("%d\t",sc_table[i][j]);
            printf("\n");
        }
         
        printf("\n");
        for(int i=0; i<count; i++)
        {
            for(int j=0; j<count; j++)
                printf("%d\t",table[i][j]);
            printf("\n");
        }
        */
         
        printf("%d\n",table[0][count-1]);
        
        num--;
    }
    return 0;
}

int sc_function(int table[][maxLen],int sc_table[][maxLen],int i,int j, int dist)
{
    int l=0;
    int max_sc[maxLen+3]= {-1}; // pick max score from all cases
    
    if(i==j||(i-1)==j)
    {
        max_sc[0]=0;
        max_sc[1]=0;
        max_sc[2]=0;
    }
    else
    {
        // case 1: gap
        max_sc[l] = table[i][j-1] - (0.2*dist);
        l++;

        // case 2: gap
        max_sc[l] = table[i+1][j] - (0.2*dist);
        l++;
 
        //case 3: match/mismatch
        if(sc_table[i][j]==dist)//match
        {
            max_sc[l]=table[i+1][j-1]+sc_table[i][j];
            l++;
        }
        else if(sc_table[i][j] < 0)//mismatch
        {
            max_sc[l]=table[i+1][j-1]+sc_table[i][j];
            l++;
        }
        else
            printf("Unexpected case!\n");
    }
    
    // 4th cases: recursive foldings at each partition k
    for(int k=i+1; i<k && k<j; k++)
    {
        max_sc[l]=table[i][k]+table[k+1][j];
        l++;
    }

    int temp=-10000;
    for(int k=0; k<l; k++)
        if(max_sc[k]>temp)
            temp=max_sc[k];
    
    return temp;
}
