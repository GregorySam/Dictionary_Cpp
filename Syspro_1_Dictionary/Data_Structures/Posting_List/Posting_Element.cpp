/*
 * PostingElement.cpp
 *
 *  Created on: Feb 27, 2018
 *      Author: greg
 */

#include "Posting_Element.h"

Posting_Element::Posting_Element(unsigned int id):doc_id(id),counter(1)
{

}

unsigned int Posting_Element::Get_id()
{
	return doc_id;

}


bool Posting_Element::operator ==(Posting_Element& p_e)
{
	return (p_e.Get_id()==this->Get_id());

}

unsigned int Posting_Element::Get_Counter()
{
	return counter;
}

void Posting_Element::Increase_Counter()
{
	counter++;
}

Posting_Element::~Posting_Element(){}
