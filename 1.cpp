#include <iostream>
using namespace std;

class SearchAlgorithms {
private:
    int *arr;
    int size;

    int recursiveBinarySearchHelper(int low, int high, int key) {
        if (low > high)
            return -1;

        int mid = low + (high - low) / 2;

        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            return recursiveBinarySearchHelper(mid + 1, high, key);
        else
            return recursiveBinarySearchHelper(low, mid - 1, key);
    }

public:
    SearchAlgorithms(int n) {
        size = n;
        arr = new int[size];
    }

    ~SearchAlgorithms() {
        delete[] arr;
    }

    void inputArray() {
        cout << "Enter " << size << " elements:\n";
        for (int i = 0; i < size; i++)
            cin >> arr[i];
    }

    void showArray() {
        cout << "Array: ";
        for (int i = 0; i < size; i++)
            cout << arr[i] << " ";
        cout << endl;
    }

    int linearSearch(int key) {
        for (int i = 0; i < size; i++) {
            if (arr[i] == key)
                return i;
        }
        return -1;
    }

    int binarySearch(int key) {
        int low = 0;
        int high = size - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] == key)
                return mid;
            else if (arr[mid] < key)
                low = mid + 1;
            else
                high = mid - 1;
        }

        return -1;
    }

    int recursiveBinarySearch(int key) {
        return recursiveBinarySearchHelper(0, size - 1, key);
    }
};

int main() {
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    SearchAlgorithms sa(n);

    sa.inputArray();

    cout << "\n";
    sa.showArray();

    int choice, key;

    cout << "\nChoose search method:\n";
    cout << "1. Linear Search\n";
    cout << "2. Binary Search\n";
    cout << "3. Recursive Binary Search\n";
    cout << "Choice: ";
    cin >> choice;

    cout << "Enter element to search: ";
    cin >> key;

    int result;

    if (choice == 1) {
        result = sa.linearSearch(key);
    }
    else if (choice == 2) {
        result = sa.binarySearch(key);
    }
    else if (choice == 3) {
        result = sa.recursiveBinarySearch(key);
    }
    else {
        cout << "Invalid choice.\n";
        return 0;
    }

    if (result != -1) {
        cout << "Element found at index " << result;
        cout << " (Position " << result + 1 << ")\n";
    }
    else {
        cout << "Element not found.\n";
    }

    return 0;
}