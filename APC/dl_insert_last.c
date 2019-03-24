
#include"common.h"

int insert_at_last(llist **head,llist **tail, data_t data)
{
    llist *new, *temp;

    if((new = (llist *)malloc(sizeof(llist))) == NULL)		// creating new link and error checking
    {
	return FAILURE;
    }

    new->data = data;						//inserting data and link
    new->next = NULL;

    if (*head == NULL)
    {
	*head = new;
	*tail = new;
	new->prev = NULL;
	return SUCCESS;
    }
	
    temp = *head;						//moving to the last node
    while(temp->next)
    {
	temp = temp->next;
    }
	
    temp->next = new;						//connecting the nodes
    new->prev = temp;
    *tail = new;

    return SUCCESS;
}
