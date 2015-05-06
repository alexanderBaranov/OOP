#pragma once
#include <string>

class CUniversity
{
public:
	CUniversity(std::string name);
	~CUniversity();

	const std::string GetName() const;
	void SetName(const std::string name);

private:
	std::string m_name;
};

