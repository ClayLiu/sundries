#include <stdio.h>
#include "solve_sudoku.h"

int main(int argc, char** argv)
{
    table table_to_solve;

    if(argc == 2)
    {
        FILE* fp = fopen(argv[1], "r");
        input_values_to_table(table_to_solve, fp);
        fclose(fp);
    
        print_table(table_to_solve, "Original table:");
        solve(table_to_solve);
        print_table(table_to_solve, "Solved table:");
    }
    else
        printf("No input file!");

    return 0;
}