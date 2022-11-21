#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void PrintArr(int* arr, int n)
{
	for (int i = 0;i < n;i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void Merge(int* arr, int left, int mid, int right)
{
	int i = left;
	int j = mid + 1;
	int k = 0;
	int len = right - left + 1;
	int* arr2 = (int*)malloc(sizeof(int) * len);	// 辅助数组
	while (i <= mid && j <= right)	// 比较
	{
		if (arr[i] < arr[j])
		{
			arr2[k] = arr[i];
			i++;
		}
		else
		{
			arr2[k] = arr[j];
			j++;
		}
		k++;
	}
	while (i <= mid)
		arr2[k++] = arr[i++];
	while (j <= right)
		arr2[k++] = arr[j++];
	for (int j = 0;j < len;j++)
		arr[left + j] = arr2[j];
	free(arr2);
	arr2 = NULL;
}

void MergeSort(int* arr, int left,int right)
{
	int mid = 0;
	if (left < right)
	{
		mid = left + (right - left) / 2;
		MergeSort(arr, left, mid);
		MergeSort(arr, mid + 1, right);
		Merge(arr, left, mid, right);
	}
}

int main()
{
	int arr[5] = { 5,4,0,2,-1 };
	MergeSort(arr, 0, 4);
	PrintArr(arr, 5);
}