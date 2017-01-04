#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define maxLen 100

typedef struct{
    int start;
    int finish;
    int profit;
}customer;

int compare (const void * a, const void * b)
{
    customer *A = (customer *)a;
    customer *B = (customer *)b;

    if(A->finish == B->finish)
	return (A->start - B->start);
    else
    	return ( A->finish - B->finish );
}

int latestNonConflict(customer arr[], int i)
{
    for (int j=i-1; j>=0; j--)
    {
        if (arr[j].finish <= arr[i].start)
            return j;
    }
    return -1;
}


// A recursive function that returns the maximum possible
// profit from given array of jobs.  The array of jobs must
// be sorted according to finish time.
int findMaxProfitRec(customer arr[], int n)
{
    // Base case
    if (n == 1) return arr[n-1].profit;
    
    // Find profit when current job is inclueded
    int inclProf = arr[n-1].profit;
    int i = latestNonConflict(arr, n);
    if (i != -1)
        inclProf += findMaxProfitRec(arr, i+1);
    
    // Find profit when current job is excluded
    int exclProf = findMaxProfitRec(arr, n-1);
    
    return inclProf > exclProf ? inclProf:exclProf;
}

// The main function that returns the maximum possible
// profit from given array of jobs
int findMaxProfitRecursion(customer arr[], int n)
{
    // Sort jobs according to finish time
    // sort(arr, arr+n, compare);
//    qsort(arr, n, sizeof(customer), compare);
    
    return findMaxProfitRec(arr, n);
}

int findMaxProfitDP(customer arr[], int n)
{
    // Sort jobs according to finish time
//    qsort(arr, n, sizeof(customer), compare);
    
    // Create an array to store solutions of subproblems.  table[i]
    // stores the profit for jobs till arr[i] (including arr[i])
    int table[n];
    table[0] = arr[0].profit;
    
    // Fill entries in M[] using recursive property
    for(int i=1; i<n; i++)
    {
        // Find profit including the current job
        int inclProf = arr[i].profit;
        int l = latestNonConflict(arr, i);

//        printf("%d %d\n", arr[i].finish, l);
        if (l != -1)
            inclProf += table[l];
        
        // Store maximum of including and excluding
        table[i] = inclProf > table[i-1]? inclProf:table[i-1];
    }
    
    // Store result and free dynamic memory allocated for table[]
    int result = table[n-1];
    // delete[] table;
    
    return result;
}

int main()
{
    int numT;
    
    // num of test cases
    scanf("%d",&numT);
    while(numT>0)
    {
        int numC;
        scanf(" %d", &numC);

        //read customers
        customer allC[numC];
        for(int i=0; i<numC; i++)
        {
            scanf("%d %d %d", &allC[i].start, &allC[i].finish, &allC[i].profit);
        }
            
//        for(int i=0; i<numC; i++)
//        {
//            printf("%d %d %d\n", allC[i].start, allC[i].finish, allC[i].profit);
//        }

        
        qsort(allC, numC, sizeof(customer), compare);

/*        
        for(int i=0; i<numC; i++)
        {
            printf("%d %d %d\n", allC[i].start, allC[i].finish, allC[i].profit);
        }
  */      
        // find last feasible appendable job
        int last[numC];
        last[0]=-1;
        for(int i=numC-1; i>=1; i--)
        {
            int index = -1;
            for(int j=i-1; j>=0; j--)
            {
                if(allC[i].start >= allC[j].finish)
                {
                    index = j;
                    break;
                    // what if multiple tie j
                }
            }
            
            last[i] = index;
            
        }
/*
        for(int i=0; i<=numC-1; i++)
        {
            printf("%d\n", last[i]);
        }
*/

        //compute optimal profits - O(n)
        int profit[numC];
        profit[0] = allC[0].profit;
        
        // DP
        for(int j = 1; j<numC; j++){
            int profitExcluding = profit[j-1];
            int profitIncluding = allC[j].profit;
            if(last[j] != -1){
                profitIncluding += profit[last[j]];
            }
            
            profit[j] = (profitIncluding > profitExcluding)?profitIncluding : profitExcluding;
        }

//        for(int i=0; i<=numC; i++)
//        {
//            printf("%d ", profit[i]);
//        }
        
//        printf("%d\n", profit[numC-1]);
        printf("%d\n", findMaxProfitDP(allC, numC));
        numT--;
    }
    
    return 0;
}


