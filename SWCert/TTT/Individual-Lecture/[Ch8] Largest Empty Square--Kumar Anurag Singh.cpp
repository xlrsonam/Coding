
#include <stdio.h>
using namespace std;

#define M 1002 
int mat[M][M]; // input and dp matrix.

/* Get minimum of 3 numbers */
int get_min(int a, int b, int c)
{
	int ret = a;
	if (b < ret)ret = b;
	if (c < ret)ret = c;
	return ret;
}

int calculate(int n)
{
	int ans = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
		{
			if (i == 0 || j == 0 || mat[i][j])
			{
				mat[i][j] = !mat[i][j];
				continue;
			}
			// Dynamic programming using previous values.
			mat[i][j] = 1 + get_min(mat[i - 1][j - 1], mat[i][j - 1], mat[i - 1][j]);
			if (ans < mat[i][j]) // Storing the maximum values.
				  ans = mat[i][j]; // Updating the answer
		}
	return ans;
}

int main()
{
	int T;
	scanf("%d",&T);
	for (int test_case = 1; test_case <= T; ++test_case)
	{
		int n; // size of input matrix.
		scanf("%d",&n);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				scanf("%1d",&mat[i][j]);
		printf("#%d %d\n", test_case, calculate(n));
	}
	return 0;
}