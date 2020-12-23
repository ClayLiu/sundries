#ifndef SOLVE_SUDOKU_H
#define SOLVE_SUDOKU_H
#include <stdio.h>

typedef int table[9][9];

/* 
    从文件中读取题目
    约定以 0 表示空白
 */
void input_values_to_table(table table_to_solve, FILE* fp);

/* 生成极小解 */
void solve(table table_to_solve);

/* 打印数独表 */
void print_table(table table_to_print, char* title);

#endif