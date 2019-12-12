/*
 * Statistics.h
 *
 *  Created on: Mar 12, 2018
 *      Author: greg
 */

#ifndef STATISTICS_H_
#define STATISTICS_H_
#include "Data_Structures/Document/Document.h"
#include "Data_Structures/Data_Structures.h"






typedef struct DocScore
{

	unsigned int doc_id;
	double score;
	char* wordsIndex;

	DocScore(unsigned int id,double s):doc_id(id),score(s),wordsIndex(NULL){};
	~DocScore()
	{
//		free(wordsIndex);
//		wordsIndex=NULL;

	}

}DocScore;



class Statistics {
	List<DocScore>* ScoreList;
	Data_Structures* D;
	DocScore* DocScoresArray;
	unsigned int ArraySize;

	const unsigned int num_of_docs;
	const double kl;
	const double b;
	double avgdl;


public:
	void PrintScores(int);
	double InverseDocumentFrequency(const unsigned int);
	DocScore* CalculateScores(char**,unsigned int);
	DocScore CalculateWordScore(unsigned int,Document*,Posting_Element&);
	Data_Structures* GetDataStructures();
	Statistics(Data_Structures&);
	~Statistics();
};

#endif /* STATISTICS_H_ */
