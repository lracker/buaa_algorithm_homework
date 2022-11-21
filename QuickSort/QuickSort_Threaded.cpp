// 期末作业多线程.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <string>
#include<Windows.h>
#include<fstream>
#define THREAD_COUNT 4
using namespace std;


void QuickSort(int arr[], int low, int high) {
    if (low >= high) return;
    int i = low;
    int j = high;
    int key = arr[i];//从左到右
    while (i < j) {
        while (arr[j] >= key && i < j)
            j--;
        arr[i] = arr[j];//找到后赋值
        while (arr[i] <= key && i < j)
            i++;
        arr[j] = arr[i];

    }
    arr[i] = key;
    QuickSort(arr, low, i - 1);
    QuickSort(arr, i + 1, high);
}



void ThreadSort(int arr[], int size, int id) {
    DWORD startTime = GetTickCount();//计时开始
    //BubleSort(test1, MAX_SIZE);
    QuickSort(arr, 0, size - 1);
    //SelectSort(arr, size);
    DWORD endTime = GetTickCount();//计时结束
    string notic = "第" + to_string(id) + "组线程运行时间为:" + to_string(endTime - startTime) + "ms\n";
    cout << notic;
}

void init() {
    ofstream fout("./input.txt");
    srand(time(nullptr));
    for (int i = 0; i < 10000000; i++) {
        fout << rand() << endl;
    }
    fout << rand();
    fout << flush;

    fout.close();
}


int main()
{
    //init();
    int arr_size[THREAD_COUNT];
    int arr_index[THREAD_COUNT];
    for (int i = 0; i < THREAD_COUNT; i++) {
        arr_size[i] = 0;
        arr_index[i] = 0;
    }

    int test[THREAD_COUNT][25000000];
    int* res = (int*)malloc(sizeof(int) * 100000000);
    //int** test = malloc(sizeof(int) * 1000 * 1000);
    ifstream fin("./input.txt");
    int index = 0;
    string buf;
    int num = 0;
    //while (getline(fin, buf)) {
    //    int temp = stoi(buf);
    //    // cout << temp << endl;
    //     //将数据存放起来
    //    index = index % THREAD_COUNT;
    //    test[index][arr_size[index]] = temp;
    //    arr_size[index]++;
    //    index++;

    //}

    while (num < 5000000) {
        int temp = rand();
        // cout << temp << endl;
         //将数据存放起来
        index = index % THREAD_COUNT;
        test[index][arr_size[index]] = temp;
        arr_size[index]++;
        index++;
        num++;

    }

    DWORD startTime = GetTickCount();//计时开始

    /*for (int i = 0; i < THREAD_COUNT; i++) {
        thread t1(ThreadSort, test[i], arr_size[i], i+1);
        t1.join();
    }*/

    thread t1(ThreadSort, test[0], arr_size[0], 0);
    thread t2(ThreadSort, test[1], arr_size[1], 1);
    thread t3(ThreadSort, test[2], arr_size[2], 2);
    thread t4(ThreadSort, test[3], arr_size[3], 3);

    t1.join();
    t2.join();
    t3.join();
    t4.join();


    ////完成后进行Merge输出
    //ofstream fout("./res.txt");


    //int arr_min[THREAD_COUNT] = {INF,INF, INF};
    int min_index;//记录哪个队列最小
    //int min;//记录最小值
    int res_index = 0;
    while (true) {
        min_index = -1;  
        //找到最小队列和最小值
        for (int i = 0; i < THREAD_COUNT; i++) {
            //判断当前队列是否遍历完
            if (arr_index[i] < arr_size[i]) {
                if (min_index == -1)
                    min_index = i;
                else {
                    if (test[min_index][arr_index[min_index]] > test[i][arr_index[i]])
                        min_index = i;
                }
            }
        }
        if (min_index == -1) break;
        res[res_index] = test[min_index][arr_index[min_index]];
        res_index++;
        //fout << test[min_index][arr_index[min_index]] << endl;
        arr_index[min_index]++;

    }
    //fout << flush;

    //fout.close();



    DWORD endTime = GetTickCount();//计时结束
    string notic = "线程运行时间为:" + to_string(endTime - startTime) + "ms\n";
    cout << notic;
}

