#include <bits/stdc++.h>
using namespace std;

#define MEM(x,y) memset(x,y,sizeof(x))

const int MM = 730 * 330;
int N, M, cnt;
int L[MM], R[MM], D[MM], U[MM], S[MM], C[MM], Row[MM], H[730], ans[90];

void link ( int r, int c ) {
	D[++cnt] = c, U[cnt] = U[c];
	D[U[c]] = cnt, U[c] = cnt;
	S[c] ++, C[cnt] = c, Row[cnt] = r;
	if ( H[r] == -1 ) H[r] = L[cnt] = R[cnt] = cnt;
	else {
		R[cnt] = H[r], L[cnt] = L[H[r]];
		R[L[H[r]]] = cnt, L[H[r]] = cnt;
	}
}

void get ( int i, int j, int k, int &r, int &c1, int &c2, int &c3, int &c4 ) {
	r = ( i*9 + j ) * 9 + k;
	c1 = i*9 + j + 1;
	c2 = 9*9 + i*9 + k;
	c3 = 9*9*2 + j*9 + k;
	c4 = 9*9*3 + ( (i/3) * 3 + (j/3) ) * 9 + k;
}

inline void LINK ( int i, int j, int k ) {
	int r, c1, c2, c3, c4;
	get ( i, j, k, r, c1, c2, c3, c4 );
	link(r,c1),link(r,c2),link(r,c3),link(r,c4);
}

bool init () {
	char ch;
	N = 728, M = 324;
	for ( int i = 0; i <= M; ++ i ) {
		L[i] = i-1, R[i] = i+1;
		U[i] = D[i] = i;
		S[i] = 0;
	}
	L[0] = M, R[M] = 0, cnt = M;
	MEM(H,-1);
	for ( int i = 0; i < 9; ++ i ) {
		for ( int j = 0; j < 9; ++ j ) {
			if ( ! ( cin >> ch ) ) return false;
			if ( ch == '0' ) {
				for ( int k = 1; k <= 9; k ++ ) {
					LINK ( i, j, k );
				}
			} else {
				LINK ( i, j, ch-'0' );
			}
		}
	}
	return true;
}

void DEL( int c ) {
	R[L[c]] = R[c], L[R[c]] = L[c];
	for ( int i = D[c]; i != c; i = D[i] ) {
		for ( int j = R[i]; j != i; j = R[j] ) {
			D[U[j]] = D[j], U[D[j]] = U[j];
			S[C[j]] --;
		}
	}
}

void INS ( int c ) {
	for ( int i = U[c]; i != c; i = U[i] ) {
		for ( int j = L[i]; j != i; j = L[j] ) {
			D[U[j]] = j, U[D[j]] = j;
			S[C[j]] ++;
		}
	}
	R[L[c]] = c, L[R[c]] = c;
}

inline int calR(int r, int n) {
	return (r-1) % n + 1;
}

int DLX( int d ) {
	if ( R[0] == 0 ) {
		int res[10][10];
		for ( int i = 0; i < d; ++ i ) {
			res[ (ans[i]-1) / 81 + 1 ][ (calR(ans[i],81)-1)/9+1 ] = calR(ans[i], 9);
		}
		for ( int i = 1; i <= 9; ++ i ) {
			for ( int j = 1; j <= 9; ++ j ) printf ( j == 1 ? "%d" : " %d", res[i][j]  );
			puts("");
		}
		return 1;
	}
	int mi = 0x7ffffff, c = 0;
	for ( int i = R[0]; i != 0; i = R[i] ) {
		if ( S[i] < mi ) mi = S[i], c = i;
	}
	DEL(c);
	for ( int i = D[c]; i != c; i = D[i] ) {
		ans[d] = Row[i];
		for ( int j = R[i]; j != i; j = R[j] ) DEL(C[j]);
		if ( DLX( d + 1 ) ) return 1;
		for ( int j = L[i]; j != i; j = L[j] ) INS(C[j]);
	}
	INS(c);
	return 0;
}

int read () {
	if ( scanf ( "%d%d", &N, &M ) == EOF ) return 0;
	return 1;
}

void prs () {
	static int f = 0;
	if ( f ++ ) puts("");
	DLX(0);
}

int main () {
	char ch;
	while ( init() ) {
		prs();
	}
	return 0;
}
