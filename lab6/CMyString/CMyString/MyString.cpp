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

	m_size = strlen(pString);
	m_chars.reset(new char[m_size + 1]);
	memcpy(m_chars.get(), pString, m_size + 1);
}

CMyString::CMyString(const char * pString, unsigned length)
{
	assert(pString);

	m_size = length;

	m_chars.reset(new char[m_size + 1]);
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
	m_chars.reset(new char[m_size + 1]);
	memcpy(m_chars.get(), stlString.c_str(), m_size + 1);
}

void CMyString::SetEmptyString()
{
	m_size = 0;
	m_chars.reset(new char[1]);
	m_chars.get()[0] = '\0';
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

CMyString const CMyString::SubString(size_t start, size_t length /*= UINT_MAX*/) const
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
	if ((index > m_size) || (index < 0))
	{
		throw exception("string subscript out of range");
	}

	return m_chars.get()[index];
}

const char& CMyString::operator[](size_t index) const
{
	if ((index > m_size) || (index < 0))
	{
		throw exception("string subscript out of range");
	}

	return m_chars.get()[index];
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

CMyString& CMyString::operator=(const CMyString &other)
{
	if (this == &other)
	{
		return *this;
	}

	m_size = other.GetLength();
	m_chars.reset(new char [m_size + 1]);
	memcpy(m_chars.get(), other.GetStringData(), m_size + 1);

	return *this;
}

int CompairStrings(const CMyString &leftString, const CMyString &rightString)
{
	size_t sizeOfLeftString = leftString.GetLength();
	size_t sizeOfRightString = rightString.GetLength();

	size_t cmpSize = (sizeOfLeftString > sizeOfRightString) ? sizeOfLeftString : sizeOfRightString;
	return memcmp(leftString.GetStringData(), rightString.GetStringData(), cmpSize);
}

bool operator ==(const CMyString &leftString, const CMyString &rightString)
{
	return CompairStrings(leftString, rightString) == 0;
}

bool operator !=(const CMyString &leftString, const CMyString &rightString)
{
	return CompairStrings(leftString, rightString) != 0;
}

CMyString operator +(const CMyString &leftString, const CMyString &rightString)
{
	if (leftString.Empty() && rightString.Empty() )
	{
		return "";
	}

	size_t sizeOfLeftString = leftString.GetLength();
	size_t sizeOfRightString = rightString.GetLength();

	size_t length = leftString.GetLength() + rightString.GetLength() + 1;
	std::unique_ptr<char[]> chars(new char[length]);

	memcpy(chars.get(), leftString.GetStringData(), sizeOfLeftString);
	memcpy(chars.get() + sizeOfLeftString, rightString.GetStringData(), sizeOfRightString);
	
	chars.get()[length - 1] = '\0';

	return CMyString(chars.get(), length-1);
}
