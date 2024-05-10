#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define pi 3.14159265358979323846

float generate_normal_random(float mean, float stddev) {
    float u1 = ((float)rand() / RAND_MAX);
    float u2 = ((float)rand() / RAND_MAX);
    float z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * pi * u2);
    return mean + stddev * z0;
}

void swap(float *a, float *b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

int Randomized_partition(float *arr, int s, int e, int *cnt) {
    srand(time(0));
    int random = s + (rand() % (e - s));
    float pivot = arr[random];
    swap(&arr[random], &arr[s]);
    int i = s - 1, j = e + 1;
    while (1) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j) {
            return j;
        }

        swap(&arr[i], &arr[j]);
        (*cnt)++;
    }
}

void Randomized_Quick_sort(float *arr, int s, int e, int *cnt) {
    if (s < e) {
        int p = Randomized_partition(arr, s, e, cnt);
        Randomized_Quick_sort(arr, s, p, cnt);
        Randomized_Quick_sort(arr, p + 1, e, cnt);
    }
}

int main() {
    int trials;
    printf("Enter the number of trials: ");
    scanf("%d", &trials);

    for (int power = 1; power <= 10; power++) {
        int num = pow(2, power);

        // Uniform Distribution (UD) dataset
        printf("\nUniform Distribution dataset for %d data points:\n", num);
        float *ud_arr = (float *)malloc(sizeof(float) * num);

        int total_ud_operations = 0;

        for (int t = 0; t < trials; t++) {
            for (int i = 0; i < num; ++i) {
                ud_arr[i] = ((float)rand() / RAND_MAX);
            }

            int ud_qcount = 0;
            Randomized_Quick_sort(ud_arr, 0, num - 1, &ud_qcount);

            total_ud_operations += ud_qcount;
        }

        float average_ud_operations = (float)total_ud_operations / trials;
        printf("Average number of operations (UD) over %d trials: %.2lf\n", trials, average_ud_operations);
        free(ud_arr);

        // Normal Distribution (ND) dataset
        printf("\nNormal Distribution dataset for %d data points:\n", num);
        float *nd_arr = (float *)malloc(sizeof(float) * num);

        int total_nd_operations = 0;

        for (int t = 0; t < trials; t++) {
            for (int i = 0; i < num; ++i) {
                nd_arr[i] = generate_normal_random(0.0, 1.0);
            }

            int nd_qcount = 0;
            Randomized_Quick_sort(nd_arr, 0, num - 1, &nd_qcount);

            total_nd_operations += nd_qcount;
        }

        float average_nd_operations = (float)total_nd_operations / trials;
        printf("Average number of operations (ND) over %d trials: %.2lf\n", trials, average_nd_operations);
        free(nd_arr);
    }

    return 0;
}