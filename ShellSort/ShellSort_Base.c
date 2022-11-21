#include<stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

clock_t start , stop;

double duration;
void shell_sort(int arr[],int len)
   {   
      int tem,gap;
      int i,j;
     for(gap=len/2;gap>=1;gap/=2)//以gap/2为下一次的分组数量
      {
        for(i=gap;i<len;i++)//从下标为gap的数据开始，gap为间隔向前插入排序
          {
              tem=arr[i];         // 当前回溯点，从这开始不断向前比较大小，直到找到正确的位置。
              j=i-gap;
              while(j>=0&&tem<arr[j])//假如当前回溯点小于一个gap之前的值，则一个gap之前的值后移一个gap，继续向前比较
              {
                 arr[j+gap]=arr[j];//被比较的数字大则后移一个gap
                 j-=gap;//继续向前一个gap比较
              }
              arr[j+gap]=tem;     // 走到最前面或者大于前一个gap，找到正确位置插入
          }
      }
     }

 void main()
 {start = clock();
    srand(time(0));
    int len = 10000000; // 百万数据
    int *arr = (int*)malloc(sizeof(int) * len);
    for (int i = 0; i < len; ++i)
    {arr[i] = rand();}
    shell_sort(arr,len);
    stop = clock();
    duration = ((double)(stop - start))/CLK_TCK;
    printf("\ntime:%f",duration);

 }