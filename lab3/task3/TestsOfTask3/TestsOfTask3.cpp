// TestsOfTask3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define BOOST_TEST_MODULE TestsOfTask3

#include <boost\test\included\unit_test.hpp>
#include "..\task3\WordCount.h"
#include <map>

using namespace std;

BOOST_AUTO_TEST_SUITE(TestsOfTask3)

BOOST_AUTO_TEST_CASE(test_calculate_the_same_words)
{
	BOOST_CHECK(CountWords("�����, �����, ����� ����� ����") == mapWords({ { "�����", 3 }, { "�����", 1 }, {"����", 1} }));
}

BOOST_AUTO_TEST_CASE(test_caunting_the_same_words_with_upper_and_lower_case_letters)
{
	BOOST_CHECK(CountWords("�����, �����, ����� ����� ����") == mapWords({ { "�����", 3 }, { "�����", 1 }, { "����", 1 } }));
}

BOOST_AUTO_TEST_CASE(test_count_word_in_the_composition_with_digit)
{
	BOOST_CHECK(CountWords("4���� ���� ����� ����, ����� ���� ����� ������") == mapWords({ { "�����", 2 }, { "����", 2 }, { "����", 1 }, { "4����", 1 }, { "�����", 1 }, {"������", 1} }));
	BOOST_CHECK(CountWords("r2d2") == mapWords({ { "r2d2", 1 } }));
	BOOST_CHECK(CountWords("������� �� 3 �������, ������� 100 ������") == mapWords({ { "�������", 1 }, { "��", 1 }, { "3", 1 }, { "�������", 1 }, { "�������", 1 }, { "100", 1 }, { "������", 1 } }));
}

BOOST_AUTO_TEST_CASE(test_counting_the_words_punctuation_mark_without_spaces_between_words)
{
	BOOST_CHECK(CountWords("�����,�����,����� ����� ����") == mapWords({ { "�����", 3 }, { "�����", 1 }, { "����", 1 } }));
}

BOOST_AUTO_TEST_CASE(test_punctuation_before_word)
{
	BOOST_CHECK(CountWords("......,,,,,., ����� ������") == mapWords({ { "�����", 1 }, { "������", 1 } }));
}

BOOST_AUTO_TEST_CASE(test_multiple_tabs_in_the_string)
{
	BOOST_CHECK(CountWords("			�����		������			") == mapWords({ { "�����", 1 }, { "������", 1 } }));
}

BOOST_AUTO_TEST_CASE(test_empty_string)
{
	BOOST_CHECK(CountWords("  ") == mapWords());
}

BOOST_AUTO_TEST_CASE(test_newline_character_in_the_string)
{
	BOOST_CHECK(CountWords("\n\r\t�����\n\r\t ������\n\r\t") == mapWords({ { "�����", 1 }, { "������", 1 } }));
}

BOOST_AUTO_TEST_SUITE_END()