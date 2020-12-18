#include <stdio.h>
#include "cal.h"

int main()
{
    char input_buff[200] = {0};
    scanf("%s", input_buff);
    Node result = compute_expression(input_buff);
    print_node(result);
    return 0;
}