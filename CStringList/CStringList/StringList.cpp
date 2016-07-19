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

void CStringList::AddString( const std::string& newString )
{
	NodePtr node = make_shared<Node>(Node(newString));

	AddNode(node);
}

void CStringList::AddNode(const NodePtr& node )
{
	if (m_head)
	{
		node->m_prev = m_tail->m_prev;
		m_tail->m_prev->m_next = node;
		node->m_next = m_tail;
		m_tail->m_prev = node;
	}
	else
	{
		
		m_head->m_next = m_tail->m_prev = node;
		node->m_prev = m_head;
		node->m_next = m_tail;
	}
}

void CStringList::Insert(list_iterator it, const std::string& newString)
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
	}
}

size_t CStringList::GetSize() const
{
	size_t size = 0;

	auto node = m_head->m_next.lock();
	while (node && (node != m_tail))
	{
		size++;
		node = node->m_next.lock();
	}

	return size;
}

void CStringList::Delete(list_iterator it)
{
	if (!it)
	{
		return;
	}

	RemoveNode(it.m_node);
}

void CStringList::RemoveNode( NodePtr& node )
{
	if (!node)
	{
		return;
	}

	NodePtr nextNode = node->m_next.lock();
	NodePtr prevNode = node->m_prev;

	bool averageNode = (node->m_prev != m_head) && (nextNode != m_tail);
	if( averageNode )
	{
		prevNode->m_next = nextNode;
		nextNode->m_prev = prevNode;
	}
	else if (node->m_prev == m_head)
	{
		m_head->m_next = nextNode;
		nextNode->m_prev = m_head;
	}
	else if (nextNode == m_tail)
	{
		m_tail->m_prev = prevNode;
		prevNode->m_next = m_tail;
	}
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
