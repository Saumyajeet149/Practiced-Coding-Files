#include <iostream>
#include <string>
using namespace std;
int main()
{
    int n,len,i,count;
    cin>>n;
    string s;
    int f[26] = { 0 };
    for(i=0;i<n;i++)
    {
        cin>>s;
        len = s.length();
        for(j=0;j<len;j++)
            f[int(s[j])-97]++;
        for(j=0;j<26;j++)
            if(f[j])
    }
}