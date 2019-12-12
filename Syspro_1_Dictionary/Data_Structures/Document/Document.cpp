/*
 * Document.cpp
 *
 *  Created on: Mar 3, 2018
 *      Author: greg
 */

#include "Document.h"


unsigned int Document::Get_document_id()
{
	return document_id;
}

char* Document::Get_Phrase()
{
	return phrase;
}


unsigned int Document::Get_WordsNum()
{
	return words_num;
}


Document::Document(unsigned int id,char* str,unsigned int length):document_id(id),phrase(str),words_num(length) {


}

Document::~Document() {
	// TODO Auto-generated destructor stub
}

bool Document::operator>(Document& D)
{
	return (this->document_id > D.Get_document_id());

}
