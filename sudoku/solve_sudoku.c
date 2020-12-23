#include <stdio.h>
#include <stdlib.h>
#include "solve_sudoku.h"
#include "check.h"

/* 在流中获取字符串 */
static char* s_get(char* des, int n, FILE* fp)
{
    /**
      * 从流中获取最多 n 个字节的数据
      * 返回去掉'\n'(如果有)的字符串
      */
    if(des == NULL)
        des = (char*)calloc(n, sizeof(char));

	int i = 0;
	des = fgets(des, n + 1, fp);
	if(des)
	{
		while(des[i] != '\n' && des[i] != 0)
			i++;
        des[i] = 0;
	}
	return des;
}

/* 清除字符串内容 */
static void EmptyString(char* str)
{
    while (*str)
    {
        *str = 0;
        str++;
    }
}

void input_values_to_table(table table_to_solve, FILE* fp)
{
    int i, j;
    char* buff = NULL;
    for(i = 0; i < 9; i++)
    {
        buff = s_get(buff, 10, fp);
        for(j = 0; j < 9; j++)
            if('0' <= buff[j] && buff[j] <= '9')
                table_to_solve[i][j] = buff[j] - '0';
            else
                table_to_solve[i][j] = 0;

        EmptyString(buff);
    }

    free(buff);
}

static bool solve_in(table table_to_solve, int id)
{
    if(id == 81)
        return true;
    
    int row = id / 9;
    int col = id % 9;

    if(table_to_solve[row][col])
        return solve_in(table_to_solve, id + 1);
    else
    {
        for(int num = 1; num <= 9; num++)
            if(check(table_to_solve, row, col, num))
            {
                table_to_solve[row][col] = num;
                if(solve_in(table_to_solve, id + 1))
                    return true;
            }
        
        table_to_solve[row][col] = 0;
        return false;
    }
}

void solve(table table_to_solve)
{
    solve_in(table_to_solve, 0);
}

void print_table(table table_to_print, char* title)
{
    int i, j;
    if(title)
        printf("%s\n", title);
        
    printf("-------------------\n");
    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)
        {
            if(!(j % 3))
                putchar('|');

            printf(" %d" + ((j % 3) == 0), table_to_print[i][j]);
        }
        printf("|\n");
        if(!((i + 1) % 3))
            printf("-------------------\n");
    }
}