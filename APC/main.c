#include"common.h"

int main()
{
    int exp1, exp2;
    printf("Enter the expression\n(eg: 123+234\n");
    expr_file_creat(&exp1, &exp2);

    //addition
    oper(exp1, exp2);

    
    return 0;
}
