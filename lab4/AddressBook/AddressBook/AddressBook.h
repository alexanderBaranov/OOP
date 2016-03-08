#pragma once
#include "Subscriber.h"
#include <memory>

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
						const std::string& telephonNamber,
						const std::string& street,
						const std::string& house,
						const std::string& apartment,
						const std::string& city);

	std::string NewSubscriber(
		const std::string& name,
		const std::string& surname,
		const std::string& patronymic,
		const std::string& email,
		const std::string& telephonNamber,
		const std::string& street,
		const std::string& house,
		const std::string& apartment,
		const std::string& city);
	
	subscribers GetSubscribers();

	void SaveSubscribers();

	bool Updated();

private:
	bool ModifySubscriber(std::shared_ptr<CSubscriber>& subscriber,
						const std::string& name,
						const std::string& surname,
						const std::string& patronymic,
						const std::string& email,
						const std::string& telephonNamber,
						const std::string& street,
						const std::string& house,
						const std::string& apartment,
						const std::string& city);

	std::string ReadInputFile(const std::string& fileName);
	void ParseBaseData(std::string line, std::vector<std::string> &outValues);

	subscribers m_subscribers;
	bool m_updateBD;
	std::string m_dataBase;
};

