#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define pi 3.14159265358979323846

double generate_normal_random()
{
    double u1 = ((double)rand() / RAND_MAX);
    double u2 = ((double)rand() / RAND_MAX);
    double z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * pi * u2);
    return z0;
}

void swap(double *a, double *b)
{
    double c = *a;
    *a = *b;
    *b = c;
}

void merge(double *arr, int s, int mid, int e, int *cnt)
{
    int l1 = (mid - s) + 1;
    int l2 = (e - mid);
    double arr1[l1], arr2[l2];
    for (int i = 0; i < l1; i++)
    {
        arr1[i] = arr[s + i];
    }
    for (int i = 0; i < l2; i++)
    {
        arr2[i] = arr[mid + 1 + i];
    }
    int index1 = 0, index2 = 0;
    int k = s;
    while (index1 < l1 && index2 < l2)
    {
        if (arr1[index1] < arr2[index2])
        {
            arr[k++] = arr1[index1++];
            (*cnt)++;
        }
        else
        {
            arr[k++] = arr2[index2++];
            (*cnt)++;
        }
    }
    while (index1 < l1)
    {
        arr[k++] = arr1[index1++];
        (*cnt)++;
    }
    while (index2 < l2)
    {
        arr[k++] = arr2[index2++];
        (*cnt)++;
    }
}

int partition(double *arr, int s, int e, int *cnt)
{
    double pivot = arr[s];
    int i = s;
    int j = e;

    while (1)
    {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;

        if (i >= j)
        {
            return j;
        }

        swap(&arr[i], &arr[j]);
        (*cnt)++;
    }
}

void Merge_sort(double *arr, int s, int e, int *cnt)
{
    if (s < e)
    {
        int mid = (s + e) / 2;
        Merge_sort(arr, s, mid, cnt);
        Merge_sort(arr, mid + 1, e, cnt);
        merge(arr, s, mid, e, cnt);
    }
}

void Quick_sort(double *arr, int s, int e, int *cnt)
{
    if (s < e)
    {
        int p = partition(arr, s, e, cnt);
        Quick_sort(arr, s, p, cnt);
        Quick_sort(arr, p + 1, e, cnt);
    }
}

int main()
{
    int num;
    int mcount = 0, qcount = 0;
    printf("Enter the number of data you want to enter : ");
    scanf("%d", &num);
    double *arr = (double *)malloc(sizeof(double) * num);
    srand((unsigned int)time(NULL));

    int number;
    printf("Enter 1 for UD or 2 for ND : ");
    scanf("%d", &number);

    switch (number)
    {
    case 1:
    {
        int choice;
        printf("Enter 1 for MS or 2 for QS : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            FILE *file = fopen("UniDist.txt", "w");

            if (file == NULL)
            {
                fprintf(stderr, "Error opening file for writing\n");
                return 1;
            }
            for (int i = 0; i < num; ++i)
            {
                arr[i] = (rand() % 100);
                fprintf(file, "%.6f\n", arr[i]);
            }

            fclose(file);

            Merge_sort(arr, 0, num - 1, &mcount);

            for (int i = 0; i < num; ++i)
            {
                printf("%f ", arr[i]);
            }

            printf("\nTotal no. of comparisons : %d\n", mcount);
            printf("Uniform Distribution dataset with merge sorting generated successfully.\n");
            break;
        }
        case 2:
        {
            FILE *file = fopen("UniDist.txt", "w");

            if (file == NULL)
            {
                fprintf(stderr, "Error opening file for writing\n");
                return 1;
            }
            for (int i = 0; i < num; ++i)
            {
                arr[i] = ((double)rand() / RAND_MAX);
                fprintf(file, "%.6f\n", arr[i]);
            }

            fclose(file);

            Quick_sort(arr, 0, num - 1, &qcount);

            for (int i = 0; i < num; ++i)
            {
                printf("%.6f ", arr[i]);
            }

            printf("\nTotal no. of swappings : %d\n", qcount);
            printf("Uniform Distribution dataset with quick sorting generated successfully.\n");
            break;
        }
        }
        break;
    }
    case 2:
    {
        int choice;
        printf("Enter 1 for MS or 2 for QS : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            double mean = 0.0;
            double stddev = 1.0;
            FILE *file = fopen("NormalDist.txt", "w");

            if (file == NULL)
            {
                fprintf(stderr, "Error opening file for writing\n");
                return 1;
            }
            for (int i = 0; i < num; ++i)
            {
                arr[i] = mean + stddev * generate_normal_random();
                fprintf(file, "%.6f\n", arr[i]);
            }

            fclose(file);
            Merge_sort(arr, 0, num - 1, &mcount);

            for (int i = 0; i < num; ++i)
            {
                printf("%f ", arr[i]);
            }
            printf("\nTotal no. of comparisons : %d\n", mcount);
            printf("Normal distribution dataset generated with merge sorting successfully.\n");
            break;
        }
        case 2:
        {
            double mean = 0.0;
            double stddev = 1.0;
            FILE *file = fopen("NormalDist.txt", "w");

            if (file == NULL)
            {
                fprintf(stderr, "Error opening file for writing\n");
                return 1;
            }
            for (int i = 0; i < num; ++i)
            {
                arr[i] = mean + stddev * generate_normal_random();
                fprintf(file, "%.6f\n", arr[i]);
            }

            fclose(file);

            Quick_sort(arr, 0, num - 1, &qcount);

            for (int i = 0; i < num; ++i)
            {
                printf("%.6f ", arr[i]);
            }
            printf("\nTotal no. of swappings : %d\n", qcount);
            printf("Normal distribution dataset generated with quick sorting successfully.\n");
            break;
        }
        }
        break;
    }
    }

    return 0;
}