#include"main.h"

void print_list(book **index_list)
{
    book *temp1;
    page *temp2;
    printf("\nAlphabet\tword\t   file count\t file name\t word count\n............................................................................\n");

    for(int i = 0; i < 26; i++)
    {
	temp1 = index_list[i];
	while(temp1)
	{
	printf("\n   %c\t", i +65);
	    printf("\t%s\t\t %d   ",temp1->word, temp1->file_count);
	    temp2 = temp1->file_table;
	    while(temp2)
	    {
		printf("\t %s \t\t %d  \t\t",temp2->file_name, temp2->word_count);
		temp2 = temp2->tab_link;
		for(int j = 1; j <  temp1->file_count; j++)
		    printf("\n\t\t\t\t");
	    }
	    temp1 = temp1->link;
	}
    }
}
