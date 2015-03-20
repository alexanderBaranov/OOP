#include "stdafx.h"
#include "AddressBook.h"
#include <iostream>
#include <locale>

using namespace std;

void PrintSubscribers(subscribers values)
{
	for each (const auto & subscriber in values)
	{
		cout << subscriber->GetIndex() << " "
			<< subscriber->GetName() << " "
			<< subscriber->GetSurname() << " "
			<< subscriber->GetPatronymic() << " "
			<< subscriber->GetEmail() << " "
			<< subscriber->GetTelephoneNumber() << " "
			<< subscriber->GetStreet() << " "
			<< subscriber->GetHouse() << " "
			<< subscriber->GetApartment() << " "
			<< subscriber->GetCity() << endl;
	}
}

void FindByName(shared_ptr<CAddressBook>&addressBook)
{
	cout << "Пример ввода: Иванов Иван Иванович" << endl;
	cout << "Введите ФИО: ";

	string name;
	cin >> name;

	PrintSubscribers(addressBook->FindByName(name));
}

void FindSubscriber(shared_ptr<CAddressBook>&addressBook)
{
	string command;
	while (command != "Q")
	{
		cout << "Выберите действие:" << endl;
		cout << "1. Поиск по ФИО" << endl;
		cout << "2. Поиск по адресу" << endl;
		cout << "3. Поиск по почте" << endl;
		cout << "3. Поиск по телефонному номеру" << endl;
		cout << "4. Поиск по всем полям" << endl;
		cout << "Q. Выйти на главное меню" << endl;

		cin >> command;

		if (command == "1")
		{
			FindByName(addressBook);
		}
/////TO DO
		if (command == "2")
		{
			FindByName(addressBook);
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	locale::global(locale("rus"));
	try
	{
		auto addressBook = make_unique<CAddressBook>();
		string command;
		while (command != "Q")
		{
			cout << "Выберите действие:" << endl;
			cout << "1. Поиск абонентов" << endl;
			cout << "2. Добавить абонента" << endl;
			cout << "3. Отредактировать/удалить абонента" << endl;
			cout << "Q. Выйти" << endl;

			cin >> command;

			if (command == "1")
			{
				FindSubscriber(addressBook);
			}
		}

		//subscribers subscribes(addressBook->FindByAddress("Россия, Йошкар-Ола"));
	}
	catch (const exception &error)
	{
		cout << error.what() << endl;
	}
	return 0;
}
