#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(0));

    int total = 10e4, sub_div = 10, max_num = 100;
    
    FILE *fp = fopen("normal_data.txt", "w");

    fprintf(fp, "values\n");

    for(int i = 0; i < total; i++){
        int sum = 0;
        for(int j = 0; j < sub_div; j++){
            sum += rand() % (max_num / sub_div);
        }

        fprintf(fp, "%d\n", sum);
    }

    fclose(fp);
}