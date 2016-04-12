# pragma once
#include <memory>
#include <string>
#include <iostream>

class CStringListIterator;
class Node;

typedef std::shared_ptr<Node> NodePtr;
typedef std::weak_ptr<Node> WeakNodePtr;

class Node
{
public:
	NodePtr m_prev; 
	WeakNodePtr m_next;
	std::string m_string;
};

class CStringList
{
public:

	void AddString(const std::string& newString);
	void Insert(CStringListIterator& iterator, const std::string& newString);
	void Delete(CStringListIterator& iterator);

	void MoveStringFromPosToNewPos(CStringListIterator& iterator, size_t newPos);

	NodePtr GetFirstNode() const;
	NodePtr GetLastNode() const;

	size_t GetSize() const;

	CStringListIterator Begin() const;
	CStringListIterator End() const;

private:
	void RemoveNode(NodePtr& node);
	void PasteNode(CStringListIterator& iterator, NodePtr& newNode);
	void AddNode(NodePtr& node);
	size_t GetIndexForIterator(CStringListIterator& iterator) const;

	NodePtr m_head, m_tail;
};

class CStringListIterator
{
public:
	CStringListIterator(NodePtr node);

	CStringListIterator& operator++();
	CStringListIterator& operator--();

	NodePtr operator*() const;
	Node* operator->() const;

	CStringListIterator operator + (size_t pos) const;
	CStringListIterator operator - (size_t pos) const ;

	bool operator!() const;

private:
	NodePtr m_node;
};
