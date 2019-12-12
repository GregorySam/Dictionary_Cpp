/*
 * DataStructures.h
 *
 *  Created on: Mar 3, 2018
 *      Author: greg
 */














#ifndef DATASTRUCTURES_H_
#define DATASTRUCTURES_H_

#include "Trie/Trie.h"
#include "../List.h"
#include "Document/Document.h"
#include <string.h>



inline int GetID(char* line_buffer)
{
	char* str_id;
	unsigned int count,i,id;

	str_id=strtok(line_buffer," \t");
	count=0;

	for(i=0;i<strlen(str_id);i++)
	{
		if(str_id[i]=='0')
		{
			count++;
		}
	}
	if(count==(strlen(str_id)))
	{
		id=0;
	}
	else
	{
		id=atoi(str_id);
		if(id==0)
		{
			return -1;

		}
	}
	return id;

}

inline char** SplitPhrase(char* phrase,unsigned int &words_num)
{
	char* pch;
	char** words=NULL;
	unsigned int count=0;

	pch = strtok(phrase," \t");

	while (pch != NULL)
	{
		count++;
		words=(char**)realloc(words,count*sizeof(char*));
		words[count-1]=(char*)malloc((strlen(pch)+1)*sizeof(char));
		strcpy(words[count-1],pch);

		pch = strtok(NULL," \t");
	}
	free(pch);
	words_num=count;
	return words;

}


class Data_Structures {
	Trie T;
	Document* Doc_Array;
	unsigned int Doc_Arraysize;

public:
	unsigned int Get_Doc_Arraysize();
	Document& Get_Document(unsigned int);
	Trie& Get_Trie();
	void InsertIn_DocMap(Document);
	Data_Structures(const char*);
	~Data_Structures();
};


#endif /* DATASTRUCTURES_H_ */


