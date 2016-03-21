#pragma once

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
	CMenu(MenuItems && items);

	void InteractWithUser(std::istream & input, std::ostream & output);

private:
	std::vector<MenuItem> m_items;
};
