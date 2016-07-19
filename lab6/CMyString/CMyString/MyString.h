#pragma once
#include <memory>
#include <string>

class CMyString
{
private:
	CMyString(std::unique_ptr<char[]> &&pString, size_t length);

public:
	CMyString();

	CMyString(const char * pString);

	CMyString(const char * pString, size_t length);

	CMyString(CMyString const& other);

	CMyString(CMyString && other);

	CMyString(std::string const& stlString);

	bool Empty()const;

	size_t GetLength()const;
	const char* GetStringData()const;

	CMyString SubString(size_t start, size_t length = SIZE_MAX)const;

	void Clear();

	CMyString& operator =(const CMyString &other);
	CMyString& operator =(CMyString &&other);

	CMyString& operator +=(const CMyString &other);

	char& operator [](size_t index);
	const char& operator [](size_t index)const;

	friend CMyString operator +(const CMyString &leftString, const CMyString &rightString);
private:
	char* GetStringDataImpl()const;

	std::unique_ptr<char[]> m_chars;
	size_t m_size;
};

bool operator ==(const CMyString &leftString, const CMyString &rightString);
bool operator !=(const CMyString &leftString, const CMyString &rightString);

CMyString operator +(const CMyString &leftString, const CMyString &rightString);
