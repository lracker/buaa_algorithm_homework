#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define MAX 987654321
clock_t start , stop;

double duration;


typedef struct _sonarr{
int* start;
int* end;
int len;
}sonarr;

DWORD APIENTRY ThreadOne ( LPVOID threadArg )
   {  sonarr *son_para=(sonarr*)threadArg;
      int tem,gap;
      int i,j;
      //int arr[];
      int *p=son_para -> start;
      int len=son_para -> len;
      //printf("start:%d\n",son_start);
     for(gap=len/2;gap>=1;gap/=2)//以gap/2为下一次的分组数量
      {
        for(i=gap;i<len;i++)//从下标为gap的数据开始，gap为间隔向前插入排序
          {
              tem=p[i];         // 当前回溯点，从这开始不断向前比较大小，直到找到正确的位置。
              j=i-gap;
              while(j>=0&&tem<p[j])//假如当前回溯点小于一个gap之前的值，则一个gap之前的值后移一个gap，继续向前比较
              {
                 p[j+gap]=p[j];//被比较的数字大则后移一个gap
                 j-=gap;//继续向前一个gap比较
              }
              p[j+gap]=tem;     // 走到最前面或者大于前一个gap，找到正确位置插入
          }
      }
     }

void Merge_mul(sonarr *p,int num,int len){
    int *new=(int*)malloc(sizeof(int)*len);
    int min=MAX;
    int min_index;
    int *ini_arr=p[0].start;
    for(int j=0;j<len;j++){
    for(int i=0;i<num;i++){
        if(p[i].start<=p[i].end&&(*p[i].start)<min){
            min_index=i;
            min=(*p[i].start);
        }  
    }
    new[j]=*p[min_index].start;
    printf("%d ",new[j]);
    p[min_index].start++;
    min=MAX;
    }
    for(int j=0;j<len;j++){*ini_arr=new[j];ini_arr++;}
    //for(int j=0;j<len;j++){printf("%d ",new[j]);}
}

void main(){
    start = clock();
    int thread_num=4;
    /*
    int len=8;
    int arr[len];
    printf("input:");
    for(int i=0;i<len;i++){scanf("%d",&arr[i]);}*/
    srand(time(0));
    int len = 20; // 百万数据
    int *arr = (int*)malloc(sizeof(int) * len);
    for (int i = 0; i < len; ++i)
    {arr[i] = rand();}
    HANDLE *thread_pool=(HANDLE*)malloc(sizeof(HANDLE)*thread_num);
    sonarr *sonarr_pool=(sonarr*)malloc(sizeof(sonarr)*thread_num);
    for(int i=0;i<thread_num;i++){
        sonarr_pool[i].start=&arr[i*(len/thread_num)];
        if(i!=thread_num-1){
            sonarr_pool[i].end=&arr[(i+1)*(len/thread_num)-1];
            sonarr_pool[i].len=len/thread_num;}
        else{sonarr_pool[i].end=&arr[len-1];
            sonarr_pool[i].len=len-i*(len/thread_num);}
        thread_pool[i] = CreateThread ( NULL, 0L, ThreadOne, (LPVOID *)&sonarr_pool[i], 0L, 0L );
            
    }

    for(int i=0;i<thread_num;i++){
        WaitForSingleObject(thread_pool[i], INFINITE );}
/*
    printf("\n\nsorted:");
    for(int i=0;i<len;i++){printf("%d ",arr[i]);}
    printf("\n");
    Merge_mul(sonarr_pool,thread_num,len);
    
    
    printf("\nmerged:");
    for(int i=0;i<len;i++){printf("%d ",arr[i]);}*/
Merge_mul(sonarr_pool,thread_num,len);
stop = clock();
duration = ((double)(stop - start))/CLK_TCK;
printf("\ntime:%f",duration);

}

