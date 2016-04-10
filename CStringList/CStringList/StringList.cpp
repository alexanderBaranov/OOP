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
		m_tail->m_index = m_tail->m_prev->m_index + 1;
	}
	else
	{
		m_head = m_tail = node;
		m_tail->m_index = 0;
	}
}

void CStringList::Insert( const std::string& newString, size_t posOfPlacing )
{
	NodePtr newNode = make_shared<Node>();
	newNode->m_string = newString;

	PasteNode(newNode, posOfPlacing);
}

void CStringList::PasteNode( NodePtr& newNode, size_t newPos )
{
	if (newNode->m_prev)
	{
		newNode->m_prev.reset();
	}
	
	if (newNode->m_next.lock())
	{
		newNode->m_next.reset();
	}
	
	if (!m_head.get()
		|| (newPos > m_tail->m_index))
	{
		AddNode(newNode);
	}
	else
	{
		auto node = GetNodeByIndex(newPos);

		if (newPos > 0)
		{
			newNode->m_prev = node->m_prev;
			node->m_prev->m_next = newNode;
		}
		else
		{
			m_head = newNode;
		}

		newNode->m_next = node;
		node->m_prev = newNode;

		RecalculateIndexes();
	}
}

size_t CStringList::GetSize() const
{
	return m_tail ? m_tail->m_index + 1 : 0;
}

void CStringList::RecalculateIndexes()
{
	auto node = m_head;
	size_t counter = 0;
	node->m_index = counter;
	while (node)
	{
		if (node->m_prev)
		{
			node->m_index = counter;
		}
		node = node->m_next.lock();

		counter++;
	}
}

const NodePtr CStringList::NodeAtIndex( size_t index ) const
{
	return GetNodeByIndex(index);
}

NodePtr CStringList::GetNodeByIndex( size_t index ) const
{
	if (index >= GetSize())
	{
		return nullptr;
	}

	auto node = m_head;
	while (node && (node->m_index != index))
	{
		node = node->m_next.lock();
	}

	return node;
}

void CStringList::Delete( size_t index )
{
	if (index >= GetSize())
	{
		return;
	}

	NodePtr node = GetNodeByIndex(index);

	RemoveNode(node);

	node.reset();

	RecalculateIndexes();
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

void CStringList::MoveStringFromPosToNewPos( size_t index, size_t newPos )
{
	if (index > (GetSize() - 1))
	{
		return;
	}

	NodePtr node = GetNodeByIndex(index);

	if (node)
	{
		RemoveNode(node);

		PasteNode(node, newPos + 1);

		RecalculateIndexes();
	}
}

void CStringList::ShowList( std::ostream& output ) const
{
	auto node = m_head;
	while (node)
	{
		output << node->m_string << endl;
		node = node->m_next.lock();
	}
}

const NodePtr CStringList::GetFirstNode() const
{
	return m_head;
}

const NodePtr CStringList::GetLastNode() const
{
	return m_tail;
}
