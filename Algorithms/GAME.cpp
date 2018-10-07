#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <dos.h>
#include <conio.h>
int x[10000];
int y[10000];
int snakelong=3;
int applex,appley;
char c;
int h=25;
int w=50;
int life=0;
int speed;
int go=5;    //0:front 1:back 2:left 3:right
int eatapple=1;    //0:yes 1:no
int setapple=0;    //0:yes 1:no
void color(int b)
{
    HANDLE hConsole = GetStdHandle((STD_OUTPUT_HANDLE)) ;
    SetConsoleTextAttribute(hConsole,b) ;
}
void gotoxy(int x, int y)
{
        COORD pos;
        pos.X = x;
        pos.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void snakemove(int go)
{
        if(eatapple==0)
        {
            eatapple=1;
            setapple=0;
            snakelong++;
        }
        else
        {
            gotoxy(x[snakelong]+1,y[snakelong]);
            printf("\b ");
        }
        int i;
        for(i=snakelong;i>=2;i--)
        {
            x[i]=x[i-1];
            y[i]=y[i-1];
        }
            if(go==0)
        {
            y[1]--;
            gotoxy(x[1],y[1]);
            printf("■");
        }
        if(go==1)
        {
            y[1]++;
            gotoxy(x[1],y[1]);
            printf("■");
        }
        if(go==2)
        {
            x[1]=x[1]-2;
            gotoxy(x[1],y[1]);
            printf("■");
        }
        if(go==3)
        {
            x[1]=x[1]+2;
            gotoxy(x[1],y[1]);
            printf("■");
        }
}
void printback(int high,int weight)
{
    int i;
    for(i=1;i<=weight;i=i+2)
    {
        gotoxy(i,0);
        printf("□");
    }
    for(i=1;i<=weight;i=i+2)
    {
        gotoxy(i,high-1);
        printf("□");
    }
    for(i=1;i<=high;i++)
    {
        gotoxy(0,i-1);
        printf("□");
    }
        for(i=1;i<=high;i++)
    {
        gotoxy(weight,i-1);
        printf("□");
    }
    gotoxy(w+3,0);
    printf("按空格键暂停");
    gotoxy(w+3,1);
    printf("按wasd控制前后左右与继续");
}
void drawapple()
{
    color(14);
    int i;
    int a=0;
    srand(time(0));
    while(1)
    {
        int a=0;
        applex=(rand()%((w/2)-1))*2+2;
        appley=(rand()%(h-2))+1;
        for(i=1;i<=snakelong;i++)if(applex!=x[i]||appley!=y[i]) a++;
        if(a==snakelong) break;
    }
    gotoxy(applex,appley);
    printf("★");
    setapple=1;
    color(10);
}
int main()
{
    system("chcp 936>NUL");//设置编码为UNICODE
    SetConsoleTitle("贪吃死的yzm by ARG");
    printf("请输入速度等级(1-10)，等级越高吃死的越快，按回车确认:");
    scanf("%d",&speed);
    if(speed<1||speed>10)
    {
        printf("输入错误，按任意键退出！");
        getch();
        exit(0);
    }
    x[1]=10;
    y[1]=10;
    int i;
    gotoxy(0,0);
    for(i=1;i<=1000;i++)printf(" ");
    color(12);
    printback(h,w);
    color(10);
    gotoxy(x[1],y[1]);
    printf("■");
    while(life==0)
    {
            if(kbhit())
        {
        c=getch();
        if(c=='w'&&go!=1) go=0;
        if(c=='s'&&go!=0) go=1;
        if(c=='a'&&go!=3) go=2;
        if(c=='d'&&go!=2) go=3;
        if(c==' ') go=5;
        }
        for(i=2;i<=snakelong;i++)
            if(x[1]==x[i]&&y[1]==y[i])
            {
                life=1;
                break;
            }
        if(life==1) break;
        if(x[1]<=0||x[1]>=w||y[1]<=0||y[1]>=h-1) break;
        if(x[1]==applex&&y[1]==appley)
        {
            eatapple=0;
            Beep(2000,50);
        }
        if(go!=5) snakemove(go);
        if(setapple==0) drawapple();
        gotoxy(w+3,3);
        printf("分数:%d",(snakelong-3)*10);
        Sleep(250-speed*23);
    }
    Beep(350,200);
    Beep(250,200);
    gotoxy(0,h+1);
    printf("你的蛇死了，按任意键退出游戏");
    getch();
    return 0;
}