#include "stdafx.h"
#define BOOST_TEST_MODULE TestOfStringList
#include "../CStringList/StringList.h"

#include <boost\test\included\unit_test.hpp>

using namespace std;

struct StringListFixture
{
	CStringList stringList;
};

BOOST_FIXTURE_TEST_SUITE(TestOfStringList, StringListFixture)

void AddNewStringAndCheckChain(CStringList& stringList, const string& newString)
{
	stringList.AddString(newString);
	auto node = stringList.GetFirstNode();
	while (node.get())
	{
		BOOST_CHECK(!node->m_string.empty());
		node = node->m_next.lock();
	}

	node = stringList.GetLastNode();
	while (node.get())
	{
		BOOST_CHECK(!node->m_string.empty());
		node = node->m_prev;
	}
}

BOOST_AUTO_TEST_CASE(testAddStringToList)
{
	AddNewStringAndCheckChain(stringList, "cat");
	AddNewStringAndCheckChain(stringList, "dog");
	AddNewStringAndCheckChain(stringList, "catdog");
	AddNewStringAndCheckChain(stringList, "cow");
}

void InsertNewString(CStringList& stringList, const string& newString, size_t index, const string& beforeString, const string& afterString)
{
	NodePtr node;

	if (index > stringList.GetSize() - 1)
	{
		node = stringList.GetLastNode();
	}
	else
	{
		node = stringList.NodeAtIndex(index);
	}
	
	stringList.Insert(newString, index);
	auto newNode = stringList.NodeAtIndex(index);

	BOOST_CHECK_EQUAL(newNode->m_string, newString);

	if (index > 0)
	{
		auto beforNode = stringList.NodeAtIndex(index - 1);
		BOOST_CHECK(beforNode->m_next.lock().get() == newNode.get());
		BOOST_CHECK_EQUAL(beforNode->m_string, beforeString);
	}

	size_t afterIndex = index + 1;
	if ((afterIndex > 0) && (afterIndex < stringList.GetSize()))
	{
		auto afterNode = stringList.NodeAtIndex(afterIndex);
		BOOST_CHECK(afterNode->m_prev.get() == newNode.get());
		BOOST_CHECK_EQUAL(afterNode->m_string, afterString);
	}
}

BOOST_AUTO_TEST_CASE(testInsertNewStringToList)
{
	AddNewStringAndCheckChain(stringList, "cat");
	AddNewStringAndCheckChain(stringList, "dog");
	AddNewStringAndCheckChain(stringList, "catdog");
	AddNewStringAndCheckChain(stringList, "cow");

	InsertNewString(stringList, "horse1", 0, "", "cat");
	InsertNewString(stringList, "horse2", 1, "horse1", "cat");
	InsertNewString(stringList, "horse3", 2, "horse2", "cat");
	InsertNewString(stringList, "horse4", 3, "horse3", "cat");
	InsertNewString(stringList, "horse5", 4, "horse4", "cat");

	AddNewStringAndCheckChain(stringList, "horse6");
}

BOOST_AUTO_TEST_CASE(testInsertNewStringToEmptyList)
{
	InsertNewString(stringList, "horse1", 0, "", "");
	InsertNewString(stringList, "horse2", 1, "horse1", "");
	InsertNewString(stringList, "horse3", 2, "horse2", "");
	InsertNewString(stringList, "horse4", 3, "horse3", "");
	InsertNewString(stringList, "horse5", 4, "horse4", "");

	AddNewStringAndCheckChain(stringList, "horse6");
}

BOOST_AUTO_TEST_CASE(testDeleteFirstNode)
{
	AddNewStringAndCheckChain(stringList, "cat");
	AddNewStringAndCheckChain(stringList, "dog");
	AddNewStringAndCheckChain(stringList, "catdog");
	AddNewStringAndCheckChain(stringList, "cow");

	auto node = stringList.NodeAtIndex(0);

	stringList.Delete(0);

	BOOST_CHECK(stringList.GetSize() == 3);
	BOOST_CHECK(stringList.NodeAtIndex(0)->m_string == "dog");
}

BOOST_AUTO_TEST_CASE(testDeleteCenterNode)
{
	AddNewStringAndCheckChain(stringList, "cat");
	AddNewStringAndCheckChain(stringList, "dog");
	AddNewStringAndCheckChain(stringList, "catdog");
	AddNewStringAndCheckChain(stringList, "cow");

	auto node = stringList.NodeAtIndex(0);

	stringList.Delete(2);

	BOOST_CHECK(stringList.GetSize() == 3);
	BOOST_CHECK(stringList.NodeAtIndex(2)->m_string == "cow");
}

BOOST_AUTO_TEST_CASE(testDeleteLastNode)
{
	AddNewStringAndCheckChain(stringList, "cat");
	AddNewStringAndCheckChain(stringList, "dog");
	AddNewStringAndCheckChain(stringList, "catdog");
	AddNewStringAndCheckChain(stringList, "cow");

	auto node = stringList.NodeAtIndex(0);

	stringList.Delete(3);

	BOOST_CHECK(stringList.GetSize() == 3);
	BOOST_CHECK(stringList.NodeAtIndex(2)->m_string == "catdog");

	stringList.Delete(4);
}

void Move(CStringList& stringList, size_t fromPos, size_t toPos, const string& prevNodeString, const string& nextNodeString)
{
	stringList.MoveString(fromPos, toPos);

	auto node = stringList.NodeAtIndex(toPos);

	if (toPos >= stringList.GetSize())
	{
		toPos = stringList.GetSize() - 1;
	}

	if (toPos > 0)
	{
		auto beforNode = stringList.NodeAtIndex(toPos - 1);
		if (node)
		{
			BOOST_CHECK(beforNode->m_next.lock().get() == node.get());
		}

		if (beforNode)
		{
			BOOST_CHECK_EQUAL(beforNode->m_string, prevNodeString);
		}
	}

	size_t afterIndex = toPos + 1;
	if ((afterIndex > 0) && (afterIndex < stringList.GetSize()))
	{
		auto afterNode = stringList.NodeAtIndex(afterIndex);
		BOOST_CHECK(afterNode->m_prev.get() == node.get());
		BOOST_CHECK_EQUAL(afterNode->m_string, nextNodeString);
	}
}

BOOST_AUTO_TEST_CASE(testMoveNode)
{
	AddNewStringAndCheckChain(stringList, "cat");
	AddNewStringAndCheckChain(stringList, "dog");
	AddNewStringAndCheckChain(stringList, "catdog");
	AddNewStringAndCheckChain(stringList, "cow");

	Move(stringList, 0, 1, "dog", "catdog");
	Move(stringList, 1, 2, "catdog", "cow");
	Move(stringList, 2, 3, "cow", "");
	Move(stringList, 3, 4, "cow", "");
}

BOOST_AUTO_TEST_CASE(testMoveEmptyNode)
{
	Move(stringList, 0, 1, "dog", "catdog");
}

BOOST_AUTO_TEST_SUITE_END()