#pragma once
#include "Subscriber.h"
#include <memory>
#include <functional>

typedef std::vector<std::shared_ptr<CSubscriber>> subscribers;

class CAddressBook
{
public:
	CAddressBook(const std::string& dataBaseFile);
	CAddressBook();
	
	void LoadSubscribersFromDataBaseFile(const std::string &dataBaseFile);

	subscribers FindByAllParams(
		const std::string& name,
		const std::string& address,
		const std::string& telephone,
		const std::string& email) const;

	subscribers FindByName(const std::string& name) const;
	subscribers FindByAddress(const std::string& address) const;
	subscribers FindByTelephone(const std::string& telephone) const;
	subscribers FindByEmail(const std::string& email) const;

	void DeleteSubscriber(const int index);
	void UpdateSubscriber(const int index,
						const std::string& name,
						const std::string& surname,
						const std::string& patronymic,
						const std::string& email,
						const std::string& phoneNumber,
						const std::string& street,
						const std::string& house,
						const std::string& apartment,
						const std::string& city);

	bool AddNewSubscriber(
		const std::string& name,
		const std::string& surname,
		const std::string& patronymic,
		const std::string& email,
		const std::string& phoneNumber,
		const std::string& street,
		const std::string& house,
		const std::string& apartment,
		const std::string& city, 
		std::string& error);
	
	subscribers GetSubscribers();

	void SaveSubscribers();

	bool Updated() const;

private:
	bool ModifySubscriber(const std::shared_ptr<CSubscriber>& subscriber,
						const std::string& name,
						const std::string& surname,
						const std::string& patronymic,
						const std::string& email,
						const std::string& phoneNumber,
						const std::string& street,
						const std::string& house,
						const std::string& apartment,
						const std::string& city);

	static std::vector<std::string> ParseDataBase(std::string line);
	
	static void CAddressBook::AppendProperty(
		std::string& str,
		const std::string& property,  
		const std::string& value);

	subscribers m_subscribers;
	bool m_updateBD;
	std::string m_dataBase;
};

