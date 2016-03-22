#include "stdafx.h"
#include "Menu.h"
#include <boost/range/algorithm/find_if.hpp>

using namespace std;
using namespace boost::range;

template <typename MenuItems>
CMenu::CMenu(MenuItems && items)
	:m_items(begin(items), end(items))
{
	for (auto& item : m_items)
	{
		cout << item.command << ". " << item.description << endl;
	}
}

void CMenu::InteractWithUser(istream & input, ostream & output)
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
				if (!it->action(input, output))
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