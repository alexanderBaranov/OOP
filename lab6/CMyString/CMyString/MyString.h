#pragma once
#include <memory>
#include <string>

class CMyString
{
public:
	CMyString() throw();

	CMyString(const char * pString);

	CMyString(const char * pString, unsigned length);

	CMyString(CMyString const& other);

	CMyString(CMyString && other);

	CMyString(std::string const& stlString);

	bool Empty()const;

	size_t GetLength()const;
	const char* GetStringData()const;

	CMyString const SubString(unsigned start, unsigned length = UINT_MAX)const;

	void Clear();

	CMyString& operator =(const CMyString &other);

	CMyString& operator +=(const CMyString &other);

	char& operator [](size_t index);
	const char& operator [](size_t index)const;

private:

	std::unique_ptr<char[]> m_chars;
	size_t m_size;
};

bool operator ==(const CMyString &leftString, const CMyString &rightString);
bool operator !=(const CMyString &leftString, const CMyString &rightString);

CMyString operator +(const CMyString &leftString, const CMyString &rightString);
