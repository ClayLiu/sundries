#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cal.h"

const int MAX_ITEM_LENGTH = 20;                     // 单项最大长度
const int MAX_EXPRESSION_ELEMENT_COUNT = 1000;      // 最大表达式元素个数

Node new_node(char mode, char oper, int int_value, double double_value)
{
    Node new;
    switch(mode)
    {
        case oper_sign:
            new.data.oper = oper;
            break;
        case int_value_sign:
            new.data.int_value = int_value;
            break;
        case double_value_sign:
            new.data.double_value = double_value;
            break;
        default:
            fprintf(stderr, "Something wrong in newing a node.");
    }
    new.mode = mode;
    return new;
}

void print_node(Node node_to_print)
{
    // printf("Node:\n Value is ");
    switch(node_to_print.mode)
    {
        case oper_sign:
            printf("%c", node_to_print.data.oper);
            break;
        case int_value_sign:
            printf("%d", node_to_print.data.int_value);
            break;
        case double_value_sign:
            printf("%.2lf", node_to_print.data.double_value);
            break;
    }
    // putchar('\n');
}

static void print_node_array(Node* array, int array_size)
{
    putchar('[');
    for(int i = 0; i < array_size; i++)
    {
        (i) && putchar(' ');
        print_node(array[i]);
    }
    
    printf("]\n");
}

static int cal_precedence(char oper)
{
    int precedence = 0;
    switch(oper)
    {
        case '(':
            precedence++;
        case '*':
        case '/':
            precedence++;
        case '+':
        case '-':
            precedence++;
    }
    return precedence;
}

static void clear_buff(char* buff)
{
    while(*buff)
    {
        *buff = 0;
        buff++;
    }
}

/* 把数字字符串转为 node */
Node num_str_to_node(char* str)
{
    char mode;
    Node new;
    for(int i = 0; str[i]; i++)
        if(str[i] == '.')
            return new_node(double_value_sign, 0, 0, atof(str));
    
    return new_node(int_value_sign, 0, atoi(str), 0);
}

/* 把新建的节点放入数组，先检查是否大于限定长度 */
void add_node_to_node_array(Node* array, int rear, Node a)
{
    if(rear >= MAX_EXPRESSION_ELEMENT_COUNT)
    {
        fprintf(stderr, "(Error) The number of elemnets is bigger than MAX_EXPRESSION_ELEMENT_COUNT.");
        exit(1);
    }

    array[rear] = a;
}

Node* to_node_array(char* str, int* item_count)
{
    int buff_length = 0, count_item = 0;
    int str_length = strlen(str);    
    char* buff = (char*)calloc(MAX_ITEM_LENGTH, sizeof(char));
    Node* node_array = (Node*)malloc(sizeof(Node) * MAX_EXPRESSION_ELEMENT_COUNT);

    
    for(int i = 0; i < str_length; i++)
    {
        switch(str[i])
        {
            case '(':
            case '+':
            case '-':
            case '*':
            case '/':
            case ')':
            case ' ':
                if(buff_length)
                {
                    add_node_to_node_array(node_array, count_item, num_str_to_node(buff));
                    count_item++;

                    clear_buff(buff);
                    buff_length = 0;
                }
                
                if(str[i] != ' ')   // 空格不算为操作符
                {
                    // Node new_node;
                    // new_node.mode = oper_sign;
                    // new_node.data.oper = str[i];
                    add_node_to_node_array(node_array, count_item, new_node(oper_sign, str[i], 0, 0));
                    count_item++;
                }
                break;
            default:
                buff[buff_length++] = str[i];
        }


    }

    if(buff_length)
    {
        add_node_to_node_array(node_array, count_item, num_str_to_node(buff));
        count_item++;
    }

    free(buff);
    *item_count = count_item;
    return node_array;
}

Node* to_inverse_polish_node_array(Node* node_array, int array_size, int* return_size)
{
    int i, j;
    int top = 0;
    Node* help_stack = (Node*)malloc(sizeof(Node) * array_size);
    Node* inv_pol_array = (Node*)malloc(sizeof(Node) * array_size);
    
    for(i = j = 0; i < array_size; i++)
    {
        if(node_array[i].mode != oper_sign)
            inv_pol_array[j++] = node_array[i];
        else
        {   
            if(node_array[i].data.oper == ')')
            {
                while(help_stack[top - 1].data.oper != '(')
                    inv_pol_array[j++] = help_stack[--top];
                top--;
            }
            else    
            {
                while(
                    top &&                                  // 栈非空
                    help_stack[top - 1].data.oper != '(' && // 如果栈顶有左括号，则无论如何都把最新的操作符压栈 
                    cal_precedence(node_array[i].data.oper) <= cal_precedence(help_stack[top - 1].data.oper)
                )
                    inv_pol_array[j++] = help_stack[--top];
                
                help_stack[top++] = node_array[i];
            }
        }
    }

    while(top)
        inv_pol_array[j++] = help_stack[--top];

    *return_size = j;
    free(help_stack);
    return inv_pol_array;
}

Node compute_two_element(Node a, Node b, char oper)
{
    Node c;
    if(a.mode ^ b.mode)             // 如果类型不一样，则向 double 转换
    {
        c.mode = double_value_sign;
        if(a.mode == int_value_sign)
            a.data.double_value = (double)a.data.int_value;
        else
            b.data.double_value = (double)b.data.int_value;
        
        switch(oper)
        {
            case '+':
                c.data.double_value = a.data.double_value + b.data.double_value;
                break;
            case '-':
                c.data.double_value = a.data.double_value - b.data.double_value;
                break;
            case '*':
                c.data.double_value = a.data.double_value * b.data.double_value;
                break;
            case '/':
                c.data.double_value = a.data.double_value / b.data.double_value;
                break;                
        }
    }
    else if (a.mode == int_value_sign)
    {
        c.mode = int_value_sign;
        switch(oper)
        {
            case '+':
                c.data.int_value = a.data.int_value + b.data.int_value;
                break;
            case '-':
                c.data.int_value = a.data.int_value - b.data.int_value;
                break;
            case '*':
                c.data.int_value = a.data.int_value * b.data.int_value;
                break;
            case '/':
                c.data.int_value = a.data.int_value / b.data.int_value;
                break;                
        }
    }
    else
    {
        c.mode = double_value_sign;
        switch(oper)
        {
            case '+':
                c.data.double_value = a.data.double_value + b.data.double_value;
                break;
            case '-':
                c.data.double_value = a.data.double_value - b.data.double_value;
                break;
            case '*':
                c.data.double_value = a.data.double_value * b.data.double_value;
                break;
            case '/':
                c.data.double_value = a.data.double_value / b.data.double_value;
                break;                
        }
    }
    return c;
}

Node compute_inv_pol_expression(Node* inv_pol_node_array, int array_size)
{
    Node a, b;
    Node result;
    Node* help_stack = (Node*)malloc(sizeof(Node) * array_size);
    int top = 0;
    
    for(int i = 0; i < array_size; i++)
    {
        if(inv_pol_node_array[i].mode != oper_sign)
            help_stack[top++] = inv_pol_node_array[i];
        else    // 如果碰到运算符，则从栈中弹出两个元素进行运算，并把结果入栈
        {
            a = help_stack[--top];
            b = help_stack[--top];
            help_stack[top++] = compute_two_element(b, a, inv_pol_node_array[i].data.oper);
        }
    }
    
    result = help_stack[top - 1];   // 最终栈顶元素为运算结果
    free(help_stack);
    return result;
}

Node compute_expression(char* expression_str)
{
    int mid_node_array_size;
    Node* mid_node_array = to_node_array(expression_str, &mid_node_array_size); // 将字符串中缀表达式转为节点数组

    int inv_pol_node_array_size;
    Node* inv_pol_node_array = to_inverse_polish_node_array(
        mid_node_array, mid_node_array_size, &inv_pol_node_array_size
    );  // 将中缀顺序的节点数组转为后缀顺序的节点数组

    Node result = compute_inv_pol_expression(inv_pol_node_array, inv_pol_node_array_size);
    free(mid_node_array);
    free(inv_pol_node_array);
    return result;
}

int main_cal()
{
    char buff[200] = {0};
    scanf("%s", buff);
    Node result = compute_expression(buff);
    print_node(result);
    return 0;
}
