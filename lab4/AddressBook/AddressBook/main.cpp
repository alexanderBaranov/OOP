#include "stdafx.h"
#include "AddressBook.h"
#include <iostream>
#include <locale>
#include <windows.h>

using namespace std;

static const string DATA_BASE = "BaseData.txt";

void PrintSubscribers(const subscribers values)
{
	if (values.empty())
	{
		cout << "Абонентов нет." << endl;
		return;
	}

	cout << endl << "Результат: " << endl;
	for (size_t i = 0; i < values.size(); i++)
	{
		const auto & subscriber = values[i];
		cout << i << " "
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

void FindByName(const shared_ptr<CAddressBook>addressBook)
{
	cout << "Пример ввода: Иванов Иван Иванович" << endl;
	cout << "Введите ФИО: ";

	string name;

	cin.ignore();
	getline(cin, name);

	PrintSubscribers(addressBook->FindByName(name));
}

void FindByAddress(const shared_ptr<CAddressBook>addressBook)
{
	cout << "Пример ввода: Москва, Шаболовка, 37, 54" << endl;
	cout << "Введите адрес: ";

	string address;
	
	cin.ignore();
	getline(cin, address);

	PrintSubscribers(addressBook->FindByAddress(address));
}

void FindByEmail(const shared_ptr<CAddressBook>addressBook)
{
	cout << "Пример ввода: ivanov@mail.ru" << endl;
	cout << "Введите email: ";

	string email;

	cin.ignore();
	getline(cin, email);

	PrintSubscribers(addressBook->FindByEmail(email));
}

void FindByTelephoneNumber(const shared_ptr<CAddressBook>addressBook)
{
	cout << "Пример ввода: 89021111111, либо 737777" << endl;
	cout << "Введите номер телефона: ";

	string number;

	cin.ignore();
	getline(cin, number);

	PrintSubscribers(addressBook->FindByTelephone(number));
}

void FindByAllParams(const shared_ptr<CAddressBook>addressBook)
{
	cout << "Введите имя (пример: Иванов Иван Иванович): ";
	string name;
	cin.ignore();
	getline(cin, name);

	cout << "Введите адрес (пример: Москва, Шаболовка, 37, 54): ";
	string address;
	getline(cin, address);

	cout << "Введите номер телефона(пример: 89021111111, либо 737777): ";
	string number;
	getline(cin, number);

	cout << "Введите email(пример: ivanov@mail.ru): ";
	string email;
	getline(cin, email);

	PrintSubscribers(addressBook->FindByAllParams(name, address, number, email));
}

void Find(const shared_ptr<CAddressBook>addressBook, const string command)
{
	if (command == "1")
	{
		FindByName(addressBook);
	}

	if (command == "2")
	{
		FindByAddress(addressBook);
	}

	if (command == "3")
	{
		FindByEmail(addressBook);
	}

	if (command == "4")
	{
		FindByTelephoneNumber(addressBook);
	}

	if (command == "5")
	{
		FindByAllParams(addressBook);
	}
}

void FinderInstruction()
{
	cout << endl;
	cout << "Выберите действие:" << endl;
	cout << "1. Поиск по ФИО" << endl;
	cout << "2. Поиск по адресу" << endl;
	cout << "3. Поиск по почте" << endl;
	cout << "4. Поиск по телефонному номеру" << endl;
	cout << "5. Поиск по всем полям" << endl;
	cout << "Q. Выйти в главное меню" << endl << endl;
}

void FindSubscriber(const shared_ptr<CAddressBook>addressBook)
{
	string command;
	while (command != "Q")
	{
		FinderInstruction();

		cout << "Команда: ";
		cin >> command;
		cout << endl;

		Find(addressBook, command);
	}
}

void NewDataOfSubscriber(
	string &name,
	string &surname,
	string &patronymic,
	string &email,
	string &telephonNamber,
	string &street,
	string &house,
	string &apartment,
	string &city)
{
	cout << "Имя: ";
	cin.ignore();
	getline(cin, name);

	cout << "Фамилие: ";
	getline(cin, surname);

	cout << "Отчество:";
	getline(cin, patronymic);

	cout << "Email:";
	getline(cin, email);

	cout << "Телефонный номер:";
	getline(cin, telephonNamber);

	cout << "Улица:";
	getline(cin, street);

	cout << "Номер дома:";
	getline(cin, house);

	cout << "Номер квартиры:";
	getline(cin, apartment);

	cout << "Город:";
	getline(cin, city);

	cout << endl;
}

string AddSubscriber(const shared_ptr<CAddressBook>addressBook)
{
	cout << "Введите данные нового абонента:" << endl;
	
	string name;
	string surname;
	string patronymic;
	string email;
	string telephonNamber;
	string street;
	string house;
	string apartment;
	string city;

	NewDataOfSubscriber(
		name,
		surname,
		patronymic,
		email,
		telephonNamber,
		street,
		house,
		apartment,
		city);

	return addressBook->NewSubscriber(name, surname, patronymic, email, telephonNamber, street, house, apartment, city);
}



void EditSubScriber(const shared_ptr<CAddressBook>addressBook, int index)
{
	cout << "Введите новые данные для пользователя:" << endl;
	string name;
	string surname;
	string patronymic;
	string email;
	string telephonNamber;
	string street;
	string house;
	string apartment;
	string city;

	NewDataOfSubscriber(
		name,
		surname,
		patronymic,
		email,
		telephonNamber,
		street,
		house,
		apartment,
		city);

	addressBook->UpdateSubscriber(
		index,
		name,
		surname,
		patronymic,
		email,
		telephonNamber,
		street,
		house,
		apartment,
		city);
}

void DeleteSubscriber(const shared_ptr<CAddressBook>addressBook, const int index)
{
	addressBook->DeleteSubscriber(index);
}

void UpdateSubscriber(const shared_ptr<CAddressBook>addressBook)
{
	string command;
	while (command != "Q")
	{
		cout << "Выберите действие:" << endl;
		cout << "1. Редактировать" << endl;
		cout << "2. Удалить" << endl;
		cout << "Q. Выход в главное меню" << endl;

		cin >> command;
		if (command == "Q")
		{
			break;
		}

		cout << "Найдите абонента для дальнейшей работы с ним." << endl;
		FinderInstruction();

		string commandFind;
		cin >> commandFind;

		Find(addressBook, commandFind);

		cout << "Выберите абонента по порядковому номеру, либо \"Q\" для выхода. ваш выбор: ";

		string number;
		cin >> number;

		if (number == "Q")
		{
			break;
		}

		if (command == "1")
		{
			EditSubScriber(addressBook, stoi(number));
		}

		if (command == "2")
		{
			DeleteSubscriber(addressBook, stoi(number));
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
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
		auto addressBook = make_shared<CAddressBook>(DATA_BASE);
		
		string command;
		while (command != "Q")
		{
			cout << "Выберите действие:" << endl;
			cout << "1. Поиск абонентов" << endl;
			cout << "2. Добавить абонента" << endl;
			cout << "3. Отредактировать/удалить абонента" << endl;
			cout << "Q. Выйти" << endl << endl;

			cout << "Команда: ";
			cin >> command;
			cout << endl;

			if (command == "1")
			{
				FindSubscriber(addressBook);
			}

			if (command == "2")
			{
				string error = AddSubscriber(addressBook);

				if (!error.empty())
					cout << error << endl;
			}

			if (command == "3")
			{
				UpdateSubscriber(addressBook);
			}
		}

		if (addressBook->Updated())
		{
			cout << "Сохранить изменения в базу данных ? (y(да)/n(нет): ";
			string command;
			cin >> command;

			if (command == "y")
			{
				addressBook->SaveSubscribers();
			}
		}
	}
	catch (const exception &error)
	{
		cout << error.what() << endl;
	}
	return 0;
}
