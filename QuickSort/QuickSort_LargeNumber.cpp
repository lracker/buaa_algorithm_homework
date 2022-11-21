// ѡ������.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#include<Windows.h>
#include <string>
using namespace std;
#define MAX_COUNT 1000000

//�ж��Ƿ����
bool cmp(string a, string b) {
    //�����Ƚ�
    if (a[0] != '-' && b[0] != '-') {
        if (a.length() == b.length()) {
            for (int i = 0; i < a.length(); i++) {
                if (a[i] > b[i]) return true;
                else if (a[i] < b[i]) return false;
            }
            return false;//���������һ��
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
            return false;//���������һ��
        }
        else {
            return a.length() < b.length();
        }
    }
}



//�����������
void QuickSort_big(string arr[], int low, int high) {
    if (low >= high) return;
    int i = low;
    int j = high;
    string key = arr[i];//������
    while (i < j) {
        while ((!cmp(key, arr[j])) && i < j)
            j--;
        arr[i] = arr[j];//�ҵ���ֵ
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


