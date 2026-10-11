
// Pivot = last or first index

#include <iostream>
#include <vector>

using namespace std;

int partition(vector<int>& arr, int start, int end) {
    int pivot = end;

    int i = 0, j = end - 1;

    while (i < j) {
        // Không được dùng if ở vòng lặp check i và j
        // Nếu như dùng if, ta sẽ không thể check được i và j mới có vi phạm
        // hay không
        while (arr[i] <= arr[pivot] && i < end) {
            ++i;
        }

        while (arr[j] >= arr[pivot] && j > 0) --j;

        if (i < j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }

        i++;
        j--;
    }

    int temp = arr[i];
    arr[i] = arr[pivot];
    arr[pivot] = temp;

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
