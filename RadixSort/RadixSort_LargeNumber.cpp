#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void PrintArr(char** buffer, int n)
{
	for (int i = 0; i < n; i++)
		printf("%s ", buffer[i]);
	printf("\n");
}

int GetMaxCount(char** arr, int n)
{
	int MaxCount = strlen(arr[0]);
	for (int i = 0; i < n; i++)
	{
		if (strlen(arr[i]) > MaxCount)
			MaxCount = strlen(arr[i]);
	}
	return MaxCount;
}

void RadixRank3(char** arr, int n, int exp)
{
	char*** bucket = (char***)malloc(sizeof(char**) * 10);
	int count[10] = { 0 };	// ����10��Ͱ����ֱ��ж��ٸ������ˡ�
	int index = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = 0; i < 10; i++)	// ��ʼ��bucket
	{
		bucket[i] = (char**)malloc(sizeof(char*) * n);
		for (j = 0; j < n; j++)
		{
			bucket[i][j] = (char*)malloc(sizeof(char) * 102);
			memset(bucket[i][j], 0, 102);
		}
	}
	for (i = 0; i < n; i++)	// ����������ݷ��䵽bucket��
	{
		if (strlen(arr[i]) < exp)
			index = 0;
		else
			index = arr[i][strlen(arr[i]) - exp]-'0';	// ��Ϊ�õ������ַ����֣�����Ҫ��ȥ'0'
		memcpy(bucket[index][count[index]], arr[i], 102);
		count[index]++;
	}
	//for (i = 0; i < 10; i++)
	//	PrintArr(bucket[i], count[i]);
	// ��������bucket�л�ԭ��ԭ����
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < count[i]; j++)
		{
			memcpy(arr[k], bucket[i][j], 102);
			k++;
		}
	}
	// �ͷ��ڴ�
	for (i = 0; i < 10; i++)	// ��ʼ��bucket
	{
		for (j = 0; j < n; j++)
		{
			free(bucket[i][j]);
			bucket[i][j] = NULL;	// ����Ұָ��
		}
		free(bucket[i]);
		bucket[i] = NULL;
	}
}

void RadixRank2(char** arr, int n)
{
	int MaxCount = GetMaxCount(arr, n);
	int exp = 1;
	for (int i = 0; i < MaxCount; i++)
	{
		RadixRank3(arr, n, exp);
		exp++;
	}
	//PrintArr(arr, n);
}
void RadixRank1(char** arr, int n)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int NegativeCount = 0;
	int PositiveCount = 0;
	for (i = 0; i < n; i++)
	{
		if (arr[i][0] == '-')	// ����Ǹ���
		{
			NegativeCount++;
		}
	}
	char** NegativeArr = (char**)malloc(sizeof(char*) * NegativeCount);	// Ϊ������������
	char** PositiveArr = (char**)malloc(sizeof(char*) * (n-NegativeCount)); // Ϊ������������
	for (i = 0; i < NegativeCount; i++)
	{
		NegativeArr[i] = (char*)malloc(sizeof(char) * 102);
		memset(NegativeArr[i], 0, 102);
	}
	PositiveCount = n - NegativeCount;
	for (i = 0; i < PositiveCount; i++)
	{
		PositiveArr[i] = (char*)malloc(sizeof(char) * 102);
		memset(PositiveArr[i], 0, 102);
	}
	for (i = 0; i < n; i++)
	{
		if (arr[i][0] == '-')	// ����Ǹ���
		{
			memcpy(NegativeArr[j], arr[i], 102);
			NegativeArr[j][0] = '0';	// ��������Ϊ0
			j++;
		}
		else
		{
			memcpy(PositiveArr[k], arr[i], 102);
			k++;
		}
	}
	//PrintArr(NegativeArr, NegativeCount);
	//PrintArr(PositiveArr, PositiveCount);
	if(NegativeCount>0)
		RadixRank2(NegativeArr, j);	// �Ը�����������
	if (PositiveCount > 0)
		RadixRank2(PositiveArr, k);	// ��������������
	for (i = 0; i < NegativeCount; i++)
	{
		NegativeArr[NegativeCount - i - 1][0] = '-';
		memcpy(arr[i], NegativeArr[NegativeCount - i - 1], 102);
		free(NegativeArr[NegativeCount - i - 1]);
		NegativeArr[NegativeCount - i - 1] = NULL;
	}
	for (i = 0; i < PositiveCount; i++)
	{
		memcpy(arr[i + NegativeCount], PositiveArr[i], 102);
		free(PositiveArr[i]);
		PositiveArr[i] = NULL;
	}
}

void main()
{
	int n;
	printf("��������Ҫ���������\n");
	scanf_s("%d", &n);
	char** arr = (char**)malloc(sizeof(char*) * n);
	for (int i = 0; i < n; i++)
	{
 		arr[i] = (char*)malloc(sizeof(char) * (100 + 2));	// ��ΪҪ֧��[-10^100,10^100]������,����ռһλ��10^100ռһλ
		memset(arr[i], 0, sizeof(100 + 2));
		scanf_s("%s", arr[i], 100 + 2);
	}
	RadixRank1(arr, n);
	printf("�����Ľ��\n");
	PrintArr(arr, n);
	for (int i = 0; i < n; i++)
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;
}