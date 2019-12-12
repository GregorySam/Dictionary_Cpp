/*
 * PostingElement.h
 *
 *  Created on: Feb 27, 2018
 *      Author: greg
 */

#ifndef POSTING_ELEMENT_H_
#define POSTING_ELEMENT_H_

class Posting_Element {
	unsigned int doc_id;
	unsigned int counter;
public:
	bool operator==(Posting_Element&);
	Posting_Element(unsigned int);
	unsigned int Get_id();
	unsigned int Get_Counter();
	void Increase_Counter();
	~Posting_Element();
};

#endif /* POSTING_ELEMENT_H_ */
