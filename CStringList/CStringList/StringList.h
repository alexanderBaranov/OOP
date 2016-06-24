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
private:
	friend class CStringList;
	friend class CStringListIterator;

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
	void Insert(CStringListIterator& iterator, const std::string& newString);
	void Delete(CStringListIterator& iterator);

	//const NodePtr GetFirstNode() const;
	//const NodePtr GetLastNode() const;

	size_t GetSize() const;

	CStringListIterator begin() const;
	//const CStringListIterator begin();

	CStringListIterator end() const;
	//const CStringListIterator end();

private:
	void RemoveNode(NodePtr& node);
	void PasteNode(CStringListIterator& iterator, NodePtr& newNode);
	void AddNode(NodePtr& node);
	size_t GetIndexForIterator(CStringListIterator& iterator) const;

	NodePtr m_head, m_tail, m_emptyNode;;
};

class CStringListIterator
{
	friend class CStringList;

public:
	CStringListIterator(NodePtr node);

	void operator++();
	void operator++(int);

	void operator--();
	void operator--(int);

	std::string& operator*() const;
	std::string* operator->() const;

	bool operator==(CStringListIterator& node);
	bool operator!=(CStringListIterator& node);

	//CStringListIterator operator + (size_t pos) const;
	//CStringListIterator operator - (size_t pos) const ;

	bool operator!() const;
private:
	NodePtr m_node;
};

