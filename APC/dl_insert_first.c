#include"common.h"

int insert_at_first(llist **head, data_t data)
{
    llist *new, *temp;
    if(head == NULL)					// if it is the first link
    {
	if((new = (llist *)malloc(sizeof(llist))) == NULL)	//error check
	{
	    return FAILURE;
	}
	new->data = data;
	new->prev= NULL;
	*head = new;
	return SUCCESS;
    }

    else 
    {
	if((new =(llist *)malloc(sizeof(llist))) == NULL)		//error check
	{
	    return FAILURE;
	}
	new->data = data;
	new->next = *head;
	*head = new;
	new->prev = NULL;
    }
    return SUCCESS;
}
