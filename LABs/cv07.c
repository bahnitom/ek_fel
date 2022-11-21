#include <stdio.h>

/*int main(void)
{
    int a, b, c;
    int arr[5];
    int arr3[25] = {[4] = 6, [19] = -8};
    printf("%d\n", *arr3);
    for (int i = 0; i < 5; ++i)
    {
        if (scanf("%d", &arr[i]) != 1)
        {
            break;
        }
    }
    printf("Nacitani dokonceno, bylo nacteno pole\n");
    for (int i = 0; i < 5; ++i)
    {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    printf("\n");

    return 0;
}
*/

/*POINTERS*/

void arr_fill(int *arr, int lenght)
{
    printf("velikost pole, ale pointer: %lu\n", sizeof(arr));
    for (int i = 0; i < lenght; ++i)
    {
        if (scanf("%d", &arr[i]) != 1)
        {
            break;
        }
    }
}
void arr_print(int *arr, int lenght)
{
    for (int i = 0; i < lenght; ++i)
    {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
}

int main(void)
{
    int lenght;
    printf("Zadej pocet cisel:\n");
    if (scanf("%u", &lenght) != 1)
    {
        return -1;
    }

    int arr[lenght];

    printf("velikost pole: %lu\n", sizeof(arr));
    arr_fill(arr, lenght);

    printf("Nacitani dokonceno, bylo nacteno pole\n");
    arr_print(arr, lenght);
    printf("\n");

    return 0;
}