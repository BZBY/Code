#include <iostream>
#include <cstring>//头文件 
using namespace std;//名字空间 
struct lucky{
    int four,seven;//定义一个结构体为lucky 
};
lucky f[1010000];//定义f数组。 
bool pd(lucky a,lucky b)//判断函数 
{
    if(a.four+a.seven+1>b.four+b.seven)//如果f[i-7].four与f[i-7].seven的两个和大于f[i]的两个数之和
    {
        return false;//不能替换 
    }
    if(a.four+a.seven+1<b.four+b.seven)//如果f[i-7].four与f[i-7].seven的两个和小于f[i]的两个数之和
    {
        return true;//可以替换 
    }
    return a.four>b.four;//如果相等，则判断他们4的个数 
}
int main()
{
    int n;
    cin>>n;//读入 
    for(int i=1; i<=n; i++)
    {
        f[i].seven=10000000;//赋值为很大的一个数 
        f[i].four=10000000;//赋值为很大的一个数 
    }
    f[0].seven=0;//确定边界 
    f[0].four=0;
    for(int i=4; i<=n; i++)//循环 
    {
        if(i-4>=0)//如果i不越界 
        {
            f[i].four=f[i-4].four+1;
            f[i].seven=f[i-4].seven;
        }
        if(i-7>=0)//如果i大于7 
        {
            if(pd(f[i-7],f[i]))//满足条件 
            {
                f[i].four=f[i-7].four;
                f[i].seven=f[i-7].seven+1;
            }
        }
    }
    if(f[n].four>=1000000||f[n].seven>=1000000)//如果它有一项很大 
    {
        cout<<-1;//就没有解，输出-1 
    }
    else
    {
        for(int i=1; i<=f[n].four; i++)
        cout<<4;//先输出所有的4 
        for(int i=1; i<=f[n].seven; i++)
        cout<<7;//再输出所有的7 
    }
    return 0;
}