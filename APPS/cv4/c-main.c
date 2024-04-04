#include <stdio.h>
#include <string.h>

void fill_pyramid_numbers(long * numbers, int size);
long multiples(long * numbers, int size, long factor);
int factorial(int * numbers, int size);
int main()
{
    long array[10];
    fill_pyramid_numbers(array, 10);
    for (int i = 0; i < 10; i++)
    {
        printf("pyramid %d.: %ld \n", i, array[i]);
    }
    long numbers[10] = {1,2,3,4,5,6,7,8,9,10};
    printf("multiples: %ld \n", multiples(numbers, 10, 5));
    for (int i = 0; i < 10; i++)
    {
        printf("multiples array %d.: %ld\n", i, numbers[i]);
    }
    
    int numbers2[10] = {0,1,2,3,4,5,6,7,8,9};
    printf("factorial preteceni: %d\n", factorial(numbers2, 10));
    for (int i = 0; i < 10; i++)
    {
        printf("factorila array %d.: %d\n", i, numbers2[i]);
    }
    

}
