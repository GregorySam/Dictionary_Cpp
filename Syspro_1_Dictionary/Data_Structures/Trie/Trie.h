/*
 * Trie.h
 *
 *  Created on: Feb 28, 2018
 *      Author: greg
 */

#ifndef TRIE_H_
#define TRIE_H_
#include "Trie_Node.h"

class Trie {
	Trie_Node Root;
	unsigned int wordsnum;
public:
	void PrintTrie();
	void PrintTrieRec(Trie_Node*,List<Trie_Node*>&,List<char>&);
	unsigned int Get_NUmberOfWords();
	List<Posting_Element>* Get_PostingListOfWord(char*);
	Trie_Node* GetWord(char*);
	void Insert_Word(char*,unsigned int);
	Trie();
	~Trie();
};

#endif /* TRIE_H_ */
