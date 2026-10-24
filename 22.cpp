#include <iostream>
#include <iomanip>
using namespace std;

class FractionalKnapsack {
private:
    struct Item {
        int weight;
        int value;
        double ratio;
        int id;
    };

    Item *items;
    int n;

    // Sort items by value/weight ratio in descending order
    // using insertion sort
    void sortByRatio() {
        for (int i = 1; i < n; i++) {
            Item key = items[i];
            int j = i - 1;

            while (j >= 0 && items[j].ratio < key.ratio) {
                items[j + 1] = items[j];
                j--;
            }

            items[j + 1] = key;
        }
    }

public:
    FractionalKnapsack(int count) {
        n = count;
        items = new Item[n];
    }

    ~FractionalKnapsack() {
        delete[] items;
    }

    void setItem(int index, int weight, int value) {
        items[index].weight = weight;
        items[index].value = value;
        items[index].ratio = (double)value / weight;
        items[index].id = index + 1;
    }

    // Greedy Fractional Knapsack
    double solve(int capacity) {
        sortByRatio();

        double totalValue = 0.0;
        int remainingCapacity = capacity;

        cout << "\n========================================\n";
        cout << "       Fractional Knapsack Selection\n";
        cout << "========================================\n";

        for (int i = 0; i < n; i++) {
            if (remainingCapacity == 0)
                break;

            if (items[i].weight <= remainingCapacity) {
                // Take the complete item
                totalValue += items[i].value;
                remainingCapacity -= items[i].weight;

                cout << "Item " << items[i].id
                     << ": 100% taken\n";
            }
            else {
                // Take only the required fraction
                double fraction =
                    (double)remainingCapacity / items[i].weight;

                totalValue += items[i].value * fraction;

                cout << "Item " << items[i].id
                     << ": " << fixed << setprecision(2)
                     << fraction * 100 << "% taken\n";

                remainingCapacity = 0;
            }
        }

        cout << "========================================\n";

        return totalValue;
    }
};

int main() {
    int n, capacity;

    cout << "Enter number of items: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid number of items.\n";
        return 0;
    }

    FractionalKnapsack problem(n);

    cout << "Enter weight and value for each item:\n";

    for (int i = 0; i < n; i++) {
        int weight, value;

        cout << "Item " << i + 1 << " (weight value): ";
        cin >> weight >> value;

        if (weight <= 0) {
            cout << "Invalid weight. Weight must be positive.\n";
            return 0;
        }

        problem.setItem(i, weight, value);
    }

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    if (capacity < 0) {
        cout << "Invalid capacity.\n";
        return 0;
    }

    double maximumValue = problem.solve(capacity);

    cout << fixed << setprecision(2);
    cout << "Maximum Total Value: " << maximumValue << endl;

    return 0;
}