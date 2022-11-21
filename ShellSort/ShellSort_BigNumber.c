#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int compare(char A[],char B[]){//返回-1，0，1，分别代表小于，等于和大于
    int sign_A;//A数组符号位
    int sign_B;//B数组符号位
    if(A[0]=='-'){sign_A=-1;}//负数符号位-1，整数符号位1，方便后面做判断
    else{sign_A=1;}
    if(B[0]=='-'){sign_B=-1;}
    else{sign_B=1;}
    if((sign_A*sign_B)==-1){return strcmp(A,B);}//如果一正一负直接strcmp,'-'比所有char类型数字小，可以直接返回
    else{
        if(strlen(A)==strlen(B)){
            return sign_A*strcmp(A,B);
        }//位数相等，则直接strcmp比较，考虑到负数情况相反，乘一个符号位sign
        else{
            //printf("get_here------------");
            if(strlen(A)>strlen(B)){return sign_A*1;}//位数不相等直接比较位数，负数情况相反乘符号位
            else{return sign_A*-1;}
        }
    }//正正负负的情况
}

void shell_sort(char **arr,int len)
   {   
      int gap;
      int i,j;
      int result;
      char tem[102];
      
     for(gap=len/2;gap>=1;gap/=2)//以gap/2为下一次的分组数量
      {
        for(i=gap;i<len;i++)//从下标为gap的数据开始，gap为间隔向前插入排序
          {
            for(int t=0;t<102;t++){
                    tem[t]=arr[i][t];}
              //tem=arr[i];         // 当前回溯点，从这开始不断向前比较大小，直到找到正确的位置。
              j=i-gap;
              //result=compare(tem,arr[j])
              
              while(j>=0&&compare(tem,arr[j])<0)//假如当前回溯点小于一个gap之前的值，则一个gap之前的值后移一个gap，继续向前比较
              {
                for(int k=0;k<102;k++){
                    arr[j+gap][k]=arr[j][k];
                }
                 //arr[j+gap]=arr[j];//被比较的数字大则后移一个gap
                 j-=gap;//继续向前一个gap比较
              }
              //printf("%d",i+gap);
              for(int k=0;k<102;k++){
                arr[j+gap][k]=tem[k];
                }
              //arr[j+gap]=tem;     // 走到最前面或者大于前一个gap，找到正确位置插入
          }
      }
     }

int main(){
    int n;//排序数量
    printf("sort number:");
    scanf("%d",&n);
    char **arr;
    arr=(char **)malloc(sizeof(char *)*n);
    for(int i=0;i<n;i++){arr[i]=(char *)malloc(sizeof(char)*102);}
    //char arr[n][102];
    printf("input:");
    for(int i=0;i<n;i++){
        scanf("%s",arr[i]);
    }
    printf("\n");
    //shell_sort(arr,n)
    printf("before sorted:");
    for(int i=0;i<n;i++){
        for(int j=0;j<strlen(arr[i]);j++){
            printf("%c",arr[i][j]);
        }
        printf(" ");
    }
    printf("\nafter_sorted:");
    shell_sort(arr,n);
    for(int i=0;i<n;i++){printf("%s ",arr[i]);}
    }