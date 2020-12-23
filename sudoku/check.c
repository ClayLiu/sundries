#include "check.h"

/* 
    检查 row 行是否已经有 num
    有就返回 false
    否则返回 true
 */
static bool check_row(table table_to_check, const int row, const int num)
{
    for(int col = 0; col < 9; col++)
        if(table_to_check[row][col] == num)
            return false;
    return true;
}

/* 
    检查 col 列是否已经有 num
    有就返回 false
    否则返回 true
 */
static bool check_col(table table_to_check, const int col, const int num)
{
    for(int row = 0; row < 9; row++)
        if(table_to_check[row][col] == num)
            return false;
    return true;
}

/* 
    检查分九宫是否已经有 num
    有就返回 false
    否则返回 true
 */
static bool check_block(table table_to_check, const int row, const int col, const int num)
{
    int block_row = row / 3 * 3;
    int block_col = col / 3 * 3;

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(table_to_check[i + block_row][j + block_col] == num)
                return false;

    return true;
}

/* 
    检查该数独表是否已经有 num
    有就返回 false
    否则返回 true
 */
bool check(table table_to_check, const int row, const int col, const int num)
{
    return check_block(table_to_check, row, col, num) &&
           check_row(table_to_check, row, num) &&
           check_col(table_to_check, col, num);
}