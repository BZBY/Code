#include<cstdio>
#include<cstdlib>
#include<ctime>
int main()
{
	srand(time(0));
	int a=rand()%100;
	printf("%d\n",a+1);
}
