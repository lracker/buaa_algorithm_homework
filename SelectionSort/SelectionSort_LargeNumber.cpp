#include<Windows.h>
#include <string>
#include <iostream>
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
//选择排序大数版本
void SelectSort_big(string arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < size; j++) {
            if (cmp(arr[min_index], arr[j]))
                min_index = j;
        }
        if (min_index != i) {
            string temp = arr[min_index];
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



    string test_str[6] = { "-75212474","22455","33","100000000000000000000000000000000000000000000000000000","8736483628456238","-55422000000000000000000000000000000012585516"};
    SelectSort_big(test_str, 6);
    //QuickSort_big(test_str, 0, 5);
    for (int i = 0; i < 6; i++)
        cout << test_str[i] << endl;
}