#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool solve(vector<int>& arr, int x) {
    int l = 0, r = arr.size() - 1;

    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (arr[mid] == x)
            return true;

        else if (arr[mid] > x)
            r = mid - 1;
        else
            l = mid + 1;
    }

    return false;
}

int main() {
    int x;
    cin >> x;

    int n;
    cin >> n;
    vector<int> arr(n);
    for (auto& inp : arr) cin >> inp;

    sort(arr.begin(), arr.end());
    cout << solve(arr, x);

    return 0;
}
