#ifndef MAIN_H
#define MAIN_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define FAILURE -1
#define EMPTY 5
#define DATA_NOT_FOUND -2
#define SUCCESS 0

#define CREATE_DATABASE 1
#define DISPLAY_DATABASE 2
#define UPDATE_DATABASE 3
#define SEARCH 4
#define SAVE_DATABASE 5

typedef char data_t;

typedef struct node
{
	int file_count;
	struct node *link;
	char word[20];
	struct fi_tab *file_table;
}book;

typedef struct fi_tab
{
	int word_count;
	char file_name[20];
	struct fi_tab *tab_link;
}page;

int create_database(book **head, data_t *string, data_t *filename);
void save(book **index_list);
void search(char * word, book **indexlist);
void print_list(book **index_list);
book * store_word(char *filename, book **index_list);
#endif

