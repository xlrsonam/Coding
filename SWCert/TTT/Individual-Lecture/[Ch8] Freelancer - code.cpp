
#include <iostream>
#define MAX(a, b)  ((a) > (b) ? (a) : (b))
#define MAXN 505

using namespace std;

// A job has start time, finish time and profit.
struct WorkRequest
{
    int start, finish, earning;
};

struct  WorkRequest data[501];


void swap(int i1, int i2)
{
    WorkRequest temp;
    temp.start = data[i1].start;
    temp.finish = data[i1].finish;
    temp.earning = data[i1].earning;
    data[i1].start = data[i2].start;
    data[i1].finish = data[i2].finish;
    data[i1].earning = data[i2].earning;
    data[i2].start = temp.start;
    data[i2].finish = temp.finish;
    data[i2].earning = temp.earning;
}
int partition(int low, int high)
{
    double pivot = data[high].finish;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (data[j].finish <= pivot)
        {
            i++;
            swap(i, j);
        }
    }
    swap(i + 1, high);
    return (i + 1);
}

void quickSort(int low, int high)
{
    if (low < high)
    {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}


// Find the latest job (in sorted array) that doesn't
// conflict with the job[i]
int latestNonConflict(WorkRequest arr[], int i)
{
    for (int j = i - 1; j >= 0; j--)
    {
        if (arr[j].finish < arr[i].start)
            return j;
    }
    return -1;
}

// The main function that returns the maximum possible
// profit from given array of jobs
int findMaxProfit(WorkRequest arr[], int n)
{
    // Sort jobs according to finish time
    quickSort(0, n - 1);
    /*
    for (int i = 0; i < n; i++)
    {
    cout << data[i].start << " " << data[i].finish << "\n";
    }
    */
    // Create an array to store solutions of subproblems.  table[i]
    // stores the profit for jobs till arr[i] (including arr[i])
    int *table = new int[n];
    table[0] = arr[0].earning;

    // Fill entries in M[] using recursive property
    for (int i = 1; i<n; i++)
    {
        // Find profit including the current job
        int inclProf = arr[i].earning;
        int l = latestNonConflict(arr, i);
        if (l != -1)
            inclProf += table[l];

        // Store maximum of including and excluding
        table[i] = MAX(inclProf, table[i - 1]);
    }

    // Store result and free dynamic memory allocated for table[]
    int result = table[n - 1];
    delete[] table;

    return result;
}

int dp[MAXN];
int findMaxEarning(int taskToConsider)//tasken in decreasing order of end/finish time
{
    if (taskToConsider == -1) return 0;

    if (dp[taskToConsider]) return dp[taskToConsider];


    //we have two options either include this task or exclude this task

    int excludePay = findMaxEarning(taskToConsider - 1);

    int latestTaskThatCanBeTaken = -1;

    for (int i = taskToConsider - 1; i >= 0; i--)
    {
        if (data[i].finish < data[taskToConsider].start)
        {
            latestTaskThatCanBeTaken = i;
            break;
        }
    }

    int includePay = data[taskToConsider].earning + findMaxEarning(latestTaskThatCanBeTaken);

    dp[taskToConsider] = MAX(excludePay, includePay);

    return dp[taskToConsider];
}




// Driver program
int main()
{
    int test_case;
    int T;
    /*
    The freopen function below opens input.txt in read only mode and
    sets your standard input to work with the opened file.
    When you test your code with the sample data, you can use the function
    below to read in from the sample data file instead of the standard input.
    So. you can uncomment the following line for your local test. But you
    have to comment the following line when you submit for your scores.
    */

    freopen("inputFree.txt", "r", stdin);
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        //take input
        int n, m;
        cin >> n >> m;
        int startTime, endTime, earningFromTask;
        for (int i = n - 1; i >= 0; i--)
        {
            cin >> startTime >> endTime >> earningFromTask;
            data[i].start = startTime;
            data[i].finish = endTime;
            data[i].earning = earningFromTask;
            dp[i] = 0;
        }
        //for bottom up
        //int ans = findMaxProfit(data, n);



        // for Top Down
        quickSort(0, n - 1);
        int ans = findMaxEarning(n - 1);
        cout << "#" << test_case << " " << ans << "\n";
    }
    return 0;
}

