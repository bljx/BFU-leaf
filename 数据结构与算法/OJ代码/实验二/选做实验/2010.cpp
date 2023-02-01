#include<iostream>
using namespace std;
int Ackermann(int n, int m)
{
    if (n == 0)
        return m + 1;
    else if (n > 0 && m == 0)
        return Ackermann(n - 1, 1);
    else if(m>0&&n>0)
        return Ackermann(n - 1, Ackermann(n, m - 1));
}
int main()
{
    int n, m;
    while (cin >> n >> m && n != 0 && m != 0)
        cout << Ackermann(n, m) << endl;
    return 0;
}
