#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void PrintArr(char** arr, int n)
{
	for (int i = 0;i < n;i++)
		printf("%s ", arr[i]);
	printf("\n");
}

bool compare(char* arr1, char* arr2)	// 如果arr1表示的数字比arr2表示的数字小，则返回true
{
	if (strlen(arr1) < strlen(arr2))	
		return true;
	else if (strlen(arr1) > strlen(arr2))
		return false;
	else // strlen(arr1)==strlen(arr2)
	{
		if (strcmp(arr1, arr2) < 0)
			return true;
		else
			return false;
	}
}

void Merge(char** arr, int left, int mid, int right)
{
	int h = 0;
	int i = left;
	int j = mid + 1;
	int k = 0;
	int len = right - left + 1;
	char** arr2 = (char**)malloc(sizeof(char*) * len);
	for (h = 0;h < len;h++)
	{
		arr2[h] = (char*)malloc(sizeof(char) * 102);
		memset(arr2[h], 0, 102);
	}
	while (i <= mid && j <= right)
	{
		if (compare(arr[i], arr[j])) // 比较大小
		{
			memcpy(arr2[k], arr[i], 102);
			i++;
		}
		else
		{
			memcpy(arr2[k], arr[j], 102);
			j++;
		}
		k++;
	}
	while (i <= mid)
		memcpy(arr2[k++], arr[i++], 102);
	while (j <= right)
		memcpy(arr2[k++], arr[j++], 102);
	for (h = 0;h < len;h++)
	{
		memcpy(arr[left + h], arr2[h], 102);
		free(arr2[h]);
		arr2[h] = NULL;
	}
	free(arr2);
	arr2 = NULL;
}

void MergeSort1(char** arr, int left, int right)
{
	int mid = left + (right - left) / 2;
	if (left < right)
	{
		MergeSort1(arr, left, mid);
		MergeSort1(arr, mid + 1, right);
		Merge(arr, left, mid, right);
	}
}

void MergeSort(char** arr, int left, int right)
{
	int n = right - left + 1;
	int NegativeCount = 0;
	int PositiveCount = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = 0;i <= right;i++)
	{
		if (arr[i][0] == '-')	// 计算负数的个数
			NegativeCount++;
		else
			PositiveCount++;
	}
	char** NegativeArr = (char**)malloc(sizeof(char*) * NegativeCount);
	char** PositiveArr = (char**)malloc(sizeof(char*) * PositiveCount);
	for (i = 0, j=0, k=0;i < n;i++)	// 正负数分组
	{
		if (arr[i][0] == '-')
		{
			NegativeArr[j] = (char*)malloc(sizeof(char) * 102);
			memset(NegativeArr[j], 0, 102);
			memcpy(NegativeArr[j], arr[i], 102);
			NegativeArr[j][0] = '0';
			j++;
		}
		else
		{
			PositiveArr[k] = (char*)malloc(sizeof(char) * 102);
			memset(PositiveArr[k], 0, 102);
			memcpy(PositiveArr[k], arr[i], 102);
			k++;
		}
	}
	MergeSort1(NegativeArr, 0, NegativeCount-1);	// 负数排序
	MergeSort1(PositiveArr, 0, PositiveCount-1);	// 负数排序
	j = 0;
	for (i = 0;i < NegativeCount;i++, j++)
	{
		memcpy(arr[j], NegativeArr[NegativeCount-i-1], 102);
		arr[j][0] = '-';
		free(NegativeArr[NegativeCount - i - 1]);
		NegativeArr[NegativeCount - i - 1] = NULL;
	}
	for (i = 0;i < PositiveCount;i++, j++)
	{
		memcpy(arr[j], PositiveArr[i], 102);
		free(PositiveArr[i]);
		PositiveArr[i] = NULL;
	}
	free(NegativeArr);
	free(PositiveArr);
	NegativeArr = NULL;
	PositiveArr = NULL;
}

int main()
{
	int n = 0;
	printf("请输入需要排序多少个数\n");
	scanf_s("%d", &n);
	char** arr = (char**)malloc(sizeof(char*) * n);
	for (int i = 0;i < n;i++)
	{
		arr[i] = (char*)malloc(sizeof(char) * 102);
		memset(arr[i], 0, 102);
		scanf_s("%s", arr[i], 102);
	}
	MergeSort(arr, 0, n - 1);
	PrintArr(arr, n);
	for (int i = 0;i < n;i++)
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;

}