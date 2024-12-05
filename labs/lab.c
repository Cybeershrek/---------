#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, Mean, last_Mean;
    int Count_orig = 0, Count_deriv = 0;
    int sequen, last_seq; // характер монотонности для "производной", где 0 - убывающая, а 1 - возрастающая
    int *differen;

    scanf("%d", &N);


    differen = (int *)malloc((N - 1) * sizeof(int));


    scanf("%d", &last_Mean);

    for (int i = 0; i < N - 1; i += 1) {
        scanf("%d", &Mean);
        differen[i] = Mean - last_Mean;
        last_Mean = Mean;
    }

    for (int j = 0; j < N - 2; j += 1) {
        if ((differen[j + 1] > 0 && differen[j] < 0) || (differen[j + 1] < 0 && differen[j] > 0)) {
            Count_orig += 1;
        }

        if (j == 0) {
            if (differen[j + 1] > differen[j]) {
                last_seq = 1;
            }
             else {
                last_seq = 0;
            }
        } 
        else {
            if (differen[j + 1] > differen[j]) {
                sequen = 1;
            }
            else {
                sequen = 0;
            }

            if (sequen != last_seq) {
                Count_deriv += 1;
                last_seq = sequen;
            }
        }
    }

    printf("\nAnswer: %d %d\n", Count_orig, Count_deriv);

    free(differen);

    return 0;
}
