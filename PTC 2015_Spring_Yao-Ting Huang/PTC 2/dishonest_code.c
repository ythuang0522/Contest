#include<stdio.h>
#include<stdlib.h>
#define size 500

char ans_table[size][size]= {0};

int cmp(const void *a,const void *b)
{
    return strcmp((char*)a,(char*)b);
}

void BWT_decoding(char *input,int card_length)
{
    char origin[size][size]= {0};
    char sort[size][size]= {0};
    int len = strlen(input);
    int i,p;

    for(i=0; i<=len+1; i++) origin[i][0] = input[i];

    for(p=1; p<=card_length; p++)
    {
        memcpy(sort,origin,sizeof(origin));
        qsort(sort, len, sizeof(sort[0]), cmp);
        for(i=0; i<len; i++) origin[i][p] = sort[i][p-1];
    }

    memcpy(ans_table,sort,sizeof(sort));
    return;
}

int main()
{
    char input[size];
    int players[30];
    int loop,i,player_num,card_num;

    scanf("%d", &loop);
    while(loop--)
    {
        scanf("%s",input);
        scanf("%d %d",&player_num,&card_num);
        for(i=0; i<player_num; i++)
            scanf("%d", &players[i]);

        BWT_decoding(input,card_num);

        for(i=0; i<player_num; i++)
            printf("%s",ans_table[players[i]-1]);

        printf("\n");
    }

    return 0;

}
