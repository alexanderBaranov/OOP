// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../university/UniversityProcess.h"
#define BOOST_TEST_MODULE TestsOfUnivercities

#include <boost\test\included\unit_test.hpp>

using namespace std;

static const string kStudentsFile = "students.txt";
static const string kUniversitiesFile = "universities.txt";

struct UniversityFixture
{
	CUniversityProcess univerProcess = CUniversityProcess(kUniversitiesFile, kStudentsFile);
};

BOOST_FIXTURE_TEST_SUITE(TestsOfUnivercity, UniversityFixture)

BOOST_AUTO_TEST_CASE(testEmpty)
{
	universites univers = univerProcess.GetListUniversites();
	BOOST_CHECK_EQUAL(univers.size(), 3);

	students students = univerProcess.GetListStudents();
	BOOST_CHECK_EQUAL(students.size(), 3);

	CUniversityProcess univerProcess2("univer.txt", "stud.txt");

	univers = univerProcess2.GetListUniversites();
	BOOST_CHECK(univers.empty());

	students = univerProcess2.GetListStudents();
	BOOST_CHECK(students.empty());
}

BOOST_AUTO_TEST_CASE(testReadStudents)
{
	students students = univerProcess.GetListStudentsFromUniversity("margtu");
	BOOST_CHECK_EQUAL(students[0]->Name(), "Валя");
	BOOST_CHECK_EQUAL(students.size(), 2);
}

BOOST_AUTO_TEST_CASE(testReplaceUniversities)
{
	BOOST_CHECK(univerProcess.ReplaceUniversity("margtu", "ips"));
	BOOST_CHECK(!univerProcess.ReplaceUniversity("asdasd", "ips"));
	BOOST_CHECK(!univerProcess.ReplaceUniversity("", "ips"));
	BOOST_CHECK(!univerProcess.ReplaceUniversity("margtu", ""));

	students students = univerProcess.GetListStudentsFromUniversity("margtu");
	BOOST_CHECK(students.empty());

	students = univerProcess.GetListStudentsFromUniversity("ips");
	BOOST_CHECK_EQUAL(students[0]->Name(), "Валя");
	BOOST_CHECK_EQUAL(students.size(), 2);

	BOOST_CHECK(univerProcess.ReplaceUniversity("ips", "margtu"));
}

BOOST_AUTO_TEST_CASE(testDeleteAndAdd)
{
	BOOST_CHECK(!univerProcess.DeleteUniversity("asdasd"));
	BOOST_CHECK(!univerProcess.DeleteUniversity(""));
	BOOST_CHECK(univerProcess.DeleteUniversity("margtu"));
	
	universites univers = univerProcess.GetListUniversites();
	BOOST_CHECK_EQUAL(univers.size(), 2);
	BOOST_CHECK_EQUAL(univers[0]->GetName(), "mgu");

	students students = univerProcess.GetListStudents();
	BOOST_CHECK_EQUAL(students.size(), 1);

	BOOST_CHECK(!univerProcess.AddNewUniversity(""));
	BOOST_CHECK(univerProcess.AddNewUniversity("margtu"));
	BOOST_CHECK(!univerProcess.AddNewUniversity("margtu"));

	univers = univerProcess.GetListUniversites();
	BOOST_CHECK_EQUAL(univers.size(), 3);
	BOOST_CHECK_EQUAL(univers[0]->GetName(), "mgu");
	BOOST_CHECK_EQUAL(univers[1]->GetName(), "mosi");
	BOOST_CHECK_EQUAL(univers[2]->GetName(), "margtu");
	
	BOOST_CHECK(univerProcess.AddNewStudent("Валя", "ж", 190, 70, 22, "margtu", 2));
	BOOST_CHECK(univerProcess.AddNewStudent("Женя", "ж", 190, 70, 22, "margtu", 2));

	students = univerProcess.GetListStudents();
	BOOST_CHECK_EQUAL(students.size(), 3);
	BOOST_CHECK_EQUAL(students[0]->Name(), "Петруха");
	BOOST_CHECK_EQUAL(students[1]->Name(), "Валя");
	BOOST_CHECK_EQUAL(students[2]->Name(), "Женя");

	BOOST_CHECK(!univerProcess.DeleteStudent(20));
	BOOST_CHECK(univerProcess.DeleteStudent(2));
	
	students = univerProcess.GetListStudents();
	BOOST_CHECK_EQUAL(students.size(), 2);
	BOOST_CHECK_EQUAL(students[0]->Name(), "Петруха");
	BOOST_CHECK_EQUAL(students[1]->Name(), "Валя");

	BOOST_CHECK(univerProcess.AddNewStudent("Женя", "ж", 190, 70, 22, "margtu", 2));
}

BOOST_AUTO_TEST_CASE(testUpdateStudent)
{
	BOOST_CHECK(univerProcess.UpdateStudentData(2, "Вика", 0, 0, 0, "", 0));
	
	students students = univerProcess.GetListStudents();
	BOOST_CHECK_EQUAL(students.size(), 3);
	BOOST_CHECK_EQUAL(students[0]->Name(), "Петруха");
	BOOST_CHECK_EQUAL(students[1]->Name(), "Валя");
	BOOST_CHECK_EQUAL(students[2]->Name(), "Вика");

	BOOST_CHECK(univerProcess.UpdateStudentData(2, "Женя", 0, 0, 0, "", 0));
}

BOOST_AUTO_TEST_CASE(testWriteChangesToInputFiles)
{
	univerProcess.Save();

	students students;
	universites univers;

	{
		CUniversityProcess univerProcess2(kUniversitiesFile, kStudentsFile);
		students = univerProcess2.GetListStudents();
		BOOST_CHECK_EQUAL(students.size(), 3);
		BOOST_CHECK_EQUAL(students[0]->Name(), "Петруха");
		BOOST_CHECK_EQUAL(students[1]->Name(), "Валя");
		BOOST_CHECK_EQUAL(students[2]->Name(), "Женя");

		BOOST_CHECK(univerProcess2.AddNewStudent("Игорь", "м", 190, 70, 22, "margtu", 2));

		students = univerProcess2.GetListStudents();
		BOOST_CHECK_EQUAL(students.size(), 4);
		BOOST_CHECK_EQUAL(students[3]->Name(), "Игорь");

		univerProcess2.Save();
	}
	{
		CUniversityProcess univerProcess2(kUniversitiesFile, kStudentsFile);

		students = univerProcess2.GetListStudents();
		BOOST_CHECK_EQUAL(students.size(), 4);
		BOOST_CHECK_EQUAL(students[3]->Name(), "Игорь");

		univerProcess2.DeleteStudent(3);

		univerProcess2.AddNewUniversity("asd");
		univers = univerProcess2.GetListUniversites();
		BOOST_CHECK_EQUAL(univers.size(), 4);
		BOOST_CHECK_EQUAL(univers[3]->GetName(), "asd");

		univerProcess2.Save();
	}
	{
		CUniversityProcess univerProcess2(kUniversitiesFile, kStudentsFile);
		univers = univerProcess2.GetListUniversites();
		BOOST_CHECK_EQUAL(univers.size(), 4);
		BOOST_CHECK_EQUAL(univers[3]->GetName(), "asd");

		univerProcess2.DeleteUniversity("asd");

		students = univerProcess2.GetListStudents();
		BOOST_CHECK_EQUAL(students.size(), 3);

		univerProcess2.Save();
	}
	{
		CUniversityProcess univerProcess2(kUniversitiesFile, kStudentsFile);
		
		students = univerProcess2.GetListStudents();
		BOOST_CHECK_EQUAL(students.size(), 3);

		univers = univerProcess2.GetListUniversites();
		BOOST_CHECK_EQUAL(univers.size(), 3);
	}
}

BOOST_AUTO_TEST_SUITE_END()
