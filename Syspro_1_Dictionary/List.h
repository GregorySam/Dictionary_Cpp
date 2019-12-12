/*
 * List.h
 *
 *  Created on: Mar 6, 2018
 *      Author: greg
 */

#ifndef LIST_H_
#define LIST_H_
#include <stdlib.h>


template <class T>
class Node
{
	Node<T> *next;
	T data;
public:
	void Set_Data(T& Newdata)
	{
		data=Newdata;
	}
	T  Get_Data_Cpy()
	{
		return data;
	}


	T&  Get_Data_Ref()
	{
		return data;
	}


	Node<T>* Get_Next()
	{
		return next;
	}
	void Set_NextNULL()
	{
		next=NULL;
	}
	void  Set_Next(Node<T> New_Node)
	{
		next=new Node<T>(New_Node);
	}

	Node(T& Data):next(NULL),data(Data)
	{}
	~Node(){};
};



template <class T>
class List {
	Node<T> *Head;
	Node<T> *End;
	unsigned int size;
public:

	List()
	{
		size=0;
		Head=NULL;
		End=NULL;
	}
	Node<T>* Get_Head()
	{
		return Head;
	}


	T* Convert_To_Array()
	{

		Node<T>* current_node=Head;
		T* Array;


		Array=(T*)malloc(size*sizeof(T));


		for(unsigned int i=0;i<size;i++)
		{

			Array[i]=current_node->Get_Data_Cpy();
			current_node=current_node->Get_Next();
		}
		return Array;

	}
	void Insert(T& new_obj)
	{
		Node<T>* current;
		size++;

		current=End;
		if(current==NULL)
		{

			current=new Node<T>(new_obj);
			End=current;
			Head=current;
			return;
		}
		else
		{
			current->Set_Next(new_obj);
			End=current->Get_Next();
		}

	}
	void RemoveLast()
	{
		Node<T>* cur;
		cur=Head;
		if(size==1)
		{
			delete cur;
			Head=NULL;
			End=NULL;
			size--;
			return;
		}
		while(cur->Get_Next()!=End)
		{
			cur=cur->Get_Next();
		}
		End=cur;
		delete cur->Get_Next();
		End->Set_NextNULL();


		size--;
	}
	T& Get_Last()
	{
		return End->Get_Data_Ref();
	}


	bool FindBool(T key)
	{
		Node<T>* current;
		current=Head;

		while(current!=NULL)
		{

			if(current->Get_Data()==key){return true;}
			current=current->Get_Next();

		}
		return false;
	}


	T* FindObject(T key)
	{

		Node<T>* current;
		current=Head;

		while(current!=NULL)
		{

			if(current->Get_Data_Ref()==key){return &current->Get_Data_Ref();}
			current=current->Get_Next();

		}
		return NULL;

	}


	unsigned int Get_Size()
	{
		return size;
	}
	~List()
	{
		Node<T>* current=Head,*next;

		while(current!=NULL)
		{
			next=current->Get_Next();

			delete current;
			current=NULL;
			current=next;
		}
		Head=NULL;
		End=NULL;

	}
};

#endif /* LIST_H_ */
