#include <iostream>
void print(int arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		std::cout << arr[i] << "  ";
	}
	std::cout << std::endl;
}

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

// Ã°ÅÝÅÅÐò
void bubbleSort(int *unsortArray, const int &length) {
	for (int i = 0; i < length; ++i) {
		for (int j = 0; j < length - 1 - i; ++j) {
			if (unsortArray[j] > unsortArray[j + 1]) {
				swap(unsortArray[j], unsortArray[j + 1]);
			}
		}
	}
}

void SelectionSort(int *arr, int size)
{
	int i, j, k;
	for (i = 0; i < size - 1; i++) {
		k = i;
		for (j = i + 1; j < size; j++) {
			if (arr[j] < arr[k]) {
				k = j;
			}
		}
		swap(arr[k], arr[i]);
	}
}

void InsertionSort(int *arr, int size)
{
	int i, j, tmp;
	for (i = 1; i < size; i++) {
		if (arr[i] < arr[i - 1]) {
			tmp = arr[i];
			for (j = i - 1; j >= 0 && arr[j] > tmp; j--) {
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = tmp;
		}
		print(arr, size);
	}
}

void QuickSort(int *arr, int maxlen, int begin, int end)
{
	int i, j;
	if (begin < end) {
		i = begin + 1;
		j = end;
		while (i < j) {
			if (arr[i] > arr[begin]) {
				swap(arr[i], arr[j]);
				j--;
			}
			else {
				i++;
			}
		}
		if (arr[i] >= arr[begin]) {
			i--;
		}
		swap(arr[begin], arr[i]);
		QuickSort(arr, maxlen, begin, i);
		QuickSort(arr, maxlen, j, end);
	}
	print(arr, maxlen);
}


void Heapify(int *arr, int m, int size)
{
	int i, tmp;
	tmp = arr[m];
	for (i = 2 * m; i <= size; i *= 2) {
		if (i + 1 <= size && arr[i] < arr[i + 1]) {
			i++;
		}
		if (arr[i] < tmp) {
			break;
		}
		arr[m] = arr[i];
		m = i;
	}
	arr[m] = tmp;
}

void BulidHeap(int *arr, int size)
{
	int i;
	for (i = n / 2; i > 0; i--) {
		Heapify(arr, i, size);
	}
}

void swap(int *arr, int i, int j)
{
	int tmp;
	tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

void HeapSort(int *arr, int size)
{
	int i;
	BulidHeap(arr, size);
	for (i = size; i > 1; i--) {
		swap(arr, 1, i);
		Heapify(arr, 1, i - 1);
	}
}


int main()
{
	int arr[] = { 3, 5, 4, 2, 1, 6 };
	HeapSort(arr, sizeof(arr) / sizeof(int));
	// QuickSort(arr, sizeof(arr) / sizeof(int), 0, 5);
	print(arr, sizeof(arr) / sizeof(int));

	system("pause");
}