#include<iostream>
using namespace std;
FILE* pF = 0;

int N; // NxN -> size of land
#define MAX_LAND_SIZE 55
#define MAX_PROFIT 1000
int profit[MAX_LAND_SIZE][MAX_LAND_SIZE];//this stores the profit value for each 1x1 square of the orginal land.
int mprofit[MAX_LAND_SIZE][MAX_LAND_SIZE];//this stores the profit value for each 1x1 square of the mirror image of orginal land.
int sum[MAX_LAND_SIZE][MAX_LAND_SIZE];//sum[i][j] stores the cumulative profit of rectangle with upper left as 1,1 and bottom right as i,j
int fieldcount[MAX_LAND_SIZE * MAX_LAND_SIZE * MAX_PROFIT * 2];//For a given shared point this array stores the count of possible upper left fields with a specific profit.
int sumoffset = MAX_PROFIT * MAX_LAND_SIZE * MAX_LAND_SIZE;
unsigned long long ways = 0;
void calculateCumulativeProfit()
{
	//i,j are the indices of bottom right corner of a rectangular field.
	for (int i = 0; i <= N; i++)
	{
		for (int j = 0; j <= N; j++)
		{
			sum[i][j] = 0;
		}
	}
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			//sum[i][j] stores the cumulative profit of rectangle with upper left as 1,1 and bottom right as i,j
			sum[i][j] = profit[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
		}
	}
}
void calculateWays()
{
	//lets select one shared point now for upper left
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			//i j is shared point 

			//let us now  cal sum for all possible upper left fields  and store it for comparison
			for (int upperLeftStartRow = 1; upperLeftStartRow <= i; upperLeftStartRow++)
			{
				for (int upperLeftStartCol = 1; upperLeftStartCol <= j; upperLeftStartCol++)
				{
					int currentProfit = sum[i][j] - sum[upperLeftStartRow - 1][j] - sum[i][upperLeftStartCol - 1] + sum[upperLeftStartRow - 1][upperLeftStartCol - 1];
					fieldcount[currentProfit + sumoffset]++;
				}
			}
			for (int bottomRightEndRow = i + 1; bottomRightEndRow <= N; bottomRightEndRow++)
			{
				for (int bottomRightEndCol = j + 1; bottomRightEndCol <= N; bottomRightEndCol++)
				{
					int currentProfit = sum[bottomRightEndRow][bottomRightEndCol] - sum[i][bottomRightEndCol] - sum[bottomRightEndRow][j] + sum[i][j];
					ways += fieldcount[currentProfit + sumoffset];
				}
			}
			for (int upperLeftStartRow = 1; upperLeftStartRow <= i; upperLeftStartRow++)
			{
				for (int upperLeftStartCol = 1; upperLeftStartCol <= j; upperLeftStartCol++)
				{
					int currentProfit = sum[i][j] - sum[upperLeftStartRow - 1][j] - sum[i][upperLeftStartCol - 1] + sum[upperLeftStartRow - 1][upperLeftStartCol - 1];
					fieldcount[currentProfit + sumoffset] = 0;
				}
			}
		}
	}
}
void mirror()
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			mprofit[i][N + 1 - j] = profit[i][j];//mprofit array is the mirror of profit array
		}
	}
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			profit[i][j] = mprofit[i][j];
		}
	}
}
int main(void)
{
	int C = 0;
	freopen_s(&pF, "input.txt", "r", stdin);
	cin >> C;//number of test cases 
	for (int c = 1; c <= C; ++c)
	{
		cin >> N;// N is size of land , it is N x N square shaped land
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				cin >> profit[i][j];
			}
		}
		calculateCumulativeProfit();
		calculateWays();
		mirror();
		calculateCumulativeProfit();
		calculateWays();
		cout << "#" << c << " " << ways << endl;
		ways = 0;
	}
	return 0; //Your program should return 0 on normal termination.
}