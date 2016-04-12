#include "stdafx.h"
#include "StringList.h"

using namespace std;

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
	
	if (!m_head.get() || !iterator->m_next.lock())
	{
		AddNode(newNode);
	}
	else
	{
		if (iterator->m_next.lock() && iterator->m_prev)
		{
			newNode->m_prev = iterator->m_prev;
			iterator->m_prev->m_next = newNode;
		}
		else if(iterator->m_next.lock())
		{
			m_head = newNode;
		}

		newNode->m_next = *iterator;
		iterator->m_prev = newNode;
	}
}

size_t CStringList::GetSize() const
{
	size_t size = 0;

	auto node = m_head;
	while (node)
	{
		node = node->m_next.lock();
		size++;
	}

	return size;
}

void CStringList::Delete(CStringListIterator& iterator)
{
	if (!iterator)
	{
		return;
	}

	RemoveNode(*iterator);

	(*iterator).reset();
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

void CStringList::MoveStringFromPosToNewPos(CStringListIterator& iterator, size_t newPos)
{
	CStringListIterator posIterator(m_head);
	posIterator = posIterator + newPos;

	size_t curPos = GetIndexForIterator(iterator);
	newPos = GetIndexForIterator(posIterator);

	if (*iterator == *posIterator)
	{
		return;
	}

	if (iterator->m_prev && iterator->m_next.lock())
	{
		iterator->m_prev->m_next = iterator->m_next;
		iterator->m_next.lock()->m_prev = iterator->m_prev;
	}
	else if (*iterator == m_head)
	{
		m_head = iterator->m_next.lock();
		m_head->m_prev.reset();
	}
	else if (*iterator == m_tail)
	{
		iterator->m_prev->m_next.reset();
		m_tail = iterator->m_prev;
	}

	if (curPos < newPos)
	{
		iterator->m_next = posIterator->m_next;

		if (iterator->m_next.lock())
		{
			iterator->m_next.lock()->m_prev = *iterator;
		}
		else
		{
			m_tail = *iterator;
		}

		iterator->m_prev = *posIterator;
		posIterator->m_next = *iterator;
	}
	else
	{
		if (*posIterator == m_head)
		{
			iterator->m_prev.reset();
			m_head = *iterator;
		}
		else
		{
			iterator->m_prev = posIterator->m_prev;
			iterator->m_prev->m_next = *iterator;
		}

		iterator->m_next = *posIterator;
		posIterator->m_prev = *iterator;
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
		if (node == *iterator)
		{
			break;
		}

		node = node->m_next.lock();
		pos++;
	}

	return pos;
}

NodePtr CStringList::GetFirstNode() const
{
	return m_head;
}

NodePtr CStringList::GetLastNode() const
{
	return m_tail;
}

CStringListIterator CStringList::Begin() const
{
	return CStringListIterator(m_head);
}

CStringListIterator CStringList::End() const
{
	return CStringListIterator(m_tail);
}


CStringListIterator::CStringListIterator(NodePtr node)
:m_node(node)
{
}

CStringListIterator& CStringListIterator::operator++()
{
	if (m_node && m_node->m_next.lock())
	{
		m_node = m_node->m_next.lock();
	}

	return *this;
}

CStringListIterator& CStringListIterator::operator--()
{
	if (m_node && m_node->m_prev)
	{
		m_node = m_node->m_prev;
	}

	return *this;
}

NodePtr CStringListIterator::operator*() const
{
	return m_node ? m_node : nullptr;
}

Node* CStringListIterator::operator->() const
{
	return m_node.get();
}

CStringListIterator CStringListIterator::operator + (size_t pos) const
{
	if (!m_node)
	{
		return nullptr;
	}

	NodePtr node = m_node;

	for (int i = 0; i != pos; ++i)
	{
		if (node->m_next.lock())
		{
			node = node->m_next.lock();
		}
		else
		{
			break;
		}
	}

	return CStringListIterator(node);
}

CStringListIterator CStringListIterator::operator - (size_t pos) const
{
	if (!m_node)
	{
		return nullptr;
	}

	NodePtr node = m_node;

	for (int i = 0; i != pos; ++i)
	{
		if (node->m_prev)
		{
			node = node->m_prev;
		}
		else
		{
			break;
		}
	}

	return CStringListIterator(node);
}

bool CStringListIterator::operator!() const
{
	return m_node ? false : true;
}
