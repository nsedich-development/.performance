#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    clock_t tic = clock();

    double sum = 0;
    double sum2 = 0;
    double sum3 = 0;

    for (double i = 0; i < 1500000000; i++) {
        sum += i;
        for (int k = 0; k < 5; k++) {
            sum2 += k;
            for (int n = 0; n < k; n++) {
                sum3 += n;
            }
        }
    }

    clock_t toc = clock();

    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    printf("%f\n", sum);
    printf("%f\n", sum2);
    printf("%f\n", sum3);

    getchar();

	//return 0;
}