#include <iostream>
#include <string>
using namespace std;

class LCS {
private:
    int **dp;
    int n, m;

public:
    LCS(const string &a, const string &b) {
        n = a.length();
        m = b.length();

        dp = new int*[n + 1];

        for (int i = 0; i <= n; i++) {
            dp[i] = new int[m + 1];

            for (int j = 0; j <= m; j++)
                dp[i][j] = 0;
        }

        // Build the LCS DP table
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (a[i - 1] == b[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = (dp[i - 1][j] > dp[i][j - 1])
                             ? dp[i - 1][j]
                             : dp[i][j - 1];
            }
        }
    }

    void displayLCS(const string &a, const string &b) {
        int i = n;
        int j = m;

        string lcs = "";

        // Trace back through the DP table
        while (i > 0 && j > 0) {
            if (a[i - 1] == b[j - 1]) {
                lcs = a[i - 1] + lcs;
                i--;
                j--;
            }
            else if (dp[i - 1][j] >= dp[i][j - 1]) {
                i--;
            }
            else {
                j--;
            }
        }

        cout << "LCS: " << lcs << endl;
        cout << "Length: " << dp[n][m] << endl;
    }

    ~LCS() {
        for (int i = 0; i <= n; i++)
            delete[] dp[i];

        delete[] dp;
    }
};

int main() {
    string first, second;

    cout << "String 1: ";
    cin >> first;

    cout << "String 2: ";
    cin >> second;

    LCS solver(first, second);

    solver.displayLCS(first, second);

    return 0;
}