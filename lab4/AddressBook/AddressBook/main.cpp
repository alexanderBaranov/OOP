#include "stdafx.h"
#include "AddressBook.h"
#include <iostream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		auto addressBook = make_unique<CAddressBook>();
		subscribers subscribes(addressBook->FindByAddress("Россия, Йошкар-Ола"));
	}
	catch (const exception &error)
	{
		cout << error.what() << endl;
	}
	return 0;
}
