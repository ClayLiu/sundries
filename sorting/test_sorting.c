#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

int* copy(int* array, int array_size)
{
    int* des = (int*)malloc(sizeof(int) * array_size);
    for(int i = 0; i < array_size; i++)
        des[i] = array[i];
    
    return des;
}

void print_array(int* array, int array_size)
{
    for(int i = 0; i < array_size; i++)
        printf(", %d" + ((!i) << 1), array[i]);
    putchar('\n');
}

int main()
{
    int test[] = {55, 30, 17, 26, 5, 20, 27, 29, 28};
    int* copy_p;

    print_array(test, 9);
    copy_p = copy(test, 9);
    bubble_sort(copy_p, 9);
    print_array(copy_p, 9);
    free(copy_p);

    copy_p = copy(test, 9);
    simply_select_sort(copy_p, 9);
    print_array(copy_p, 9);
    free(copy_p);

    copy_p = copy(test, 9);
    directly_insert_sort(copy_p, 9);
    print_array(copy_p, 9);
    free(copy_p);

    copy_p = copy(test, 9);
    merge_sort(copy_p, 9);
    print_array(copy_p, 9);
    free(copy_p);

    copy_p = copy(test, 9);
    quick_sort(copy_p, 9);
    print_array(copy_p, 9);
    free(copy_p);

    copy_p = copy(test, 9);
    improved_bubble_sort(copy_p, 9);
    print_array(copy_p, 9);
    free(copy_p);

    copy_p = copy(test, 9);
    heap_sort(copy_p, 9);
    print_array(copy_p, 9);
    free(copy_p);


    printf("done\n");
    return 0;
}