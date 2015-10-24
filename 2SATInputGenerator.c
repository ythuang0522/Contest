#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    // N is the number of variables, M is the number of clauses, numT is number of test cases
    int numT;

    scanf("%d", &numT);
    for(int i=0; i<numT; i++)
    {
        int N=(rand()%500)+1;
        int M=(rand()%10000)+1;

        printf("%d %d\n", N, M);
        for(int j=0; j< M; j++)
        {
            // generate two random variables
            int xi = (rand()%N)+1;
            int xj = (rand()%N)+1;

            // random negation
            xi = (rand()%2)?xi:-xi;
            xj = (rand()%2)?xj:-xj;

            // random operator
            char op = rand()%3;
            if(op==0)
                op='+';
            else if(op==1)
                op='*';
            else if(op==2)
                op='/';

            if(j<M-1)
                printf("%d %c %d ", xi, op, xj);
            else
                printf("%d %c %d\n", xi, op, xj);
        }
    }
}

