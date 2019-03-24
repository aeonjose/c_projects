/***************************************************************************************************************************************************
 *Author         :Emertxe(http://www.emertxe.com)
 *Date           :Mon 22 May 2017 15:56:15 IST
 *File           :search.c
 *Title          :To search the words.
 *Description    :Each word is now used to search in the linkedlist. The word has to be compared with
 :each word in the linked list. When found, the file details can be retrieved. Since the
 :linkedlist is in sorted order, the complexity of searching the word in the complete list
 :can be avoided. While string comparison, if the word in linkedlist is greater than the
 :word to be search, it shows the word doesnt exists in the list,
 ****************************************************************************************************************************************************/
#include "main.h"

void search (char *word, book **indexlist)
{
    /* Definition here */
    int index = word[0] % 96 -1;
    if (index > 26)
	index = word[0] % 64;

    book *temp1;
    page *temp2;

    //finding the index for the word
    index  = word[0] % 96 - 1;
    if(index > 26 )
	index  = word[0] % 64 - 1;

    {
	temp1 = indexlist[index];
	printf("\n Searched Word\t\tFile Count\t\tFile Names\t\tWord Count\n.....................................................................................\n");
	while(temp1)
	{
	    if(!strcasecmp(temp1->word, word))
	    {
		printf("     %s\t\t     %d   ",temp1->word, temp1->file_count);
		temp2 = temp1->file_table;
		while(temp2)
		{
		    printf("\t\t %s   \t\t %d  \t\t",temp2->file_name, temp2->word_count);
		    temp2 = temp2->tab_link;
		    for(int j = 1; j <  temp1->file_count; j++)
			printf("\n\t\t\t\t");
		}
	    }
	    temp1 = temp1->link;
	}
    }


}

