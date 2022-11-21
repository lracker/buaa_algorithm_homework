

#include <iostream>
#include<Windows.h>
#include <string>
using namespace std;
#define MAX_COUNT 1000000
//选择排序
void SelectSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[min_index] > arr[j])
                min_index = j;
        }
        if (min_index != i) {
            int temp = arr[min_index];
            arr[min_index] = arr[i];
            arr[i] = temp;
        }
    }
}

int main()
{
    int* res = (int*)malloc(sizeof(int) * MAX_COUNT);
    int num = 0;
    while (num < MAX_COUNT) {
        res[num] = rand();
        num++;

    }



    DWORD startTime = GetTickCount();//计时开始
    //int test[5] = { 4,3,5,1,3 };
    //QuickSort(res, 0, MAX_COUNT - 1);
    SelectSort(res, MAX_COUNT);
    DWORD endTime = GetTickCount();//计时结束
    string notic = "线程运行时间为:" + to_string(endTime - startTime) + "ms\n";
    cout << notic;
    //string test_str[6] = { "-75212474","22455","33","100000000000000000000000000000000000000000000000000000","8736483628456238","-55422000000000000000000000000000000012585516"};
    ////SelectSort_big(test_str, 6);
    //QuickSort_big(test_str, 0, 5);
    for (int i = 0; i < 6; i++)
        cout << res[i] << endl;
}