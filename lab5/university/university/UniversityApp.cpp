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
	cout << endl << "Выберите действие:" << endl;

	const MenuItem items[] = {
		{ "1", "Вывести список университетов", BindMethodToAction(&CUniversityApp::GetListUnivesities) },
		{ "2", "Переименовать университет", BindMethodToAction(&CUniversityApp::RenameUniversity) },
		{ "3", "Удалить университет", BindMethodToAction(&CUniversityApp::DeleteUniversity) },
		{ "4", "Вывести список студентов университета", BindMethodToAction(&CUniversityApp::GetStudentsFromUniversity) },
		{ "5", "Добавить университет", BindMethodToAction(&CUniversityApp::AddUniversity) },
		{ "6", "Вывести список студентов", BindMethodToAction(&CUniversityApp::GetListStudents) },
		{ "7", "Обновить данные о студенте", BindMethodToAction(&CUniversityApp::UpdateStudent) },
		{ "8", "Удалить студента", BindMethodToAction(&CUniversityApp::DeleteStudent) },
		{ "9", "Добавить студента", BindMethodToAction(&CUniversityApp::AddStudent) },
		{ "Q", "Выход", BindMethodToAction(&CUniversityApp::Quit) }
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
	output << "Список университетов:" << endl;
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
		output << "Список университетов пуст." << endl;
	}

	return true;
}

bool CUniversityApp::RenameUniversity(istream & input, ostream & output)
{
	output << "Введите название заменяемого университета: ";

	string oldName;
	getline(input, oldName);

	output << "Введите новое имя университета: ";

	string newName;
	getline(input, newName);

	if (!m_universityManagement->RenameUniversity(oldName, newName))
	{
		output << "Не удалось изменить название университета" << endl;
	}

	return true;
}

bool CUniversityApp::DeleteUniversity(istream & input, ostream & output)
{
	output << "Введите название удаляемого университета: ";

	string name;
	getline(input, name);

	if (!m_universityManagement->DeleteUniversity(name))
	{
		output << "Не удалось удалить \"" << name << "\" университет" << endl;
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
	output << "Введите название университета: ";

	string name;
	getline(input, name);

	Students students = m_universityManagement->GetStudentsFromUniversity(name);

	if (students.size())
	{
		output << "Список cтудентов, обучающихся в \"" << name << "\":" << endl;

		PrintStudents(output, students);
	}
	else
	{
		output << "Cтудентов в этом университете нет" << endl;
	}

	return true;
}

bool CUniversityApp::AddUniversity(istream & input, ostream & output)
{
	output << "Введите название добавляемого университета: ";

	string name;
	getline(input, name);

	if (!m_universityManagement->AddNewUniversity(name))
	{
		output << "Не удалось добавить университет с таким названием." << endl;
	}

	return true;
}

bool CUniversityApp::GetListStudents(istream & input, ostream & output)
{
	output << "Список студентов:" << endl;
	Students students = m_universityManagement->GetStudents();
	if (!students.empty())
	{
		PrintStudents(output, students);
	}
	else
	{
		output << "Список университетов пуст." << endl;
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

	output << "Имя: ";
	getline(input, name);

	output << "Рост: ";
	input >> growth;

	output << "Вес: ";
	input >> weight;

	output << "Лет: ";
	input >> age;

	input.ignore();

	output << "Университет: ";
	getline(input, university);

	output << "Сколько проучился: ";
	input >> numberOfYearsStudy;
}


bool CUniversityApp::UpdateStudent(istream & input, ostream & output)
{
	GetListStudents(input, output);
	output << "Выберите из списка студента по его порядковому номеру, которого хотите обновить: ";

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
		output << "Не удалось обновить студента. " << error << endl;
	}

	return true;
}

bool CUniversityApp::DeleteStudent(istream & input, ostream & output)
{
	GetListStudents(input, output);
	output << "Выберите из списка студента по его порядковому номеру, которого хотите удалить: ";

	int number;
	input >> number;

	if (!m_universityManagement->DeleteStudent(number))
	{
		output << "Не удалось удалить студента" << endl;
	}

	return true;
}

bool CUniversityApp::AddStudent(istream & input, ostream & output)
{
	output << "Введите данные нового студента: " << endl;

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
	output << "Пол: " << endl;
	getline(input, gender);

	if (!m_universityManagement->AddNewStudent(name, GetEnumGenderFromString(gender), growth, weight, age, university, numberOfYearsStudy))
	{
		output << "Не удалось добавить студента" << endl;
	}

	return true;
}

bool CUniversityApp::Quit(istream& input, ostream& output)
{
	if (m_universityManagement->Updated())
	{
		output << "Сохранить изменения? (y(да)/n(нет): ";
		string command;
		input >> command;

		if (command == "y")
		{
			m_universityManagement->SaveChanges();
		}
	}
	return false;
}
