#include <stdio.h>

void multiple_by_2(int *numb) {
    *numb = *numb * 2;
}

int main(void) {
    int numb = 4;
    multiple_by_2(&numb);
    printf("%d\n", numb);

    return 0;
}