// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../university/UniversityProcess.h"
#define BOOST_TEST_MODULE TestsOfUnivercities

#include <boost\test\included\unit_test.hpp>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

static const string STUDENTS_FILE = "students.txt";
static const string UNIVERSITIES_FILE = "universities.txt";

struct UniversityFixture
{
	UniversityFixture()
	{
		path tempPath = temp_directory_path();
		
		m_tempFileOfUniversities = tempPath;
		m_tempFileOfUniversities /= unique_path();

		m_tempFileOfStudents = tempPath;
		m_tempFileOfStudents /= unique_path();

		copy_file(STUDENTS_FILE, m_tempFileOfStudents);
		copy_file(UNIVERSITIES_FILE, m_tempFileOfUniversities);

		univerProcess = CUniversityManagement(m_tempFileOfUniversities.string(), m_tempFileOfStudents.string());
	};

	~UniversityFixture()
	{
		remove(m_tempFileOfUniversities);
		remove(m_tempFileOfStudents);
	};

	path m_tempFileOfUniversities;
	path m_tempFileOfStudents;
	CUniversityManagement univerProcess;
};

BOOST_FIXTURE_TEST_SUITE(TestsOfUnivercity, UniversityFixture)

BOOST_AUTO_TEST_CASE(testEmpty)
{
	CUniversityManagement universityProcess;
	Universites univers = universityProcess.GetUniversites();
	BOOST_CHECK_EQUAL(univers.size(), 0);

	Students students = universityProcess.GetStudents();
	BOOST_CHECK_EQUAL(students.size(), 0);

	BOOST_CHECK_THROW(CUniversityManagement univerProcess2("univer.txt", "stud.txt"), exception);
}

BOOST_AUTO_TEST_CASE(testReadStudents)
{
	Students students = univerProcess.GetStudentsFromUniversity("margtu");
	BOOST_CHECK_EQUAL(students[0]->GetName(), "����");
	BOOST_CHECK_EQUAL(students.size(), 2);
}

BOOST_AUTO_TEST_CASE(testReplaceUniversities)
{
	BOOST_CHECK(univerProcess.RenameUniversity("margtu", "ips"));
	BOOST_CHECK(!univerProcess.RenameUniversity("asdasd", "ips"));
	BOOST_CHECK(!univerProcess.RenameUniversity("", "ips"));
	BOOST_CHECK(!univerProcess.RenameUniversity("margtu", ""));

	Students students = univerProcess.GetStudentsFromUniversity("margtu");
	BOOST_CHECK(students.empty());

	students = univerProcess.GetStudentsFromUniversity("ips");
	BOOST_CHECK_EQUAL(students[0]->GetName(), "����");
	BOOST_CHECK_EQUAL(students.size(), 2);

	BOOST_CHECK(univerProcess.RenameUniversity("ips", "margtu"));
}

BOOST_AUTO_TEST_CASE(testDeleteAndAdd)
{
	BOOST_CHECK(!univerProcess.DeleteUniversity("asdasd"));
	BOOST_CHECK(!univerProcess.DeleteUniversity(""));
	BOOST_CHECK(univerProcess.DeleteUniversity("margtu"));
	
	Universites univers = univerProcess.GetUniversites();
	BOOST_CHECK_EQUAL(univers.size(), 2);
	BOOST_CHECK_EQUAL(univers[0]->GetName(), "mgu");

	Students students = univerProcess.GetStudents();
	BOOST_CHECK_EQUAL(students.size(), 1);

	BOOST_CHECK(!univerProcess.AddNewUniversity(""));
	BOOST_CHECK(univerProcess.AddNewUniversity("margtu"));
	BOOST_CHECK(!univerProcess.AddNewUniversity("margtu"));

	univers = univerProcess.GetUniversites();
	BOOST_CHECK_EQUAL(univers.size(), 3);
	BOOST_CHECK_EQUAL(univers[0]->GetName(), "mgu");
	BOOST_CHECK_EQUAL(univers[1]->GetName(), "mosi");
	BOOST_CHECK_EQUAL(univers[2]->GetName(), "margtu");
	
	BOOST_CHECK(univerProcess.AddNewStudent("����", "�", 190, 70, 22, "margtu", 2));
	BOOST_CHECK(univerProcess.AddNewStudent("����", "�", 190, 70, 22, "margtu", 2));

	students = univerProcess.GetStudents();
	BOOST_CHECK_EQUAL(students.size(), 3);
	BOOST_CHECK_EQUAL(students[0]->GetName(), "�������");
	BOOST_CHECK_EQUAL(students[1]->GetName(), "����");
	BOOST_CHECK_EQUAL(students[2]->GetName(), "����");

	BOOST_CHECK(!univerProcess.DeleteStudent(20));
	BOOST_CHECK(univerProcess.DeleteStudent(2));
	
	students = univerProcess.GetStudents();
	BOOST_CHECK_EQUAL(students.size(), 2);
	BOOST_CHECK_EQUAL(students[0]->GetName(), "�������");
	BOOST_CHECK_EQUAL(students[1]->GetName(), "����");

	BOOST_CHECK(univerProcess.AddNewStudent("����", "�", 190, 70, 22, "margtu", 2));
}

BOOST_AUTO_TEST_CASE(testUpdateStudent)
{
	BOOST_CHECK(univerProcess.UpdateStudentData(2, "����", 0, 0, 0, "", 0));
	
	Students students = univerProcess.GetStudents();
	BOOST_CHECK_EQUAL(students.size(), 3);
	BOOST_CHECK_EQUAL(students[0]->GetName(), "�������");
	BOOST_CHECK_EQUAL(students[1]->GetName(), "����");
	BOOST_CHECK_EQUAL(students[2]->GetName(), "����");

	BOOST_CHECK(univerProcess.UpdateStudentData(2, "����", 0, 0, 0, "", 0));
}

BOOST_AUTO_TEST_CASE(testWriteChangesToInputFiles)
{
	univerProcess.SaveChanges();

	Students students;
	Universites univers;

	{
		students = univerProcess.GetStudents();
		BOOST_CHECK_EQUAL(students.size(), 3);
		BOOST_CHECK_EQUAL(students[0]->GetName(), "�������");
		BOOST_CHECK_EQUAL(students[1]->GetName(), "����");
		BOOST_CHECK_EQUAL(students[2]->GetName(), "����");

		BOOST_CHECK(univerProcess.AddNewStudent("�����", "�", 190, 70, 22, "margtu", 2));

		students = univerProcess.GetStudents();
		BOOST_CHECK_EQUAL(students.size(), 4);
		BOOST_CHECK_EQUAL(students[3]->GetName(), "�����");

		univerProcess.SaveChanges();
	}
	{
		students = univerProcess.GetStudents();
		BOOST_CHECK_EQUAL(students.size(), 4);
		BOOST_CHECK_EQUAL(students[3]->GetName(), "�����");

		univerProcess.DeleteStudent(3);

		univerProcess.AddNewUniversity("asd");
		univers = univerProcess.GetUniversites();
		BOOST_CHECK_EQUAL(univers.size(), 4);
		BOOST_CHECK_EQUAL(univers[3]->GetName(), "asd");

		univerProcess.SaveChanges();
	}
	{
		univers = univerProcess.GetUniversites();
		BOOST_CHECK_EQUAL(univers.size(), 4);
		BOOST_CHECK_EQUAL(univers[3]->GetName(), "asd");

		univerProcess.DeleteUniversity("asd");

		students = univerProcess.GetStudents();
		BOOST_CHECK_EQUAL(students.size(), 3);

		univerProcess.SaveChanges();
	}
	{	
		students = univerProcess.GetStudents();
		BOOST_CHECK_EQUAL(students.size(), 3);

		univers = univerProcess.GetUniversites();
		BOOST_CHECK_EQUAL(univers.size(), 3);
	}
}

BOOST_AUTO_TEST_SUITE_END()
