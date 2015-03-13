#pragma once
#include "Subscriber.h"
#include <memory>

typedef std::vector<std::shared_ptr<CSubscriber>> subscribers;

class CAddressBook
{
public:
	CAddressBook();
	~CAddressBook();
	
	subscribers Find(
		const std::string name,
		const std::string address = "",
		const std::string telephone = "",
		const std::string email = "");

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
						const std::string city,
						const std::string republic,
						const std::string country);
	
	subscribers GetSubscribers();

private:
	void LoadSubscribers();
	void SaveSubscribers();
	void ModifySubscriber(shared_ptr<CSubscriber>& subscriber,
						const int index,
						const std::string name,
						const std::string surname,
						const std::string patronymic,
						const std::string email,
						const std::string telephonNamber,
						const std::string street,
						const std::string house,
						const std::string apartment,
						const std::string city,
						const std::string republic,
						const std::string country);

	void NewSubscriber(const int index,
		const std::string name,
		const std::string surname,
		const std::string patronymic,
		const std::string email,
		const std::string telephonNamber,
		const std::string street,
		const std::string house,
		const std::string apartment,
		const std::string city,
		const std::string republic,
		const std::string country);

	std::string ReadInputFile(const std::string fileName);
	void ParseBaseData(std::string line, std::vector<std::string> &outValues);

	subscribers m_subscribers;
	bool m_updateBD;
};

