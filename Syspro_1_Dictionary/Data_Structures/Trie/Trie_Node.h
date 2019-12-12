/*
 * TrieNode.h
 *
 *  Created on: Mar 6, 2018
 *      Author: greg
 */

#ifndef DATA_STRUCTURES_TRIE_TRIE_NODE_H_
#define DATA_STRUCTURES_TRIE_TRIE_NODE_H_

#include "../../List.h"
#include "../Posting_List/Posting_Element.h"

class Trie_Node {
	List<Trie_Node>* Children_list;
	char c;
	unsigned int counter;
	List<Posting_Element>* p_list;

public:
	unsigned int GetCounter();
	bool operator==(Trie_Node&);
	void Add_Children(Trie_Node);
	void AddOrUpdate_PostingElement(unsigned int);
	char& Get_char();
	List<Trie_Node>*& Get_ChildrenList();
	List<Posting_Element>*& Get_PostingList();
	Trie_Node(char);
	~Trie_Node();
};

#endif /* DATA_STRUCTURES_TRIE_TRIE_NODE_H_ */
