#include <iostream>
#include <string>
#include <sstream>
#pragma once
using namespace std;
enum class priority {//три приоритета
	low,
	medium,
	high
};

class List
{
public:
	List();
	~List();
	List(const List& p);
	List(List&& p);
	List& operator =(const List& p);
	List& operator =(List&& p);
	void pop_front();
	void push_back(int data);
	void push_back(int data, priority pr);
	void clear();
	int GetSize()const;
	int GetLowSize()const;
	int GetMediumSize()const;
	int GetHighSize()const;
	bool Is_Empty()const;
	pair<int, priority> GetHead()const;
	friend ostream& operator <<(ostream& s, const List& p);
	struct Node//элемент очереди
	{
		Node* pNext;
		int data;
		priority pr;
		Node(int data = int(), priority pr = priority(), Node* pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
			this->pr = pr;
		}
	};
private:
	int Size;
	int Low_size;
	int Medium_size;
	int High_size;
	Node* head;
	Node* rear_high;
	Node* rear_medium;
	Node* rear_low;
};
