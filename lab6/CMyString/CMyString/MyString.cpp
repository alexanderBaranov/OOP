#include "stdafx.h"
#include "MyString.h"
#include <assert.h>

using namespace std;

CMyString::CMyString()
{
	SetEmptyString();
}

CMyString::CMyString(const char * pString)
{
	assert(pString);

	size_t size = strlen(pString);
	m_chars.reset(new char[size + 1]);
	memcpy(m_chars.get(), pString, size + 1);

	m_size = size;
}

CMyString::CMyString(const char * pString, size_t length)
{
	assert(pString);

	m_chars.reset(new char[length + 1]);
	memcpy(m_chars.get(), pString, length);
	m_chars.get()[length] = '\0';

	m_size = length;
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
{
	size_t size = stlString.length();

	m_chars.reset(new char[size + 1]);
	memcpy(m_chars.get(), stlString.c_str(), size + 1);

	m_size = size;
}

void CMyString::SetEmptyString()
{
	m_chars.reset(new char[1]);
	m_chars.get()[0] = '\0';
	m_size = 0;
}

bool CMyString::Empty() const
{
	return !m_size;
}

size_t CMyString::GetLength() const
{
	return m_size;
}

const char* CMyString::GetStringData() const
{
	return m_size ? m_chars.get() : "";
}

CMyString CMyString::SubString(size_t start, size_t length /*= UINT_MAX*/) const
{
	if (start >= m_size)
	{
		return CMyString();
	}

	if (start + length > m_size)
	{
		return CMyString(m_chars.get() + start, m_size - start);
	}
	
	return CMyString(m_chars.get() + start, length);
}

void CMyString::Clear()
{
	if (m_size)
	{
		SetEmptyString();
	}
}

char& CMyString::operator[](size_t index)
{
	if (index > m_size)
	{
		throw out_of_range("string subscript out of range");
	}

	return m_chars.get()[index];
}

const char& CMyString::operator[](size_t index) const
{
	if (index > m_size)
	{
		throw out_of_range("string subscript out of range");
	}

	return m_chars.get()[index];
}

CMyString& CMyString::operator+=(const CMyString &other)
{
	if (!other.GetLength())
	{
		return *this;
	}

	*this = *this + other;

	return *this;
}

CMyString& CMyString::operator=(const CMyString &other)
{
	if (this == &other)
	{
		return *this;
	}

	size_t length = other.GetLength();

	m_chars.reset(new char[length + 1]);
	memcpy(m_chars.get(), other.GetStringData(), length + 1);
	m_size = length;

	return *this;
}

CMyString& CMyString::operator=(CMyString &&other)
{
	if (this == &other)
	{
		return *this;
	}

	m_chars = move(other.m_chars);
	m_size = other.m_size;
	other.m_size = 0;

	return *this;
}


bool CompareStrings(const CMyString &leftString, const CMyString &rightString)
{
	size_t sizeOfLeftString = leftString.GetLength();
	size_t sizeOfRightString = rightString.GetLength();

	return (sizeOfLeftString == sizeOfRightString) ?
		memcmp(leftString.GetStringData(), rightString.GetStringData(), sizeOfRightString) == 0 :
		false;
}

bool operator ==(const CMyString &leftString, const CMyString &rightString)
{
	return CompareStrings(leftString, rightString);
}

bool operator !=(const CMyString &leftString, const CMyString &rightString)
{
	return !CompareStrings(leftString, rightString);
}

CMyString operator +(const CMyString &leftString, const CMyString &rightString)
{
	if (leftString.Empty() && rightString.Empty())
	{
		return "";
	}

	size_t sizeOfLeftString = leftString.GetLength();
	size_t sizeOfRightString = rightString.GetLength();

	size_t length = sizeOfLeftString + sizeOfRightString;

	CMyString str(leftString.GetStringData(), length);
	memcpy((char*)str.GetStringData(), leftString.GetStringData(), sizeOfLeftString);
	memcpy((char*)str.GetStringData() + sizeOfLeftString, rightString.GetStringData(), sizeOfRightString);

	return str;
}
