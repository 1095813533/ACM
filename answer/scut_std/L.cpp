#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    string str;
    cin >> n;
    while (n-- > 0) {
        cin >> str;
        if (str == "Scissors") cout << "Rock\n";
        if (str == "Rock") cout << "Paper\n";
        if (str == "Paper") cout << "Scissors\n";
    }
    return 0;
}
