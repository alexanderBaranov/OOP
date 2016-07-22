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
	}

	CStringListIterator operator++()
	{
		NodePtr nextNode = m_node->m_next.lock();
		assert(m_node);
		m_node = nextNode;

		return m_node;
	}

	CStringListIterator operator++(int)
	{
		CStringListIterator temp(*this);
		++*this;
		return temp;
	}

	CStringListIterator operator--()
	{
		assert(m_node || m_node->m_prev);
		m_node = m_node->m_prev;

		return m_node;
	}

	CStringListIterator operator--(int)
	{
		CStringListIterator temp(*this);
		--*this;
		return temp;
	}

	reference operator*() const
	{
		assert(m_node);
		return m_node->m_string;
	}

	pointer operator->() const
	{
		assert(m_node);
		return &m_node->m_string;
	}

	bool operator==(const CStringListIterator& other) const
	{
		return m_node == other.m_node;
	}

	bool operator!=(const CStringListIterator& other) const
	{
		return m_node != other.m_node;
	}

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

	CStringList(const CStringList& otherList);
	CStringList(CStringList&& otherList) _NOEXCEPT;

	void AddString(const std::string& newString);
	void Insert(const list_iterator & it, const std::string& newString);
	void Delete(const list_iterator & it) _NOEXCEPT;

	size_t GetSize() const _NOEXCEPT;

	list_iterator begin() const _NOEXCEPT;
	const_list_iterator cbegin() const _NOEXCEPT;
	
	list_iterator end() const _NOEXCEPT;
	const_list_iterator cend() const _NOEXCEPT;

	CStringList& operator =(const CStringList &otherList);
	CStringList& operator =(CStringList &&otherList) _NOEXCEPT;

	void Clear() _NOEXCEPT;

private:
	void AddNode(const NodePtr& node);

	NodePtr m_head, m_tail;
	size_t m_size;
};

