// 选择排序.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<Windows.h>
#include <string>
using namespace std;
#define MAX_COUNT 1000000

//判断是否大于
bool cmp(string a, string b) {
    //正正比较
    if (a[0] != '-' && b[0] != '-') {
        if (a.length() == b.length()) {
            for (int i = 0; i < a.length(); i++) {
                if (a[i] > b[i]) return true;
                else if (a[i] < b[i]) return false;
            }
            return false;//这种情况是一样
        }
        else {
            return a.length() > b.length();
        }
    }
    else if (a[0] == '-' && b[0] != '-') return false;
    else if (a[0] != '-' && b[0] == '-') return true;
    else {
        if (a.length() == b.length()) {
            for (int i = 1; i < a.length(); i++) {
                if (a[i] > b[i]) return false;
                else if (a[i] < b[i]) return true;
            }
            return false;//这种情况是一样
        }
        else {
            return a.length() < b.length();
        }
    }
}



//快速排序大数
void QuickSort_big(string arr[], int low, int high) {
    if (low >= high) return;
    int i = low;
    int j = high;
    string key = arr[i];//从左到右
    while (i < j) {
        while ((!cmp(key, arr[j])) && i < j)
            j--;
        arr[i] = arr[j];//找到后赋值
        while ((!cmp(arr[i], key)) && i < j)
            i++;
        arr[j] = arr[i];

    }
    arr[i] = key;
    QuickSort_big(arr, low, i - 1);
    QuickSort_big(arr, i + 1, high);
}


int main()
{
    string test_str[6] = { "-75212474","22455","33","100000000000000000000000000000000000000000000000000000","8736483628456238","-55422000000000000000000000000000000012585516"};
    //SelectSort_big(test_str, 6);
    QuickSort_big(test_str, 0, 5);
    for (int i = 0; i < 6; i++)
        cout << test_str[i] << endl;
}


