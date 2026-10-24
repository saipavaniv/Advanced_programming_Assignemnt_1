#include <iostream>
using namespace std;

class ActivitySelection {
private:
    struct Activity {
        int start;
        int finish;
        int id; // Original activity identifier
    };

    Activity *activities;
    int n;

    // Sort activities by finish time in ascending order using insertion sort
    void sortByFinishTime() {
        for (int i = 1; i < n; i++) {
            Activity key = activities[i];
            int j = i - 1;

            while (j >= 0 && activities[j].finish > key.finish) {
                activities[j + 1] = activities[j];
                j--;
            }

            activities[j + 1] = key;
        }
    }

public:
    ActivitySelection(int count) {
        n = count;
        activities = new Activity[n];
    }

    ~ActivitySelection() {
        delete[] activities;
    }

    void setActivity(int index, int start, int finish) {
        activities[index].start = start;
        activities[index].finish = finish;
        activities[index].id = index + 1;
    }

    // Greedy Activity Selection Method
    void selectActivities() {
        if (n == 0) {
            cout << "No activities provided.\n";
            return;
        }

        // Step 1: Sort by finish time
        sortByFinishTime();

        cout << "\n========================================\n";
        cout << "       Greedy Activity Selection        \n";
        cout << "========================================\n";
        cout << "Selected Activities: ";

        int selected = 0;
        int lastFinish = -1;

        // Step 2: Greedily pick non-overlapping activities
        for (int i = 0; i < n; i++) {
            if (selected == 0 || activities[i].start >= lastFinish) {
                cout << "A" << activities[i].id << " ";
                lastFinish = activities[i].finish;
                selected++;
            }
        }

        cout << "\nMaximum non-overlapping activities selected: " << selected << "\n";
        cout << "========================================\n";
    }
};

int main() {
    int n;

    cout << "Enter number of activities: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid number of activities.\n";
        return 0;
    }

    ActivitySelection problem(n);

    cout << "Enter start and finish time for each activity:\n";
    for (int i = 0; i < n; i++) {
        int start, finish;
        cout << "Activity " << i + 1 << " (start finish): ";
        cin >> start >> finish;
        problem.setActivity(i, start, finish);
    }

    problem.selectActivities();

    return 0;
}