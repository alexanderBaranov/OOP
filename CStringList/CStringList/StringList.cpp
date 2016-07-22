#include "stdafx.h"
#include "StringList.h"

using namespace std;

Node::Node(const std::string& newString)
:m_string(newString)
{
}

CStringList::CStringList()
{
	m_head = make_shared<Node>();
	m_tail = make_shared<Node>();
	m_head->m_next = m_tail;
	m_tail->m_prev = m_head;

	m_size = 0;
}

CStringList::~CStringList()
{
	while (m_head)
	{
		NodePtr tail = m_head->m_next.lock();
		m_head->m_prev.reset();
		m_head.reset();
		m_head = tail;
	}
}

CStringList::CStringList(const CStringList& otherList)
	:CStringList()
{
	*this = otherList;
}

CStringList::CStringList(CStringList&& otherList)
	:CStringList()
{
	*this = move(otherList);
}

void CStringList::AddString( const std::string& newString )
{
	NodePtr node = make_shared<Node>(Node(newString));

	AddNode(node);
}

void CStringList::AddNode(const NodePtr& node )
{
	node->m_prev = m_tail->m_prev;
	m_tail->m_prev->m_next = node;
	node->m_next = m_tail;
	m_tail->m_prev = node;

	m_size++;
}

void CStringList::Insert(const list_iterator & it, const std::string& newString)
{
	NodePtr newNode = make_shared<Node>();
	newNode->m_string = newString;

	NodePtr nextNode = it.m_node->m_next.lock();

	bool listEmpty = !m_head.get() || !nextNode;
	if (listEmpty)
	{
		AddNode(newNode);
	}
	else
	{
		NodePtr prevNode = it.m_node->m_prev;

		bool averageNode = (nextNode != m_head) && (prevNode != m_tail);
		if( averageNode )
		{
			newNode->m_prev = prevNode;
			prevNode->m_next = newNode;
		}
		else if (nextNode != m_tail)
		{
			m_head->m_next = newNode;
			newNode->m_prev = m_head;
		}

		newNode->m_next = it.m_node;
		it.m_node->m_prev = newNode;

		m_size++;
	}
}

size_t CStringList::GetSize() const
{
	return m_size;
}

void CStringList::Delete(const list_iterator & it)
{
	bool shouldBeRemoveEndIterator = (it.m_node == m_tail);
	bool shouldBeRemoveBeginIterator = (it.m_node == m_head);
	if (!it.m_node || shouldBeRemoveEndIterator || shouldBeRemoveBeginIterator)
	{
		return;
	}

	if (!it.m_node)
	{
		return;
	}

	NodePtr nextNode = it.m_node->m_next.lock();
	NodePtr prevNode = it.m_node->m_prev;

	bool middleNode = (prevNode != m_head) && (nextNode != m_tail);
	if (middleNode)
	{
		prevNode->m_next = nextNode;
		nextNode->m_prev = prevNode;
	}
	else if (prevNode == m_head)
	{
		m_head->m_next = nextNode;
		nextNode->m_prev = m_head;
	}
	else if (nextNode == m_tail)
	{
		m_tail->m_prev = prevNode;
		prevNode->m_next = m_tail;
	}

	m_size--;
}

CStringList& CStringList::operator = (const CStringList &otherList)
{
	if (this == &otherList)
	{
		return *this;
	}

	CStringList tempList;
	for (const auto str : otherList)
	{
		tempList.AddString(str);
	}

	*this = move(tempList);

	return *this;
}

CStringList& CStringList::operator = (CStringList &&otherList)
{
	if (this == &otherList)
	{
		return *this;
	}

	Clear();

	auto otherNextElem = otherList.m_head->m_next.lock();
	auto otherPrevElem = otherList.m_tail->m_prev;

	otherNextElem->m_prev = m_head;
	m_head->m_next = otherNextElem;
	
	otherPrevElem->m_next = m_tail;
	m_tail->m_prev = otherPrevElem;

	otherList.m_head->m_next = otherList.m_tail;
	otherList.m_tail->m_prev = otherList.m_head;

	m_size = otherList.m_size;
	otherList.m_size = 0;

	return *this;
}

void CStringList::Clear()
{
	if (!GetSize())
	{
		return;
	}

	auto currentNode = m_head->m_next.lock();
	m_head->m_next.reset();

	while (currentNode != m_tail)
	{
		NodePtr nextReadNode = currentNode->m_next.lock();
		currentNode->m_prev.reset();
		currentNode.reset();
		currentNode = nextReadNode;
	}

	m_tail->m_prev.reset();

	m_head->m_next = m_tail;
	m_tail->m_prev = m_head;

	m_size = 0;
}

list_iterator CStringList::begin() const
{
	return list_iterator(m_head->m_next.lock());
}

const_list_iterator CStringList::cbegin() const
{
	return const_list_iterator(m_head->m_next.lock());
}

list_iterator CStringList::end() const
{
	return list_iterator(m_tail);
}

const_list_iterator CStringList::cend() const
{
	return const_list_iterator(m_tail);
}
