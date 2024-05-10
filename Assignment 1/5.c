#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node
{
    float data;
    struct Node *next;
} Node;

Node *Insertion_sort(Node *head)
{
    if (head == NULL || head->next == NULL)
        return head;
    Node *p = head;
    Node *q = head->next;
    q = Insertion_sort(q);
    if (p->data <= q->data)
    {
        p->next = q;
        return p;
    }
    Node *start = q;
    while (q->next != NULL)
    {
        if (p->data < q->next->data)
            break;
        else
            q = q->next;
    }
    p->next = q->next;
    q->next = p;
    return start;
}

// Sorting function
void BucketSort(float arr[], int n)
{
    int i, j;
    struct Node **buckets;

    // Create buckets and allocate memory size
    buckets = (struct Node **)malloc(sizeof(struct Node *) * n);

    // Initialize empty buckets
    for (i = 0; i < n; i++)
    {
        buckets[i] = NULL;
    }

    // Fill the buckets with respective elements
    for (i = 0; i < n; ++i)
    {
        struct Node *current;
        int pos = arr[i] * n;
        current = (struct Node *)malloc(sizeof(struct Node));
        current->data = arr[i];
        current->next = buckets[pos];
        buckets[pos] = current;
    }

    for (i = 0; i < n; ++i)
    {
        buckets[i] = Insertion_sort(buckets[i]);
    }

    // Put sorted elements on arr
    for (j = 0, i = 0; i < n; ++i)
    {
        struct Node *node;
        node = buckets[i];
        while (node)
        {
            arr[j++] = node->data;
            node = node->next;
        }
    }
}

void print(float ar[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        printf("%f ", ar[i]);
    }
    printf("\n");
}

float mean_arr(float *arr, int n)
{
    float sum = 0.0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return (sum / n);
}

int main(void)
{
    int n;
    printf("Enter the number of elements required\n");
    scanf("%d", &n);
    srand(time(0));
    float *a = (float *)malloc(sizeof(float) * n);
    for (int i = 0; i < n; i++)
    {
        a[i] = (rand() % 100) / 100.0;
    }

    printf("Initial array: ");
    print(a, n);
    printf("-------------\n");

    BucketSort(a, n);
    FILE *file = fopen("UniDist.txt", "w");
    for (int i = 0; i < n; i++)
    {
        fprintf(file, "%f\n", a[i]);
    }
    fclose(file);
    printf("-------------\n");
    printf("Sorted array: ");
    print(a, n);
    for (int i = 0; i < n; i++)
    {
        float num[12];
        for (int j = 0; j < 12; j++)
        {
            num[j] = (rand() % 100) / 100.0;
        }
        a[i] = mean_arr(num, 12);
    }
    printf("Initial array: ");
    print(a, n);
    printf("-------------\n");

    BucketSort(a, n);
    file = fopen("NormalDist.txt", "w");
    for (int i = 0; i < n; i++)
    {
        fprintf(file, "%f\n", a[i]);
    }
    fclose(file);
    printf("-------------\n");
    printf("Sorted array: ");
    print(a, n);
    return 0;
}