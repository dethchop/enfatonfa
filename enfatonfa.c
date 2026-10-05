#include <stdio.h>

#define MAX 10

int n, m;
char symbols[MAX];
int epsilon[MAX][MAX];
int trans[MAX][MAX][MAX];
int closure[MAX][MAX];
int closureSize[MAX];

void findClosure(int state, int visited[])
{
    visited[state] = 1;
    closure[state][closureSize[state]++] = state;

    for(int i=0;i<n;i++)
    {
        if(epsilon[state][i] && !visited[i])
            findClosure(i, visited);
    }
}

int main()
{
    int i,j,k;

    printf("Enter number of states: ");
    scanf("%d",&n);

    printf("Enter number of input symbols: ");
    scanf("%d",&m);

    printf("Enter symbols: ");
    for(i=0;i<m;i++)
        scanf(" %c",&symbols[i]);

    printf("\nEnter epsilon transition matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d",&epsilon[i][j]);

    printf("\nEnter transition table:\n");

    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            printf("Number of transitions from q%d using %c: ",i,symbols[j]);
            int count;
            scanf("%d",&count);

            for(k=0;k<count;k++)
            {
                int x;
                scanf("%d",&x);
                trans[i][j][x]=1;
            }
        }
    }


    for(i=0;i<n;i++)
    {
        int visited[MAX]={0};
        closureSize[i]=0;
        findClosure(i,visited);
    }

    printf("\nEpsilon Closures\n");

    for(i=0;i<n;i++)
    {
        printf("EC(q%d) = { ",i);

        for(j=0;j<closureSize[i];j++)
            printf("q%d ",closure[i][j]);

        printf("}\n");
    }

    printf("\nEquivalent NFA (without epsilon transitions)\n");

    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            int result[MAX]={0};

            for(k=0;k<closureSize[i];k++)
            {
                int s=closure[i][k];

                for(int x=0;x<n;x++)
                {
                    if(trans[s][j][x])
                    {
                        for(int y=0;y<closureSize[x];y++)
                            result[closure[x][y]]=1;
                    }
                }
            }

            printf("δ(q%d,%c) = { ",i,symbols[j]);

            for(k=0;k<n;k++)
                if(result[k])
                    printf("q%d ",k);

            printf("}\n");
        }
    }

    return 0;
}
