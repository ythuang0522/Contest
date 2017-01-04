#include<iostream>
#include<fstream>
using namespace std;
struct person
{
    int start_time,finish_time,profit;

};

int main()
{
    ifstream fin("PA.in");
    int case_num,i,j,num,last_P;
    int S[101];
    person P[101];
    fin>>case_num;
    while(case_num--)
    {
        fin>>num;
        for(i=0;i<num;i++)
            fin>>P[i].start_time>>P[i].finish_time>>P[i].profit;//read data

        //sort
        for(i=0;i<num;i++)
        {
            for(j=i+1;j<num;j++)
            {
                if(P[i].finish_time>P[j].finish_time)
                {
                    person tmp=P[i];
                    P[i]=P[j];
                    P[j]=tmp;
                }
            }
        }//sort the finish time



        for(i=0;i<num;i++)
        {
            for(j=i+1;j<num && P[j].finish_time==P[i].finish_time;j++)
            {
                if(P[i].start_time>P[j].start_time)
                {
                    person tmp=P[i];
                    P[i]=P[j];
                    P[j]=tmp;
                }
            }
        }//second sort


        S[0]=P[0].profit;//boundary condition

        for(i=1;i<num;i++)
        {
            last_P=-1;// if last_P == -1, means that no person's finish time is less than or equal to P[i]

            for(j=i-1;j>=0;j--)
            {
                if(P[i].start_time>=P[j].finish_time)
                {
                    last_P=j;// record the last person with finish time less than or equal to P[i]
                    break;
                }
            }

//cout << last_P << endl;

            int tmp=P[i].profit;
            if(last_P>=0)tmp+=S[last_P];

            if(tmp>S[i-1])S[i]=tmp;
            else
                S[i]=S[i-1];
        }//DP
        //for(i=0;i<num;i++)fout<<S[i]<<" ";

        //fout<<endl<<"****************************\n";

        cout<<S[num-1]<<endl;
    }

    return 0;
}

