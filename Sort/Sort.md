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

---

# Quick sort

Ascending:

**B1**: Chọn 1 phần tử bất kì trong mảng làm pivot. Ở đây ta chọn phần tử ở giữa

**B2**: Setup 2 index `left` = 0 và `right` = n-1, đồng thời `i` = `left`, và `j` = `right`. Lập vòng lặp `while(i <= j)`.

**B3**: Trong vòng lặp while, dùng thêm 2 vòng lặp while. 

- Một vòng kiểm tra `arr[i]`, nếu bé hơn hoặc bằng pivot thì `i++`

- Một vòng kiểm tra `arr[j]`, nếu lớn hơn hoặc bằng pivot thì `j--`

**B4**: Nếu `i` <= `j`, ta swap `arr[i]` và `arr[j]`, đồng thời `i++` và `j--`.

**B5**: Kết thúc vòng lặp 

- Nếu `left` bé hơn `j`, thực hiện đệ quy với `left` gốc và `right` = `j`.

- Nếu `i` bé hơn `right`, thực hiện đệ quy với `left` = `i` và `right` gốc.

```cpp
//Ascending
//left = 0, right = arr.size()-1
void quick_sort(vector<int>& arr, int left, int right)
{
	if(left >= right) return;

	int pivot = arr[left + (right-left)/2];
	int i = left, j = right;

	while(i <= j)
	{
		while(arr[i] < pivot) ++i;
		while(arr[j] > pivot) --j;

		if(i <= j){
			swap(arr[i], arr[j]);
			++i; --j;
		}
	}

	if(left < j) quick_sort(arr, left, j);
	if(i < right) quick_sort(arr, i, right);
}
```

## Lưu ý

Xem vòng lặp while sau:

```cpp
while(i <= j)
{
	while(arr[i] < pivot) ++i;
	while(arr[j] > pivot) --j;

	if(i <= j){
		swap(arr[i], arr[j]);
		++i; --j;
	}
}
```

Ở đây ta có các điều kiện:

- `while(i <= j)`

- `	while(arr[i] < pivot) ++i;` (1)

- `	while(arr[j] > pivot) --j;` (2)

- `if(i <= j)`

Nếu như ta thêm bớt dấu bằng vào các điều kiện thì chuyện gì sẽ xảy ra?

### while(i <= j) ==> while(i < j)

Điều kiện này sẽ bỏ qua việc `i == j`. Ta thử nhìn vào 2 câu lệnh cuối hàm:

```cpp
if(left < j) quick_sort(arr, left, j);
if(i < right) quick_sort(arr, i, right);
```

Lúc này, chỉ số `j` của lệnh 1 và `i` của lệnh 2 sẽ bằng nhau. Sau khi lệnh 1 hoàn tất, vị trí `arr[i]` - tương đương `arr[j]`, có thể đã bị thay đổi, 
trong khi điều ta cần là chia arr thành 2 mảng độc lập để thực hiện sort. 

Nếu như lệnh sort trước can thiệp vào mảng kia => Sai bản chất.

### Vòng while kiểm tra index vi phạm (1, 2)

Ta thử với mảng arr = [5, 6, 7, 2], ascending sort.

#### Không có dấu bằng

i = 0, j = 3, pivot = 6

- (1)

arr[i] = 5, hợp lệ. ++i = 1

arr[i] = 6, bằng với pivot, dừng.

- (2)

arr[j] = 2, vi phạm, dừng.


Swap i và j

arr = [5, 2, 7, 6]

++i = 2, --j = 2

- (1)

arr[i] = 7, lớn hơn pivot, dừng.

- (2)

arr[j] = 7, lớn hơn pivot, --j = 1

arr[j] = 2, bé hơn, dừng

i > j, ta dừng vòng lặp

arr = [5, 2, 7, 6]

Kết thúc, nửa trái bé hơn pivot, nửa sau lớn hơn hoặc bằng pivot

Các bước đệ quy sẽ sắp xếp về đúng thứ tự, ta không cần xét thêm.

#### Có dấu bằng

arr = [5, 6, 7, 2]

i = 0, j = 3, pivot = 6

- (1)

i chạy đến 2

- (2)

j giữ nguyên

swap: arr = [5, 6, 2, 7]

i tăng lên 3, j giảm xuống 2

i > j, ta dừng

Rõ ràng, pivot là 6, nhưng 2 nửa của mảng đều không tuân theo quy tắc một mảng lớn hơn hoặc bằng pivot, một mảng bé hơn pivot

=> Thuật toán sẽ hỏng.

Giờ ta xét thêm arr2 = [1, 7, 2, 3], ascending. Nếu như dùng thêm dấu bằng, nó sẽ bỏ qua luôn số 7, khiến i và j cuối cùng sẽ vượt qua nhau. Mảng vẫn sẽ là [1, 7, 2, 3], không tuân theo bất kì nguyên tắc nào.

Vậy ta đã confirm được:

- `while(i <= j)`

- `	while(arr[i] < pivot) ++i;` 

- `	while(arr[j] > pivot) --j;` 

Còn điều kiện cuối: `if(i <= j)`

### `if(i <= j)`  -> `if(i < j)`

Giả sử i == j, arr[i] = 5, pivot = arr[i]

- `while(i <= j)`: Chạy

- `	while(arr[i] < pivot) ++i;`: i giữ nguyên

- `	while(arr[j] > pivot) --j;`: j giữ nguyên

Giờ ta xét các trường hợp

- `if(i <= j)`

Swap với chính nó, rồi giảm j và tăng i.

- `if(i < j)`

Không chạy, do i == j. i và j giữ nguyên. 

Với `if(i < j)` khi chạy ngược về điều kiện while ban đầu, nó sẽ thỏa mãn, nhưng bản thân i và j sẽ không hề thay đổi nếu tiếp tục xét các điều kiện bên trong vòng lặp ấy.

=> Lặp vô tận.

Vậy các điều kiện trong code mẫu đều là điều kiện chuẩn.

---
