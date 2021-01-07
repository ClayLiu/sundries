#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

#define print_i_j(x) printf("%d i = %d, j = %d\n", x, i, j);
#define debug(x) printf("%d :", x); print_array(array, array_size); system("pause");

int swap(int* a, int* b)
{
    if(a != b)
    {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
    return 0;
}

void directly_insert_sort(int* array, int array_size)
{
    int i, j;
    for(i = 1; i < array_size; i++)
        for(j = i - 1; j >= 0 && array[j] > array[j + 1]; j--)
            swap(array + j, array + j + 1);
}

void bubble_sort(int* array, int array_size)
{
    int i, j;
    for(i = 0; i < array_size - 1; i++)
        for(j = 0; j < array_size - i - 1; j++)
            if(array[j] > array[j + 1])
                swap(array + j, array + j + 1);
}

void improved_bubble_sort(int* array, int array_size)
{
    int i, j;
    char flag = 0;
    for(i = 0; i < array_size - 1; i++)
    {
        flag = 0;
        for(j = 0; j < array_size - i - 1; j++)
            if(array[j] > array[j + 1])
            {
                swap(array + j, array + j + 1);
                flag = 1;
            }    
        
        if(!flag)
            return;
    }
}

void simply_select_sort(int* array, int array_size)
{
    int i, j;
    int min_index;
    for(i = 0; i < array_size - 1; i++)
    {
        for(min_index = i, j = i + 1; j < array_size; j++)
            if(array[min_index] > array[j])
                min_index = j;
        
        if(min_index != i)
            swap(array + min_index, array + i);
    }
}

static void merge(int* array_1, int* array_2, int* temp, int array_1_size, int array_2_size)
{
    int i, j;
    i = j = 0;

    while(i < array_1_size && j < array_2_size)
    {
        if(array_1[i] < array_2[j])
        {
            *temp = array_1[i];
            i++;
        }
        else
        {
            *temp = array_2[j];
            j++;
        }
        temp++;
    }

    while(i < array_1_size)
    {
        *temp = array_1[i];
        i++;
        temp++;
    }

    while(j < array_2_size)
    {
        *temp = array_2[j];
        j++;
        temp++;
    }
}

static void merge_sort_in(int* array, int* temp, int array_size)
{
    if(array_size == 1)
        return;
    int mid = array_size >> 1;
    merge_sort_in(array, temp, mid);
    merge_sort_in(array + mid, temp + mid, array_size - mid);
    merge(array, array + mid, temp, mid, array_size - mid);

    while(array_size--)
    {
        *array = *temp;
        array++;
        temp++;
    }
}

void merge_sort(int* array, int array_size)
{
    int temp[array_size];
    merge_sort_in(array, temp, array_size);
}

static void heap_adjust(int* heap, int index, int heap_size)
{
    // Max heap sorting.
    
    int i;
    int save = heap[index];
    for(i = (index << 1) + 1; i < heap_size; i <<= 1)
    {
        i += ((i + 1) < heap_size) && (heap[i] < heap[i + 1]);    // Find the bigger way to go through.

        if(save >= heap[i]) // If put that here can keep heap,
            break;          // then break the loop.

        heap[index] = heap[i];
        index = i;
    }

    heap[index] = save;
}

void heap_sort(int* array, int array_size)
{
    // Max heap sorting.
    int i;
    for(i = (array_size >> 1) - 1; i >= 0; i--) // Build the heap.
        heap_adjust(array, i, array_size);
    
    for(i = array_size - 1; i > 0; i--)
    {
        swap(array, array + i);
        heap_adjust(array, 0, i);
    }
}

void shell_sort(int* array, int array_size)
{

}

static int quick_sort_partion(int* array, int array_size)
{
    int i, j;
    i = 0;
    j = array_size;

    while(i < j)
    {   
        while(
            i < j &&                        // First priority.
            i < (--j) &&                    // Changed j(or i) must obey this condition.
            (
                (array[i] < array[j]) ||    // If find the against order number (while 'array[i] < array[j]' is false),
                swap(array + i, array + j)  // then swap it. And because swap() returns 0, loop conditions false.
            )
        );

        while(
            i < j && 
            (++i) < j && 
            (
                (array[i] < array[j]) || 
                swap(array + i, array + j)
            )
        );
    }
    return i;
}

void quick_sort(int* array, int array_size)
{
    if(array_size == 0 || array_size == 1)
        return;
    int pivot = quick_sort_partion(array, array_size);
    quick_sort(array, pivot);
    quick_sort(array + pivot + 1, array_size - pivot - 1);
}
