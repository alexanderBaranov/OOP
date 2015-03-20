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
	cout << "������ �����: ������ ���� ��������" << endl;
	cout << "������� ���: ";

	string name;
	cin >> name;

	PrintSubscribers(addressBook->FindByName(name));
}

void FindSubscriber(shared_ptr<CAddressBook>&addressBook)
{
	string command;
	while (command != "Q")
	{
		cout << "�������� ��������:" << endl;
		cout << "1. ����� �� ���" << endl;
		cout << "2. ����� �� ������" << endl;
		cout << "3. ����� �� �����" << endl;
		cout << "3. ����� �� ����������� ������" << endl;
		cout << "4. ����� �� ���� �����" << endl;
		cout << "Q. ����� �� ������� ����" << endl;

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
			cout << "�������� ��������:" << endl;
			cout << "1. ����� ���������" << endl;
			cout << "2. �������� ��������" << endl;
			cout << "3. ���������������/������� ��������" << endl;
			cout << "Q. �����" << endl;

			cin >> command;

			if (command == "1")
			{
				FindSubscriber(addressBook);
			}
		}

		//subscribers subscribes(addressBook->FindByAddress("������, ������-���"));
	}
	catch (const exception &error)
	{
		cout << error.what() << endl;
	}
	return 0;
}
