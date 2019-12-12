/*
 * DataStructures.cpp
 *
 *  Created on: Mar 3, 2018
 *      Author: greg
 */

#include "Data_Structures.h"

#include <stdio.h>





void Data_Structures::InsertIn_DocMap(Document D)
{
	static unsigned int index=0;

	Doc_Array[index]=D;

	index++;


}

Trie& Data_Structures::Get_Trie()
{
	return T;
}



Document& Data_Structures::Get_Document(unsigned int id)
{
	return Doc_Array[id];
}



unsigned int Data_Structures::Get_Doc_Arraysize()
{
	return Doc_Arraysize;
}


bool CheckFile(const char* filename,unsigned int& DocMapSize)
{
	FILE* fp;
	char *line_buffer=NULL;
	size_t n;
	unsigned int count=0,id;
	bool flag=true;


	fp=fopen(filename,"r");
	if(fp==NULL)
	{
		return false;
	}

	while(getline(&line_buffer,&n,fp)!=-1)
	{

		id=GetID(line_buffer);

		if(id!=count)
		{
			fclose(fp);
			return false;
		}
		count++;
		DocMapSize++;
	}

	free(line_buffer);
	line_buffer=NULL;
	fclose(fp);
	return true;


}




Data_Structures::Data_Structures(const char* filename)
{
	FILE* fp;
	unsigned int words_num,i,DocMapSize=0;
	char *line_buffer=NULL;
	char** words;
	unsigned int id,count;

	char* tmp_phrase,*phrase;

	size_t n=0;



	if(!CheckFile(filename,DocMapSize))
	{
		printf("File error\n");
		exit(EXIT_FAILURE);
	}

	Doc_Arraysize=DocMapSize;

	Doc_Array=(Document*)malloc(DocMapSize*sizeof(Document));

	fp=fopen(filename,"r");
	if(fp==NULL)
	{
		printf("Couldn't read file\n");
		exit(EXIT_FAILURE);
	}
	while(getline(&line_buffer,&n,fp)!=-1)
	{


		id=GetID(line_buffer);

		/////////////////////////////

		tmp_phrase=strtok(NULL,"\n");
		phrase=(char*)malloc((strlen(tmp_phrase)+1)*sizeof(char));
		strcpy(phrase,tmp_phrase);

		words=SplitPhrase(tmp_phrase,words_num);
		InsertIn_DocMap(Document(id,phrase,words_num));

		////////////////////////////


		for(i=0;i<words_num;i++)
		{
			T.Insert_Word(words[i],id);
			free(words[i]);
			words[i]=NULL;
		}
		free(words);
		words=NULL;

		//////////////////////////////
		count++;
	}
	free(line_buffer);
	line_buffer=NULL;

	fclose(fp);


}

Data_Structures::~Data_Structures() {
//	free( Doc_Array;
//	Doc_Array=NULL;
}

