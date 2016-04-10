#include "stdafx.h"
#define BOOST_TEST_MODULE TestOfStringList
#include "../CStringList/StringList.h"
#include <stdlib.h>
#include <boost\test\included\unit_test.hpp>

using namespace std;

struct StringListFixture
{
	CStringList stringList;
};

BOOST_FIXTURE_TEST_SUITE(TestOfStringList, StringListFixture)

void CheckContentOfStringList(const CStringList& stringList, const vector<string> & list)
{
	auto node = stringList.GetFirstNode();
	for (const auto& str : list)
	{
		BOOST_CHECK(node);
		BOOST_CHECK_EQUAL(node->m_string, str);

		node = node->m_next.lock();
	}
}

void AddToStringListFromArray(CStringList& stringList, const vector<string>& list)
{
	auto node = stringList.GetFirstNode();
	for (const auto& str : list)
	{
		stringList.AddString(str);
	}
}

BOOST_AUTO_TEST_CASE(testAddStringToList)
{
	vector<string> list = { "cat", "dog", "catdog", "cow"};

	AddToStringListFromArray(stringList, list);
	CheckContentOfStringList(stringList, list);
}

BOOST_AUTO_TEST_CASE(testInsertNewStringToList)
{
	vector<string> list = { "cat", "dog", "catdog", "cow" };

	AddToStringListFromArray(stringList, list);
	CheckContentOfStringList(stringList, list);

	auto InsertProperty = [&](const string& value, size_t pos){
		stringList.Insert(value, pos);

		auto it = (pos < list.size()) ? list.begin() + pos : list.end();
		list.insert(it, value);
		CheckContentOfStringList(stringList, list);
	};

	InsertProperty("horse1", 0);

	InsertProperty("horse2", 1);
	InsertProperty("horse3", 2);
	InsertProperty("horse4", 3);
	InsertProperty("horse5", 4);
	InsertProperty("horse6", 20);
}

BOOST_AUTO_TEST_CASE(testInsertNewStringToEmptyList)
{
	stringList.Insert("horse1", 0);

	vector<string> list = { "horse1" };
	CheckContentOfStringList(stringList, list);
}

BOOST_AUTO_TEST_CASE(testDeleteFirstNode)
{
	vector<string> list = { "cat", "dog", "catdog", "cow" };

	AddToStringListFromArray(stringList, list);

	stringList.Delete(0);
	list.erase(list.begin());

	CheckContentOfStringList(stringList, list);
}

BOOST_AUTO_TEST_CASE(testDeleteCenterNode)
{
	vector<string> list = { "cat", "dog", "catdog", "cow" };

	AddToStringListFromArray(stringList, list);

	stringList.Delete(2);
	list.erase(list.begin() + 2);

	CheckContentOfStringList(stringList, list);
}

BOOST_AUTO_TEST_CASE(testDeleteLastNode)
{
	vector<string> list = { "cat", "dog", "catdog", "cow" };

	AddToStringListFromArray(stringList, list);

	stringList.Delete(3);
	list.erase(list.begin() + 3);

	CheckContentOfStringList(stringList, list);

	stringList.Delete(30);

	CheckContentOfStringList(stringList, list);
}

BOOST_AUTO_TEST_CASE(testMoveNode)
{
	vector<string> list = { "cat", "dog", "catdog", "cow" };

	AddToStringListFromArray(stringList, list);

	auto MoveProperty = [&](size_t fromPos, size_t toPos){
		stringList.MoveStringFromPosToNewPos(fromPos, toPos);

		if (fromPos < list.size())
		{
			string strOfList = list[fromPos];
			list.erase(list.begin() + fromPos);
			auto it = (toPos < list.size()) ? list.begin() + toPos : list.end();
			list.insert(it, strOfList);
		}

		CheckContentOfStringList(stringList, list);
	};

	MoveProperty(0, 1);

	MoveProperty(1, 2);
	MoveProperty(2, 3);
	MoveProperty(3, 4);
}

BOOST_AUTO_TEST_CASE(testMoveEmptyNode)
{
	stringList.MoveStringFromPosToNewPos(0, 1);
}

BOOST_AUTO_TEST_SUITE_END()