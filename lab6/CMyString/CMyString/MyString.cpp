#include "stdafx.h"
#include "MyString.h"

using namespace std;

CMyString::CMyString() throw()
{
	m_size = 0;
	m_chars.reset((char*)malloc(m_size + 1));
	*m_chars = '\0';
}

CMyString::CMyString(const char * pString)
:m_size(strlen(pString))
{
	m_chars.reset((char*)malloc(m_size + 1));
	memcpy(m_chars.get(), pString, m_size + 1);
}

CMyString::CMyString(const char * pString, unsigned length)
:m_size(length)
{
	size_t strLen = strlen(pString);
	if (length > strLen)
	{
		m_size = strLen;
	}

	m_chars.reset((char*)malloc(m_size + 1));
	memcpy(m_chars.get(), pString, m_size);
	m_chars.get()[m_size] = '\0';
}

CMyString::CMyString(CMyString const& other)
{
	*this = other;
}

CMyString::CMyString(CMyString && other)
{
	*this = move(other);
}

CMyString::CMyString(std::string const& stlString)
: m_size(stlString.length())
{
	m_chars.reset((char*)malloc(m_size + 1));
	memcpy(m_chars.get(), stlString.c_str(), m_size + 1);
}

unsigned CMyString::GetLength() const
{
	return m_size;
}

const char* CMyString::GetStringData() const
{
	return m_chars.get();
}

CMyString const CMyString::SubString(unsigned start, unsigned length /*= UINT_MAX*/) const
{
	if (start + length > m_size)
	{
		return nullptr;
	}
	
	return CMyString(m_chars.get() + start, length);
}

void CMyString::Clear()
{
	m_chars.reset(nullptr);
}

char& CMyString::operator[](const int index) const
{
	if ((size_t)index > m_size)
	{
		return m_chars.get()[0];
	}

	return m_chars.get()[index];
}

bool CMyString::operator==(const CMyString &other) const
{
	return strcmp(m_chars.get(), other.GetStringData()) == 0;
}

bool CMyString::operator!=(const CMyString &other) const
{
	return strcmp(m_chars.get(), other.GetStringData()) != 0;
}

CMyString& CMyString::operator+=(const CMyString &other)
{
	if (!other.GetLength())
	{
		return *this;
	}

	CMyString tmp = *this + other;
	*this = tmp;

	return *this;
}

CMyString CMyString::StringConcatenation(const char *str) const
{
	if (!str)
	{
		return nullptr;
	}

	size_t length = m_size + strlen(str) + 1;
	std::unique_ptr<char, deleter> chars;
	chars.reset((char*)malloc(length));

	strcpy_s(chars.get(), length, m_chars.get());
	strcat_s(chars.get(), length, str);

	return CMyString(chars.get());
}

CMyString CMyString::operator+(const char *other) const
{
	return StringConcatenation(other);
}

CMyString CMyString::operator+(const std::string &other) const
{
	return StringConcatenation(other.c_str());
}

CMyString CMyString::operator+(const CMyString &other) const
{
	return StringConcatenation(other.GetStringData());
}

CMyString& CMyString::operator=(const CMyString &other)
{
	if (this == &other)
	{
		return *this;
	}

	m_size = other.GetLength();
	m_chars.reset((char*)malloc(m_size + 1));
	memcpy(m_chars.get(), other.GetStringData(), m_size + 1);

	return *this;
}

CMyString::~CMyString() throw()
{
}
