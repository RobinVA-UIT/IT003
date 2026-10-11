# Classification 

## Tính chất của danh sách A

### Offline Sorting

➢Toàn bộ tập dữ liệu đầu vào phải có sẵn đầy đủ từ đầu trước khi thuật toán bắt đầu thực thi. → Offline Sorting

- Selection sort, Bubble sort: Quét qua toàn bộ mảng để tìm min/max hoặc đẩy phần tử về cuối.

- Merge sort: Chia đôi toàn bộ danh sách xuống từng phần tử rồi gộp lại.

- Heap sort: Xây dựng heap tĩnh từ toàn bộ mảng ban đầu rồi trích xuất.

- Quick Sort: Cần toàn bộ mảng để chọn pivot và phân hoạch (partition).

### Online Sorting

➢Từng phần tử của A được sắp xếp tuần tự mà không cần biết trước toàn bộ A → Online Sorting

- Insertion sort: Khi số mới xuất hiện, chỉ cần dịch chuyển phần tử lớn hơn để chèn số mới vào đúng vị trí

- Tree sort: Phần tử mới được chèn vào cây


## Trật tự của kết quả sắp xếp

➢Thứ tự trước/sau của các phần tử có cùng giá trị không đổi so với ban đầu → Stable Sorting.

➢Ngược lại → Unstable sorting.


## Nơi lưu trữ chính của danh sách

➢Toàn bộ danh sách A được lưu trữ trên RAM trong quá trình sắp xếp → Internal Sorting.

- Interchange Sort

- Insertion Sort

- Quick Sort

Áp dụng khi toàn bộ tập dữ liệu cần sắp xếp có kích thước nhỏ hơn hoặc bằng dung lượng bộ nhớ chính (RAM) khả dụng của hệ thống.

➢Toàn bộ danh sách A được lưu trữ trên bộ nhớ ngoài trong quá trình sắp xếp do kích thước danh sách quá lớn → External Sorting.
- Merge Sort

---

# Selection sort

**B1**: i = 0

**B2**: Dò từ i đến N để tìm giá trị bé hơn a[i], gán index vào min

**B3**: Nếu i != min (hoặc max, tùy vào sắp xếp tăng hay giảm), ta swap a[i] và a[min]

Lặp lại cho đến khi i == N thì dừng

```cpp
//Ascending
int selection(vector<int>& arr)
{
	for(int i = 0; i < arr.size() - 1; ++i)
	{
		int min = i;

		for(int j = 1+i; j < arr.size(); ++j)
		{
			if(arr[min] > arr[j]) min = j;
		}

		if(min != i) swap(arr[i], arr[min]);
	}
}

```

## Complexity

Best, average and worst cases all have O(n^2) time complexity.

Auxiliary space: O(1) since temporary vars are used.

---

# Insertion sort

**B1**: i = 1.

**B2**: Đặt x = arr[i], duyệt từ j = i-1 đến 0.

**B3**: Nếu như tìm được phần tử tại j sao cho thỏa điều kiện với i, ta swap arr[j+1] và arr[i].

**B4**: Khi không thỏa điều kiện, arr[j+1] = x, break.

Lặp lại cho đến i = n-1.

```cpp
//Descending
int insertion(vector<int>& arr)
{
	for(int i = 1; i < arr.size(); ++i)
	{
		int x = arr[i], j = i-1;

		for(; j > -1; --j)
		{
			if(arr[j] < x) //Smaller than x => Have to be shifted right
			{
				arr[j+1] = arr[j];
			}
			else break;
		}

		arr[j+1] = x;
	}
}
```

## Complexity

| Complexity | Big-O | Explanation |
|------------|-------|-------------|
| Best case | O(n) | The array is already sorted. |
| Worst case | O(n^2) | The array is not sorted at all (reverse order). |
| Average case | O(n^2) | The array is randomly ordered. |
| Auxiliary Space | O(1) | Use some iterating indices. |

