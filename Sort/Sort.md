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

- Một vòng kiểm tra `arr[i]`, nếu bé hơn pivot thì `i++`

- Một vòng kiểm tra `arr[j]`, nếu lớn hơn pivot thì `j--`

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

Với `if(i <= j)` khi chạy ngược về điều kiện while ban đầu, nó sẽ thỏa mãn, nhưng bản thân i và j sẽ không hề thay đổi nếu tiếp tục xét các điều kiện bên trong vòng lặp ấy.

=> Lặp vô tận.

Vậy các điều kiện trong code mẫu đều là điều kiện chuẩn.


## Complexity

### Time

| Complexity | Big-O | Explanation |
|------------|-------|-------------|
| Best case | O(nlogn) | The pivot divides the array into two equal halves. |
| Worst case | O(n^2) | The largest or smallest value is always chosen as the pivot. |
| Average case | O(n^2) | The array divides the array into two halves, but not necessarily equal. |

### Space

* Worst-case scenario: O(n) due to unbalanced partitioning leading to a skewed recursion tree requiring a call stack of size O(n).

* Best-case scenario: O(log n) as a result of balanced partitioning leading to a balanced recursion tree with a call stack of size O(log n).

Source: [GeeksForGeeks](https://www.geeksforgeeks.org/dsa/quick-sort-algorithm/#:~:text=8%209%2010-,Complexity%20Analysis,-Time%20Complexity%3A)

---

# Merge sort

## Top-down (recursive)

Từ một mảng lớn, ta gọi đệ quy chia mảng ra làm đôi. Chia như thế cho đến khi còn 1 phần tử trong mảng.

Sau đó, thực hiện so sánh phần tử của 2 mảng nhỏ, thêm vào mảng temp, rồi dần dần ghép vào mảng chính.

```cpp
//Ascending
//left = 0, right = arr.size() - 1
void topDownMerge(vector<int>& arr, int left, int right)
{
	if(left >= right) return;
	int mid = left + (right - left)/2;

	topDownMerge(arr, left, mid);
	topDownMerge(arr, mid+1, right);

	myMerge(arr, left, mid ,right);
}

void myMerge(vector<int>& arr, int left, int mid, int right)
{
	vector<int> leftArr;
	vector<int> rightArr;
	
	int i = 0;
	for(; i<mid+1, ++i)
	{
		leftArr.push_back(arr[i]);
	}

	for(; i<right+1; ++i)
	{
		rightArr.push_back(arr[i]);
	}

	int leftInd = 0, rightInd = 0;
	i = left;
	while(leftInd < leftArr.size() && rightInd < rightArr.size())
	{
		if(leftArr[leftInd] < rightArr[rightInd])
		{
			arr[i] = leftArr[leftInd];
			++i; ++leftInd;
		}
		else{
			arr[i] = rightArr[rightInd];
			++i; ++rightInd;
		}
	}

	for(leftInd < leftArr.size()){
		arr[i] = leftArr[leftInd];
		++i; ++leftInd;
	}

	for(rightInd < rightArr.size()){
		arr[i] = rightArr[rightInd];
		++i; ++rightInd;
	}
}
```

## Bottom-up (iterative)

Chia mảng ra thành N mảng, rồi ghép dần dần với nhau theo window size.

Hàm merge tương tự với recursive.

```cpp
void iterativeMerge(vector<int>& arr)
{
	int n = arr.size();

	for(int windSize = 1; windSize < n; windSize *= 2)
	{
		//Do not iterate the last element, since there's nothing to merge behind
		for(int left = 0; left < n - 1; left += windSize * 2)
		{
			int mid = min(left + windSize - 1, n - 1);
			int right = min(left + windSize*2 - 1, n - 1);

			//myMerge func is the same as the one in recursive version
			myMerge(arr, left, mid, right);
		}
	}
}
```

## Complexity

Time: Cả 2 phiên bản đều có độ phức tạp thời gian như nhau, ở cả 3 cases: O(N * log(N))

- Mỗi lần đệ quy đều chia đôi mảng ra, vậy nên số tầng đệ quy là log2(N)

- Mỗi tầng đều tốn N chi phí để ghép

1 mảng N => Tốn N, 2 mảng N/2 => Tốn 2 * N/2 = N, 4 mảng N/4 => Tốn 4 * N/4 = N,...

Space: 

- Recursive: O(d), với d là độ sâu tầng đệ quy. Mỗi lần gọi lại hàm, ta lại phải tốn thêm chi phí lưu stack frame.

---

# Heap sort

**B1**: Build heap mảng sao cho tuân theo max heap (sắp xếp tăng dần) hoặc min heap (giảm dần), bằng cách heapify cả mảng.

**B2**: Đẩy phần tử ở i = 0 về boundary, với boundary ban đầu = N - 1.

**B3**: Heapify ở i = 0.

**B4**: Giảm boundary xuống 1 đơn vị, i++.

Lặp từ bước 2 đến bước 4 tổng cộng N/2 - 1 lần, vì node ở N/2 - 1 là node cuối có con trong heap.

## Heapify

### Max heap
- Là cây nhị phân hoàn chỉnh (complete binary tree).

- Giá trị của một node bất kỳ trên cây sẽ luôn lớn hơn hoặc bằng giá trị của các node con của nó (nếu có).

### Max heap
- Cũng là cây nhị phân hoàn chỉnh.

- Giá trị của một node bất kỳ trên cây sẽ luôn nhỏ hơn hoặc bằng giá trị của các node con của nó (nếu có).

### Bản chất

Lấy ví dụ khi sắp xếp tăng dần. 

Khi ta build max heap, các số ở càng gần gốc cây nhị phân thì giá trị sẽ càng cao. Vì thế, ta đẩy chúng về cuối mảng.

==> Luôn đảm bảo phần tử ở cuối là phần tử lớn nhất.

Ở mỗi lần swap thành công, ta giảm boundary đi 1 để không can thiệp vào phần tử lớn nhất đã sort ở cuối. Nhờ bước này, phần tử ở i = 0 sẽ luôn là phần tử lớn nhất trong phần unsorted của mảng.

## Code

```cpp
//Ascending
void heap_sort(vector<int>& arr)
{
	//Build max heap
	for(int i = arr.size()/2 - 1; i > -1; --i)
	{
		maxHeapify(arr, i, 2*i + 1, 2*i + 2, arr.size());
	}

	//Swap 
	for(int boundary = arr.size() - 1; boundary > 0; --boundary)
	{
		swap(arr[boundary], arr[0]);

		maxHeapify(arr, 0, 1, 2, boundary + 1);
	}
}

void maxHeapify(vector<int>& arr, int root, int left, int right, int heapSize)
{
	if(left >= root) return;

	int maxInd = root;

	if(arr[left] > arr[maxInd]) maxInd = left;

	if(right < heapSize)
	{
		if(arr[right] > arr[maxInd]) maxInd = right;
	}

	if(maxInd != root)
	{
		swap(arr[maxInd], arr[root]);

		maxHeapify(arr, maxInd, maxInd * 2 + 1, maxInd * 2 + 2, heapSize);
	}
}

```

## Complexity

Cả 3 case đều có time complexity là O(N * log(N)) (recursive): Có log2(N) tầng, mỗi tầng thực hiện N khối lượng công việc.

UIT (tính đến HK1 2026-2027) không dạy iterative nên ta bỏ qua.

Space: O(log(N)) đối với recursive.
