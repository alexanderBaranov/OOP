#pragma once
#include "Subscriber.h"
#include <memory>

typedef std::vector<std::shared_ptr<CSubscriber>> subscribers;

class CAddressBook
{
public:
	CAddressBook();
	~CAddressBook();
	
	subscribers FindByAllParams(
		const std::string name,
		const std::string address,
		const std::string telephone,
		const std::string email);

	subscribers FindByName(const std::string name);
	subscribers FindByAddress(const std::string address);
	subscribers FindByTelephone(const std::string telephone);
	subscribers FindByEmail(const std::string email);

	void DeleteSubscriber(const int index);
	void UpdateSubscriber(const int index,
						const std::string name,
						const std::string surname,
						const std::string patronymic,
						const std::string email,
						const std::string telephonNamber,
						const std::string street,
						const std::string house,
						const std::string apartment,
						const std::string city);
	
	subscribers GetSubscribers();

private:
	void LoadSubscribers();
	void SaveSubscribers();
	void ModifySubscriber(std::shared_ptr<CSubscriber>& subscriber,
						const int index,
						const std::string name,
						const std::string surname,
						const std::string patronymic,
						const std::string email,
						const std::string telephonNamber,
						const std::string street,
						const std::string house,
						const std::string apartment,
						const std::string city);

	void NewSubscriber(const int index,
		const std::string name,
		const std::string surname,
		const std::string patronymic,
		const std::string email,
		const std::string telephonNamber,
		const std::string street,
		const std::string house,
		const std::string apartment,
		const std::string city);

	std::string ReadInputFile(const std::string fileName);
	void ParseBaseData(std::string line, std::vector<std::string> &outValues);
	//void ParseString(std::string line, vector<std::string> &outValues);
	//std::shared_ptr<CSubscriber> CAddressBook::ParseInputData(std::string line);

	subscribers m_subscribers;
	bool m_updateBD;
};

