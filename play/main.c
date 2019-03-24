/***************************************************************************************************************************************************
 *Author		:Emertxe(http://www.emertxe.com)
 *Date		:Mon 22 May 2017 14:00:05 IST
 *File		:main.c
 *Title		:Driver function
 *Description	:This function acts like the driver function for the project inverted search
 ****************************************************************************************************************************************************/
#include"main.h"

int main(int argc, char *argv[])
{
    /* Define the main function here */
    book *index_list[26] = {NULL};
    char filename[20], search_word[20], opt;
    int choice;

    do 
    {
	printf("1.Creat Database\t2.Display Database\t3.Update Database\t4.Search\t5.Save Database\nEnter the choiice : ");
	scanf("%d", &choice);
	switch(choice)
	{
	    case CREATE_DATABASE : printf("Enter the file name : \n");
		     scanf("%s", filename);
		     store_word(filename, index_list);
		     break;

	    case 2 : print_list(index_list);
		     break;

	    case 3 : printf("enter the file name : " );
		     scanf("%s", filename);
		     store_word(filename, index_list);
		     break;

	    case 4 : printf("Enter the word you want to search\n");
		     scanf("%s", search_word);
		     search(search_word, index_list);
		     break;

	    case 5 : save(index_list);
		     break;

	    default : printf("Check the entry\n");

	}
	printf("\nDo you wish to do another operation\n");
	scanf(" %c", &opt);
    }while(opt == 'y');
    return 0;
}

