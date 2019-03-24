#include <stdio.h>
#include<string.h>
#include "encode.h"
#include "types.h"

/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("INFO: IMAGE INFO: Width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("	       	  Height = %u\n", height);

    // Return image capacity
    return width * height * 3;
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
	perror("fopen");
	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

	return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
	perror("fopen");
	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

	return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
	perror("fopen");
	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

	return e_failure;
    }
    printf("INFO: Opening beautiful.bmp\n");
    printf("INFO: Opening secret.txt\n");
    // No failure return e_success
    return e_success;
}

/* Copy bmp image header */
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
    printf("INFO: Copying Image Header\n");
    char ch;
    fseek(fptr_src_image,0L,SEEK_SET);
    while(ftell(fptr_src_image) != 54)
    {
	ch = fgetc(fptr_src_image);
	putc(ch,fptr_dest_image);
    }
    printf("INFO: Done\n");
    return e_success;
}

/* Store Magic String */
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    printf("INFO: Encoding Magic String Signature\n");
    char ch,magic;
    magic = *magic_string;
    for(int i = 0; i < 8; i++)
    {
	ch = getc(encInfo->fptr_src_image);
	ch = ((ch & ~1) | (magic & 1));
	magic = magic >> 1;
	putc(ch, encInfo->fptr_stego_image);
    }
    printf("INFO: Done\n");
} 

/* Encode secret file extenstion */
Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo)
{
    printf("INFO: Encoding secret.txt File Extention\n");
    int extn_size, lim;
    extn_size = strlen(file_extn);
    lim = extn_size;
    char ch, temp[extn_size];
    for(int i=0;i<extn_size;i++)
	temp[i] = file_extn[i];

    for(int i = 0; i < 32; i++)
    {
	ch = getc(encInfo->fptr_src_image);
	ch = (ch & ~1) | (extn_size & 1);
	extn_size = extn_size >> 1;
	putc(ch, encInfo->fptr_stego_image);
    }

    int j = 0;
    while(j < lim)
    {
	for(int i = 0; i < 8; i++)
	{

	    ch = getc(encInfo->fptr_src_image);
	    ch = (ch & ~1) | ( temp[j] & 1);
	    temp[j] = temp[j] >> 1;
	    putc(ch, encInfo->fptr_stego_image);
	}
	j++;
    }
    printf("INFO: Done\n");
    return e_success;
}

/* Get file size */
uint get_file_size(FILE *fptr)
{
    uint size;
    fseek(fptr,0L,SEEK_END);
    size = ftell(fptr) - 1;
    return size;
}

/* Encode secret file size */
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{

    printf("INFO: Encoding secret.txt File Size\n");
    char ch;
    for(int i = 0; i < 32; i++)
    {
	ch = getc(encInfo->fptr_src_image);
	ch = (ch & ~1) | (file_size & 1);
	file_size = file_size >> 1;
	putc(ch, encInfo->fptr_stego_image);
    }
    printf("INFO: Done\n");
    return e_success;
}

/* check capacity */
Status check_capacity(EncodeInfo *encInfo)
{
    if(encInfo->image_capacity < encInfo->size_secret_file )
    {
	printf("INFO: The data cant be stored in the image file \n");	
	return e_failure;
    }	
    else
	printf("INFO: The data can be stored in the image file !!\n");
    return e_success;	

}


/* Encode secret file data*/
Status encode_secret_file_data(EncodeInfo *encInfo)
{
    printf("INFO: Encoding secret.txt File data\n");
    char ch,tx;
    fseek(encInfo->fptr_secret, 0L, SEEK_SET);
    int j, i, size = encInfo->size_secret_file;
    while(j != size)
    {
	tx = getc(encInfo->fptr_secret);
	for(i = 0; i < 8; i++)
	{
	    ch = getc(encInfo->fptr_src_image);
	    ch = (ch & ~1) | (tx & 1);
	    tx = tx >> 1;
	    putc(ch, encInfo->fptr_stego_image);

	}
	j++;
    }
    printf("INFO: Done\n");
    return e_success;
}

/* Copy remaining image bytes from src to stego image after encoding */
Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
    printf("INFO: Copying Remaining Image Data \n");
    char ch;
    while( !feof(fptr_src))
    {
	ch = getc(fptr_src);
	putc(ch,fptr_dest);
    }
    printf("INFO: Done \n");
    return e_success;
}

Status check_magic(FILE *sec_in)
{
    int i;
    char ch, magic = 0;
    fseek(sec_in , 54L,SEEK_SET);
    for(i=0;i<8;i++)
    {
	ch = getc(sec_in);
	ch = (ch & 1) << i;
	magic = ch | magic;
    }
    if (magic == '%')
	printf("INFO: Magic String Found\n      Decoding Process Initiated\n");
    else
	return 1;
}

int get_extn_size(FILE *sec_in)
{
    int i, ext_siz = 0;
    char ch;
    for(i=0;i<32;i++)
    {
	ch =getc(sec_in);
	ext_siz = (((ch & 1) << i) | ext_siz );
    }

    return ext_siz;
}
char *get_extn(FILE * sec_in, char * extn, int ext_siz)
{
    char ch, ext;
    int i, j = 0;
    //char temp[ext_siz];
    while(j < ext_siz)
    {
	char ch, ext = 0;
	for(i=0;i<8;i++)
	{
	    ch = getc(sec_in);
	    ext = (((ch & 1) << i) | ext);
	}
	extn[j]=ext;
	j++;
    }
    return extn;
}


Status decode_data_file(FILE * sec_in, FILE * data_out)
{
    printf("INFO: Decoding Data\n");
    int size=0, i, j=0;
    char ch, data = 0;
    for(i=0;i<32;i++)
    {
	ch = getc(sec_in);
	size = (((ch & 1) << i) | size );
    }

    while(j < size)
    {
	data = 0;
	for(i=0;i<8;i++)
	{
	    ch = getc(sec_in);
	    data = (((ch & 1) << i) | data);
	}
	putc(data,data_out);
	j++;
    }
    printf("INFO: Done\nINFO: Data Decoded successfully\n");

}
