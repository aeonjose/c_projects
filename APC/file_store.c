#include"common.h"

int expr_file_creat(int *expr1, int *expr2)
{
    FILE *f1;
    char ch;
    int  count = 0, flag = 0;

    //opening file to write the exression
    f1 = fopen("expr.txt", "w");
    if(f1 == NULL)
    {
	return FAILURE;
    }

    while(ch = getchar())
    {
	if(ch == '\n')
	    break;
	fputc(ch, f1);
	count++;
	if(ch  == '+' || ch == '-')
	{
	    if(count > 1)
	    {
		count = 0;
	    }
	    flag++;
	}
    }
    *expr2 = count;
    *expr1 = ftell(f1) - *expr2 - 1;
    fclose(f1);

    printf(" count 1 = %d\n", *expr1);
    printf(" count 2 = %d\n", *expr2);

    return SUCCESS;
}
