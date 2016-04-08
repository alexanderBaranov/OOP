# pragma once
#include <memory>
#include <string>
#include <iostream>

class Node;
typedef std::shared_ptr<Node> NodePtr;
typedef std::weak_ptr<Node> WeakNodePtr;

class Node
{
public:
	NodePtr m_prev; 
	WeakNodePtr m_next;
	std::string m_string;
	size_t m_index;
};

class CStringList
{
public:
	void AddString(const std::string& newString);
	void Insert(const std::string& newString, size_t pos);
	void Delete(size_t index);

	void MoveString(size_t index, size_t newPos);
	void ShowList(std::ostream& output) const;
	
	const NodePtr GetFirstNode() const;
	const NodePtr GetLastNode() const;

	const NodePtr NodeAtIndex(size_t index) const;

	size_t GetSize() const;

private:
	NodePtr GetNodeByIndex(size_t index) const;
	void RecalculateIndexes();
	void RemoveNode(NodePtr& node);
	void PasteNode(NodePtr& newNode, size_t newPos);
	void AddNode(NodePtr& node);

	NodePtr m_head, m_tail;
};