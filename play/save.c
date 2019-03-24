#include"main.h"

void save(book **index_list)
{
    FILE *fptr;
    fptr = fopen("Backup.txt", "w");
    book *temp1;
    page *temp2;

    fprintf(fptr,"\nAlphabet\tword\t   file count\t file name\t word count\n............................................................................\n");

    for(int i = 0; i < 26; i++)
    {
	temp1 = index_list[i];
	while(temp1)
	{
	fprintf(fptr,"\n   %c\t", i +65);
	    fprintf(fptr,"\t%s\t\t %d   ",temp1->word, temp1->file_count);
	    temp2 = temp1->file_table;
	    while(temp2)
	    {
		fprintf(fptr,"\t %s \t\t %d  \t\t",temp2->file_name, temp2->word_count);
		temp2 = temp2->tab_link;
		for(int j = 1; j <  temp1->file_count; j++)
		    fprintf(fptr, "\n\t\t\t\t");
	    }
	    temp1 = temp1->link;
	}
    }
    fclose(fptr);
}
