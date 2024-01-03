/*
Orion Mulgrew
Custom Dynamic Array
12/20/2023
*/

#ifndef DNYARR_H
#define DYNARR_H

#include <iostream>

struct Node
{
public:
	int value;
	Node* next;

	Node() = delete;

	Node(const int &val, Node*& ptr)			: value(val), next(ptr) {}
	Node(const int &val, std::nullptr_t nl_ptr)	: value(val), next(nl_ptr) {}
	Node(const int &val)						: Node(val, nullptr) {}
};

class DynArr
{
private:
	Node* m_first;

	Node* node_at(int) const;

public:
	DynArr() : m_first(nullptr) {}

	~DynArr();

	int length() const;

	int at(int) const;

	void set(int, int);

	void add(int v);

	DynArr operator+(DynArr&);

	void operator+=(DynArr&);

	void append_array(const int*, int);

	int& operator[](int) const;

	Node getNodeAt(int&) const;

	void remove(int);

	void insert(int, int);

	void printDynArr(bool = false) const;
};

#endif