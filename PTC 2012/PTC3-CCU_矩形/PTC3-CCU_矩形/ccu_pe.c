#include <stdio.h>
#include <stdlib.h>
int x=0,y=0;
int i=0;


void square(int K, int X, int Y)
{
    int s1,s2,s3,s4;
    s1=X-2*K;
    s2=X+2*K;
    s3=Y-K;
    s4=Y+K;


    if((s1<=x) && (s2>=x) && (s3<=y) && (s4>=y))
    i++;

    if(K/2!=0)
    {
        square(K/2,s1,s3);
        square(K/2,s1,s4);
        square(K/2,s2,s3);
        square(K/2,s2,s4);
    }
    return;
}


int main()
{

    int k;

    while(1)
   {
        scanf("%d",&k);
        scanf("%d",&x);
        scanf("%d",&y);
        if(k==0 && x==0 && y==0)
        {return 0;}
        else if(k>256 || k<1)
        {
            printf("illegal input!");
        }
        else if(x>2048 || x<0 || y>2048 || y<0)
        {
            printf("illegal input!");
        }
        else
        {
        square(k,1024,1024);
        printf("%d",i);
        printf("\n");
        i=0;
        }
    }

return 0;


}

