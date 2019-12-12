/*
 * Insert_Words.cpp
 *
 *  Created on: Mar 2, 2018
 *      Author: greg
 */


#include "Interface.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>









int main(int argc ,char** argv)
{
	char *input=NULL;
	size_t n;
	int topRes=0,opt,size=0;
	char* fp;
	char** TokenAr;


	if(argc==0)
	{
		printf("Usage:./Minisearch -i docfile -k K(num oftop results)\n");
		exit(EXIT_FAILURE);
	}
	while((opt=getopt(argc,argv,"i:k:"))!=-1)
	{
		switch(opt)
		{
		case 'i':
			fp=optarg;

			break;
		case 'k':
			 topRes=atoi(optarg);
			 if(topRes==0){
				 printf("K must be >0\n");
				 exit(EXIT_FAILURE);
			 }
			 break;
		default:
			printf("Usage:./Minisearch -i docfile -k K(num oftop results)\n");
			exit(EXIT_FAILURE);
		}

	}



	Interface I(fp,topRes);


	while(getline(&input,&n,stdin)!=-1){
		input=strtok(input,"\n");
		
		if(I.Read_Input(input)==exit_program)
		{
			break;
		}

	}



}
