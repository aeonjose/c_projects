#ifndef COMMON_H
#define COMMON_H

#include<stdio.h>
#include<stdlib.h>

typedef int data_t;

typedef struct llist
{
    data_t data;
    struct llist *prev;
    struct llist *next;
}llist;

#define SUCCESS 0
#define FAILURE 1

int insert_at_first(llist **head ,data_t data); 
int insert_at_last(llist **head , llist **tail, data_t data); 
void print_list(llist *head);
int expr_eval();
int expr_file_creat();
int add(char *arr1, char *arr2, int expr1, int expr2, char oper);
int oper( int expr1, int expr2);

#endif
