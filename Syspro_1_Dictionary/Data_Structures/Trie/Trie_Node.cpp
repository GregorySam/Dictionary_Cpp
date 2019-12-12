/*
 * TrieNode.cpp
 *
 *  Created on: Mar 6, 2018
 *      Author: greg
 */

#include "Trie_Node.h"



void Trie_Node::Add_Children(Trie_Node new_T)
{
	if(Children_list==NULL)
	{
		Children_list=new List<Trie_Node>;
	}
	Children_list->Insert(new_T);

}


void Trie_Node::AddOrUpdate_PostingElement(unsigned int id)
{
	Posting_Element *p;

	counter++;

	if(p_list==NULL)
	{
		p_list= new List<Posting_Element>;
		Posting_Element pE(id);
		p_list->Insert(pE);
		return;

	}
	if((p=p_list->FindObject(Posting_Element(id)))!=NULL)
	{
		p->Increase_Counter();
	}
	else
	{
		Posting_Element pE(id);
		p_list->Insert(pE);
	}
}


unsigned int Trie_Node::GetCounter()
{
	return counter;
}

bool Trie_Node::operator==(Trie_Node& T)
{
	return (this->Get_char()==T.Get_char());

}


Trie_Node::Trie_Node(char character):Children_list(NULL),c(character),counter(0),p_list(NULL) {
	// TODO Auto-generated constructor stub

}

Trie_Node::~Trie_Node() {

	if(Children_list!=NULL)
	{
		delete Children_list;
		Children_list=NULL;

	}
	if(p_list!=NULL)
	{
		delete p_list;
		p_list=NULL;

	}



	// TODO Auto-generated destructor stub
}


char& Trie_Node::Get_char()
{
	return c;
}

List<Trie_Node>*& Trie_Node::Get_ChildrenList()
{
	return Children_list;
}


List<Posting_Element>*& Trie_Node::Get_PostingList()
{
	return p_list;
}
