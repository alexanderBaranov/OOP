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
	cout << "Список университетов:" << endl;
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
		cout << "Список университетов пуст." << endl;
	}
}

void RenameUniversity(shared_ptr<CUniversityProcess>univerProcess)
{
	cout << "Введите название заменяемого университета: ";
	
	cin.ignore();

	string oldName;
	getline(cin, oldName);

	cout << "Введите новое имя университета: ";

	string newName;
	getline(cin, newName);

	if (!univerProcess->ReplaceUniversity(oldName, newName))
	{
		cout << "Не удалось изменить название университета" << endl;
	}
}

void DeleteUniversity(shared_ptr<CUniversityProcess>univerProcess)
{
	cout << "Введите название удаляемого университета: ";

	cin.ignore();

	string name;
	getline(cin, name);

	if (!univerProcess->DeleteUniversity(name))
	{
		cout << "Не удалось удалить \""<< name <<"\" университет" << endl;
	}
}

void GetStudentsFromUniversity(shared_ptr<CUniversityProcess>univerProcess)
{
	cout << "Введите название университета: ";

	cin.ignore();

	string name;
	getline(cin, name);

	students students = univerProcess->GetListStudentsFromUniversity(name);

	if (students.size())
	{
		cout << "Список cтудентов, обучающихся в \"" << name << "\":" << endl;
		
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
		cout << "Не удалось найти университет с таким названием" << endl;
	}

}

void AddUniversity(shared_ptr<CUniversityProcess>univerProcess)
{
	cout << "Введите название добавляемого университета: ";

	cin.ignore();

	string name;
	getline(cin, name);

	if (!univerProcess->AddNewUniversity(name))
	{
		cout << "Не удалось добавить университет с таким названием." << endl;
	}
}

void GetListStudents(shared_ptr<CUniversityProcess>univerProcess)
{
	cout << "Список студентов:" << endl;
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
		cout << "Список университетов пуст." << endl;
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

	cout << "Имя: ";
	getline(cin, name);

	cout << "Рост: ";
	cin >> growth;

	cout << "Вес: ";
	cin >> weight;

	cout << "Лет: ";
	cin >> age;

	cin.ignore();
	cout << "Университет: ";
	getline(cin, university);

	cout << "Сколько проучился: ";
	cin >> numberOfYearsStudy;
}


void UpdateStudent(shared_ptr<CUniversityProcess>univerProcess)
{
	GetListStudents(univerProcess);
	cout << "Выберите из списка студента по его порядковому номеру, которого хотите обновить: ";

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
		cout << "Не удалось обновить студента" << endl;
	}
}

void DeleteStudent(shared_ptr<CUniversityProcess>univerProcess)
{
	GetListStudents(univerProcess);
	cout << "Выберите из списка студента по его порядковому номеру, которого хотите удалить: ";

	int number;
	cin >> number;

	if (!univerProcess->DeleteStudent(number))
	{
		cout << "Не удалось удалить студента" << endl;
	}
}

void AddStudent(shared_ptr<CUniversityProcess>univerProcess)
{
	cout << "Введите данные нового студента: " << endl;
	
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
	cout << "Пол: " << endl;
	getline(cin, gender);

	if (!univerProcess->AddNewStudent(name, gender, growth, weight, age, university, numberOfYearsStudy))
	{
		cout << "Не удалось добавить студента" << endl;
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
			cout << endl <<  "Выберите действие:" << endl;
			cout << "1. Вывести список университетов" << endl;
			cout << "2. Переименовать университет" << endl;
			cout << "3. Удалить университет" << endl;
			cout << "4. Вывести список студентов университета" << endl;
			cout << "5. Добавить университет" << endl;
			cout << "6. Вывести список студентов" << endl;
			cout << "7. Обновить данные о студенте" << endl;
			cout << "8. Удалить студента" << endl;
			cout << "9. Добавить студента" << endl;
			cout << "Q. Выход" << endl;

			cout << "Команда: ";
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
			cout << "Сохранить изменения? (y(да)/n(нет): ";
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

