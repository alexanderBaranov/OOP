#pragma once
#include "UniversityProcess.h"
#include <functional>
#include <iostream>
#include <sstream>
#include <boost/range/algorithm/find_if.hpp>
#include <vector>

struct MenuItem
{
	typedef std::function<bool(std::istream & input, std::ostream & output)> Action;

	std::string command;
	std::string description;
	Action action;
};

class CMenu
{
public:
	template <typename MenuItems>
	CMenu(MenuItems && items)
		:m_items(std::begin(items), std::end(items))
	{
		for (auto& item : m_items)
		{
			cout << item.command << ". " << item.description << endl;
		}
	}


	void InteractWithUser(std::istream & input, std::ostream & output)
	{
		std::string line;
		std::string command;
		while (getline(input, line))
		{
			std::istringstream cmdStream(line);
			if (cmdStream >> command)
			{
				auto it = boost::range::find_if(m_items, [&](const MenuItem& item){
					return item.command == command;
				});

				if (it != m_items.end())
				{
					if (!it->action(input, output))
					{
						break;
					}
				}
				else
				{
					output << "Command " << command << " is not recognized" << std::endl;
				}
			}
		}
	}

private:
	std::vector<MenuItem> m_items;
};

class CUniversityApp
{
public:
	CUniversityApp(std::unique_ptr<CUniversityManagement>&& univerManagment);

	void Run();

private:
	typedef bool (CUniversityApp::*HandlerMethod)(std::istream & input, std::ostream & output);

	MenuItem::Action BindMethodToAction(HandlerMethod method);

	bool GetListUnivesities(std::istream & input, std::ostream & output);
	bool RenameUniversity(std::istream & input, std::ostream & output);
	bool DeleteUniversity(std::istream & input, std::ostream & output);
	void PrintStudents(std::ostream & output, const Students& students);
	bool GetStudentsFromUniversity(std::istream & input, std::ostream & output);
	bool AddUniversity(std::istream & input, std::ostream & output);
	bool GetListStudents(std::istream & input, std::ostream & output);
	static void StudentData(std::istream & input,
		std::ostream & output,
		std::string& name,
		double& growth,
		double& weight,
		int& age,
		std::string& university,
		int& numberOfYearsStudy);

	bool UpdateStudent(std::istream & input, std::ostream & output);
	bool DeleteStudent(std::istream & input, std::ostream & output);
	bool AddStudent(std::istream & input, std::ostream & output);
	bool Quit(std::istream& input, std::ostream& output);


	std::unique_ptr<CUniversityManagement> m_universityManagement;
};

