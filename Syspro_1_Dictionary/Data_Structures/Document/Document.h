/*
 * Document.h
 *
 *  Created on: Mar 3, 2018
 *      Author: greg
 */

#ifndef DOCUMENT_H_
#define DOCUMENT_H_

class Document {
	unsigned int document_id;
	char* phrase;
	unsigned int words_num;

public:
	bool operator>(Document& D);
	unsigned int Get_WordsNum();
	unsigned int Get_document_id();
	char* Get_Phrase();
	Document(unsigned int,char*,unsigned int);
	~Document();
};

#endif /* DOCUMENT_H_ */
