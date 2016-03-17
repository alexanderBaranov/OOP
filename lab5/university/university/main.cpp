// university.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "UniversityProcess.h"
#include <iostream>
#include <locale>
#include <windows.h>
#include <algorithm>
#include <atlconv.h>

using namespace std;

void GetListUnivesities(shared_ptr<CUniversityProcess>univerProcess)
{
	cout << "������ �������������:" << endl;
	universites univers = univerProcess->GetListUniversites();

	if (!univers.empty())
	{
		for_each(univers.begin(), univers.end(), [](const shared_ptr<CUniversity>univer)
		{
			cout << univer->GetName() << endl;
		});
	}
	else
	{
		cout << "������ ������������� ����." << endl;
	}
}

void RenameUniversity(shared_ptr<CUniversityProcess>univerProcess)
{
	cout << "������� �������� ����������� ������������: ";
	
	cin.ignore();

	string oldName;
	getline(cin, oldName);

	cout << "������� ����� ��� ������������: ";

	string newName;
	getline(cin, newName);

	if (!univerProcess->ReplaceUniversity(oldName, newName))
	{
		cout << "�� ������� �������� �������� ������������" << endl;
	}
}

void DeleteUniversity(shared_ptr<CUniversityProcess>univerProcess)
{
	cout << "������� �������� ���������� ������������: ";

	cin.ignore();

	string name;
	getline(cin, name);

	if (!univerProcess->DeleteUniversity(name))
	{
		cout << "�� ������� ������� \""<< name <<"\" �����������" << endl;
	}
}

void GetStudentsFromUniversity(shared_ptr<CUniversityProcess>univerProcess)
{
	cout << "������� �������� ������������: ";

	cin.ignore();

	string name;
	getline(cin, name);

	students students = univerProcess->GetListStudentsFromUniversity(name);

	if (students.size())
	{
		cout << "������ c��������, ����������� � \"" << name << "\":" << endl;
		
		int count = 0;
		for_each(students.begin(), students.end(), [&](const shared_ptr<CStudent>stud)
		{
			cout << stud->GetName() << " " 
				<< univerProcess->GetStringFromEnumGender(stud->GetGender()) << " "
				<< stud->GetGrowth() << " "
				<< stud->GetAge() << " "
				<< stud->GetWeight() << " "
				<< stud->GetNumberOfYearsStudy() << " "
				<< stud->GetUniversity().lock()->GetName() << endl;
		});
	}
	else
	{
		cout << "�� ������� ����� ����������� � ����� ���������" << endl;
	}

}

void AddUniversity(shared_ptr<CUniversityProcess>univerProcess)
{
	cout << "������� �������� ������������ ������������: ";

	cin.ignore();

	string name;
	getline(cin, name);

	if (!univerProcess->AddNewUniversity(name))
	{
		cout << "�� ������� �������� ����������� � ����� ���������." << endl;
	}
}

void GetListStudents(shared_ptr<CUniversityProcess>univerProcess)
{
	cout << "������ ���������:" << endl;
	students students = univerProcess->GetListStudents();
	if (!students.empty())
	{
		int count = 0;
		for_each(students.begin(), students.end(), [&](const shared_ptr<CStudent>stud)
		{
			cout << count << "." 
				<< stud->GetName() << " "
				<< univerProcess->GetStringFromEnumGender(stud->GetGender()) << " "
				<< stud->GetGrowth() << " "
				<< stud->GetAge() << " "
				<< stud->GetWeight() << " "
				<< stud->GetNumberOfYearsStudy() << " "
				<< stud->GetUniversity().lock()->GetName() << endl;

			count++;
		});
	}
	else
	{
		cout << "������ ������������� ����." << endl;
	}
}

void StudentData(string& name,
	double& growth,
	double& weight,
	int& age,
	string& university,
	int& numberOfYearsStudy)
{
	cin.ignore();

	cout << "���: ";
	getline(cin, name);

	cout << "����: ";
	cin >> growth;

	cout << "���: ";
	cin >> weight;

	cout << "���: ";
	cin >> age;

	cin.ignore();
	cout << "�����������: ";
	getline(cin, university);

	cout << "������� ���������: ";
	cin >> numberOfYearsStudy;
}


void UpdateStudent(shared_ptr<CUniversityProcess>univerProcess)
{
	GetListStudents(univerProcess);
	cout << "�������� �� ������ �������� �� ��� ����������� ������, �������� ������ ��������: ";

	int number;
	cin >> number;

	string name;
	double growth;
	double weight;
	int age;
	string university;
	int numberOfYearsStudy;

	StudentData(name,
		growth,
		weight,
		age,
		university,
		numberOfYearsStudy);

	if (!univerProcess->UpdateStudentData(number, name, growth, weight, age, university, numberOfYearsStudy))
	{
		cout << "�� ������� �������� ��������" << endl;
	}
}

void DeleteStudent(shared_ptr<CUniversityProcess>univerProcess)
{
	GetListStudents(univerProcess);
	cout << "�������� �� ������ �������� �� ��� ����������� ������, �������� ������ �������: ";

	int number;
	cin >> number;

	if (!univerProcess->DeleteStudent(number))
	{
		cout << "�� ������� ������� ��������" << endl;
	}
}

void AddStudent(shared_ptr<CUniversityProcess>univerProcess)
{
	cout << "������� ������ ������ ��������: " << endl;
	
	string name;
	string gender;
	double growth;
	double weight;
	int age;
	string university;
	int numberOfYearsStudy;

	StudentData(name,
		growth,
		weight,
		age,
		university,
		numberOfYearsStudy);

	cin.ignore();
	cout << "���: " << endl;
	getline(cin, gender);

	if (!univerProcess->AddNewStudent(name, gender, growth, weight, age, university, numberOfYearsStudy))
	{
		cout << "�� ������� �������� ��������" << endl;
	}
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
		
		auto univerProcess = make_shared<CUniversityProcess>(W2A(argv[1]), W2A(argv[2]));
		
		string command;
		while (command != "Q")
		{
			cout << endl <<  "�������� ��������:" << endl;
			cout << "1. ������� ������ �������������" << endl;
			cout << "2. ������������� �����������" << endl;
			cout << "3. ������� �����������" << endl;
			cout << "4. ������� ������ ��������� ������������" << endl;
			cout << "5. �������� �����������" << endl;
			cout << "6. ������� ������ ���������" << endl;
			cout << "7. �������� ������ � ��������" << endl;
			cout << "8. ������� ��������" << endl;
			cout << "9. �������� ��������" << endl;
			cout << "Q. �����" << endl;

			cout << "�������: ";
			cin >> command;
			cout << endl;

			if (command == "1")
			{
				GetListUnivesities(univerProcess);
			}
			else if (command == "2")
			{
				RenameUniversity(univerProcess);
			}
			else if (command == "3")
			{
				DeleteUniversity(univerProcess);
			}
			else if (command == "4")
			{
				GetStudentsFromUniversity(univerProcess);
			}
			else if (command == "5")
			{
				AddUniversity(univerProcess);
			}
			else if (command == "6")
			{
				GetListStudents(univerProcess);
			}
			else if (command == "7")
			{
				UpdateStudent(univerProcess);
			}
			else if (command == "8")
			{
				DeleteStudent(univerProcess);
			}
			else if (command == "9")
			{
				AddStudent(univerProcess);
			}
		}

		if (univerProcess->Updated())
		{
			cout << "��������� ���������? (y(��)/n(���): ";
			string command;
			cin >> command;

			if (command == "y")
			{
				univerProcess->Save();
			}
		}
	}
	catch (const exception &error)
	{
		cout << error.what() << endl;
	}
	
	return 0;
}

