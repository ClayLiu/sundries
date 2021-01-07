#ifndef SORTING_H
#define SORTING_H

/* 直接插入排序 */
void directly_insert_sort(int* array, int array_size);

/* 冒泡排序 */
void bubble_sort(int* array, int array_size);

/* 改良冒泡排序 */
void improved_bubble_sort(int* array, int array_size);

/* 简单选择排序 */
void simply_select_sort(int* array, int array_size);

/* 归并排序 (递归) */
void merge_sort(int* array, int array_size);

/* 希尔排序 */
void shell_sort(int* array, int array_size);

/* 快速排序 */
void quick_sort(int* array, int array_size);

/* 堆排序 */
void heap_sort(int* array, int array_size);

#endif