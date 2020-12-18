#include <stdio.h>
#include <stdlib.h>

#define oper_sign           1
#define int_value_sign      2
#define double_value_sign   3

typedef union value
{
    char oper;
    int int_value;
    double double_value;
}Value;

typedef struct node
{
    Value data;
    char mode;
}Node;

void print_node(Node node_to_print);

Node compute_expression(char* expression_str);