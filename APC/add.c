#include"common.h"

int add(char * arr1, char *arr2, int expr1, int expr2, char oper )
{
    int sum = 0, k, i = 0, j = 0, data = 0, carry = 0, diff = 0, flag = 0;
    llist *head1 = NULL, *head2 = NULL, *tail1 = NULL, *tail2 = NULL, *head3 = NULL;
    char temp1[10], temp2[10], sign = '+';


    // considering special cases
    if(oper == '+')
    {
	if(arr1[0] == '-')
	{
	    arr1[0] = '0';
	    if(arr2[0] == '-')
	    {
		arr2[0] = '0';
		oper = '+';
		sign = '-';
	    }
	    else 
	    {
	printf("fdfsadfadas\n");
		oper = '-';
		sign = '-';
	    }
	}
	else if(arr1[0] == '+') 
	{
	    arr1[0] = '0';
	    if(arr2[0] == '-')
	    {
		arr2[0] = '0';
		oper = '-';
	    }
	}
    }
    else if(oper == '-')
    {
	if(arr1[0] == '-')
	{
	    arr1[0] = '0';
	    if(arr2[0] == '-')
	    {
		arr2[0] = '0';
		oper = '-';
		sign = '-';
	    }
	    else 
	    {
		oper = '+';
		sign = '-';
	    }
	}
	else  
	{
	    if(arr2[0] == '-')
	    {
		arr2[0] = '0';
		oper = '+';
	    }
	}
    }
    //filling the list for the first operant
    //filling the fist node
    k = expr1 % 9;
    if(k != 0)
    {
	char first1[k+1];
	for(i = 0; i < k; i++)
	{
	    first1[i] = arr1[i];
	}
	first1[i] = '\0';
	data = atoi(first1);
	insert_at_last(&head1, &tail1, data);
    }

    //filling the remaning node
    while(i < expr1)
    {
	for(int j=0; j < 9; j++)
	{
	    temp1[j] = arr1[i];
	    i++;
	}
	//	temp1[j] = '\0';
	data = atoi(temp1);
	insert_at_last(&head1, &tail1, data);
    }

    //filling the list for the second operant
    //filling the fist node
    i = 0;
    k = expr2 % 9;
    if(k != 0)
    {
	char first2[k+1];
	for(i = 0; i < k; i++)
	{
	    first2[i] = arr2[i];
	}
	first2[i] = '\0';
	data = atoi(first2);
	insert_at_last(&head2, &tail2, data);
    }

    //filling the remaning node
    while(i < expr2)
    {
	for(int j=0; j < 9; j++)
	{
	    temp2[j] = arr2[i];
	    i++;
	}
	//	temp2[j] = '\0';
	data = atoi(temp2);
	insert_at_last(&head2, &tail2, data);
    }


    switch(oper)
    {
	case '+' : {
		       llist *temp1, *temp2;
		       temp1 = tail1;
		       temp2 = tail2;

		       while(temp1 && temp2)
		       {
			   data = temp1->data + temp2->data + carry;
			   carry = 0;
			   if((data / 1000000000) != 0 )
			   {
			       data = data % 1000000000;
			       carry = 1;
			   }
			   insert_at_first(&head3, data);
			   temp1 = temp1->prev;
			   temp2 = temp2->prev;
		       }

		       while(temp1)
		       {
			   data = temp1->data + carry;
			   carry = 0;
			   insert_at_first(&head3, data);
			   temp1 = temp1->prev;
		       }
		       while(temp2)
		       {
			   data = temp2->data + carry;
			   carry = 0;
			   insert_at_first(&head3, data);
			   temp2 = temp2->prev;
		       }
		       if(carry == 1)
			   insert_at_first(&head3, carry);

		       printf("the sum is %c", sign);
		       print_list(head3);
		       printf("\n");
		   }
		   break;

	case '-' : printf("SUB\n");
		   llist *temp1, *temp2;
		   if(expr1 < expr2)
		   {
		       temp1 = tail2;
		       temp2 = tail1;
		       sign = '-';
		   }
		   else if(expr1 == expr2)
		   {
		       temp1 = head1;
		       temp2 = head2;
		       while(temp1)
		       {
			   if(temp1->data < temp2->data)
			   {
			       temp1 = tail2;
			       temp2 = tail1;	
			       sign = '-';
			       break;
			   }
			   temp1 = temp1->next;
			   temp2 = temp2->next;
		       }
		       temp1 = tail1;
		       temp2 = tail2;
		   }
		   else
		   {
		       temp1 = tail1;
		       temp2 = tail2;
		   }
		   while(temp1 && temp2)
		   {
		       if(flag == 1)
		       {
			   temp1->data = temp1->data - 1;
			   flag = 0;
		       }
		       if(temp1->data < temp2->data)
		       {
			   temp1->data = temp1->data+1000000000;
			   flag = 1;
			   if(temp1->data == 0 && (temp1->prev != NULL))
			   {
			       temp1->data = 1000000000;
			   }
		       }
		       diff = temp1->data - temp2->data;
		       insert_at_first(&head3, diff);
		       temp1 = temp1->prev;
		       temp2 = temp2->prev;
		   }

		   while(temp1)
		   {
		       if(flag == 1)
		       {
			   temp1->data = temp1->data - 1;
			   flag = 0;
		       }
		       insert_at_first(&head3, temp1->data);
		       temp1 = temp1->prev;
		   }
		   printf("the difference is : %c", sign);
		   print_list(head3);
		   printf("\n");

		   break;
    }
}
