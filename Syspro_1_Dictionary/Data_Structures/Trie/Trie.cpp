/*
 * Trie.cpp
 *
 *  Created on: Feb 28, 2018
 *      Author: greg
 */

#include "Trie.h"
#include <stdio.h>
#include <string.h>

Trie::Trie():Root('\0'),wordsnum(0) {

}

void Trie::PrintTrie()
{
	List<Trie_Node*> NodeStack;
	Trie_Node* cur=&Root;
	NodeStack.Insert(cur);
	List<char> letters;


	PrintTrieRec(&Root,NodeStack,letters);

}

Trie_Node* Trie::GetWord(char* word)
{

	char* p;
	Trie_Node* p_t;
	List<Trie_Node>* L;

	p=word;
	p_t=&Root;
	for(unsigned int i=0;i<strlen(word);i++)
	{
		L=p_t->Get_ChildrenList();
		if(L==NULL){return NULL;}
		p_t=p_t->Get_ChildrenList()->FindObject(Trie_Node(*p));
		if(p_t==NULL){return NULL;}
		p++;
	}
	return p_t;




}



void Trie::PrintTrieRec(Trie_Node* curNode,List<Trie_Node*>& NodeStack,List<char>& letterStack)
{

	int visitedchildren=0;
	List<Trie_Node>* chilist;


	int chilistsize;

	chilist=curNode->Get_ChildrenList();
	if(chilist==NULL)
	{
		chilistsize=0;
	}
	else
	{
		chilistsize=curNode->Get_ChildrenList()->Get_Size();
	}

	while(chilistsize>visitedchildren)
	{
		Node<Trie_Node> *N;
		if(visitedchildren==0)
		{
			N=curNode->Get_ChildrenList()->Get_Head();
			curNode=&N->Get_Data_Ref();
		}
		else
		{
			N=N->Get_Next();
			curNode=&N->Get_Data_Ref();
		}
		NodeStack.Insert(curNode);
		letterStack.Insert(curNode->Get_char());

		PrintTrieRec(curNode,NodeStack,letterStack);
		curNode=NodeStack.Get_Last();


		visitedchildren++;
	}


	if(chilistsize==visitedchildren && curNode->Get_PostingList()==NULL)
	{
		if(NodeStack.Get_Size()==0 || letterStack.Get_Size()==0){return;}
		NodeStack.RemoveLast();
		letterStack.RemoveLast();
		return;
	}
	else if((chilistsize==visitedchildren))
	{
		char* Word;
		char c='\0';
		letterStack.Insert(c);
		Word=letterStack.Convert_To_Array();
		printf("%s  %d\n",Word,curNode->Get_PostingList()->Get_Size());
		letterStack.RemoveLast();
		letterStack.RemoveLast();
		NodeStack.RemoveLast();
		free(Word);
		return;
	}



}




List<Posting_Element>* Trie::Get_PostingListOfWord(char* word)
{
	char* p;
	Trie_Node* p_t;

	p=word;
	p_t=&Root;
	for(unsigned int i=0;i<strlen(word);i++)
	{
		p_t=p_t->Get_ChildrenList()->FindObject(Trie_Node(*p));
		if(p_t==NULL){return NULL;}
		p++;
	}
	return p_t->Get_PostingList();

}

unsigned int Trie::Get_NUmberOfWords()
{
	return wordsnum;
}



void Trie::Insert_Word(char* word,unsigned int doc_id)
{
	Trie_Node* current_node,*tmp_node;
	List<Trie_Node>* Childrens_ofcurrentnode;


	char* p;

	p=word;
	current_node=&Root;



	while(*p!='\0')
	{
		Childrens_ofcurrentnode=current_node->Get_ChildrenList();

		if(Childrens_ofcurrentnode==NULL || (tmp_node=Childrens_ofcurrentnode->FindObject(Trie_Node(*p)))==NULL)
		{	while(*p!='\0')
			{
				current_node->Add_Children(Trie_Node(*p));
				current_node=&current_node->Get_ChildrenList()->Get_Last();
				p++;
			}
			wordsnum++;
			current_node->AddOrUpdate_PostingElement(doc_id);
			return;
		}



		current_node=tmp_node;
		p++;
	}
	current_node->AddOrUpdate_PostingElement(doc_id);
	return;


}


Trie::~Trie() {
	// TODO Auto-generated destructor stub
}

