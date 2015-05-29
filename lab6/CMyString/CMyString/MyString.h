#pragma once
#include <memory>
#include <string>

struct deleter
{
	void operator()(char* p) const
	{
		if (p)
			free(p);
	}
};

class CMyString
{
public:
	CMyString() throw();
	~CMyString() throw();

	CMyString(const char * pString);

	CMyString(const char * pString, unsigned length);

	CMyString(CMyString const& other);

	CMyString(CMyString && other);

	CMyString(std::string const& stlString);

	unsigned GetLength()const;
	const char* GetStringData()const;

	CMyString const SubString(unsigned start, unsigned length = UINT_MAX)const;

	void Clear();

	CMyString& operator =(const CMyString &other);
	
	CMyString operator +(const CMyString &other) const;
	CMyString operator +(const std::string &other) const;
	CMyString operator +(const char *other) const;

	CMyString& operator +=(const CMyString &other);

	bool operator ==(const CMyString &other) const;
	bool operator !=(const CMyString &other) const;

	char& operator [](const int index)const;

private:
	CMyString StringConcatenation(const char *str) const;

	std::unique_ptr<char, deleter> m_chars;
	size_t m_size;
};

