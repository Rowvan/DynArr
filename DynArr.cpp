/*
Orion Mulgrew
Custom Dynamic Array
12/20/2023
*/

#include "DynArr.h"

// Private

Node* DynArr::node_at(int indx) const
{
	Node* current = m_first;

	for (int x = 0; x < indx; x++)
	{
		current = current->next;
		// std::cout << current->m_value << "v" << std::endl;
	}

	return current;
}

// Public

DynArr::~DynArr()
{
	for (int x = length() - 2; x > -1; x--)
	{
		delete node_at(x)->next;
	}
	delete m_first;
}

int DynArr::length() const
{
	if (m_first == nullptr) { return 0; }
	int len = 1;
	Node* n = m_first;
	while (n->next != nullptr)
	{
		len++;
		n = n->next;
	}
	return len;
}

int DynArr::at(int indx) const
{
	return (*this)[indx];
}

void DynArr::set(int indx, int value)
{
	(*this)[indx] = value;
}

void DynArr::add(int v)
{
	if (m_first != nullptr)
	{
		Node* last = node_at(length() - 1);
		Node* next = new Node(v);
		last->next = next;
	}
	else
	{
		m_first = new Node(v);
	}
}

DynArr DynArr::operator+(DynArr& other)
{
	DynArr n_dyn;
	for (int x = 0; x < this->length(); x++)
	{
		n_dyn.add(this->at(x));
	}

	for (int x = 0; x < other.length(); x++)
	{
		n_dyn.add(other.at(x));
	}
	return n_dyn;
}

void DynArr::operator+=(DynArr& other)
{
	for (int x = 0; x < other.length(); x++)
	{
		this->add(other.at(x));
	}
}

void DynArr::append_array(const int* arr, int len)
{
	for (int x = 0; x < len; x++)
	{
		add(*(arr + x));
	}
}

int& DynArr::operator[](int indx) const
{
	return node_at(indx)->value;
}

Node DynArr::getNodeAt(int& indx) const
{
	return *node_at(indx);
}

void DynArr::remove(int indx)
{
	if (indx == 0)
	{
		if (m_first->next != nullptr)
		{
			Node* old = m_first;
			m_first = m_first->next;
			delete old;
		}
		else
			m_first = nullptr;
		return;
	}

	Node* before = node_at(indx - 1);
	Node* poppin = node_at(indx);
	before->next = poppin->next;
	delete poppin;
}

void DynArr::insert(int indx, int v)
{
	if (indx == 0)
	{
		Node* old_first = m_first;
		m_first = new Node(v, old_first);
		return;
	}
	Node* at = node_at(indx);
	Node* before = node_at(indx - 1);
	Node* insert = new Node(v, at);
	before->next = insert;
}

void DynArr::printDynArr(bool do_endl) const
{
	if (length() == 0) { std::cout << "[ ]"; return; }
	std::cout << "[ ";
	for (int x = 0; x < length() - 1; x++)
	{
		std::cout << at(x) << ", ";
	}
	std::cout << at(length() - 1) << " ]";
	if (do_endl) { std::cout << std::endl; }
}