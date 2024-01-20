/*
Orion Mulgrew
Custom Templated Dynamic Array
12/20/2023
*/

#ifndef TEMPLDNYARR_H
#define TEMPLDYNARR_H

#include <iostream>

template<typename T>
struct Node
{
public:
	T value;
	Node* next;

	Node() = delete;

	Node(const T &val, Node*& ptr) : value(val), next(ptr) {}
	Node(const T &val, std::nullptr_t nl_ptr) : value(val), next(nl_ptr) {}
	Node(const T &val) : Node(val, nullptr) {}
};

template<typename T>
class TemplDynArr
{
private:
	Node<T>* m_first;

	Node<T>* node_at(int indx) const
	{
		Node<T>* current = m_first;

		for (int x = 0; x < indx; x++)
		{
			current = current->next;
			// std::cout << current->m_value << "v" << std::endl;
		}

		return current;
	}

public:
	TemplDynArr() : m_first(nullptr) {}

	~TemplDynArr()
	{
		for (int x = length() - 2; x > -1; x--)
		{
			delete node_at(x)->next;
		}
		delete m_first;
	}

	int length() const
	{
		if (m_first == nullptr) { return 0; }
		int len = 1;
		Node<T>* n = m_first;
		while (n->next != nullptr)
		{
			len++;
			n = n->next;
		}
		return len;
	}

	int at(int indx) const
	{
		return (*this)[indx];
	}

	void set(int indx, T value)
	{
		(*this)[indx] = value;
	}

	void add(T v)
	{
		if (m_first != nullptr)
		{
			Node<T>* last = node_at(length() - 1);
			Node<T>* next = new Node<T>(v);
			last->next = next;
		}
		else
		{
			m_first = new Node<T>(v);
		}
	}

	TemplDynArr<T> operator+(TemplDynArr<T>& other)
	{
		TemplDynArr<T> n_dyn;
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

	void operator+=(TemplDynArr<T>& other)
	{
		for (int x = 0; x < other.length(); x++)
		{
			this->add(other.at(x));
		}
	}

	void append_array(const T* arr, int len)
	{
		for (int x = 0; x < len; x++)
		{
			add(*(arr + x));
		}
	}

	T& operator[](int indx) const
	{
		return node_at(indx)->value;
	}

	Node<T> getNodeAt(T& indx) const
	{
		return *node_at(indx);
	}

	void remove(int indx)
	{
		if (indx == 0)
		{
			if (m_first->next != nullptr)
			{
				Node<T>* old = m_first;
				m_first = m_first->next;
				delete old;
			}
			else
				m_first = nullptr;
			return;
		}

		Node<T>* before = node_at(indx - 1);
		Node<T>* poppin = node_at(indx);
		before->next = poppin->next;
		delete poppin;
	}

	void insert(int indx, T v)
	{
		if (indx == 0)
		{
			Node<T>* old_first = m_first;
			m_first = new Node<T>(v, old_first);
			return;
		}
		Node<T>* at = node_at(indx);
		Node<T>* before = node_at(indx - 1);
		Node<T>* insert = new Node<T>(v, at);
		before->next = insert;
	}

	void printDynArr(bool do_endl = 0) const
	{
		if (length() == 0) { std::cout << "[ ]"; return; }
		std::cout << "[ ";
		Node<T>* current = m_first;
		while (current != 0)
		{
			std::cout << current->value << ", ";
			current = current->next;
		}
		std::cout << at(length() - 1) << " ]";
		if (do_endl) { std::cout << std::endl; }
	}
};

#endif