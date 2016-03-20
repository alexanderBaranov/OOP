// university.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "UniversityProcess.h"
#include <locale>
#include <windows.h>
#include <algorithm>
#include <atlconv.h>
#include <functional>
#include <iostream>
#include <sstream>
#include <boost/range/algorithm/find_if.hpp>

using namespace std;
using namespace std::placeholders;
using namespace boost::range;

struct MenuItem
{
	string command;
	string description;
	function<bool(istream & input, ostream & output, const shared_ptr<CUniversityManagement>& univerProcess)> action;
};

class CMenu
{
public:
	template <typename MenuItems>
	CMenu(MenuItems && items, shared_ptr<CUniversityManagement>&& univerProcess)
		:m_items(begin(items), end(items))
		, m_univerProcess(move(univerProcess))
	{
		for (auto& item : m_items)
		{
			cout << item.command << ". " << item.description << endl;
		}
	}

	~CMenu()
	{
		if (m_univerProcess->Updated())
		{
			cout << "��������� ���������? (y(��)/n(���): ";
			string command;
			cin >> command;

			if (command == "y")
			{
				m_univerProcess->SaveChanges();
			}
		}
	}

	void InteractWithUser(istream & input, ostream & output)
	{
		string line;
		string command;
		while (getline(input, line))
		{
			istringstream cmdStream(line);
			if (cmdStream >> command)
			{
				auto it = find_if(m_items, [&](const MenuItem& item){
					return item.command == command;
				});

				if (it != m_items.end())
				{
					if (!it->action(input, output, m_univerProcess))
					{
						break;
					}
				}
				else
				{
					output << "Command " << command << " is not recognized" << endl;
				}
			}
		}
	}

private:
	vector<MenuItem> m_items;
	shared_ptr<CUniversityManagement> m_univerProcess;
};

bool GetListUnivesities(istream & input, ostream & output, const shared_ptr<CUniversityManagement>& univerProcess)
{
	output << "������ �������������:" << endl;
	Universites univers = univerProcess->GetUniversites();

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

bool RenameUniversity(istream & input, ostream & output, const shared_ptr<CUniversityManagement>& univerProcess)
{
	output << "������� �������� ����������� ������������: ";

	string oldName;
	getline(input, oldName);

	output << "������� ����� ��� ������������: ";

	string newName;
	getline(input, newName);

	if (!univerProcess->RenameUniversity(oldName, newName))
	{
		output << "�� ������� �������� �������� ������������" << endl;
	}

	return true;
}

bool DeleteUniversity(istream & input, ostream & output, const shared_ptr<CUniversityManagement>& univerProcess)
{
	cout << "������� �������� ���������� ������������: ";

	string name;
	getline(input, name);

	if (!univerProcess->DeleteUniversity(name))
	{
		output << "�� ������� ������� \"" << name << "\" �����������" << endl;
	}

	return true;
}

void PrintStudents(ostream & output, const Students& students, const shared_ptr<CUniversityManagement>& univerProcess)
{
	int count = 0;
	for (const auto& stud : students)
	{
		output << count << "."
			<< stud->GetName() << " "
			<< univerProcess->GetStringFromEnumGender(stud->GetGender()) << " "
			<< stud->GetGrowth() << " "
			<< stud->GetAge() << " "
			<< stud->GetWeight() << " "
			<< stud->GetNumberOfYearsStudy() << " "
			<< stud->GetUniversity()->GetName() << endl;

		count++;
	};
}

bool GetStudentsFromUniversity(istream & input, ostream & output, const shared_ptr<CUniversityManagement>& univerProcess)
{
	output << "������� �������� ������������: ";

	string name;
	getline(input, name);

	Students students = univerProcess->GetStudentsFromUniversity(name);

	if (students.size())
	{
		output << "������ c��������, ����������� � \"" << name << "\":" << endl;

		PrintStudents(output, students, univerProcess);
	}
	else
	{
		output << "C�������� � ���� ������������ ���" << endl;
	}

	return true;
}

bool AddUniversity(istream & input, ostream & output, const shared_ptr<CUniversityManagement>& univerProcess)
{
	output << "������� �������� ������������ ������������: ";

	string name;
	getline(input, name);

	if (!univerProcess->AddNewUniversity(name))
	{
		output << "�� ������� �������� ����������� � ����� ���������." << endl;
	}

	return true;
}

bool GetListStudents(istream & input, ostream & output, const shared_ptr<CUniversityManagement>& univerProcess)
{
	output << "������ ���������:" << endl;
	Students students = univerProcess->GetStudents();
	if (!students.empty())
	{
		PrintStudents(output, students, univerProcess);
	}
	else
	{
		output << "������ ������������� ����." << endl;
	}

	return true;
}

void StudentData(istream & input, 
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


bool UpdateStudent(istream & input, ostream & output, const shared_ptr<CUniversityManagement>& univerProcess)
{
	GetListStudents(input, output, univerProcess);
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

	if (!univerProcess->UpdateStudentData(number, name, growth, weight, age, university, numberOfYearsStudy))
	{
		output << "�� ������� �������� ��������" << endl;
	}

	return true;
}

bool DeleteStudent(istream & input, ostream & output, const shared_ptr<CUniversityManagement>& univerProcess)
{
	GetListStudents(input, output, univerProcess);
	cout << "�������� �� ������ �������� �� ��� ����������� ������, �������� ������ �������: ";

	int number;
	input >> number;

	if (!univerProcess->DeleteStudent(number))
	{
		output << "�� ������� ������� ��������" << endl;
	}

	return true;
}

bool AddStudent(istream & input, ostream & output, const shared_ptr<CUniversityManagement>& univerProcess)
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

	if (!univerProcess->AddNewStudent(name, gender, growth, weight, age, university, numberOfYearsStudy))
	{
		output << "�� ������� �������� ��������" << endl;
	}

	return true;
}

bool Quit(istream & /*input*/, ostream & /*output*/, const shared_ptr<CUniversityManagement>& /*univerProcess*/)
{
	return false;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 3)
	{
		cout << "Example:university.exe <file_universities.txt> <file_students.txt>" << endl;
		return 1;
	}

	locale::global(locale("rus"));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	HANDLE hCon = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	if (hCon != INVALID_HANDLE_VALUE) {
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
		cfi.nFont = 0;
		cfi.dwFontSize.X = 0;
		cfi.dwFontSize.Y = 12;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = 400;
		lstrcpyW(cfi.FaceName, L"Lucida Console");
		SetCurrentConsoleFontEx(hCon, FALSE, &cfi);
	}

	try
	{
		USES_CONVERSION;

		cout << endl << "�������� ��������:" << endl;

		const MenuItem items[] = {
			{ "1", "������� ������ �������������", GetListUnivesities },
			{ "2", "������������� �����������", RenameUniversity },
			{ "3", "������� �����������", DeleteUniversity },
			{ "4", "������� ������ ��������� ������������", GetStudentsFromUniversity},
			{ "5", "�������� �����������", AddUniversity },
			{ "6", "������� ������ ���������", GetListStudents },
			{ "7", "�������� ������ � ��������", UpdateStudent },
			{ "8", "������� ��������", DeleteStudent },
			{ "9", "�������� ��������", AddStudent },
			{ "Q", "�����", Quit}
		};

		CMenu menu(items, make_shared<CUniversityManagement>(W2A(argv[1]), W2A(argv[2])));
		menu.InteractWithUser(cin, cout);
	}
	catch (const exception &error)
	{
		cout << error.what() << endl;
	}
	
	return 0;
}

