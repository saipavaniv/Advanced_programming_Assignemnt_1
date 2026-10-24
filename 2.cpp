#include <iostream>
using namespace std;

class SortingAlgorithms {
private:
    int *arr;
    int size;

    void swap(int &a, int &b) {
        int temp = a;
        a = b;
        b = temp;
    }

public:
    SortingAlgorithms(int n) {
        size = n;
        arr = new int[size];
    }

    ~SortingAlgorithms() {
        delete[] arr;
    }

    void inputArray() {
        cout << "Enter " << size << " elements:\n";
        for (int i = 0; i < size; i++)
            cin >> arr[i];
    }

    void showArray() {
        for (int i = 0; i < size; i++)
            cout << arr[i] << " ";
        cout << endl;
    }

    void bubbleSort() {
        for (int i = 0; i < size - 1; i++) {
            bool swapped = false;

            for (int j = 0; j < size - 1 - i; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }

            if (!swapped)
                break;
        }
    }

    void selectionSort() {
        for (int i = 0; i < size - 1; i++) {
            int minIndex = i;

            for (int j = i + 1; j < size; j++) {
                if (arr[j] < arr[minIndex])
                    minIndex = j;
            }

            swap(arr[i], arr[minIndex]);
        }
    }

    void insertionSort() {
        for (int i = 1; i < size; i++) {
            int key = arr[i];
            int j = i - 1;

            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }

            arr[j + 1] = key;
        }
    }
};

int main() {
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    SortingAlgorithms sa(n);

    sa.inputArray();

    cout << "\nOriginal array: ";
    sa.showArray();

    int choice;

    cout << "\nChoose sorting algorithm:\n";
    cout << "1. Bubble Sort\n";
    cout << "2. Selection Sort\n";
    cout << "3. Insertion Sort\n";
    cout << "Choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            sa.bubbleSort();
            break;

        case 2:
            sa.selectionSort();
            break;

        case 3:
            sa.insertionSort();
            break;

        default:
            cout << "Invalid choice.\n";
            return 0;
    }

    cout << "Sorted array: ";
    sa.showArray();

    return 0;
}