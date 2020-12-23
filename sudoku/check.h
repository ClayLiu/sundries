#ifndef CHECK_H
#define CHECK_H

#include <stdbool.h>
#include "solve_sudoku.h"

/* 
    检查该数独表是否已经有 num
    有就返回 false
    否则返回 true
 */
bool check(table table_to_check, const int row, const int col, const int num);

#endif