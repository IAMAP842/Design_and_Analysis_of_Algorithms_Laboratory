#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> //for true keyword

// all position should be given according to zero indexed array

void insertion_sort(int arr[], int initial, int final) {
    for (int i = initial; i <= final; i++) {
        int value = arr[i];
        int pos = i - 1;
        while (pos >= initial && arr[pos] > value) {
            arr[pos + 1] = arr[pos];
            pos--;
        }
        arr[pos + 1] = value;
    }
}

// all position should be given according to zero indexed array

int give_median(int arr[], int initial, int final) {
    insertion_sort(arr, initial, final);
    int mid = (initial + final) / 2;
    return arr[mid];
}

//give arr_size as sizeof(arr)/sizeof(int)

int median_of_median(int arr[], int arr_size, int divide_size) {
    if (arr_size < divide_size) {
        int median = give_median(arr, 0, arr_size - 1);
        return median;
    }
    int no_full_group = arr_size / divide_size;
    int elements_in_last = arr_size % divide_size;
    int next_arr_size;
    if (elements_in_last == 0)
        next_arr_size = no_full_group;
    else
        next_arr_size = no_full_group + 1;
    int next_arr[next_arr_size];
    for (int i = 0; i < next_arr_size; i++) {
        if (i == next_arr_size - 1)
            next_arr[i] = give_median(arr, divide_size * i, arr_size - 1);
        else
            next_arr[i] = give_median(arr, divide_size * i, divide_size * (i + 1) - 1);
    }
    return median_of_median(next_arr, next_arr_size, divide_size);
}

void swap(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

int partition(int *arr, int initial, int final) {
    int pivot_value = arr[initial];
    int left_iterator = initial;
    int right_iterator = final;
    while (true) {
        while (arr[left_iterator] < pivot_value)
            left_iterator++;
        while (pivot_value < arr[right_iterator])
            right_iterator--;
        if (arr[left_iterator] == arr[right_iterator]) {
            if (left_iterator == right_iterator)
                return left_iterator;
            else
                right_iterator--;
        }
        else if (left_iterator < right_iterator)
            swap(&arr[left_iterator], &arr[right_iterator]);
        else
            return left_iterator;
    }
}

int find_partition_size_MoM(int *arr, int arr_size, int divide_size) {
    int val = median_of_median(arr, arr_size, divide_size);
    for (int i = 0; i < arr_size; i++)
        if (arr[i] == val) {
            swap(&arr[0], &arr[i]);
            return partition(arr, 0, arr_size - 1);
        }
}

void text_to_arr(int *arr, int n) {
    FILE *fin = fopen("UniDist.txt", "r");
    int temp = 0;
    for (int i = 0; i < n; i++) {
        int skip_line = rand() % 10;
        for (int j = 0; j < skip_line; j++)
            fscanf(fin, "%d\n", &temp);
        fscanf(fin, "%d\n", &temp);
        arr[i] = (short)temp;
    }
}

int main() {
    srand(time(0));
    const int max_arr_size = 1e5;
    int divide_size = 5;
    int num_iter = 10;
    int part_size;
    float avg_part_size;
    FILE *fout = fopen("mom_normal_part_7_obs.txt", "w");
    fprintf(fout, "arr_size,avg_partition_size\n");
    for (int arr_size = 100; arr_size <= max_arr_size; arr_size += 100) {
        int arr[arr_size];
        avg_part_size = 0;
        for (int i = 0; i < num_iter; i++) {
            text_to_arr(arr, arr_size);
            part_size = find_partition_size_MoM(arr, arr_size, divide_size);
            avg_part_size += part_size;
        }
        avg_part_size = avg_part_size / num_iter;
        printf("array_size: %d avg_part_size: %f \n", arr_size, avg_part_size);
        fprintf(fout, "%d,%f\n", arr_size, avg_part_size);
    }
    fclose(fout);
    return 0;
}