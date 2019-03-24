#include"common.h"

int oper( int expr1, int expr2)
{

    char arr1[expr1+1], arr2[expr2+1], oper, temp1[10], temp2[10], *ptr;
    int i = 0;
    FILE *f1;

    //opening file to process numbers
    f1 = fopen("expr.txt", "r");

    //moving 1st number to array1
    while(i < expr1)
    {
	arr1[i] = fgetc(f1);
	i++;
    }
    arr1[i] = '\0';
    //saving the operator
    oper = fgetc(f1);
    

    //moving 2nd number to array2
    i = 0;
    while(i < expr2)
    {
	arr2[i] = fgetc(f1);
	i++;
    }
    arr2[i] = '\0';
    fclose(f1);

    printf("\n");

    add(arr1, arr2, expr1, expr2, oper);

    return SUCCESS;
}
