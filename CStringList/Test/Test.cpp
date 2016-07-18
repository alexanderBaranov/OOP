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
	BOOST_CHECK(list.size() == stringList.GetSize());
	auto node = stringList.begin();
	for (const auto& str : list)
	{
		BOOST_REQUIRE(node);
		BOOST_CHECK_EQUAL(*node, str);

		node++;
	}
}

void AddToStringListFromArray(CStringList& stringList, const vector<string>& list)
{
	for (const auto& str : list)
	{
		stringList.AddString(str);
	}
}

CStringListIterator<std::string> GetStringListIteratorFromPos(const CStringList& stringList, size_t pos)
{
	auto begIterator = stringList.begin();
	for (int i = 0; begIterator != stringList.end(); begIterator++)
	{
		if (i == pos)
		{
			break;
		}

		i++;
	}

	return begIterator;
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

	auto InsertProperty = [&](const string& value, size_t pos)
	{
		int position = 0;

		auto begIterator = GetStringListIteratorFromPos(stringList, pos);

		stringList.Insert(begIterator, value);

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
	stringList.Insert(stringList.begin(), "horse1");

	vector<string> list = { "horse1" };
	CheckContentOfStringList(stringList, list);
}

BOOST_AUTO_TEST_CASE(testDeleteFirstNode)
{
	vector<string> list = { "cat", "dog", "catdog", "cow" };

	AddToStringListFromArray(stringList, list);

	stringList.Delete(stringList.begin());
	list.erase(list.begin());

	CheckContentOfStringList(stringList, list);
}

BOOST_AUTO_TEST_CASE(testDeleteCenterNode)
{
	vector<string> list = { "cat", "dog", "catdog", "cow" };

	AddToStringListFromArray(stringList, list);

	stringList.Delete(GetStringListIteratorFromPos(stringList, 2));
	list.erase(list.begin() + 2);

	CheckContentOfStringList(stringList, list);
}

BOOST_AUTO_TEST_CASE(testDeleteLastNode)
{
	vector<string> list = { "cat", "dog", "catdog", "cow" };

	AddToStringListFromArray(stringList, list);

	stringList.Delete(GetStringListIteratorFromPos(stringList, 3));
	list.erase(list.begin() + 3);

	CheckContentOfStringList(stringList, list);
}

//BOOST_AUTO_TEST_CASE(test_large_std_list)
//{
//	std::list<string> lst;
//	for (size_t i = 0; i < 100000; i++)
//	{
//		lst.emplace_back(std::to_string(i));
//	}
//}


BOOST_AUTO_TEST_CASE(test_large_list)
{
	CStringList lst;

	for (size_t i = 0; i < 100000; i++)
	{
		lst.AddString(std::to_string(i));
	}

	BOOST_CHECK(lst.GetSize() == 100000);
}

BOOST_AUTO_TEST_CASE(test_RBF)
{
	vector<string> list = { "cat", "dog", "catdog", "cow" };

	AddToStringListFromArray(stringList, list);

	auto templateIterator = list.begin();

	int i = 0;
	for (auto it : stringList)
	{
		BOOST_CHECK_EQUAL(templateIterator->c_str(), it);

		templateIterator++;
	}

	BOOST_CHECK(templateIterator == list.end());
}

BOOST_AUTO_TEST_CASE(test_end_iterator)
{
	vector<string> list = { "cat", "dog", "catdog", "cow" };

	AddToStringListFromArray(stringList, list);

	auto it = stringList.end();
	it--;

	auto templateIterator = list.end();
	templateIterator--;

	BOOST_CHECK(*it == *templateIterator);
}

BOOST_AUTO_TEST_CASE(test_change_content_list_through_iterator)
{
	vector<string> list = { "cat", "dog", "catdog", "cow" };

	AddToStringListFromArray(stringList, list);

	auto it = stringList.begin();
	it++;
	*it = "worm";

	CheckContentOfStringList(stringList, { "cat", "worm", "catdog", "cow" });
}

BOOST_AUTO_TEST_CASE(all_end_iterators_must_be_identical)
{
	CStringList lst;
	auto end0 = lst.end();
	lst.AddString("one");
	auto end1 = lst.end();
	lst.AddString("two");
	auto end2 = lst.end();

	BOOST_REQUIRE(end0 == end1);
	BOOST_REQUIRE(end1 == end2);

	--end0;
	--end1;
	--end2;
	BOOST_REQUIRE(end0 == end1);
	BOOST_REQUIRE(end1 == end2);
	BOOST_REQUIRE_EQUAL(*end1, "two");
}

BOOST_AUTO_TEST_SUITE_END()