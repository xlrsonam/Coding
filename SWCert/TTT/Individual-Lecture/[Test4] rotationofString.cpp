#include <iostream>
#include <string>
using namespace std;
#define MX 100007
int lps[MX];
void cal_lps(string &s)
{
	int len = 0, i = 1, m = s.length();
	while (i<m)
	{
		if (s[i] == s[len])
			lps[i++] = ++len;
		else if (len>0)
			len = lps[len - 1];
		else
			lps[i++] = 0;
	}
}
int main()
{
	int t;
	cin >> t;
	for (int tc = 1; tc <= t; tc++)
	{
		string s1, s2;
		int n, m, cnt = 0;
		cin >> s1 >> s2;
		s1 = s1 + s1;
		n = s1.length(), m = s2.length();
		cal_lps(s2);
		for (int i = 0, j = 0; i<n;)
		{
			if (s1[i] == s2[j])
				i++, j++;
			else if (j>0)
				j = lps[j - 1];
			else
				i++;
			if (j == m)
			{
				cnt = i-m;
				break;
			}
		}
		cout << "#" << tc << " " << cnt << endl;
	}
	return 0;
}