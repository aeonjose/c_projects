/***************************************************************************************************************************************************
 *Author         :Emertxe(http://www.emertxe.com)
 *Date           :Mon 22 May 2017 14:15:06 IST
 *File           :store_word.c
 *Title          :To store the words one by one
 *Description    :This function process word by word and stores it in the data base.
 ****************************************************************************************************************************************************/
#include"main.h"

book* store_word(char *filename, book **index_list)
{
    /* Definition here */
    FILE * fptr = NULL;
    fptr = fopen(filename, "r");
    if(fptr == NULL)
    {
	printf("File cant be opened\n");
	exit(0);
    }
    char ch, word[10];
    int i = 0, index;
    book * new1, *temp1, *prev1;
    page *new2, *temp2, *prev2;

    while(ch = fgetc(fptr))
    {
	if(ch == EOF)
	    break;
	if(ch == ' ' || ch == '\n')
	{
	    word[i] = '\0';
	    i=0;

	    // finding index 
	    index = word[0] % 96 - 1;
	    if(index > 26)
		index = word[0] % 64 - 1;

	    //inserting at the first node
	    if(index_list[index] == NULL)
	    {
		new1 = malloc(sizeof(book));
		new1->file_count = 1;
		new1->link = NULL;
		strcpy(new1->word, word);
		new2 = malloc(sizeof(page));
		new2->word_count = 1;
		for(int j =0; j<strlen(filename); j++)
		{
		    new2->file_name[j] = filename[j] ;
		}
		new2->tab_link = NULL;
		new1->file_table = new2;
		index_list[index] = new1;

	    }
	    else  
	    {
		temp1 = index_list[index];
		while(temp1)
		{
		    if(!strcasecmp(temp1->word, word))
		    {
			temp2 = temp1->file_table;	
			while(temp2)
			{
			    // incrementing the word count in same file
			    if(!strcmp(temp2->file_name, filename))
			    {
				(temp2->word_count)++;
				break;
			    }
			    prev2 = temp2;
			    temp2 = temp2->tab_link;
			}
			// inserting the new file name for the same word
			if(!temp2)
			{
			    temp1->file_count++;
			    new2 = malloc(sizeof(page));
			    new2->word_count =1; 
			    for(int j = 0; j<strlen(filename); j++)
				new2->file_name[j] =filename[j];
			    new2->tab_link =NULL; 
			    prev2->tab_link = new2;
			    break;
			}
		    }
		    prev1 = temp1;
		    temp1 = temp1->link;
		}

		// inserting a new word for same index
		if(!temp1 && !temp2)
		{
		    new1 = malloc(sizeof(book));
		    new1->file_count = 1;
		    new1->link = NULL;
		    strcpy(new1->word, word);
		    new2 = malloc(sizeof(page));
		    new2->word_count = 1;
		    for(int j = 0; j<strlen(filename); j++)
			new2->file_name[j] = filename[j];
		    new2->tab_link = NULL;
		    new1->file_table = new2;
		    prev1->link = new1;
		}
	    }
	}

	// accepting characters and creating words
	if(ch > 64  && ch < 91 || ch > 96 && ch < 123)
	{
	    word[i] = ch;
	    i++;
	}
    }
}

