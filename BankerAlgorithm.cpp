  #include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define False 0
#define True 1
/********主要数据结构********/
char NAME[100]={0};//资源的名称 ，只能是单个字符
int Max[100][100]={0};//最大需求矩阵
int Available[100]={0};//可用资源矩阵
int Allocation[100][100]={0};//系统已分配矩阵
int Need[100][100]={0};//还需要资源矩阵
int Request[100]={0};//请求资源向量
int Security[100]={0};//存放安全序列
int Work[100]={0};//存放系统可提供资源
int M=100;//进程的最大数
int N=100;//资源的最大数

/********初始化数据：输入进程数量、资源种类、各种资源可利用数量、
各进程的资源已分配数量、各进程对资源最大需求量等。********/
void init()
{
	/* m为进程个数，即矩阵行数，n为资源种类，即矩阵列数。*/
    int i,j,m,n;
	int number,flag;
	char name;//输入资源名称
	int temp[100]={0};//统计已经分配的资源
	printf("系统可用资源种类为:");
	scanf("%d",&n);
	N=n;
	for(i=0;i<n;i++)//输入资源信息：资源名称及数量
	{
		printf("资源%d的名称:",i);
		scanf("%s",&name); //不能用%c,否则出错
		NAME[i]=name;
		printf("资源%c的初始个数为:",name);
		scanf("%d",&number);
		Available[i]=number;
	}
	printf("\n");
	printf("请输入进程的数量:");
	scanf("%d",&m);
	M=m;
	printf("请输入各进程的最大需求矩阵的值)[Max]:\n");
	for(i=0;i<m;i++)//输入Max矩阵
		for(j=0;j<n;j++)
			scanf("%d",&Max[i][j]);
	do{
		flag=0;
		printf("请输入各进程已经分配的资源量[Allocation]:\n");
		for(i=0;i<m;i++)
		  for(j=0;j<n;j++){
			scanf("%d",&Allocation[i][j]);
			if(Allocation[i][j]>Max[i][j])
               flag=1;
			Need[i][j]=Max[i][j]-Allocation[i][j];
			temp[j]+=Allocation[i][j];//统计已经分配给进程的资源数目
		   }
		if(flag==1)
			printf("分配的资源大于最大需求量，请重新输入!\n");
	}while(flag);
	for(j=0;j<n;j++)
		Available[j]=Available[j]-temp[j];//剩下的可用资源=初始可用资源-已分配资源
}

/********显示资源分配矩阵********/
void showdata()
{
	int i,j;
	printf("*************************************************************\n");
	printf("系统目前可用的资源[Available]:\n");
	for(i=0;i<N;i++)  //输出可用资源名
        printf("%c  ",NAME[i]);
	printf("\n");
	for (j=0;j<N;j++)
        printf("%d  ",Available[j]);//输出可用资源的数量
	printf("\n");
	printf("系统当前的资源分配情况如下：\n");
	printf("           Max   Allocation    Need\n");
	printf("进程名     ");
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

/********尝试分配资源********/
int test(int i)//进行资源分配
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

/********安全性算法********/
/*
从第一个进程开始检查，看是否所有进程都可以顺利运行完成
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
				apply++;//可用资源类型计数
				if(apply==N)//查看所有可用资源是否大于某一进程的需求
				{  //直到每类资源尚需数都小于系统可利用资源数才可分配
					for(m=0;m<N;m++)
				        Work[m]=Work[m]+Allocation[i][m];//i号进程执行完成，释放资源，改变可分配资源数
					Finish[i]=True;
					Security[k]=i; //Security中保存安全序列
					i=-1; //保证每次查询均从第一个进程开始
					k++;
				}
			}
		}
	}
	for(i=0;i<M;i++){
		if(Finish[i]==False){
			printf("系统不安全\n");//不成功系统不安全
			return -1;
		}
	}
    printf("系统是安全的!\n");//如果安全，输出成功
    printf("存在一个安全序列:");
	for(i=0;i<M;i++){//输出运行进程数组
		printf("P%d",Security[i]);
		if(i<M-1)
			printf("->");
	}
	printf("\n");
	return 0;
}

/********利用银行家算法对申请资源进行试分配********/
void bank()
{
	char ch;
	int i,j;
	ch='y';
	printf("请输入请求分配资源的进程号(0-%d):",M-1);  //0---M-1
    scanf("%d",&i);//输入须申请资源的进程号
	printf("请输入进程P%d要申请的资源个数:\n",i);
	for(j=0;j<N;j++)
	{
		printf("%c:",NAME[j]);
		scanf("%d",&Request[j]);//输入需要申请的资源
	}
    for (j=0;j<N;j++){
		if(Request[j]>Need[i][j])//判断申请是否大于需求，若大于则出错
		{
			printf("进程P%d申请的资源大于它需要的资源",i);
			printf(" 分配不合理，不予分配！\n");
			ch='n';
			break;
		}
		else {
            if(Request[j]>Available[j])//判断申请是否大于当前可分配资源，若大于则出错
			{
				printf("进程&d申请的资源大于系统现在可利用的资源",i);
				printf("\n");
				printf(" 系统尚无足够资源，不予分配!\n");
				ch='n';
				break;
			}
		}
    }
   if(ch=='y') {
		test(i);//根据进程需求量变换资源
		showdata();//根据进程需求量显示变换后的资源
		safe();//根据进程需求量进行银行家算法判断
    }
}


int main()//主函数
{
	char choice;
	printf("\t---------------------------------------------------\n");
	printf("\t||                                               ||\n");
	printf("\t||               银行家算法的实现                ||\n");
	printf("\t||                                               ||\n");
	printf("\t||                                               ||\n");
	printf("\t||                     在此输入个人姓名：小贺    ||\n");
	printf("\t||                                               ||\n");
	printf("\t---------------------------------------------------\n");
	init();//初始化数据
    showdata();//显示各种资源
    safe();//用银行家算法判定系统当前是否安全 (是否可以全部运行完)
		printf("*************************************************************\n");
		printf("\n");
		printf("\n");
		printf("\t-------------------银行家算法演示------------------\n");
		printf("                     R(r):请求分配   \n");
		printf("                     E(e):退出       \n");
		printf("\t---------------------------------------------------\n");
		printf("请选择：");
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
			default: printf("请正确选择!\n");break;
		}
	}
}

