#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define size 500

char Card_Rotation[size][size]={0};

int cmp(const void *a,const void *b){
	return strcmp((char*)a,(char*)b);
}
    
int main()
{
	char card_box[13]={"123456789HIJK"};
	int random_box[size]={0};
	int i,j,k,tmp;
	int player = 20;
	int card   = 20;
	int CRpoint= -1;
	
	srand(time(NULL));
	
	for(i=0;i<player;i++) random_box[i] = i+1;
	for(i=0;i<player;i++)
	{
		j = rand()%player;
		tmp = random_box[i];
		random_box[i] = random_box[j];
		random_box[j] =tmp;
	}
	
	for(i=0;i<player;i++)
	{
		CRpoint++;
		// create origin card
		for(j=0;j<card;j++)
			Card_Rotation[CRpoint][j]=card_box[rand()%13];
		// sort origin card
		qsort(Card_Rotation[CRpoint], j, sizeof(char), cmp);
		// prinf origin card
		printf("%s\n",Card_Rotation[CRpoint]);
		// create rotation string
		for(j=0;j<card-1;j++)
		{
			CRpoint++;
			for(k=0;k<card-1;k++)
				Card_Rotation[CRpoint][k] = Card_Rotation[CRpoint-1][k+1];
			Card_Rotation[CRpoint][k] = Card_Rotation[CRpoint-1][0];
		}	
	}
	// print all string
	//for(j=0;j<=CRpoint;j++) printf("%d\t%s\n",j,Card_Rotation[j]);
	// sorting all string
	qsort(Card_Rotation+1, CRpoint, sizeof(Card_Rotation[0]), cmp);
	// print all string
	//for(j=0;j<=CRpoint;j++) printf("%d\t%s\n",j,Card_Rotation[j]);
	// print last ascii
	for(j=0;j<=CRpoint;j++)
			printf("%c",Card_Rotation[j][card-1]);
	
	printf("\n%d %d",player,card);
	
	for(i=0;i<player;i++) 
		printf(" %d",random_box[i]);
	
	return 0;
}

