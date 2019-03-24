#include <stdio.h>
#include<string.h>
#include "encode.h"
#include "types.h"

void delay();
int main(int argc, char **argv)
{
    EncodeInfo encInfo;
    uint img_size, extn_size, mode;
    char magic_string;
    mode = strcmp(argv[1],"-e");

    if(mode == 0)
    {

	// Fill with sample filenames
	encInfo.src_image_fname = argv[2];
	encInfo.secret_fname = argv[3];
	encInfo.stego_image_fname = "stego_img.bmp";

	// Test open_files
	printf("INFO: Opening Requied Files\n");
	if (open_files(&encInfo) == e_failure)
	{
	    printf("ERROR: %s function failed\n", "open_files" );
	    return 1;
	}
	else
	{
	    printf("INFO: %s function completed\n", "open_files" );
	}

	// Test get_image_size_for_bmp
	img_size = get_image_size_for_bmp(encInfo.fptr_src_image);
	printf("	 	  Image size = %u\n", img_size);

	//cpying header file
	copy_bmp_header(encInfo.fptr_src_image, encInfo.fptr_stego_image);
	magic_string = '%';

	//encoding magic string
	encode_magic_string(&magic_string, &encInfo);

	//ENCODING EXTENTION OF SECRET FILE
	//extn_size = strlen(strstr(argv[3],"."));
	char * extn_file = strstr(argv[3],".");
	encode_secret_file_extn(extn_file, &encInfo);

	//geting file size of secret file
	encInfo.size_secret_file = get_file_size(encInfo.fptr_secret);
	encode_secret_file_size(encInfo.size_secret_file, &encInfo);


	//capacity check
	encInfo.image_capacity = img_size;
	check_capacity(&encInfo);

	//data encoding
	encode_secret_file_data(&encInfo);


	copy_remaining_img_data( encInfo.fptr_src_image, encInfo.fptr_stego_image);
	printf("INFO: Encoding Compleated Successfuly\n");
    }
    else if (mode == -1)									//For decoding
    {
	printf("INFO: Decoding\nINFO: Opening required files\n");

	//opening Files
	FILE *sec_in, *data_out;									
	sec_in = fopen(argv[2],"r");
	if(sec_in == NULL)
	{
	    printf("INFO: Input File Was Not Found\n");
	    return 1;
	}
	printf("INFO: %s was successfully opend\n",argv[2]);
	if(argc > 3)
	    data_out = fopen(argv[3],"w");
	else 
	    data_out = fopen("data_out.txt","w");
	if(data_out == NULL)
	{
	    printf("INFO: output File coud't be created\n");
	    return 1;
	}
	uint extn_size, data_size;

	//Checking for magic string
	char magic_string;
	printf("INFO: Decoding Magic string\n");
	check_magic(sec_in);

	//decoding file extrention size
	extn_size = get_extn_size(sec_in);
	printf("INFO: Decoding File Size\n");
	char extn[extn_size];

	//decoding file extention
	get_extn(sec_in, extn,extn_size);

	// decoding secret file size and data
	decode_data_file(sec_in,data_out);
    }
    return 0;
}
void delay()
{
    for(int i=0;i<3277;i++)
    {
	for(int i=0;i<327;i++)
	{
	    for(int j =0; j <367;j++)
	    {}
	}
    }
}
