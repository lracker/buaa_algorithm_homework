#include <stdio.h>
#include <stdlib.h>
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
	for (int i = left; i <= right; i++)
		printf("%d ", arr[i]);
	printf("\n");
}
void RadixSort2(int* arr, int left, int n, int exp)
{
	int* bucket[10];// ����ʮ��Ͱ
	for (int i = 0; i < 10; i++)
	{
		bucket[i] = (int*)malloc(sizeof(int) * n);
 		memset(bucket[i], 0, n*sizeof(int));
	}
	int count[10] = { 0 };
	int index;
	for (int i = 0; i < n; i++) // ����Ͱ��
	{
		index = arr[left+i] / exp % 10;
		bucket[index][count[index]] = arr[left+i];
		count[index]++;
	}
	int k = 0;
	// ��ԭ��ԭ����
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < count[i]; j++)
			arr[left+k++] = bucket[i][j];
	}
	for (int i = 0; i < 10; i++)
	{
		free(bucket[i]);
		bucket[i] = NULL;
	}
}

int GetMax(int* arr, int left, int n)
{
	int count = 0;
	int max = arr[left];	// �������Ԫ���Ǵ�left��ʼ��
	for (int i = 0; i < n; i++)
	{
		if (max < arr[left + i])
			max = arr[left + i];
	}
	while (max / 10)
	{
		max = max / 10;
		count++;
	}
	return count + 1;
}
void RadixSort1(PARAMETER* parameter)
{
	//printf("��%d �ң�%d\n", parameter->left, parameter->right);
	int n = parameter->right - parameter->left + 1;
	int MaxCount = GetMax(parameter->arr, parameter->left, n);
	int exp = 1;
	for (int i = 0; i < MaxCount; i++)
	{
		RadixSort2(parameter->arr, parameter->index, n, exp);
		//PrintArr(parameter->arr, n);
		exp = exp * 10;
	}
}

void Merge(PARAMETER* parameter, int ThreadNum, int n)
{
	int min;
	int index=0;
	int* arr = (int*)malloc(sizeof(int) * n);
	memset(arr, 0, n*sizeof(int));
	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < ThreadNum; i++)
		{
			if (parameter[i].index <= parameter[i].right)
			{
				min = parameter[i].arr[parameter[i].index];	// ��ʣ���������ҳ�һ��
				break;
			}
		}
		for (int i = 0; i < ThreadNum; i++)
		{
			if (min >= parameter[i].arr[parameter[i].index] && parameter[i].index <= parameter[i].right)
			{
				min = parameter[i].arr[parameter[i].index];	// �ҳ���С��
				index = i;
			}
		}
		parameter[index].index++;
		arr[k] = min;
	}
	for (int i = 0; i < n; i++)
		parameter->arr[i] = arr[i];
}
int main()
{
	int ThreadNum;
	printf("�������߳���:\n");
	scanf_s("%d", &ThreadNum);
	clock_t start, end;
	srand((unsigned int)time(NULL));
	int size = 1000*10000;
	int* arr = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand();
	}
	PARAMETER* parameter = (PARAMETER*)malloc(sizeof(PARAMETER) * ThreadNum);
	HANDLE* ThreadHandle = (HANDLE*)malloc(sizeof(HANDLE) * ThreadNum);
	start = clock();
	for (int i = 0; i < ThreadNum; i++)
	{
		parameter[i].arr = arr;
		parameter[i].left = i * (size / ThreadNum);
		parameter[i].right = (i + 1) * (size / ThreadNum) - 1;
		parameter[i].index = parameter[i].left;
		ThreadHandle[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RadixSort1, &parameter[i], 0, NULL);
	}
	WaitForMultipleObjects(ThreadNum, ThreadHandle, TRUE, -1);
	Merge(parameter, ThreadNum, size);
	end = clock();
	//PrintArr(arr, 1000);
	printf("����ʱ�䣺%f\n", (double)(end - start) / CLK_TCK);
	for (int i = 0; i < size; ++i)
	{
		//printf("%d \n",arr[i]);
		if (i > 0 && arr[i - 1] > arr[i])
			printf("wrong %d %d\n", arr[i - 1], arr[i]);
	}
}