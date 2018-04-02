#include <iostream>
#include <string>
using namespace std;
#define MX 1001
#define BASE 31
#define MOD 1000000007
typedef long long ll;
int hashFun(string s)
{
	int hash = 0,len=s.length();
	for (int i = 0; i < len; i++)
		hash = ((ll)hash*BASE + (s[i] - 'a'))%MOD;
	return hash;
}
bool isRotation(string a, string b)
{
	int hashA = hashFun(a), hashB = hashFun(b);
	if (hashA == hashB)
		return true;
	int len = a.length(),hashPrev=hashA,hashNext,baseN=1;
	for (int i = 0; i < len; i++)
		baseN = (baseN*BASE)%MOD;
	for (int i = 0; i < len; i++)
	{
		hashNext = (((ll)hashPrev*BASE)%MOD - ((ll)((baseN - 1+MOD)%MOD)*(a[i] - 'a')) % MOD+MOD)%MOD;
		if (hashNext == hashB)
			return true;
		hashPrev = hashNext;
	}
	return false;
}
string findInterestingString(string a[MX],string b[MX],int numPairs)
{
	for (int i = 0; i < numPairs; i++)
		if (isRotation(a[i], b[i]))
			return a[i];
	return "";
}

int main()
{
	int numPairs;
	cin>>numPairs;
	string s1[MX],s2[MX];
	for(int i=0;i<numPairs;i++)
		cin>>s1[i]>>s2[i];
	string ans=findInterestingString(s1,s2,numPairs);
	cout<<ans<<endl;
	return 0;
}