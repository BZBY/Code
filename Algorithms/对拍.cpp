#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std; 
int main(){
    for(int i=1;i<=10000;i++){
        system("data.exe > date.out");//system:接受字符串参数，且将其当做一个指令。 
        double st=clock();
        system("sss.exe < date.out > sss.out");
        double ed=clock();
        system("pre.exe < date.out > pre.out");
        if(system("fc sfa.out pre.out")){
            cout<<"WA"<<endl;
            return 0; 
        }
        else{
            printf("Ac,测试点 #%d, 用时 %.0lfms\n",i,ed-st);
        }
    }
    return 0;
}
