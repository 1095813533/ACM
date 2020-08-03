# Pollard-Rho算法<br>
题目描述<br>
对于每个数字检验是否是质数，是质数就输出Prime；如果不是质数，输出它最大的质因子是哪个。<br>
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;
char buf[700000000];
int cnt = 0;
ll ans;
template<typename T> inline T read(T a) {
	T res = 0, f = 1;
	char ch = buf[cnt++];
	while (!isdigit(ch)) {
		if (ch == '-') f = -1;
		ch = buf[cnt++];
	}
	while (isdigit(ch)) {
		res = (res<<3)+(res<<1) + ch - 48;
		ch = buf[cnt++];
	}
	return res*f;
}
template<typename T> inline void write(T x) {
	if (x < 0) {
		putchar('-');
		write(-x);
		return;
	}
	if (x > 9) write(x/10);
	putchar(x%10+48);
}
inline ll gcd(ll a, ll b) {
	if (b == 0) return a;
	return gcd(b,a%b);
}
inline ll qpow(ll a, ll b, ll mod) {
	ll res = 1;
	while (b) {
		if (b&1) res = (lll)res*a%mod;
		a = (lll)a*a%mod;
		b >>= 1;
	}
	return res;
}
inline bool test(ll x, ll b) {
	ll k = x-1;
	while (k) {
		ll cur = qpow(b,k,x);
		if (cur!=1 && cur!=x-1) return false;
		if ((k&1)==1 || cur==x-1) return true;
		k >>= 1;
	}
	return true;
}
inline bool Miller_Rabin(ll x) {
	if (x==46856248255981LL || x<2) return false;
	if (x==2 || x==3 || x==7 || x==61 || x==24251) return true;
	return test(x,2)&&test(x,61);
}
inline ll pollard_rho(ll x) {
	ll s = 0, t = 0, c = 1LL*rand()%(x-1)+1;
    ll val = 1;
    for (int goal = 1;; goal<<=1, s=t, val=1) {
        for (int stp = 1; stp<=goal; ++stp) {
            t = ((lll)t*t+c)%x;
            val = (lll)val*abs(t-s)%x;
            if ((stp%127) == 0) {
                ll d = gcd(val,x);
                if (d>1) return d;
            }
        }
        ll d = gcd(val,x);
        if (d>1) return d;
    }
}
inline void findfac(ll x) {
	if (x <= ans || x < 2) return;
	if (Miller_Rabin(x)) {
		ans = ans > x ? ans : x;
		return;
	}
	ll p = x;
	while (p >= x) p = pollard_rho(x);
	while ((x%p) == 0) x /= p;
	findfac(x), findfac(p);
}
int main() {
	fread(buf,1,700000000,stdin);
	int t; t = read(t);
	while (t--) {
		ll n; n = read(n);
		ans = 0;
		findfac(n);
		if (ans == n) puts("Prime");
		else write(ans), putchar('\n'); 
	}
	return 0; 
}
```
