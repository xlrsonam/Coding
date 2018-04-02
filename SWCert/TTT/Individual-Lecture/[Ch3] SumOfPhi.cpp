#if 0
#include<iostream>

using namespace std;

#define MAX 1000001
#define MAXP 80000
bool isPrime[MAX];
int primeN[MAXP];
long long euler[MAX];


void sieve(){

	for (int i = 0; i < MAX; i++) {
		isPrime[i] = true;
		euler[i] = i;
	}

	for (int i = 2; i < MAX; i++){
		if (isPrime[i] == false) continue;

		euler[i] -= 1;
		for (int j = i + i; j < MAX; j += i){	
			isPrime[j] = false;
			euler[j] = (euler[j] * (i - 1)) / i;
		}
	}

	for (int i = 1; i < MAX; i++) euler[i] += euler[i - 1];
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	//freopen("input.txt", "r", stdin);
	cin >> T;

	sieve();
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int a, b;
		cin >> a >> b;

		cout << "#" << test_case << " " << euler[b] - euler[a - 1] << endl;
	}
	return 0;
}
#endif