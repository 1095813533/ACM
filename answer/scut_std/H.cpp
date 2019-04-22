#include<bits/stdc++.h>
using namespace std;
  
const int N=5e5+5;
const int P=1e9+7;
int n,i,j,ans,a[N],l[N],v[N];
int main()
{
    scanf("%d",&n);
    for(i=1;i<=n;i++)scanf("%d",&a[i]);
    for(i=1;i<=n;i++)
	for(v[i]=a[i],j=l[i]=i;j;j=l[j]-1) {
            v[j]=__gcd(v[j],a[i]);
            while(l[j]>1&&__gcd(a[i],v[l[j]-1])==__gcd(a[i],v[j]))
		l[j]=l[l[j]-1];
            ans=(1LL*v[j]*(j-l[j]+1)+ans)%P;
        }
    printf("%d",ans);
    return 0;
}