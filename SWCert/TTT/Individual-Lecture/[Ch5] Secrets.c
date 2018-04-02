#include <stdio.h>

int max_ans, n;
int vis[12];
int ad_matrix[12][12];
int relation[12];

void dfs(int x, int len)
{
	int i, j;

	vis[x] = 1;
	len++;

	if (len > max_ans)
	{
		max_ans = len;
	}

	for (i = 1; i <= n; i++)
	{
		if (ad_matrix[x][i] == 1 && vis[i] == 0)
		{
			dfs(i, len);
		}
	}

	vis[x] = 0;
}


void init()
{
	int i,j;
	
	max_ans = 0;

	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			ad_matrix[i][j] = 0;
		}

		relation[i] = 0;
	}

}


int main(void)
{
	int test_case;
	int T;

	setbuf(stdout, NULL);
	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case)
	{
		int k, i, j;
		int list[12][12];		

		scanf("%d", &n);                            //scan n = number of students    , k =  number of secrets
		scanf("%d", &k);

		init();                                     //initialization

		for (i = 0; i < k; i++)
		{
			int num, a, b;
			scanf("%d", &num);                      //scan input data for each secret

			scanf("%d", &a);

			for (j = 1; j < num; j++)
			{
				scanf("%d", &b);

				if (ad_matrix[a][b] == 0)           //updation of outdegree in relation array
					relation[a]++;

				ad_matrix[a][b] = 1;                // updation of adjacency matrix

				a = b;
			}
		}

		for (i = 1; i <= n; i++)
		{
			dfs(i, 0);
		}

		printf("#%d", test_case);                   //output

		for (i = 1; i <= n; i++)
		{
			printf(" %d", relation[i]);
		}

		printf(" %d\n", max_ans);


	}
	return 0;
}