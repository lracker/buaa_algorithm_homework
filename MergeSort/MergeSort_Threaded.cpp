#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>

typedef struct _PARAMETER
{
	int* arr;
	int left;
	int right;
	int index;
}PARAMETER;
void PrintArr(int* arr, int left, int right)
{
	for (int i = left;i <= right;i++)
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

void MergeSort1(int* arr, int left, int right)
{
	int mid = 0;
	if (left >= right)
		return;
	/*if (left < right)
	{*/
	mid = left + (right - left) / 2;
	MergeSort1(arr, left, mid);
	MergeSort1(arr, mid + 1, right);
	Merge(arr, left, mid, right);
}

void MergeSort(PARAMETER* parameter)
{
	//printf("本次线程：左->%d 右->%d\n", parameter->left, parameter->right);
	MergeSort1(parameter->arr, parameter->left, parameter->right);
	//PrintArr(parameter->arr, parameter->left, parameter->right);
}

void Merge2(PARAMETER* parameter, int ThreadNum, int size)
{
	int* arr = (int*)malloc(sizeof(int) * size);
	memset(arr, 0, size);
	int k = 0;
	int index = 0;
	int min = parameter[0].arr[0];
	for (int i = 0;i < size;i++)
	{

		for (int j = 0;j < ThreadNum;j++)
		{
			if (min >= parameter[j].arr[parameter[j].index]&&parameter[j].index<=parameter[j].right)
			{
				min = parameter[j].arr[parameter[j].index];
				index = j;	// 记录是哪个线程的首元素最小
			}
		}
		parameter[index].index++;
		arr[i] = min;
		for (int j = 0;j < ThreadNum;j++)
		{
			if (parameter[j].index <= parameter[j].right)
				min = parameter[j].arr[parameter[j].index];
		}
	}
	for (int i = 0;i < size;i++)
		parameter->arr[i] = arr[i];
}

int main()
{
	int ThreadNum ;	// 线程数
	printf("请输入线程数:\n");
	scanf_s("%d", &ThreadNum);
	clock_t  start, end;
	srand(time(0));
	int size = 1000*10000;	// 百万数据
	int* arr = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; ++i)
	{
		arr[i] = rand();
	}
	//int arr[12] = { 9,8,7,6,5,4,3,2,1,0, -1, -2 };
	//int size = 12;
	start = clock();
	HANDLE* ThreadHandle = (HANDLE*)malloc(sizeof(HANDLE) * ThreadNum);
	PARAMETER* parameter = (PARAMETER*)malloc(sizeof(PARAMETER) * ThreadNum);
	for (int i = 0;i < ThreadNum;i++)
	{
		parameter[i].arr = arr;
		parameter[i].left = (size / ThreadNum) * i;
		parameter[i].right = (i + 1) * (size/ThreadNum) - 1;
		parameter[i].index = parameter[i].left;
		ThreadHandle[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MergeSort, &parameter[i], 0, 0);
	}
	WaitForMultipleObjects(ThreadNum, ThreadHandle, TRUE, -1);
	Merge2(parameter, ThreadNum, size); // 多路归并
	end = clock();
	printf("完成时间：%f\n", (double)(end - start) / CLK_TCK);
	for (int i = 0; i < size; ++i)
	{
		if (i > 0 && arr[i - 1] > arr[i])
			printf("wrong %d %d\n", arr[i - 1], arr[i]);
	}
	system("pause");
}
