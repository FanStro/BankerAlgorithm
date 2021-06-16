  #include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define False 0
#define True 1
/********��Ҫ���ݽṹ********/
char NAME[100]={0};//��Դ������ ��ֻ���ǵ����ַ�
int Max[100][100]={0};//����������
int Available[100]={0};//������Դ����
int Allocation[100][100]={0};//ϵͳ�ѷ������
int Need[100][100]={0};//����Ҫ��Դ����
int Request[100]={0};//������Դ����
int Security[100]={0};//��Ű�ȫ����
int Work[100]={0};//���ϵͳ���ṩ��Դ
int M=100;//���̵������
int N=100;//��Դ�������

/********��ʼ�����ݣ����������������Դ���ࡢ������Դ������������
�����̵���Դ�ѷ��������������̶���Դ����������ȡ�********/
void init()
{
	/* mΪ���̸�����������������nΪ��Դ���࣬������������*/
    int i,j,m,n;
	int number,flag;
	char name;//������Դ����
	int temp[100]={0};//ͳ���Ѿ��������Դ
	printf("ϵͳ������Դ����Ϊ:");
	scanf("%d",&n);
	N=n;
	for(i=0;i<n;i++)//������Դ��Ϣ����Դ���Ƽ�����
	{
		printf("��Դ%d������:",i);
		scanf("%s",&name); //������%c,�������
		NAME[i]=name;
		printf("��Դ%c�ĳ�ʼ����Ϊ:",name);
		scanf("%d",&number);
		Available[i]=number;
	}
	printf("\n");
	printf("��������̵�����:");
	scanf("%d",&m);
	M=m;
	printf("����������̵������������ֵ)[Max]:\n");
	for(i=0;i<m;i++)//����Max����
		for(j=0;j<n;j++)
			scanf("%d",&Max[i][j]);
	do{
		flag=0;
		printf("������������Ѿ��������Դ��[Allocation]:\n");
		for(i=0;i<m;i++)
		  for(j=0;j<n;j++){
			scanf("%d",&Allocation[i][j]);
			if(Allocation[i][j]>Max[i][j])
               flag=1;
			Need[i][j]=Max[i][j]-Allocation[i][j];
			temp[j]+=Allocation[i][j];//ͳ���Ѿ���������̵���Դ��Ŀ
		   }
		if(flag==1)
			printf("�������Դ�������������������������!\n");
	}while(flag);
	for(j=0;j<n;j++)
		Available[j]=Available[j]-temp[j];//ʣ�µĿ�����Դ=��ʼ������Դ-�ѷ�����Դ
}

/********��ʾ��Դ�������********/
void showdata()
{
	int i,j;
	printf("*************************************************************\n");
	printf("ϵͳĿǰ���õ���Դ[Available]:\n");
	for(i=0;i<N;i++)  //���������Դ��
        printf("%c  ",NAME[i]);
	printf("\n");
	for (j=0;j<N;j++)
        printf("%d  ",Available[j]);//���������Դ������
	printf("\n");
	printf("ϵͳ��ǰ����Դ����������£�\n");
	printf("           Max   Allocation    Need\n");
	printf("������     ");
	for(j=0;j<3;j++)
{
		for(i=0;i<N;i++)
			printf("%c ",NAME[i]);
		printf("      ");
	}
	printf("\n");
	for(i=0;i<M;i++)
{
		printf(" P%d        ",i);
	    for(j=0;j<N;j++)
			printf("%d  ",Max[i][j]);
		printf("    ");
		for(j=0;j<N;j++)
			printf("%d  ",Allocation[i][j]);
		printf("    ");
		for(j=0;j<N;j++)
			printf("%d  ",Need[i][j]);
		printf("\n");
	}
}

/********���Է�����Դ********/
int test(int i)//������Դ����
{
	int j;
	//for(j=0;j<M;j++)
	for(j=0;j<N;j++)
	{
		Available[j]=Available[j]-Request[j];
		Allocation[i][j]=Allocation[i][j]+Request[j];
		Need[i][j]=Need[i][j]-Request[j];
	}
	return 1;
}

/********��ȫ���㷨********/
/*
�ӵ�һ�����̿�ʼ��飬���Ƿ����н��̶�����˳���������
*/
int safe()
{
	int i,j,k=0,m,apply;
	int Finish[100]={0};
	//for (j=0;j<M;j++)
	for(j=0;j<N;j++)
        Work[j]=Available[j];

	for(i=0;i<M;i++)
	{
		apply=0;
		for(j=0;j<N;j++)
		{
			if (Finish[i]==False&&Need[i][j]<=Work[j])
			{
				apply++;//������Դ���ͼ���
				if(apply==N)//�鿴���п�����Դ�Ƿ����ĳһ���̵�����
				{  //ֱ��ÿ����Դ��������С��ϵͳ��������Դ���ſɷ���
					for(m=0;m<N;m++)
				        Work[m]=Work[m]+Allocation[i][m];//i�Ž���ִ����ɣ��ͷ���Դ���ı�ɷ�����Դ��
					Finish[i]=True;
					Security[k]=i; //Security�б��氲ȫ����
					i=-1; //��֤ÿ�β�ѯ���ӵ�һ�����̿�ʼ
					k++;
				}
			}
		}
	}
	for(i=0;i<M;i++){
		if(Finish[i]==False){
			printf("ϵͳ����ȫ\n");//���ɹ�ϵͳ����ȫ
			return -1;
		}
	}
    printf("ϵͳ�ǰ�ȫ��!\n");//�����ȫ������ɹ�
    printf("����һ����ȫ����:");
	for(i=0;i<M;i++){//������н�������
		printf("P%d",Security[i]);
		if(i<M-1)
			printf("->");
	}
	printf("\n");
	return 0;
}

/********�������м��㷨��������Դ�����Է���********/
void bank()
{
	char ch;
	int i,j;
	ch='y';
	printf("���������������Դ�Ľ��̺�(0-%d):",M-1);  //0---M-1
    scanf("%d",&i);//������������Դ�Ľ��̺�
	printf("���������P%dҪ�������Դ����:\n",i);
	for(j=0;j<N;j++)
	{
		printf("%c:",NAME[j]);
		scanf("%d",&Request[j]);//������Ҫ�������Դ
	}
    for (j=0;j<N;j++){
		if(Request[j]>Need[i][j])//�ж������Ƿ�������������������
		{
			printf("����P%d�������Դ��������Ҫ����Դ",i);
			printf(" ���䲻����������䣡\n");
			ch='n';
			break;
		}
		else {
            if(Request[j]>Available[j])//�ж������Ƿ���ڵ�ǰ�ɷ�����Դ�������������
			{
				printf("����&d�������Դ����ϵͳ���ڿ����õ���Դ",i);
				printf("\n");
				printf(" ϵͳ�����㹻��Դ���������!\n");
				ch='n';
				break;
			}
		}
    }
   if(ch=='y') {
		test(i);//���ݽ����������任��Դ
		showdata();//���ݽ�����������ʾ�任�����Դ
		safe();//���ݽ����������������м��㷨�ж�
    }
}


int main()//������
{
	char choice;
	printf("\t---------------------------------------------------\n");
	printf("\t||                                               ||\n");
	printf("\t||               ���м��㷨��ʵ��                ||\n");
	printf("\t||                                               ||\n");
	printf("\t||                                               ||\n");
	printf("\t||                     �ڴ��������������С��    ||\n");
	printf("\t||                                               ||\n");
	printf("\t---------------------------------------------------\n");
	init();//��ʼ������
    showdata();//��ʾ������Դ
    safe();//�����м��㷨�ж�ϵͳ��ǰ�Ƿ�ȫ (�Ƿ����ȫ��������)
		printf("*************************************************************\n");
		printf("\n");
		printf("\n");
		printf("\t-------------------���м��㷨��ʾ------------------\n");
		printf("                     R(r):�������   \n");
		printf("                     E(e):�˳�       \n");
		printf("\t---------------------------------------------------\n");
		printf("��ѡ��");
		scanf("%s",&choice);
	while(choice)
	{
		switch(choice)
		{
			case 'r':
			case 'R':
				bank();break;
			case 'e':
			case 'E':
				exit(0);//break;
			default: printf("����ȷѡ��!\n");break;
		}
	}
}

