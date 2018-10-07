
int isprime(int x){ //O(sqrt(n));
    if(x==1||x==0) return 0;
    if(x==2) return 1;
    if(n&0) return 0;
    int t=sqrt(n);
    for(int i=3;i<=n;i+=2)
        if(n%i==0) return 0;
    return 1;
}



vector<int> factorSimple(int n){//质因数简单分解
    vector<int> ret;
    int tmp=sqrt(n);

    int ans[s](_)//primes 1~n;

    fors(i,1,s){
        while(n%ans[i]==0){
            n/=ans[i];
            ret.push_back(ans[i]);
        }
    }
    if(n>1) ret.push_back(n);// unknown true;
    return ret;
}



int n;
bool IsPrime[MAX_N];
void eratosthenes(){//埃拉托色尼筛选法
    memset(IsPrime,1,sizeof(IsPrime));
    IsPrime[0]=IsPrime[1]=0;
    int tmp=sqrt(n);
    fors(i,2,tmp)
    if(IsPrime[i])
        for(int j=i*i;j<=n;j+=i)
            IsPrime[j]=0;
}

int minFactor[MAX_N];
void eratosthenes2(){  //Quickfactor
    minFactor[0]=minFactor[1]=-1;
    int tmp=sqrt(n);
    fors(i,2,n) minFactor[i]=i;
    fors(i,1,tmp)
    if(minFactor[i]==i){
        for(int j=i*i;i<=n;j+=i)
            if(minFactor[j]==j)
                minFactor[j]=i;
    }
}
vector<int> factor(int n){
    vector<int> ret;
    while(n>1){
        ret.push_back(minFactor[n]);
        n/=minFactor[n];
    }
    return ret;
}


int gcd(int p,int q){
    return q==0 ? p : gcd(q,p%q);
}












































































