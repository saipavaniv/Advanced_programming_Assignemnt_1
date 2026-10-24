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

    void merge(int low, int mid, int high) {
        int n1 = mid - low + 1;
        int n2 = high - mid;

        int *left = new int[n1];
        int *right = new int[n2];

        for (int i = 0; i < n1; i++)
            left[i] = arr[low + i];

        for (int i = 0; i < n2; i++)
            right[i] = arr[mid + 1 + i];

        int i = 0;
        int j = 0;
        int k = low;

        while (i < n1 && j < n2) {
            if (left[i] <= right[j]) {
                arr[k] = left[i];
                i++;
            }
            else {
                arr[k] = right[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = left[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = right[j];
            j++;
            k++;
        }

        delete[] left;
        delete[] right;
    }

    void mergeSortRecursive(int low, int high) {
        if (low >= high)
            return;

        int mid = low + (high - low) / 2;

        mergeSortRecursive(low, mid);
        mergeSortRecursive(mid + 1, high);

        merge(low, mid, high);
    }

    int partition(int low, int high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }

        swap(arr[i + 1], arr[high]);

        return i + 1;
    }

    void quickSortRecursive(int low, int high) {
        if (low < high) {
            int pivotIndex = partition(low, high);

            quickSortRecursive(low, pivotIndex - 1);
            quickSortRecursive(pivotIndex + 1, high);
        }
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

    void mergeSort() {
        mergeSortRecursive(0, size - 1);
    }

    void quickSort() {
        quickSortRecursive(0, size - 1);
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
    cout << "1. Merge Sort\n";
    cout << "2. Quick Sort\n";
    cout << "Choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            sa.mergeSort();
            break;

        case 2:
            sa.quickSort();
            break;

        default:
            cout << "Invalid choice.\n";
            return 0;
    }

    cout << "Sorted array: ";
    sa.showArray();

    return 0;
}