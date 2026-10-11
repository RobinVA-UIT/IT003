// Pivot = last index

#include <iostream>
#include <vector>

using namespace std;

int partition(vector<int>& arr, int start, int end) {
    int temp;

    int i = -1, j = 0;

    for (; j < end; ++j) {
        if (arr[j] < arr[end]) {
            ++i;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    ++i;
    temp = arr[end];
    arr[end] = arr[i];
    arr[i] = temp;

    return i;
}

void quicksort(vector<int>& arr, int start, int end) {
    if (end <= start) return;

    int pivot = partition(arr, start, end);

    quicksort(arr, start, pivot - 1);
    quicksort(arr, pivot + 1, end);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> arr(n);

    for (auto& x : arr) {
        cin >> x;
    }

    quicksort(arr, 0, arr.size() - 1);

    for (auto& x : arr) {
        cout << x << " ";
    }

    return 0;
}
