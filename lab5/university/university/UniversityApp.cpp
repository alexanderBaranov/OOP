#include "stdafx.h"
#include "UniversityApp.h"
#include <algorithm>

using namespace std;
using namespace std::placeholders;

CUniversityApp::CUniversityApp(std::unique_ptr<CUniversityManagement>&& univerManagment)
	:m_universityManagement(move(univerManagment))
{
}

void CUniversityApp::Run()
{
	cout << endl << "�������� ��������:" << endl;

	const MenuItem items[] = {
		{ "1", "������� ������ �������������", BindMethodToAction(&CUniversityApp::GetListUnivesities) },
		{ "2", "������������� �����������", BindMethodToAction(&CUniversityApp::RenameUniversity) },
		{ "3", "������� �����������", BindMethodToAction(&CUniversityApp::DeleteUniversity) },
		{ "4", "������� ������ ��������� ������������", BindMethodToAction(&CUniversityApp::GetStudentsFromUniversity) },
		{ "5", "�������� �����������", BindMethodToAction(&CUniversityApp::AddUniversity) },
		{ "6", "������� ������ ���������", BindMethodToAction(&CUniversityApp::GetListStudents) },
		{ "7", "�������� ������ � ��������", BindMethodToAction(&CUniversityApp::UpdateStudent) },
		{ "8", "������� ��������", BindMethodToAction(&CUniversityApp::DeleteStudent) },
		{ "9", "�������� ��������", BindMethodToAction(&CUniversityApp::AddStudent) },
		{ "Q", "�����", BindMethodToAction(&CUniversityApp::Quit) }
	};

	CMenu menu(items);
	menu.InteractWithUser(cin, cout);
}

MenuItem::Action CUniversityApp::BindMethodToAction(HandlerMethod method)
{
	return bind(method, this, _1, _2);
}

bool CUniversityApp::GetListUnivesities(istream & input, ostream & output)
{
	output << "������ �������������:" << endl;
	Universites univers = m_universityManagement->GetUniversites();

	if (!univers.empty())
	{
		for_each(univers.begin(), univers.end(), [&](const shared_ptr<CUniversity>univer)
		{
			output << univer->GetName() << endl;
		});
	}
	else
	{
		output << "������ ������������� ����." << endl;
	}

	return true;
}

bool CUniversityApp::RenameUniversity(istream & input, ostream & output)
{
	output << "������� �������� ����������� ������������: ";

	string oldName;
	getline(input, oldName);

	output << "������� ����� ��� ������������: ";

	string newName;
	getline(input, newName);

	if (!m_universityManagement->RenameUniversity(oldName, newName))
	{
		output << "�� ������� �������� �������� ������������" << endl;
	}

	return true;
}

bool CUniversityApp::DeleteUniversity(istream & input, ostream & output)
{
	output << "������� �������� ���������� ������������: ";

	string name;
	getline(input, name);

	if (!m_universityManagement->DeleteUniversity(name))
	{
		output << "�� ������� ������� \"" << name << "\" �����������" << endl;
	}

	return true;
}

void CUniversityApp::PrintStudents(ostream & output, const Students& students)
{
	int count = 0;
	for (const auto& stud : students)
	{
		output << count << "."
			<< stud->GetName() << " "
			<< GetStringFromEnumGender(stud->GetGender()) << " "
			<< stud->GetGrowth() << " "
			<< stud->GetAge() << " "
			<< stud->GetWeight() << " "
			<< stud->GetNumberOfYearsStudy() << " "
			<< stud->GetUniversity()->GetName() << endl;

		count++;
	};
}

bool CUniversityApp::GetStudentsFromUniversity(istream & input, ostream & output)
{
	output << "������� �������� ������������: ";

	string name;
	getline(input, name);

	Students students = m_universityManagement->GetStudentsFromUniversity(name);

	if (students.size())
	{
		output << "������ c��������, ����������� � \"" << name << "\":" << endl;

		PrintStudents(output, students);
	}
	else
	{
		output << "C�������� � ���� ������������ ���" << endl;
	}

	return true;
}

bool CUniversityApp::AddUniversity(istream & input, ostream & output)
{
	output << "������� �������� ������������ ������������: ";

	string name;
	getline(input, name);

	if (!m_universityManagement->AddNewUniversity(name))
	{
		output << "�� ������� �������� ����������� � ����� ���������." << endl;
	}

	return true;
}

bool CUniversityApp::GetListStudents(istream & input, ostream & output)
{
	output << "������ ���������:" << endl;
	Students students = m_universityManagement->GetStudents();
	if (!students.empty())
	{
		PrintStudents(output, students);
	}
	else
	{
		output << "������ ������������� ����." << endl;
	}

	return true;
}

void CUniversityApp::StudentData(istream & input,
	ostream & output,
	string& name,
	double& growth,
	double& weight,
	int& age,
	string& university,
	int& numberOfYearsStudy)
{
	input.ignore();

	output << "���: ";
	getline(input, name);

	output << "����: ";
	input >> growth;

	output << "���: ";
	input >> weight;

	output << "���: ";
	input >> age;

	input.ignore();

	output << "�����������: ";
	getline(input, university);

	output << "������� ���������: ";
	input >> numberOfYearsStudy;
}


bool CUniversityApp::UpdateStudent(istream & input, ostream & output)
{
	GetListStudents(input, output);
	output << "�������� �� ������ �������� �� ��� ����������� ������, �������� ������ ��������: ";

	int number;
	input >> number;

	string name;
	double growth;
	double weight;
	int age;
	string university;
	int numberOfYearsStudy;

	StudentData(input,
		output,
		name,
		growth,
		weight,
		age,
		university,
		numberOfYearsStudy);

	string error;
	if (!m_universityManagement->UpdateStudentData(number, name, growth, weight, age, university, numberOfYearsStudy, error))
	{
		output << "�� ������� �������� ��������. " << error << endl;
	}

	return true;
}

bool CUniversityApp::DeleteStudent(istream & input, ostream & output)
{
	GetListStudents(input, output);
	output << "�������� �� ������ �������� �� ��� ����������� ������, �������� ������ �������: ";

	int number;
	input >> number;

	if (!m_universityManagement->DeleteStudent(number))
	{
		output << "�� ������� ������� ��������" << endl;
	}

	return true;
}

bool CUniversityApp::AddStudent(istream & input, ostream & output)
{
	output << "������� ������ ������ ��������: " << endl;

	string name;
	string gender;
	double growth;
	double weight;
	int age;
	string university;
	int numberOfYearsStudy;

	StudentData(input,
		output,
		name,
		growth,
		weight,
		age,
		university,
		numberOfYearsStudy);

	input.ignore();
	output << "���: " << endl;
	getline(input, gender);

	if (!m_universityManagement->AddNewStudent(name, GetEnumGenderFromString(gender), growth, weight, age, university, numberOfYearsStudy))
	{
		output << "�� ������� �������� ��������" << endl;
	}

	return true;
}

bool CUniversityApp::Quit(istream& input, ostream& output)
{
	if (m_universityManagement->Updated())
	{
		output << "��������� ���������? (y(��)/n(���): ";
		string command;
		input >> command;

		if (command == "y")
		{
			m_universityManagement->SaveChanges();
		}
	}
	return false;
}
