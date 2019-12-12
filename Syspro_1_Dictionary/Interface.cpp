/*
 * Interface.cpp
 *
 *  Created on: Mar 3, 2018
 *      Author: greg
 */

#include "Interface.h"
#include "Statistics.h"

#include <stdio.h>

ReturnCode Interface::Read_Input(char* Input)
{
	char* command;
	if(Input==NULL)
	{return error;}

	if(Input[0]!='/'){return error;}
	command=strtok(Input," ");

	if(strcmp(command,"/search")==0)
	{

		Search_Words(strtok(NULL,"\n"));

	}
	else if(strcmp(command,"/df")==0)
	{
		char* word;
		word=strtok(NULL," ");
		if(word!=NULL)
		{
			Trie_Node* T;
			T=D.Get_Trie().GetWord(word);
			if(T!=NULL)
			{
				printf("%s  %d\n",word,T->Get_PostingList()->Get_Size());

			}
			else{
				printf("Did not find word\n");
				return success;
			}
		}
		else
		{
			D.Get_Trie().PrintTrie();
		}

	}
	else if(strcmp(command,"/tf")==0)
	{
		int id;
		char* word;
		char* strid;
		Posting_Element* p;
		List<Posting_Element>* pl;

		strid=strtok(NULL," ");
		word=strtok(NULL,"\n");
		if(strid==NULL || word==NULL)
		{
			printf("Command Error\n");
			return error;
		}
		id=GetID(strid);
		if(id<0 || word==NULL)
		{
			printf("Command Error\n");
			return error;
		}

		pl=D.Get_Trie().Get_PostingListOfWord(word);
		if(pl==NULL)
		{
			printf("No word: %s\n",word);
			return success;
		}

		p=pl->FindObject(Posting_Element(id));
		if(p==NULL)
		{
			printf("No word: %s in doc: %d\n",word,id);
			return success;

		}
		printf("%d %s %d\n",id,word,p->Get_Counter());
		return success;
	}
	else if(strcmp(command,"/exit")==0)
	{
		return exit_program;

	}
	return success;




}


ReturnCode Interface::Search_Words(char* Words)
{
	char** words_array;
	unsigned int words_num=0;




	Statistics S(D);

	if(Words==NULL){return error;}

	words_array=SplitPhrase(Words,words_num);

	if(S.CalculateScores(words_array,words_num)!=NULL)
	{
		S.PrintScores(results_num);
	}
	else
	{
		printf("No Document found with words\n");
	}

	for(unsigned int i=0;i<words_num;i++)
	{
		free(words_array[i]);
		words_array[i]=NULL;
	}
	free(words_array);

	words_array=NULL;


	return success;




}


Interface::Interface(char* filename,unsigned int results):D(filename),results_num(results)
{


}

Interface::~Interface() {
	// TODO Auto-generated destructor stub
}
