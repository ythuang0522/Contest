#include <cstdio>
#include <vector>
#include <cstring>
//#include <map>
using namespace std;

#define SIZE  2*500+1

typedef vector<int> Graph;

// running 1st DFS on the reverse graph
void dfs_reverse(Graph Grev[], int& t, bool explored[], int finish[], int i)
{
    explored[i] = true;
    for(Graph::iterator it = Grev[i].begin(); it != Grev[i].end(); it++)
        if(!explored[*it])
            dfs_reverse(Grev, t, explored, finish, *it);
    t++;
    finish[i] = t;
}

// running 2nd DFS on the original graph
void dfs(Graph G[], bool explored[], int leader[], int& parent, int i)
{
    explored[i] = true;
    leader[i] = parent;
    for(Graph::iterator it = G[i].begin(); it != G[i].end(); it++)
        if(!explored[*it])
            dfs(G, explored, leader, parent, *it);
}

// check if u & v are in the same connected component
bool stronglyConnected(int leader[], int u, int v)
{
    return leader[u] == leader[v];
}

void addORClauses(Graph G[], Graph Grev[], int N, int u, int v)
{
    // Internally, complement of variable x is represented as N + x.
    if(u > 0)
    {
        if(v > 0)
        {
            G[N+u].push_back(v);
            G[N+v].push_back(u);
            Grev[v].push_back(N+u);
            Grev[u].push_back(N+v);
        }
        else
        {
            G[N+u].push_back(N-v);
            G[-v].push_back(u);
            Grev[N-v].push_back(N+u);
            Grev[u].push_back(-v);
        }
    }
    else
    {
        if(v > 0)
        {
            G[-u].push_back(v);
            G[N+v].push_back(N-u);
            Grev[v].push_back(-u);
            Grev[N-u].push_back(N+v);
        }
        else
        {
            G[-u].push_back(N-v);
            G[-v].push_back(N-u);
            Grev[N-v].push_back(-u);
            Grev[N-u].push_back(-v);
        }
    }
}

void addANDClauses(Graph G[], Graph Grev[], int N, int u, int v)
{
    addORClauses(G, Grev, N, u, v);
    addORClauses(G, Grev, N, -u, v);
    addORClauses(G, Grev, N, u, -v);
}

void addXORClauses(Graph G[], Graph Grev[], int N, int u, int v)
{
    addORClauses(G, Grev, N, u, v);
    addORClauses(G, Grev, N, -u, -v);
}

int main()
{
    // N is the number of variables, M is the number of clauses, numT is number of test cases
    int N, M, numT;

    scanf("%d", &numT);
    for(int i=0; i<numT; i++)
    {
        scanf("%d %d", &N, &M);
        //printf("%d %d\n", N, M);

        // Assuming vertices are labeled 1...V,
        Graph G[SIZE], Grev[SIZE];  //adjacent matrix

        int u, v;   // values of two boolean variables
        char op;    // operator in a clause
        for(int j=0; j<M; j++)
        {
            /*  Each clause is of the form u+v or u*v or u/v
                1 <= x <= N for an uncomplemented variable x
                -N <= x <= -1 for a complemented variable x
                -x is the complement of a variable x
            */
            scanf(" %d %c %d", &u, &op, &v);
            // printf("%d %c %d\n", u, op, v);

            if(op == '+')
                addORClauses(G, Grev, N, u, v);
            else if(op == '*')
                addANDClauses(G, Grev, N, u, v);
            else if(op == '/')
                addXORClauses(G, Grev, N, u, v);
        }

        // 1st run DFS on the reverse graph to get reverse postorder
        bool explored[SIZE];
        memset(explored, false, (2*N+1)*sizeof(bool));

        int t = 0;  // finish time stamp
        int finish[SIZE];   // finish time of each vertex
        int order[SIZE];    // sorted finish time of each vertex
        for(int j=2*N; j>0; j--)
        {
            if(!explored[j])
                dfs_reverse(Grev, t, explored, finish, j);

            // Bucket sort on finish time into order
            order[finish[j]] = j;
        }

        // 2nd run DFS on the actual graph in forward postorder
        memset(explored, false, (2*N + 1)*sizeof(bool));
        int parent=0;       // parent is the representing vertex of each component
        int leader[SIZE];   // component ID is represented by the parent index

        // starting DFS from the largest finish time in order[]
        for(int j=2*N; j>0; j--)
            if(!explored[order[j]])
            {
                parent = order[j];  // parent is the index of starting vertex of each DFS
                dfs(G, explored, leader, parent, order[j]);
            }
        /*
            printf("Original graph :\n");
            for(i=1; i<=2*N; i++)  {
                if(!G[i].empty())   {
                    printf("%d : ", i);
                    for(Graph::iterator it = G[i].begin(); it != G[i].end(); it++)
                        printf("%d ", *it);
                    printf("\n");
                }
            }
            printf("Reverse graph :\n");
            for(i=1; i<=2*N; i++)  {
                if(!Grev[i].empty())   {
                    printf("%d : ", i);
                    for(Graph::iterator it = Grev[i].begin(); it != Grev[i].end(); it++)
                        printf("%d ", *it);
                    printf("\n");
                }
            }
        */
        // check if a variable and its complement belong in the same SCC in reverse postorder
        // map <int, bool> truthAssignment;
        int same;
        for(same=2*N; same>0; same--)
        {
            u = order[same];
            if(u > N)
            {
                if(stronglyConnected(leader, u, u-N)) break;

                // assign truth values to SCC
                //            if(truthAssignment.find(leader[u]) == truthAssignment.end())    {
                //                truthAssignment[leader[u]] = true;
                //                truthAssignment[leader[u-N]] = false;
                //            }
            }
            else
            {
                if(stronglyConnected(leader, u, N+u)) break;

                //            if(truthAssignment.find(leader[u]) == truthAssignment.end())    {
                //                truthAssignment[leader[u]] = true;
                //                truthAssignment[leader[N+u]] = false;
                //            }
            }
        }

        if(same > 0)
            printf("No\n");
        else
        {
            printf("Yes\n");

            //        for(int j=1; j<=N; j++)
            //            printf("%d : %s\n", j, truthAssignment[leader[j]] ? "true" : "false");
        }
    }

    return 0;
}

