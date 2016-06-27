#include "stdafx.h"
#include "StringList.h"

using namespace std;

CStringList::CStringList()
{
	m_emptyNode = make_shared<Node>();
}

CStringList::~CStringList()
{
	while (m_head)
	{
		NodePtr *tail = &m_head->m_next.lock();
		m_head->m_prev.reset();
		m_head.reset();
		m_head = *tail;
	}
}

void CStringList::AddString( const std::string& newString )
{
	NodePtr node = make_shared<Node>();
	node->m_string = newString;

	AddNode(node);
}

void CStringList::AddNode( NodePtr& node )
{
	if (m_head)
	{
		node->m_prev = m_tail;
		m_tail->m_next = node;
		m_tail = node;
	}
	else
	{
		m_head = m_tail = node;
	}

	m_tail->m_next = m_emptyNode;
	m_emptyNode->m_prev = m_tail;
}

void CStringList::Insert(CStringListIterator& iterator, const std::string& newString)
{
	NodePtr newNode = make_shared<Node>();
	newNode->m_string = newString;

	PasteNode(iterator, newNode);
}

void CStringList::PasteNode(CStringListIterator& iterator, NodePtr& newNode)
{
	if (newNode->m_prev)
	{
		newNode->m_prev.reset();
	}
	
	if (newNode->m_next.lock())
	{
		newNode->m_next.reset();
	}
	
	if (!m_head.get() || !iterator.m_node->m_next.lock())
	{
		AddNode(newNode);
	}
	else
	{
		if (iterator.m_node->m_next.lock() && iterator.m_node->m_prev)
		{
			newNode->m_prev = iterator.m_node->m_prev;
			iterator.m_node->m_prev->m_next = newNode;
		}
		else if (iterator.m_node->m_next.lock())
		{
			m_head = newNode;
		}

		newNode->m_next = iterator.m_node;
		iterator.m_node->m_prev = newNode;
	}
}

size_t CStringList::GetSize() const
{
	size_t size = 0;

	auto node = m_head;
	while (node && (node != m_emptyNode))
	{
		size++;
		node = node->m_next.lock();
	}

	return size;
}

void CStringList::Delete(CStringListIterator& iterator)
{
	if (!iterator)
	{
		return;
	}

	RemoveNode(iterator.m_node);

	iterator.m_node.reset();
}

void CStringList::RemoveNode( NodePtr& node )
{
	if (!node)
	{
		return;
	}

	if (node->m_prev && node->m_next.lock())
	{
		node->m_prev->m_next = node->m_next.lock();
		node->m_next.lock()->m_prev = node->m_prev;
	}
	else if (!node->m_prev)
	{
		m_head = node->m_next.lock();
		m_head->m_prev.reset();
	}
	else if (!node->m_next.lock())
	{
		m_tail = node->m_prev;
		m_tail->m_next.reset();
	}
}

size_t CStringList::GetIndexForIterator(CStringListIterator& iterator) const 
{
	if (!iterator)
	{
		return 0;
	}

	size_t pos = 0;
	auto node = m_head;
	while (node)
	{
		if (node == iterator.m_node)
		{
			break;
		}

		node = node->m_next.lock();
		pos++;
	}

	return pos;
}

CStringListIterator CStringList::begin() const
{
	return CStringListIterator(m_head);
}

CStringListIterator CStringList::end() const
{
	return CStringListIterator(m_tail->m_next.lock());
}

CStringListIterator::CStringListIterator(NodePtr node)
:m_node(node)
{
}

void CStringListIterator::operator++()
{
	m_node = m_node->m_next.lock();
}

void CStringListIterator::operator++(int)
{
	++*this;
}

void CStringListIterator::operator--()
{
	m_node = m_node->m_prev;
}

void CStringListIterator::operator--(int)
{
	--*this;
}

string& CStringListIterator::operator*() const
{
	return m_node->m_string;
}

std::string* CStringListIterator::operator->() const
{
	return &m_node->m_string;
}

bool CStringListIterator::operator!() const
{
	return m_node ? false : true;
}

bool CStringListIterator::operator == (CStringListIterator& node)
{
	return m_node == node.m_node;
}

bool CStringListIterator::operator != (CStringListIterator& node)
{
	return m_node != node.m_node;
}