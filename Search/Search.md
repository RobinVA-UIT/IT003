# Linear search

Search từ đầu cho đến cuối mảng 

| Complexity | Big-O | Explanation |
|------------|-------|-------------|
| Best case | O(1) | The element to find is right at the beginning. |
| Worst case | O(n) | Have to search until the end of the array to find, or maybe can't find it at all. |
| Average case | O(n) | |
| Auxiliary Space | O(1) | Only have to use one variable for iterating index |

```cpp
bool linear(int x, vector<int> arr)
{
	for(int i = 0; arr.size(); ++i)
	{
		if (arr[i] == x) return true;
	}

	return false;
}

```

## Sentinel linear search

Thêm phần tử cần tìm làm lính canh ở cuối mảng 

```cpp
bool sentinelLinear(int x, vector<int> arr)
{
	arr.push_back(x);

	for(int i = 0; arr.size(); ++i)
	{
		if (arr[i] == x){
			if(i == arr.size() - 1) return false;
		}
		else return true;
	}
}
```

Complexity tương tự linear search thông thường.

--- 

# Binary search

Chỉ áp dụng trên mảng đã có thứ tự.

| Complexity | Big-O | Explanation |
|------------|-------|-------------|
| Best case | O(1) | The element to find is at the middle of the array. |
| Worst case | O(log(N)) | Everytime the algo can't find the target, it reduces its scope on array by half. |
| Average case | O(log(N)) | |
| Auxiliary Space (recursive) | O(log(N)) | It calls another search after an unsuccessful find. |
| Auxiliary Space (iterative) | O(1) | Two vars for low and high position. |

## Iterative

```cpp
bool iterative(vector<int>& arr, int x) {
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
```

## Recursive

```cpp
bool recursive(vector<int>& arr, int x, int l, int r) {
	if(l > r) return false;

	int mid = l + (r-l)/2;

	if(arr[mid] == x) return true;

	else if(arr[mid] > x) return recursive(arr, x, l, mid - 1);

	else return recursive(arr, x, mid+1, r);
}
```

