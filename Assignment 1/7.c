#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define pi 3.14159265358979323846

void swap(double* a,double* b){
    double temp = *a;
    *a = *b;
    *b = temp;
}

void bubble(double* arr,int n){
    for(int i=0;i<n-1;i++){
        int swapped = 0;
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                swap(&arr[j],&arr[j+1]);
                swapped=1;
            }
        }
        if(!swapped) break;
    }
}

double findMedian(double* arr, int n) {
    if (n % 2 == 1) return arr[n/2];
    else return (arr[n/2 - 1] + arr[n/2]) / 2.0;
}

int partition(double* arr,int s,int e,double pivot){
    int i=s,j=e;
    while (1) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;

        if (i >= j) return j;

        swap(&arr[i], &arr[j]);
    }
}

double MoM(double* arr, int s, int e) {
    int length = e - s + 1;
    if(length <= 5) {
        bubble(arr + s, length);
        return findMedian(arr + s, length);
    }
    int nlength = (length + 4) / 5;
    for(int i = 0; i < nlength; i++) {
        int left = s + i * 5;
        int right = left + 4;
        if(right > e) right = e;
        double median = MoM(arr, left, right);
        swap(&arr[right], &arr[s + i]);
    }
    return MoM(arr, s, s + nlength - 1);
}

void Quick_sort(double* arr,int s,int e){
    if(s<e){
    double pivot = MoM(arr, s, e);
    int p = partition(arr, s, e, pivot);
    Quick_sort(arr,s,p);
    Quick_sort(arr,p+1,e);
    }
}

int main() {
    // double arr[] = {8.3659,9.3654,2.9586,6.213,3.6584,4.2136};
    // int n = sizeof(arr)/sizeof(arr[0]);
    // Quick_sort(arr,0,n-1);
    // for(int i=0;i<n;i++){
    //     printf("%f\t",arr[i]);
    // }
    return 0;
}