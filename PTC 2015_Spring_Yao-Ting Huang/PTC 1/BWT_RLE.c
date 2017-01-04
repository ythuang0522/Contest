#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define size 500

int cmp(const void *a,const void *b)
{
    return strcmp((char*)a,(char*)b);
}

void reverse (char *in)
{
	int i,back;
	char temp;

	for(i=0,back=strlen(in)-1;i<strlen(in)/2;i++,back--)
	{
		temp = in[i];
		in[i] = in[back];
		in[back] = temp;
	}
	return;
}

void RLE_decoding (char *in)
{
	int i,j,p,num;
	char out[size]={0};

	for(i=0,p=0,num=0;i<strlen(in);i++)
	{
		if(in[i]>='0' && in[i]<='9')
		{
			num *= 10;
			num += in[i]-'0';
		}
		else
		{
			for(j=0;j<num;j++)
				out[p++] = in[i];
			num = 0;
		}
	}
	memcpy(in,out,sizeof(out));
	return;
}

void RLE_encoding (char *in)
{
	int i,j,p,num;
	char out[size]={0};
	char zero[10]={0};
	char ch_num[10]={0};
	char con = 0;

	for(i=0,p=0,num=0,con=0;i<strlen(in);i++)
	{
		if( con!=0 && con!=in[i] )
		{
			memcpy(ch_num,zero,sizeof(zero));
			j=0;
			while(num>0)
			{
				ch_num[j++]= num%10 +'0' ;
				num /= 10;
			}
			reverse(ch_num);

			for(j=0;j<strlen(ch_num);j++)
				out[p++] = ch_num[j];

			out[p++] = con;
			con = in[i];
			num = 1;
		}
		else if( con==0 || con==in[i] )
		{
			if(con==0)con = in[i];
			num++;
		}
	}
	memcpy(ch_num,zero,sizeof(zero));
	j=0;
	while(num>0)
	{
		ch_num[j++]= num%10 +'0' ;
		num /= 10;
	}
	reverse(ch_num);
	for(j=0;j<strlen(ch_num);j++)
		out[p++] = ch_num[j];

	out[p++] = con;

	memcpy(in,out,sizeof(out));
	return;
}

void BWT_decoding(char *input,int search_num)
{
	char origin[size][size]={0};
	char sort[size][size]={0};
	int len = strlen(input);
	int i,p;

	for(i=0;i<=len+1;i++) origin[i][0] = input[i];

	for(p=1;p<=len;p++)
	{
		memcpy(sort,origin,sizeof(origin));
		qsort(sort, len, sizeof(sort[0]), cmp);
		for(i=0;i<len;i++) origin[i][p] = sort[i][p-1];
	}

	memcpy(input,sort[search_num-1],sizeof(sort[0]));
	return;
}

void BWT_encoding(char *input)
{
	char origin[size][size]={0};
	char sort[size][size]={0};
	int len = strlen(input);
	int i,j;

	for(i=0;i<len;i++) origin[0][i] = input[i];
	for(i=1;i<len;i++)
	{
		for(j=0;j<len-1;j++)
			origin[i][j] = origin[i-1][j+1];
		origin[i][j] = origin[i-1][0];
	}
	memcpy(sort,origin,sizeof(origin));
	qsort(sort, len, sizeof(sort[0]), cmp);

	for(i=0;i<len;i++) input[i] = sort[i][len-1];

	return;
}

int main()
{
	char input[size]={0};
	char end[5]={"END"};
	int num;

    FILE * pFile = fopen("testdata.in.txt", "r");
    FILE * pFileOut = fopen("testdata.out.txt", "w");

	while(fscanf(pFile, "%s %d",input,&num)!=EOF)
	{
		if( num==0 && !strcmp(input,end) ) break;

		RLE_decoding(input);
		BWT_decoding(input,num);
		reverse(input);
		BWT_encoding(input);
		RLE_encoding(input);
		fprintf(pFileOut, "%s\n",input);
	}

	return 0;
}

