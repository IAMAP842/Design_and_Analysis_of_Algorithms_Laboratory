#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(0));

    int total = 10e4, max_num = 100;
    
    FILE *fp = fopen("uniform_data.txt", "w");

    fprintf(fp, "values\n");
    
    for(int i = 0; i < total; i++){
        fprintf(fp, "%d\n", rand() % max_num);
    }

    fclose(fp);
}