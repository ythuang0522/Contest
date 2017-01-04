#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int sc_function(int table[][100],int sc_table[][100],int i,int j);
int main()
{
    char read[2000]= {'\0'};
    int table[100][100]= {0},sc_table[100][100]= {0};
    int i,j,k=2,num;
    time_t st;
    time_t en;
    st=time(&st);
    scanf("%d",&num);
    while(num>0)
    {
        scanf("%s",read);
        for(i=0; i<100; i++)//initial table
            for(j=0; j<100; j++)
            {
                if(i==j)
                    table[i][j]=-1;
                else
                    table[i][j]=0;
            }

        for(i=0; i<strlen(read); i++)//initial sc_table
            for(j=0; j<strlen(read); j++)
            {
                if((read[i]-32==read[j])||(read[j]-32==read[i]))
                    sc_table[i][j]=2;
                else
                    sc_table[i][j]=-1;
            }

        for(k=0; k<strlen(read)-1; k++)//complete the table
            for(i=0,j=1+k; j<strlen(read)&&i<strlen(read); i++,j++)
                table[i][j]=sc_function(table,sc_table,i,j);


        /*for(i=0; i<strlen(read); i++)
        {
            for(j=0; j<strlen(read); j++)
                printf("%d ",sc_table[i][j]);
            printf("\n");
        }
        printf("\n");
        for(i=0; i<strlen(read); i++)
        {
            for(j=0; j<strlen(read); j++)
                printf("%d ",table[i][j]);
            printf("\n");
        }*/
        printf("%d\n",table[0][strlen(read)-1]);
        //        en=time(&en);
        num--;
    }
    return 0;
}

int sc_function(int table[][100],int sc_table[][100],int i,int j)
{
    int k,l=0,m;
    int max_sc[120]= {-1},temp=-10000;
    if(i==j||(i-1)==j)
    {
        max_sc[0]=0;
        max_sc[1]=0;
        max_sc[2]=0;
    }
    else
    {
        max_sc[l]=table[i][j-1]-1;//gap
        l++;
        max_sc[l]=table[i+1][j]-1;//gap
        l++;
        if(sc_table[i][j]==2)//match
        {
            max_sc[l]=table[i+1][j-1]+sc_table[i][j];
            l++;
        }
        else if(sc_table[i][j]==-1)//mismatch
        {
            max_sc[l]=table[i+1][j-1]+sc_table[i][j];
            l++;
        }
    }
    for(k=i+1; i<k&&k<j; k++)
    {
        max_sc[l]=table[i][k]+table[k+1][j];
        l++;
    }
    for(k=0; k<l; k++)
        if(max_sc[k]>temp)
            temp=max_sc[k];
    return temp;
}
