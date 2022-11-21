#include <iostream>
#include<Windows.h>
#include <string>
using namespace std;
#define MAX_COUNT 1000000

//��������
void QuickSort(int arr[], int low, int high) {
    if (low >= high) return;
    int i = low;
    int j = high;
    int key = arr[i];//������
    while (i < j) {
        while (arr[j] >= key && i < j)
            j--;
        arr[i] = arr[j];//�ҵ���ֵ
        while (arr[i] <= key && i < j)
            i++;
        arr[j] = arr[i];

    }
    arr[i] = key;
    QuickSort(arr, low, i - 1);
    QuickSort(arr, i + 1, high);
}

int main()
{
    int* res = (int*)malloc(sizeof(int) * MAX_COUNT);
    int num = 0;
    while (num < MAX_COUNT) {
        res[num] = rand();
        num++;

    }



    DWORD startTime = GetTickCount();//��ʱ��ʼ
    //int test[5] = { 4,3,5,1,3 };
     QuickSort(res, 0, MAX_COUNT-1);
    //SelectSort(res, MAX_COUNT);
    DWORD endTime = GetTickCount();//��ʱ����
    string notic = "�߳�����ʱ��Ϊ:" + to_string(endTime - startTime) + "ms\n";
    cout << notic;
    //string test_str[6] = { "-75212474","22455","33","100000000000000000000000000000000000000000000000000000","8736483628456238","-55422000000000000000000000000000000012585516"};
    ////SelectSort_big(test_str, 6);
    //QuickSort_big(test_str, 0, 5);
    for (int i = 0; i < 6; i++)
        cout << res[i] << endl;
}