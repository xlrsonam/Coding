#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

const int max_  = 500001;
const int mult = 259;
const int mod = 10000019;
char str[max_];
char rot[max_];

long long hash(const char* s, int length)
{
	long long h = s[0];
	for (int i = 1; i < length; ++i)
	{
		h = (h * mult + s[i]) % mod;
	}
	return h;
}

int rotation_v1()
{
	int length = 0;
	for (; str[length] != 0; ++length);
	
	//compute hash
	long long h = hash(str, length);
	long long  hr = hash(rot, length);
	if (h == hr)
		return 0;

	long long  an1 = 1; //a^(n-1)
	for (int i = 0; i < length - 1; ++i)
		an1 = (an1 * mult) % mod;

	long long  hpre = h;
	for (int i = 0; i < length; ++i)
	{
		int c = str[i];
		long long  hnext = (hpre - ((an1 * c) % mod)) % mod;
		hnext = (hnext + mod) % mod;
		hnext = (hnext * mult) % mod + c;
		hnext = hnext % mod;
		if (hnext == hr)
			return i + 1;
		hpre = hnext;
	}
	return -1;
}

int rotation(int length)
{
	long long h, hr,an=1;
	//compute hash
	if ((h = hash(str, length)) == (hr = hash(rot, length)))
		return 0;

	for (int i = 0; i < length; ++i)
		an = (an * mult) % mod;

	long long  hpre = h;
	for (int i = 0; i < length - 1; ++i)
	{
		int c = str[i];
		long long  hnext = (hpre * mult) % mod;
		hnext -= ((an - 1+mod)%mod*c)%mod;
		hnext = (hnext + mod) % mod; 
		if (hnext == hr)
			return i + 1; //TODO: do exact comparison
		hpre = hnext;
	}
	return -1;
}

int main(void)
{
	int test_case;
	int T;
	setbuf(stdout, NULL);
	scanf("%d", &T);
	for (test_case = 1; test_case <= T; ++test_case)
	{
		scanf("%s", str);
		scanf("%s", rot);
		int length = 0;
		for (; str[length] != 0; ++length);
		printf("#%d %d\n", test_case, rotation(length));
	}
	return 0; 
}
#endif