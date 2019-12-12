/*
 * Statistics.cpp
 *
 *  Created on: Mar 12, 2018
 *      Author: greg
 */

#include "Statistics.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <math.h>









enum OrderBy{id,score};

void SwapDocScores(DocScore& DS1,DocScore& DS2 )
{
	DocScore DStmp(DS2);

	DS2=DS1;
	DS1=DStmp;

}


int partition (DocScore*&  DocScoresArray, int low, int high,OrderBy k)
{
    DocScore* pivot = &DocScoresArray[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {

    	if(k==id)
    	{
    		if (DocScoresArray[j].doc_id >= pivot->doc_id)
			{
				i++;    // increment index of smaller element
				SwapDocScores(DocScoresArray[i], DocScoresArray[j]);
			}
    	}
    	else if(k==score)
    	{
    		if (DocScoresArray[j].score >= pivot->score)
			{
				i++;    // increment index of smaller element
				SwapDocScores(DocScoresArray[i], DocScoresArray[j]);
			}
    	}

    }
    SwapDocScores(DocScoresArray[i + 1], DocScoresArray[high]);
    return (i + 1);
}


void QuickSort(DocScore*&  DocScoresArray, int low, int high,OrderBy k)
{
    if (low < high)
    {

        int pi = partition(DocScoresArray, low, high,k);

        QuickSort(DocScoresArray, low, pi - 1,k);
        QuickSort(DocScoresArray, pi + 1, high,k);
    }
}


char*** TokenizeStrings(unsigned int offset,char* Docstr,char* Indexstr,unsigned int& arraysize)
{
	int currentsize,start=0,finish=0;
	int line_size,k;
	char* stroken;
	char* indextok;
	char** TokenAray;
	char** IndexArray;
	char*** StringsOut;

	List<char*> DocTokens;
	List<char*> IndexTokens;

	struct winsize size;
	ioctl(STDOUT_FILENO,TIOCGWINSZ,&size);


	line_size=size.ws_col-offset;

	currentsize=strlen(Docstr);

	if(currentsize<=line_size)
	{
		DocTokens.Insert(Docstr);
		IndexTokens.Insert(Indexstr);

	}
	else
	{
		while(currentsize>0)
		{

			finish=start+line_size-1;
			while(Docstr[finish]!=' ')
			{
				finish--;
			}
			stroken=(char*)malloc(((finish-start)+2)*sizeof(char));
			indextok=(char*)malloc(((finish-start)+2)*sizeof(char));
			k=0;
			for(int j=start;j<=finish;j++)
			{
				stroken[k]=Docstr[j];
				indextok[k]=Indexstr[j];
				k++;
			}

			stroken[k]='\0';
			indextok[k]='\0';

			DocTokens.Insert(stroken);
			IndexTokens.Insert(indextok);

			currentsize=currentsize-(finish-start+1);
			start=finish+1;

		}


	}

	TokenAray=DocTokens.Convert_To_Array();
	IndexArray=IndexTokens.Convert_To_Array();

	StringsOut=(char***)malloc(2*sizeof(char**));
	StringsOut[0]=TokenAray;
	StringsOut[1]=IndexArray;

	arraysize=DocTokens.Get_Size();

	return StringsOut;



}





Statistics::Statistics(Data_Structures& Data):D(&Data),num_of_docs(D->Get_Doc_Arraysize()),kl(1.2),b(0.75),DocScoresArray(NULL),ArraySize(0)
{

	unsigned int wordscount=0;

	ScoreList=new List<DocScore>;

	for(unsigned int i=0;i<num_of_docs;i++)
	{
		wordscount=wordscount+D->Get_Document(i).Get_WordsNum();
	}
	avgdl=(double)wordscount/(double)num_of_docs;


}


void Statistics::PrintScores(int Res)
{
	unsigned int counter=1,size=0,offset;

	char* out;
	Document* D_p;
	char*** PhraseIndexing;

	for(int i=0;i<Res;i++)
	{
		D_p=&D->Get_Document(DocScoresArray[i].doc_id);
		asprintf(&out,"%d .(%.5d)[%.4f] ",counter,DocScoresArray[i].doc_id,DocScoresArray[i].score);
		offset=strlen(out);
		PhraseIndexing=TokenizeStrings(offset,D_p->Get_Phrase(),DocScoresArray[i].wordsIndex,size);
		printf("%s",out);
		for(int j=0;j<size;j++)
		{

			printf("%s\n",PhraseIndexing[0][j]);

			for(int k=1;k<=offset;k++){
				putchar(' ');
			}

			printf("%s\n",PhraseIndexing[1][j]);
			putchar('\n');

			if(j!=(size-1))
			{
				for(int k=1;k<=offset;k++){
					putchar(' ');
				}
			}


		}
		counter++;

		free(out);
		out=NULL;


		for(int l=0;l<size;l++)
		{
			free(PhraseIndexing[0][l]);
			PhraseIndexing[0][l]=NULL;
			free(PhraseIndexing[1][l]);
			PhraseIndexing[1][l]=NULL;
		}
		free(PhraseIndexing[0]);
		PhraseIndexing[0]=NULL;
		free(PhraseIndexing[1]);
		PhraseIndexing[1]=NULL;
		free(PhraseIndexing);
		PhraseIndexing=NULL;

	}




}



void FindDuplicates(DocScore*& DocScoresArray,unsigned int& size)
{
	DocScore* cur;
	int cur_index=0;
	unsigned int final_size=1;

	cur=&DocScoresArray[cur_index];
	for(unsigned int i=1;i<size;i++)
	{
		if(cur->doc_id==DocScoresArray[i].doc_id)
		{
			cur->score=cur->score+DocScoresArray[i].score;
			for(unsigned int j=0;j<strlen(cur->wordsIndex);j++)
			{
				if(cur->wordsIndex[j]=='^' || DocScoresArray[i].wordsIndex[j]=='^')
				{
					cur->wordsIndex[j]='^';
				}
				else
				{
					cur->wordsIndex[j]=' ';
				}
			}
		}
		else
		{
			final_size++;
			cur_index++;
			DocScoresArray[cur_index]=DocScoresArray[i];
			cur=&DocScoresArray[cur_index];

		}

	}


	size=final_size;
	DocScoresArray=(DocScore*)realloc(DocScoresArray,size*sizeof(DocScore));




}

void IndexStr(char* word,char* phrase,char*& currentIndex)
{

	unsigned int strLen,wordLen,i,j,k,l;
	bool found;



	 strLen  = strlen(phrase);  // Find length of string
	wordLen = strlen(word); // Find length of word
	l=strLen - wordLen;

	if(currentIndex==NULL)
	{
		currentIndex=(char*)malloc((strLen+1)*sizeof(char));
		for(i=0; i<strLen;i++)
		{
			currentIndex[i]=' ';
		}
		currentIndex[strLen]='\0';

	}



	for(i=0; i<=l; i++)
	{
		// Match word at current position
		found = true;
		for(j=0; j<wordLen; j++)
		{
			// If word is not matched

			if(phrase[i + j] != word[j])
			{
				found = false;
				break;
			}
		}
		if(found)
		{
			if(i==0 || i==l )
			{
				for(k=i;k<i+wordLen;k++)
				{
					currentIndex[k]='^';

				}
				i=i+wordLen;

			}
			else if((phrase[i-1]==' ' ||  phrase[i-1]=='\t') && (phrase[i+wordLen]==' ' ||  phrase[i+wordLen]=='\t') )
			{
				for(k=i;k<i+wordLen;k++)
				{
					currentIndex[k]='^';

				}
				i=i+wordLen;

			}

		}
	}

}








DocScore* Statistics::CalculateScores(char** wordsArray,unsigned int size)
{
	Node<Posting_Element>* N_pe;

	Document* Dp;

	List<Posting_Element>* L_p;
	if(size>10)
	{
		size=10;
	}




	for(unsigned int i=0;i<size;i++)
	{
		L_p=D->Get_Trie().Get_PostingListOfWord(wordsArray[i]);
		if(L_p==NULL){continue;}
		N_pe=L_p->Get_Head();

		while(N_pe!=NULL)
		{
			Dp=&D->Get_Document(N_pe->Get_Data_Ref().Get_id());


			DocScore DS=CalculateWordScore(L_p->Get_Size(),Dp,N_pe->Get_Data_Ref());
			IndexStr(wordsArray[i],Dp->Get_Phrase(),DS.wordsIndex);

			ScoreList->Insert(DS);

			N_pe=N_pe->Get_Next();
		}

	}
	if(ScoreList->Get_Size()==0){return NULL;}
	DocScoresArray=ScoreList->Convert_To_Array();
	ArraySize=ScoreList->Get_Size();
	delete ScoreList;

	QuickSort(DocScoresArray,0,ArraySize-1,id);
	FindDuplicates(DocScoresArray,ArraySize);
	QuickSort(DocScoresArray,0,ArraySize-1,score);

	return DocScoresArray;


}

double Statistics::InverseDocumentFrequency(const unsigned int num_of_docswith_word)
{

	return log10(((double)num_of_docs-(double)num_of_docswith_word+0.5)/((double)num_of_docswith_word+0.5));


}




DocScore Statistics::CalculateWordScore(const unsigned int num_of_docswith_word,Document* Doc,Posting_Element& pe)
{

	double idf;
	double score;
	double term_frequency;
	double numerator,denominator;

	idf=InverseDocumentFrequency(num_of_docswith_word);
	term_frequency=(double)pe.Get_Counter();
	numerator=term_frequency*(kl+1);

	denominator=term_frequency+kl*(1-b+b*((double)Doc->Get_WordsNum()/avgdl));

	score=idf*numerator/denominator;

	return DocScore(Doc->Get_document_id(),score);



}


Data_Structures* Statistics::GetDataStructures()
{

	return D;
}












Statistics::~Statistics() {

//	ScoreList=NULL;
//
//	free(DocScoresArray);
//	DocScoresArray=NULL;
}
