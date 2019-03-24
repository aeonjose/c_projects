#include"common.h"

void print_list(llist *head)
{
    int flag = 0, count  = 0, temp, i;
    while (head)
    {
	if(flag == 1)
	{
	    temp = head->data;
	    if(head->data == 0)
	    {
		printf("00000000");
	    }
	    else
	    {
		while(temp != 0)
		{
		    temp = temp/10;
		    count++;
		}
		for(i = 0; i < 9 - count; i++)
		    printf("0");
	    }
	}
	printf("%d",head->data);
	head = head->next;
	flag = 1;
    }
    //printf("NULL\n");
}
