#include <iostream>
using namespace std;

class DynamicProgramming {
private:
    long long fibonacciMemoHelper(int n, long long memo[]) {
        if (n <= 1)
            return n;

        if (memo[n] != -1)
            return memo[n];

        memo[n] = fibonacciMemoHelper(n - 1, memo) +
                  fibonacciMemoHelper(n - 2, memo);

        return memo[n];
    }

public:
    // 1. Fibonacci using simple recursion
    long long fibonacciRecursive(int n) {
        if (n <= 1)
            return n;

        return fibonacciRecursive(n - 1) +
               fibonacciRecursive(n - 2);
    }

    // 2. Fibonacci using memoization
    long long fibonacciMemoization(int n) {
        long long *memo = new long long[n + 1];

        for (int i = 0; i <= n; i++)
            memo[i] = -1;

        long long result = fibonacciMemoHelper(n, memo);

        delete[] memo;
        return result;
    }

    // 3. Fibonacci using tabulation
    long long fibonacciTabulation(int n) {
        if (n <= 1)
            return n;

        long long *dp = new long long[n + 1];

        dp[0] = 0;
        dp[1] = 1;

        for (int i = 2; i <= n; i++)
            dp[i] = dp[i - 1] + dp[i - 2];

        long long result = dp[n];

        delete[] dp;
        return result;
    }

    // 4. 0/1 Knapsack using Dynamic Programming
    int knapsack(int weights[], int values[], int n, int capacity) {
        int **dp = new int*[n + 1];

        for (int i = 0; i <= n; i++) {
            dp[i] = new int[capacity + 1];

            for (int w = 0; w <= capacity; w++)
                dp[i][w] = 0;
        }

        for (int i = 1; i <= n; i++) {
            for (int w = 1; w <= capacity; w++) {

                // Do not include the current item
                dp[i][w] = dp[i - 1][w];

                // Include the current item if possible
                if (weights[i - 1] <= w) {
                    int take = values[i - 1] +
                               dp[i - 1][w - weights[i - 1]];

                    if (take > dp[i][w])
                        dp[i][w] = take;
                }
            }
        }

        int result = dp[n][capacity];

        for (int i = 0; i <= n; i++)
            delete[] dp[i];

        delete[] dp;

        return result;
    }
};

int main() {
    DynamicProgramming dp;

    int n;

    cout << "=== Fibonacci ===\n";
    cout << "Enter n: ";
    cin >> n;

    if (n < 0) {
        cout << "Invalid value of n.\n";
        return 0;
    }

    cout << "Fibonacci using Recursion: "
         << dp.fibonacciRecursive(n) << "\n";

    cout << "Fibonacci using Memoization: "
         << dp.fibonacciMemoization(n) << "\n";

    cout << "Fibonacci using Tabulation: "
         << dp.fibonacciTabulation(n) << "\n";


    int items, capacity;

    cout << "\n=== 0/1 Knapsack ===\n";

    cout << "Enter number of items: ";
    cin >> items;

    if (items <= 0) {
        cout << "Invalid number of items.\n";
        return 0;
    }

    int *weights = new int[items];
    int *values = new int[items];

    cout << "Enter weights: ";
    for (int i = 0; i < items; i++)
        cin >> weights[i];

    cout << "Enter values: ";
    for (int i = 0; i < items; i++)
        cin >> values[i];

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    if (capacity < 0) {
        cout << "Invalid capacity.\n";
        delete[] weights;
        delete[] values;
        return 0;
    }

    cout << "Maximum Knapsack Value: "
         << dp.knapsack(weights, values, items, capacity)
         << "\n";

    delete[] weights;
    delete[] values;

    return 0;
}