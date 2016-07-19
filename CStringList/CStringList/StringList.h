# pragma once
#include <memory>
#include <string>
#include <iostream>
#include <assert.h>
#include <iterator>

class Node;
class CStringList;
template<typename T> class CStringListIterator;

typedef std::shared_ptr<Node> NodePtr;
typedef std::weak_ptr<Node> WeakNodePtr;

typedef CStringListIterator<std::string> list_iterator;
typedef CStringListIterator<const std::string> const_list_iterator;

template<typename T>
class CStringListIterator:public std::iterator<std::input_iterator_tag, T>
{
	friend class CStringList;

public:
	CStringListIterator(NodePtr node)
		:m_node(node)
	{
	};

	CStringListIterator operator++()
	{
		assert(m_node);
		m_node = m_node->m_next.lock();

		return m_node;
	};

	CStringListIterator operator++(int)
	{
		CStringListIterator temp(*this);
		++*this;
		return temp;
	};

	CStringListIterator operator--()
	{
		assert(m_node);
		m_node = m_node->m_prev;

		return m_node;
	};

	CStringListIterator operator--(int)
	{
		CStringListIterator temp(*this);
		--*this;
		return temp;
	};

	reference& operator*() const
	{
		assert(m_node);
		return m_node->m_string;
	};

	pointer* operator->() const
	{
		assert(m_node);
		return &m_node->m_string;
	};

	bool operator==(CStringListIterator& node)
	{
		return m_node == node.m_node;
	};

	bool operator!=(CStringListIterator& node)
	{
		return m_node != node.m_node;
	};

	bool operator!() const
	{
		return m_node ? false : true;
	};

private:
	NodePtr m_node;
};

class Node
{
public:
	Node() = default;
	Node(const std::string& newString);

private:
	friend class CStringList;
	template<typename T> friend class CStringListIterator;

	NodePtr m_prev; 
	WeakNodePtr m_next;
	std::string m_string;
};

class CStringList
{
public:
	CStringList();
	~CStringList();

	void AddString(const std::string& newString);
	void Insert(list_iterator it, const std::string& newString);
	void Delete(list_iterator it);

	size_t GetSize() const;

	list_iterator begin() const;
	const_list_iterator cbegin() const;
	
	list_iterator end() const;
	const_list_iterator cend() const;

private:
	void RemoveNode(NodePtr& node);
	void AddNode(const NodePtr& node);
	size_t GetIndexForIterator(list_iterator& iterator) const;

	NodePtr m_head, m_tail, m_emptyNode;;
};

