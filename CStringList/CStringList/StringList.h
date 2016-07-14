# pragma once
#include <memory>
#include <string>
#include <iostream>
#include <assert.h>
#include <iterator>

class Node;
class CStringList;

typedef std::shared_ptr<Node> NodePtr;
typedef std::weak_ptr<Node> WeakNodePtr;

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
	void Insert(CStringListIterator<std::string>& iterator, const std::string& newString);
	void Delete(CStringListIterator<std::string>& iterator);

	size_t GetSize() const;

	CStringListIterator<std::string> begin() const;
	CStringListIterator<const std::string> cbegin() const;
	
	CStringListIterator<std::string> end() const;
	CStringListIterator<const std::string> cend() const;

private:
	void RemoveNode(NodePtr& node);
	void PasteNode(CStringListIterator<std::string>& iterator, NodePtr& newNode);
	void AddNode(NodePtr& node);
	size_t GetIndexForIterator(CStringListIterator<std::string>& iterator) const;

	NodePtr m_head, m_tail, m_emptyNode;;
};

